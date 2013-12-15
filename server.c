/* 
 * File:   server.c
 * Author: Venkat, Zhengqi
 * 
 * Created on December 4, 2013, 6:14 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

/*
 * 
 */
 
void sendMsg(int * new_fd);
void recvMsg(int * new_fd);
#define MAXDATALEN 256
int main()
{
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    char username[15];
    int thrSend;
    int thrRecv;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = 1999;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bind(sockfd, (struct sockaddr *) &server_addr,
	 sizeof(struct sockaddr));
    listen(sockfd, 2);
    int cli_size = sizeof(struct sockaddr_in);	//cli_size necessary as an argument for pthread_create
    int new_fd =
	accept(sockfd, (struct sockaddr *) &client_addr, &cli_size);
    if (recv(new_fd, username,sizeof(username), 0)>0){
    	printf("%s has joined the chat.\n", username);
    	pthread_create(&thrSend,NULL,sendMsg,&new_fd);
    	pthread_create(&thrRecv,NULL,recvMsg,&new_fd);
    }
    
    
    
    return (EXIT_SUCCESS);
}


sendMsg(int * new_fd){
	while(1){
		char * message[MAXDATALEN];
		printf(":");
		scanf("%s",message);
		send(*new_fd,&message,MAXDATALEN, 0);
	}
}

recvMsg(int * new_fd){
	char * message[MAXDATALEN];
	while(1){
		if(recv(*new_fd,message,sizeof(message),0)>0){
			printf("%s\n",message);
		}
	}
}
