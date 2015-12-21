#include "web_utility.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

Url* parseURL(char* URL){
		Url* url = (Url*)malloc(sizeof(Url));
		printf("%s\n", URL);
		url->server = findSequence(URL , "://.*(([.]com)|([.]ru)|([.]en))");
		url->content = findSequence(URL , "[^/]/[^/].*");
		url->content = (url->content == NULL) ? NULL : url->content + 2;
		printf("%s\n" , url->server);
		if(url->server == NULL){
			free(url);
			return NULL;
		}

		url->server = url->server + 3;
		return url;
}

char*  sendHTTPGetRequest(int sct , char* content ,  ServerNode* serverNode){
		char sendMessage[1024];
		char* revMessage = (char*)malloc(10000);
		int lengthRevMessage = 0;
		if(content == NULL)
			sprintf(sendMessage , "GET / HTTP/1.0\r\nHost: %s\r\n\r\n", serverNode->name);
		else
			sprintf(sendMessage , "GET /%s HTTP/1.0\r\nHost: %s\r\n\r\n", content, serverNode->name);

		if(connect (sct, &serverNode->servAddr, sizeof(serverNode->servAddr)) < 0)
			printf("Failed connect operation because of %s\n\n" , strerror(errno));


		send(sct , sendMessage , strlen(sendMessage) , 0);
		int length;
		while((length = recv (sct, revMessage + lengthRevMessage, 10000 - lengthRevMessage, 0)) > 0){
			lengthRevMessage += length;
		}
		printf("%s?????????????????\n", serverNode->name);
		return revMessage;

}

char** 	parseAttr(char* attr , char* HTML){
		char** attrs = (char**)malloc(sizeof(char*) * 100);
		int i = 0, offset = 0;
		char regex[100];
		sprintf(regex , "%s[' '\t]*=[' '\t]*\"[^\"]*\"" , attr);
		for(i = 0 ; i < 100 && (attrs[i] = findSequence(HTML + offset , regex)) != NULL ; i++){
			offset += lastOffset;
		}
		return attrs;
}

char* findSequence(char* text , char* regex){
	regex_t regexS;
	regmatch_t matches;
	if(regcomp(&regexS , regex , REG_EXTENDED | REG_ICASE))
		return NULL;
	if(regexec(&regexS , text , 1 , &matches , 0))
		return NULL;

	char* result = (char*)malloc(matches.rm_eo - matches.rm_so + 1);
	memcpy(result , text + matches.rm_so , matches.rm_eo - matches.rm_so );
	result[matches.rm_eo - matches.rm_so ] = '\0';
	lastOffset = matches.rm_eo;
	regfree(&regexS);
	return result;
}
