#ifndef SERVER_H_
#define SERVER_H_

 #include <netinet/in.h>
 #include <netdb.h>
 #include <memory.h>

typedef struct ServerNode{
	struct sockaddr_in servAddr;
	char* name;
}ServerNode;

static struct hostent* host = NULL;
static ServerNode* serverNode;

int createConnect(char* server ,  int port);
ServerNode* getConnect();;

#endif