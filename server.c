#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int createConnect(char* server , int port){
	host = gethostbyname(server);
	printf("Find address %s\n\n" , host->h_name);

	serverNode = (ServerNode*)malloc(sizeof(ServerNode));
	memset ((char *)&serverNode->servAddr, '\0', sizeof(serverNode->servAddr));
	serverNode->servAddr.sin_family = AF_INET;
	memcpy ((char *)&serverNode->servAddr.sin_addr,host->h_addr,host->h_length);
	serverNode->servAddr.sin_port = htons(port);
	serverNode->name = server;

	return 1;
}
ServerNode* getConnect(){
	return serverNode;
}