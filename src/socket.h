#ifndef SOCKET_H
#define SOCKET_H

/**
    * Function that opens a TCP socket and connects it to the server.
     * @param ip: server's ip.
     * @param port: port where server awaits connection.
     * @return: 0 or -1 in case of error.
*/
int start_socket(char*ip,int port);

/**
    * Function that gets the reply code from the server and the full reply text.
     * @param socketfd: socket's file descriptor.
     * @return: reply code.
*/
int getReply(int socketfd);

/**
    * Function that writes request commands to the socket.
     * @param socketfd: socket's file descriptor.
     * @param cmd: string of command that we wish to write in thesocket.
     * @param arg: string of results that we wish to write in the socket
     * @return: 0 or -1 in case of error.
*/
int write_commands(int socketfd,char*cmd,char*arg);

/**
    * Function that gets the server's reply to a command and the value of the server's port where it awaits the connection.
     * @param socketfd: socket's file descriptor.
     * @return: value of the server's port where it awaits the connection.
*/
int getPort(int socketfd);

/**
    * Function that gets the value of the reply code and the server's reply to a command.
     * @param socketfd: socket's file descriptor.
     * @param reply: string where the value of the server's reply will be stored.
     * @return: value of the reply code.
*/
int getCode(int socketfd,char*reply);

/**
    * Function that transfers the file whose path is indicated by the path variable.
     * @param socketfd: socket's file descriptor.
     * @param path: string that has the value of the file path that will be transfered.
     * @return: 0 or -1 in case of error.
*/
int transfer(int socketfd, char*path);

#endif
