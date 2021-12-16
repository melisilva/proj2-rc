#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include<arpa/inet.h>

#include "parse.h"
#include "socket.h"
#include "constants.h"

int main(int argc, char * argv[]){
    //It should take an argument that adopts the URL syntax
    //So argc has to be 2 (at least, we can feel need to have more arguments I guess)

    if(argc != 2){ //we can change it to < in the future
        printf("ERROR");
    }

    if(strncmp("ftp://", argv[1], 6) !=0){ //it's not a ftp URL
        printf("ERROR");
    }

    //We don't need to parse the whole url, just the part after ftp://
    int size_url = strlen(argv[1])-5;
    char*url = (char*)malloc(size_url);
    memcpy(url,argv[1]+6,size_url);
    printf("%s\n",url);
    //Need to parse the URL to get the user, password, host and url-path
    
    char* user= (char*)malloc(512); //might need to make this a constant?
    char* password= (char*)malloc(512);
    char*host= (char*)malloc(512);
    char*path=(char*)malloc(512);

    parse_url(url,size_url,user,password,host,path);

    printf("%s\n",user);
    printf("%s\n",password);
    printf("%s\n",host);
    printf("%s\n",path);

    //Get server's IP-->code from getip.c
    struct hostent *h;
    if ((h = gethostbyname(host)) == NULL) {
        herror("gethostbyname()");
        return 1;
    }

    printf("Host name  : %s\n", h->h_name);
    printf("IP Address : %s\n", inet_ntoa(*((struct in_addr *) h->h_addr)));

    char* ip =  inet_ntoa(*((struct in_addr *) h->h_addr));
    //Start connection telnet ftp.up.pt 21
    int socketfd=start_socket(ip,PORT);

    //Get reply 220-Welcome to the University of Porto's mirror archive (mirrors.up.pt) 
    int code= getReply(socketfd);
    //Check if it's the code we wanted
    if(code!=SERVICE_READY){
        return 1;
    }

    //Do login with user + pass
    //Send the value of user
    if(write_commands(socketfd,"user",user)<0){ //does user have to be in all caps?
        return 1;
    }
    //Check if the code received was 331 or 230 (check RFC 959 page 50)
    code=getReply(socketfd);
    if(code!=USER_OKAY && code != USER_LOGGED_IN){
        return 1;
    }
    
    //Send the value of password
    if(write_commands(socketfd,"pass",password)<0){
        return 1;
    }

    //Check if the code received was 230
    code=getReply(socketfd);
    if(code != USER_LOGGED_IN){
        return 1;
    }

    //Enter passive mode

    //term_B socket

    //Retrieve file




}
