#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include<pthread.h>

struct word{
	char w[20];
	char synonyms[5][20];
	int nSyns;
};

struct word words[100];
int numOfWords = 0;


struct word queryWord(char * w){
	int i = 0;
	for(i = 0; i < numOfWords; i++){
		if(words[i] != NULL){
			if(strcmp(words[i].w,w) == 0){
				printf("Got a match for %s", w);
				return words[i];
			}
		}
	}
	struct word w1;
	strcpy(w1.w, "00");
	return w1;
}

int addWord(char * w, char * s){
	struct word w1;
	strcpy(w1.w, w);
	char *token = strtok(s, " ");
	int i = 0;
	while(token != NULL){
		strcpy(w1.synonyms[i], token);
		token = strtok(NULL, " ");
		i++;
	}   
	
	printf("Adding the Word: %s", w1.w);
	words[numOfWords++] = w1;
	return 1;
}

int removeWord(char * w){
	int i = 0;
	for(i = 0; i < numOfWords; i++){
		if(words[i] != NULL){
			if(strcmp(words[i].w,w) == 0){
			printf("Removing the word: %s", w);
			words[i] = NULL;
			}
		}
	}
	return 1;
}

void *ProcessRequest(void *args)
{
	int cl_fd=(int)args;
	char str[256];
	char buffer[256];	
	//get input
	//decipher as Q/A/R
	//do action
	//send error/success
	int con;
	while(con != 0){
		read(cl_fd,str,255);
		char *token = strtok(str, " ");
		if(strcmp(token,"q")){
			token = strtok(NULL, " ");
			struct word w1 = queryWord(token);
			if (strcmp(w1.w, "00")){
				write(cl_fd, w1.w, 3);
			}else {
				
			}
		}
	
	
	}
	write(cl_fd,str,20);
	close(cl_fd);
}

int main()
{
	pthread_t t[10];
	int welcomeSocket, newSocket;
	char buffer[1024];
	int port, i;
	struct sockaddr_in serverAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size;	
	welcomeSocket = socket(AF_INET, SOCK_STREAM, 0);
	serverAddr.sin_family = AF_INET;
	printf("Please enter server port: ");
	scanf("%d", &port);
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));  
	bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
	printf("\nSocket has been created\n");
	listen(welcomeSocket,0); 
	printf("Listening ... \n");
	while(1){
		for(i = 0; i<10; i++){
			newSocket = accept(welcomeSocket,NULL,NULL);
			printf("\nConnected to client %d\n", newSocket);
			if(pthread_create(&t[i], NULL, ProcessRequest, (void *)newSocket)){
				printf("Cannot create thread with i as %d", i);
			}
		}
	}
	return 0;
}
