/* 
 * File:   client.c
 * Author: Venkat, Zhengqi
 * 
 * Created on December 4, 2013, 6:14 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

char[15] serverIP;
int portNum;
struct sock_addr server_address;
int sockfd;
char[15] username;
int main(int argc, char[] argv){
   printf("Type in server IP");
   scanf(%s, &serverIP); 
   printf("\nType in port number");
   scanf(%d, &portNum);
   server_address.sin_family = AF_INET;
   server_address.sin_port = portNum;
   if(inet_aton(serverIP)!=0)
   server_address.sin_addr.s_addr=inet_addr(serverIP);
   else{
     printf("Invalid IP Address.");
     return 0;
   }
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   connect(sockfd, &server_address, sizeof(server_address));    //casting removed.
   printf("Enter Username:");
   scanf(%s, &username);
   send(sockfd, &username, sizeof(username), 0);
    
}
