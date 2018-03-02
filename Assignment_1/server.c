#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(){
	int welcomeSocket, newSocket;
	char buffer[1024];
	int port;
	struct sockaddr_in serverAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size;
	char usernames[7][12] = {"Alice", "Bob", "Cindy", "David", "Eve", "Frank", "George"};
	char passwords[7][12] = {"aaaaaaaaaa", "bbbbbbbbb", "cccccccccc", "ddddddddd", "eeeeeeeeee", "ffffffffff"};
	
	welcomeSocket = socket(AF_INET, SOCK_STREAM, 0);
	serverAddr.sin_family = AF_INET;
	printf("Please enter server port: ");
	scanf("%d", &port);
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));  
	bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
	if(listen(welcomeSocket,5)==0){
		printf("Listening\n");
	}else{
		printf("Error\n");
	}	
	addr_size = sizeof(serverStorage);
	while(1){
		newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
		bzero(buffer, sizeof(buffer));
		//get username
		recv(newSocket, buffer, 1024, 0);
		int i = 0;
		int userid = -1;
		while (i<7){
			if (strcmp(buffer, &usernames[i][0])==0){
				userid = i;
				break;
			}
			i++;
		}
		bzero(buffer, sizeof(buffer));
		strcpy(buffer,"username ok\n");
		send(newSocket,buffer,13,0);
		//get password
		bzero(buffer, sizeof(buffer));
		recv(newSocket, buffer, 1024, 0);
		if (userid != -1){
			if (strcmp(buffer, &passwords[userid][0])==0){
				//Access Granted
				bzero(buffer, sizeof(buffer));
				strcpy(buffer,"Access Granted\n");
				send(newSocket,buffer,16,0);
			}else {
				//Access Denied
				bzero(buffer, sizeof(buffer));
				strcpy(buffer,"Access Denied\n");
				send(newSocket,buffer,15,0);
			}
		}else {
				//Access Denied
				bzero(buffer, sizeof(buffer));
				strcpy(buffer,"Access Denied\n");
				send(newSocket,buffer,15,0);
			}
	}
}
