#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include<arpa/inet.h>
#include <unistd.h>

#include "parse.h"
#include "socket.h"
#include "constants.h"

int main(int argc, char * argv[]){
    //It should take an argument that adopts the URL syntax
    //So argc has to be 2 

    if(argc != 2){ 
        printf(RED "ERROR - you need to provide an URL in order for this app to work\n");
        return 1;
    }

    if(strncmp("ftp://", argv[1], 6) !=0){ //it's not a ftp URL
        printf(RED "ERROR - you need to provide a ftp URL in order for this app to work\n");
        return 1;
    }

    //We don't need to parse the whole url, just the part after ftp://
    int size_url = strlen(argv[1])-5;
    char*url = (char*)malloc(size_url);
    memcpy(url,argv[1]+6,size_url);

    //Need to parse the URL to get the user, password, host and url-path
    
    char* user= (char*)malloc(PARAMETER_LENGTH); 
    char* password= (char*)malloc(PARAMETER_LENGTH);
    char*host= (char*)malloc(PARAMETER_LENGTH);
    char*path=(char*)malloc(PARAMETER_LENGTH);

    parse_url(url,size_url,user,password,host,path);

    printf(CYN "Username: %s\n",user);
    printf(CYN "Password: %s\n",password);
    printf(CYN "Host: %s\n",host);
    printf(CYN "Path %s\n",path);

    //Get server's IP-->code from getip.c
    struct hostent *h;
    if ((h = gethostbyname(host)) == NULL) {
        herror("gethostbyname()");
        return 1;
    }

    printf(CYN "Host name  : %s\n", h->h_name);
    printf(CYN "IP Address : %s\n", inet_ntoa(*((struct in_addr *) h->h_addr)));

    char* ip =  inet_ntoa(*((struct in_addr *) h->h_addr));
    int socketAfd=start_socket(ip,PORT);

    //Get code reply 220
    int code= getReply(socketAfd);
    //Check if it's the code we wanted
    if(code!=SERVICE_READY){
        printf(RED "ERROR - instead of code 220, sinalizing that the socket was ready, we got an error code\n");
        return 1;
    }


    //Do login with user + pass
    //Send the value of user
    if(write_commands(socketAfd,"user ",user)<0){ 
        printf(RED "ERROR - we weren't successful in requesting the username\n");
        return 1;
    }
    //Check if the code received was 331 or 230 (check RFC 959 page 50)
    code=getReply(socketAfd);
    if(code!=USER_OKAY && code != USER_LOGGED_IN){
       printf(RED "ERROR - instead of code 230 or 331, we got an error message when checking if the username was correct + login had been successful\n");
       return 1;
    }
    
    //Send the value of password
    if(write_commands(socketAfd,"pass ",password)<0){
       printf(RED "ERROR - we weren't successful in requesting the password\n");
       return 1;
    }

    //Check if the code received was 230
    code=getReply(socketAfd);
    if(code != USER_LOGGED_IN){
        printf(RED "ERROR - instead of code 230, we got an error message when checking if the login had been successful\n");
        return 1;
    }


    //Enter passive mode
    if(write_commands(socketAfd,"pasv","")){
        printf(RED "ERROR - we weren't successful in initializing the passive mode\n");
        return 1;
    }

    /*
    We need to check if the code reply is 227 + get the server's port where it
awaits the connection
    Example: 227 Entering Passive Mode (193,136,28,12,19,91)
             server's IP: (193.136.28.12)
             port= 19*256+91= 4955
    */
    int port;
    if((port=getPort(socketAfd))<0){
        printf(RED "ERROR - we weren't successful in getting the port where the server awaits connection\n");
        return 1;
    }

    //term_B socket
    int socketBfd=start_socket(ip,port);

    //Reply doesn't matter right now
    //Retrieve file (in the first socket <=> term_A)
    //Example: retr pub/kodi/timestamp.txt -->so basically it's retr + path
    if(write_commands(socketAfd,"retr ",path)<0){
       printf(RED "ERROR - we weren't successful in requesting a file\n");
       return 1;
    }

    //Check if reply code is 150.
    char* reply=(char*)malloc(BUFFER_LENGTH);
    code=getCode(socketAfd,reply);
    if(code != FILE_OKAY_DATA_SOON){
        printf(RED "ERROR - instead of code 150, we got an error message when checking if the file was okay and would provide data soon\n");
        return 1;
    }

    //B has to send the wanted file to A
    if(transfer(socketBfd,path)<0){
        printf(RED "ERROR - the file transfer between client and server wasn't successful\n");
        return 1;
    }
    

    //Check if reply code is 226
    code=getCode(socketAfd,reply);
    if(code != FILE_TRANSFER_SUCCESS){
        printf(RED "ERROR - instead of code 226, we got an error message when checking if the data transfer had gone correctly\n");
        return 1;
    }    

    close(socketAfd);
    close(socketBfd);
    free(reply);
    free(url);
    free(user);
    free(password);
    free(host);
    free(path);
    return 0;
}
