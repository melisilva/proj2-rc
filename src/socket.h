int start_socket(char*ip,int port);
int getReply(int socketfd);
int write_commands(int socketfd,char*cmd,char*arg);
int getPort(int socketfd);
int getCode(int socketfd);
int transfer(int socketfd, char*path);
