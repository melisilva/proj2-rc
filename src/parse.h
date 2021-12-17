#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>
#include <stdlib.h>

/*
Simple state machine used to parse URL (argument provided in the start of the app).*/
typedef enum
{
    USER,
    PWD,
    HOST,
    PATH
} urlState;

/**
    * Function that divides/parses URL into parts and saves the significant ones in the corresponding variable.
     * @param url: string that contains the URL needed to be parsed.
     * @param size_url: size of the URL.
     * @param user: string where the value of the username included in the URL will be stored.
     * @param password: string where the value of the password included in the URL will be stored.
     * @param host: string where the value of the host included in the URL will be stored.
     * @param path: string where the value of the path included in the URL will be stored.
     * @return: 0 or -1 in case of error.
*/
int parse_url(char* url, int size_url, char* user, char*password, char*host, char*path);

#endif