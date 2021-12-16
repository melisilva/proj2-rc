#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

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
    if (connect(sockfd,
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
        if(buffer[3]==' '){
            sccanf(buffer,"%d",code);
            break;
        }
    }
    return code;
}

int write_commands(int socketfd,char*cmd,char*arg){
    if(write(socketfd,cmd,strlen(cmd))<0){
        return 1;
    }
    if(write(socketfd,arg,strlen(arg))<0){
        return 1;
    }
    if(write(socketfd,'\n',strlen('\n'))<0){
        return 1;
    }
    return 0;
}
