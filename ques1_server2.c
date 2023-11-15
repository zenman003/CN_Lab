
/*Write a TCP concurrent client server program where server accepts integer array from
client and sorts it and returns it to the client along with process id.*/

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
pid_t pid=fork();
sockfd=socket(AF_INET,SOCK_STREAM,0);
server.sin_family=AF_INET;
server.sin_addr.s_addr=inet_addr("10.0.2.15");
server.sin_port=htons(10200);
bind(sockfd,(struct sockaddr*)&server,sizeof(server));
listen(sockfd,5);
while(1)
{
    int arr[5],i,j,n,temp;
    int clinen=sizeof(client);
    newsockfd=accept(sockfd,(struct sockaddr*)&client,&clinen);
    if(fork()==0)
    {
        printf("\nClient is online\n");
        read(newsockfd,arr,sizeof(arr));
        printf("\nReceived array is: ");
        for(i=0;i<5;i++)
        printf("%d ",arr[i]);
        printf("\n");
        for(i=0;i<5;i++)
        {
            for(j=0;j<5-i-1;j++)
            {
                if(arr[j]>arr[j+1])
                {
                    temp=arr[j];
                    arr[j]=arr[j+1];
                    arr[j+1]=temp;
                }
            }
        }
        //process id
        printf("\nProcess id is: %d\n",getpid());
        printf("\nSorted array is: ");
        for(i=0;i<5;i++)
        printf("%d ",arr[i]);
        printf("\n");
        printf("pid: %d and ppid: %d \n",getpid(),getppid());
        write(newsockfd,pid,sizeof(pid));
        write(newsockfd,arr,sizeof(arr));
        close(newsockfd);
        exit(0);
    }
    else
    {
        printf("pid: %d\n",getpid());

        close(newsockfd);
    }
}
}