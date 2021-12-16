#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    USER,
    PWD,
    HOST,
    PATH
} urlState;

int parse_url(char* url, int size_url, char* user, char*password, char*host, char*path);
char * getFilename(char * path);
