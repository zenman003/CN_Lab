#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 12345

int main() {
    int sockfd;
    struct sockaddr_in serverAddr;
    int matrix[10][10] = {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20}
    };

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("10.0.2.15");

    for (int i = 0; i < 4; i++) {
        sendto(sockfd, matrix[i], sizeof(matrix[i]), 0, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
        printf("Sent row %d: ", i + 1);
        for (int j = 0; j < 5; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    close(sockfd);

    return 0;
}