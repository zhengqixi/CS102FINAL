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
#include <systypes.h>

/*
 * 
 */
int main(int argc, char **argv)
{
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    char[15] username;

    server_addr.sin_addr = AF_INET;
    server_addr.sin_family.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = 1999;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bind(sockfd, (struct sockaddr *) &server_addr,
	 sizeof(struct sockaddr));
    listen(sockfd, 2);
    int cli_size = sizeof(struct sockaddr_in);	//cli_size necessary as an argument for pthread_create
    int new_fd =
	accept(sockfd, (struct sockaddr *) &client_addr, &cli_size);
    if (recv(new_fd, username,sizeof(username), 0)>0){
    	printf("%s has joined the chat.", username);
    }
    
    return (EXIT_SUCCESS);
}
