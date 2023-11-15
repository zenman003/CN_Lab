/*Implement concurrent Remote Math Server To perform arithmetic operations in the
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
struct sockaddr_in server,client;
sockfd=socket(AF_INET,SOCK_STREAM,0);
server.sin_family=AF_INET;
server.sin_addr.s_addr=inet_addr("10.0.2.15");
server.sin_port=htons(10200);
bind(sockfd,(struct sockaddr*)&server,sizeof(server));
listen(sockfd,5);
while(1)
{
    int a,b;
    char op;
    int clinen=sizeof(client);
    newsockfd=accept(sockfd,(struct sockaddr*)&client,&clinen);
    int pid=fork();
    if(pid==0)
    {
        printf("\nClient is online\n");
        read(newsockfd,&a,sizeof(a));
        read(newsockfd,&b,sizeof(b));
        read(newsockfd,&op,sizeof(op));
        int result;
        switch(op)
        {
            case '+': result=a+b;
                      break;
            case '-': result=a-b;
                      break;
            case '*': result=a*b;
                      break;
            case '/': result=a/b;
                      break;
            default: printf("\nInvalid operator\n");
                     exit(0);
        }
        printf("\nResult is: %d\n",result);
        write(newsockfd,&result,sizeof(result));
        close(newsockfd);
        exit(0);
    }
    else
    {
        close(newsockfd);
    }
}
}
