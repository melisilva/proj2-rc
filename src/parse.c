#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parse.h"

int parse_url(char* url, int size_url, char* user, char*password, char*host, char*path){
    /*url is ftp://[<user>:<password>@]<host>/<url-path>
    example: ftp://ftp.up.pt/pub/kodi/timestamp.txt where we don't have user and password here but we have host
and url-path. host is ftp.up.pt and the path is pub/kodi/timestamp.txt

    We need to find a / to get the url-path
    We need to find a : to know when user stopped and password started
    And we need a @ to know that the password ended and the host started
    
    Like the example showed us, there might not be an user and password defined
    */
   printf("IN PARSE\n");
   printf("%s\n",url);
   int i=0,u=0,p=0,h=0,pt=0;
   char rn;
   urlState state=USER;

    //Check if there's user and password in the url
       if(strchr(url,'@')!=NULL){ //paths could have :
          while(1){
              if(i<size_url){
                    rn=url[i];
                }
                i++;
              switch(state){
                case USER:
                  if(rn==':'){
                      state=PWD;
                  }
                  else{
                      user[u]=rn;
                      u++;
                  }
                  break;
                case PWD:
                 if(rn=='@'){
                      state=HOST;
                  }
                  else{
                      password[p]=rn;
                      p++;
                  }
                  break;
                case HOST:
                 if(rn=='/'){
                    state=PATH;
                  }
                  else{
                      host[h]=rn;
                      h++;
                  }
                  break;
                case PATH:
                  if(i==size_url){
                      return 0;
                  }
                  else{
                      path[pt]=rn;
                      pt++;
                  }
            } 
          }   
    }
    else{ //In case it's an anonymous login
        printf("Hello\n");
        state=HOST;
        while(1){
            if(i<size_url){
                    rn=url[i];
                }
                i++;
            switch(state){
                case HOST:
                 if(rn=='/'){
                    state=PATH;
                  }
                  else{
                      host[h]=rn;
                      h++;
                  }
                  break;
                case PATH:
                  if(i==size_url){
                      return 0;
                  }
                  else{
                      path[pt]=rn;
                      pt++;
                  }
        }
        }
    }
    return -1;    
}

char * getFilename(char * path) {
    char * filename = path, *p;
    for (p = path; *p; p++) {
        if (*p == '/' || *p == '\\' || *p == ':') {
            filename = p + 1;
        }
    }
    return filename;
}