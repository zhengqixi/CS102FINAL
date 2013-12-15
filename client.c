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
#include <sys/types.h>
#include <unistd.h>


char serverIP[15];
int portNum;
struct sockaddr_in server_address;
int sockfd;
char username[15];
int thrSend;
int thrRecv;
#define MAXDATALEN 256
void sendMsg(int * sockfd);
void recvMsg(int * sockfd);
int main(){
   printf("Type in server IP");
   scanf("%s", &serverIP); 
   printf("\nType in port number");
   scanf("%d", &portNum);
   printf("Server IP:   %s\n",&serverIP);
   server_address.sin_family = AF_INET;
   printf("Thank you.\n");
      
   server_address.sin_port = portNum;
   printf("Thank you.\n");
   
   server_address.sin_addr.s_addr=inet_addr(serverIP);
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   connect(sockfd,(const struct sockaddr*) &server_address, sizeof(server_address));    //casting removed.
   printf("Enter Username:");
   scanf("%s", &username);
   send(sockfd, &username, sizeof(username), 0);
   pthread_create(&thrSend,NULL,sendMsg,&sockfd);
   pthread_create(&thrRecv,NULL,recvMsg,&sockfd);
}

sendMsg(int * sockfd){
   while(1){
      char* message[MAXDATALEN];
      printf(":");
      scanf("%s",message);
      send(*sockfd,message,sizeof(message), 0);
   }
}

recvMsg(int * sockfd){
   char * message[MAXDATALEN];
   if(recv(*sockfd, message,sizeof(message),0)>0)
      printf("%s\n",message);

}
