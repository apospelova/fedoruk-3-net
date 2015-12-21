#ifndef WEB_UTILITY_H
#define WEB_UTILITY_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <memory.h>
#include "server.h" 
#include <regex.h>

typedef struct {
	char* server;
	char* content;
} Url;

static int lastOffset = 0;

Url* 	parseURL(char* URL);
char*   sendHTTPGetRequest(int sct , char* URL ,  ServerNode* serverNode);
char** 	parseAttr(char* attr , char* HTML);
char* 	findSequence(char* text , char* regex);

#endif