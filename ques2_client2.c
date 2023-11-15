/*mplement concurrent Remote Math Server To perform arithmetic operations in the
server and display the result to the client. The client accepts two integers and an
operator from the user and sends it to the server. The server then receives integers and
operator. The server will perform the operation on integers and sends the result back
to the client which is displayed on the client screen. Then both the processes
terminate.*/

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>
int main()
{
int sockfd,newsockfd,clength;
struct sockaddr_in server;
sockfd=socket(AF_INET,SOCK_STREAM,0);
server.sin_family=AF_INET;
server.sin_addr.s_addr=inet_addr("10.0.2.15");
server.sin_port=htons(10200);
connect(sockfd,(struct sockaddr*)&server,sizeof(server));

int a,b;
char op;
printf("\nEnter the first number: ");
scanf("%d",&a);
printf("\nEnter the second number: ");
scanf("%d",&b);
printf("\nEnter the operator: ");
scanf(" %c",&op);
write(sockfd,&a,sizeof(a));
write(sockfd,&b,sizeof(b));
write(sockfd,&op,sizeof(op));
int result;
read(sockfd,&result,sizeof(result));
printf("\nResult is: %d\n",result);
close(sockfd);
return 0;

}
