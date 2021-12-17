#ifndef CONSTANTS_H
#define CONSTANTS_H

#define FILE_OKAY_DATA_SOON  150  //File status okay; about to open data connection
#define SERVICE_CLOSING  221  //Service closing control connection
#define SERVICE_READY  220  // Service ready for new user
#define DATA_CONNECT_OPEN 225 //Data connection open; no transfer in progress
#define FILE_TRANSFER_SUCCESS   226 //File transfer was completed with success
#define PASSIVE_MODE  227 //Passive mode activated
#define USER_LOGGED_IN  230  //User is logged in
#define USER_OKAY  331  //User name okay
#define NOT_LOGGED_IN  530  //Not logged in
#define PORT  21
#define BUFFER_LENGTH 255
#define PARAMETER_LENGTH 512

//Adding a lil color for fun
#define CYN   "\x1B[36m"
#define RED   "\x1B[31m"
#define MAG   "\x1B[35m"
#define RESET "\x1B[0m"

#endif