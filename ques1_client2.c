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
struct sockaddr_in server;

sockfd=socket(AF_INET,SOCK_STREAM,0);
server.sin_family=AF_INET;
server.sin_addr.s_addr=inet_addr("10.0.2.15");

server.sin_port=htons(10200);

printf("\nClient is online\n");
connect(sockfd,(struct sockaddr*)&server,sizeof(server));
int arr[5],i,j,n,temp;
printf("\nEnter the number of elements in the array: ");
scanf("%d",&n);
printf("\nEnter the elements of the array: ");
for(i=0;i<n;i++)
scanf("%d",&arr[i]);
write(sockfd,arr,sizeof(arr));
read(sockfd,arr,sizeof(arr));
printf("\nSorted array is: ");
for(i=0;i<n;i++)
printf("%d ",arr[i]);
printf("\n");
close(sockfd);
return 0;
}
