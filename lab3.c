#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include "web_utility.h"
#include "server.h"
#include <stdlib.h>

#define SOCKET_ERROR "Bad configuration socket"
#define BIND_ERROR "Bad configuration bind operation"

int main (int argc, char **argv){
	//******** Begin configuration client  *****************//
	struct addrinfo *result  ,*res;
	int error;

	struct sockaddr_in hostAddr;

	int s = socket (AF_INET, SOCK_STREAM, 0);

	if(s < 0){
		printf("%s\n" , SOCKET_ERROR);
		return -1;
	}

	memset ((char *)&hostAddr, '\0', sizeof(hostAddr));
    hostAddr.sin_family = AF_INET;
    hostAddr.sin_addr.s_addr = INADDR_ANY;
    hostAddr.sin_port = 80;
    
    if(bind (s, (struct sockaddr *)&hostAddr, sizeof(hostAddr)) != 0){
    	printf("%s\n", BIND_ERROR);
    	return -1;
    }


    //********** Send HTTP REQUEST ****************//
 	char* answer;
 	char** urls = (char**)malloc(sizeof(char*) * 100);


 	Url* url = parseURL(argv[1]);
 	createConnect(url->server , 80);
 	while((answer = sendHTTPGetRequest(s , url->content , getConnect())) != NULL){
 		printf("%s \n /////////////////////////////////////////////////////\n", answer);
 		int i = 0  , input;
 		char** attr = parseAttr("href" , answer);
 		for(i = 0 ; attr[i] != NULL ; i++)
 			printf("%d :: %s\n", i , attr[i]);

 		if(i == 0 || (scanf("%d" , &input) && input) >= i || input < 0)
 			break;

 		attr[input][strlen(attr[input]) - 1] = '\0';
 		if(url->content != NULL){
 			char* newUrl = (char*)malloc(strlen(url->content) + strlen(attr[input]));
 			sprintf(newUrl, "%s%s", url->content , attr[input] + 6);
 			url->content = newUrl;
 		}
 		else
 			url->content = attr[input] + 6;
 		printf("You choice %s\n", url->content);
 		close(s);
 		s = socket (AF_INET, SOCK_STREAM, 0);
 		free(answer);
 	}
 	printf("This is the END\n");
 	close(s);
	return 1;
}

