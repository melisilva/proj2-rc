#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <libgen.h> 

#include "constants.h"

int start_socket(char*ip,int port){
    int socketfd;
    struct sockaddr_in server_addr;
    /*server address handling*/
    bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip);    /*32 bit Internet address network byte ordered*/
    server_addr.sin_port = htons(port);        /*server TCP port must be network byte ordered */

     /*open a TCP socket*/
    if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket()");
        return -1;
    }

     /*connect to the server*/
    if (connect(socketfd,
                (struct sockaddr *) &server_addr,
                sizeof(server_addr)) < 0) {
        perror("connect()");
        return -1;
    }

    return socketfd;
}

int getReply(int socketfd){ 
    //We stop reading when the line only consists on the reply code
    FILE*socket=fdopen(socketfd,"r");
    char*buffer;
    int code;
    size_t bytes=0;
    while(getline(&buffer,&bytes,socket)>0){
        printf(RESET "%s",buffer);
        if(buffer[3]==' '){
            code=atoi(buffer);
            break;
        }
    }
    return code;
}

int getCode(int socketfd,char*reply){
    char*str_code= (char*)malloc(4);
    int code;
    read(socketfd,reply,BUFFER_LENGTH);
    printf(RESET "%s",reply);
    memcpy(str_code,reply,3);
    code=atoi(str_code);
    free(str_code);
    return code;
}

int write_commands(int socketfd,char*cmd,char*arg){
    /*
    USER <SP> <username> <CRLF>
    CRLF means Carriage Return Line Feed
    A line feed means moving one line forward. The code is \n .
    A carriage return means moving the cursor to the beginning of the line. The code is \r .
    */


    if(write(socketfd,cmd,strlen(cmd))<0){
        printf(RED "ERROR - not able to write command\n");
        return -1;
    }
    if(arg!=""){
        if(write(socketfd,arg,strlen(arg))<0){
            printf(RED "ERROR - not able to write companion information to the command\n");
            return -1;
        }
    }
    if(write(socketfd,"\r\n",strlen("\r\n"))<0){
        printf(RED "ERROR - not able to write CRLF\n");
        return -1;
    }
    return 0;
}

int getPort(int socketfd){
    //227 Entering Passive Mode (193,136,28,12,19,91)
    char* reply=(char*)malloc(BUFFER_LENGTH);
    int code=getCode(socketfd,reply);

    //Check if code is 227
    if(code != PASSIVE_MODE){
        printf(RED "ERROR - instead of code 227, indicating that we have successful gotten into passive mode, we got an error message\n");
        return -1;
    }

    /*
    The C library function char *strtok(char *str, const char *delim) 
    breaks string str into a series of tokens using the delimiter delim.

    We can use this function to break the reply to get what we want.
    */
    char*token,*n1,*n2,*n3,*n4,*n5,*n6;
    token=strtok(reply,"(");
    token=strtok(NULL,"(");
    token=strtok(token,")");
    n1=strtok(token,",");
    n2=strtok(NULL,",");
    n3=strtok(NULL,",");
    n4=strtok(NULL,",");
    n5=strtok(NULL,",");
    n6=strtok(NULL,",");

    int port=atoi(n5)*256+atoi(n6);
    free(reply);
    return port;
}

int transfer(int socketfd, char*path){
    char*fileName= basename(path); /*The functions dirname() and basename() break a null-terminated pathname string into directory and filename components. In the usual case, dirname() returns the string up to, but not including, the final '/', and basename() returns the component following the final '/'. */
    //Opening BINARY mode data connection-->so we need to open file in writing binary mode
    FILE *fp=fopen(fileName,"wb");
    if(fp==NULL){
        printf(RED "ERROR - file doesn't exist\n");
        return -1;
    }

    //socket B has the data that we need to put in the file for A
    char buffer[BUFFER_LENGTH];
    int bytes;
    while((bytes=read(socketfd,buffer,BUFFER_LENGTH))>0){
        if(fwrite(buffer,bytes,1,fp)<0){
            printf(RED "ERROR - not able to write in file\n");
            return -1;
        }
    }
    fclose(fp);
    return 0;
}
