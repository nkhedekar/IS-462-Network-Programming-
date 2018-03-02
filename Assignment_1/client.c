#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

int main(){
	int clientSocket;
	char buffer[1024];
	struct sockaddr_in serverAddr;
	socklen_t addr_size;
	int port;
	char *ip;
	
	clientSocket = socket(PF_INET, SOCK_STREAM, 0);
	serverAddr.sin_family = AF_INET;
	printf("Please enter server IP Address : ");
	scanf("%s", ip);
	serverAddr.sin_addr.s_addr = inet_addr(ip);
	printf("Please enter server port number : ");
	scanf("%d", &port);
	serverAddr.sin_port = htons(port);
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  
	addr_size = sizeof(serverAddr);
	connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);
	//connection made
	
	bzero(buffer, sizeof(buffer));
	printf("Welcome to the fifth and hopefully final iteration of this program. This is the barebones verion as the advanced functionalities I tried to put in the previous versions did not work. Enjoy ... \n\n");
	printf("Username : ");
	scanf("%s", buffer);
	send(clientSocket,buffer,strlen(buffer)+1,0);
	recv(clientSocket, buffer, 1024, 0);
	printf("%s",buffer);   
	bzero(buffer, sizeof(buffer));
	printf("Password : ");
	scanf("%s", buffer);
	send(clientSocket,buffer,strlen(buffer)+1,0);
	recv(clientSocket, buffer, 1024, 0);
	printf("%s",buffer);   
	return 0;
}
