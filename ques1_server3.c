#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 12345
#define MAX_ROWS 10
#define MAX_COLS 10

int main() {
    int sockfd;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrLen = sizeof(clientAddr);
    int matrix[MAX_ROWS][MAX_COLS];
    int num_rows_received = 0;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

    printf("Server waiting for rows...\n");

    while (num_rows_received < MAX_ROWS) {
        int row[MAX_COLS];
        ssize_t received = recvfrom(sockfd, row, sizeof(row), 0, (struct sockaddr *)&clientAddr, &addrLen);

        if (received < 0) {
            perror("Error receiving data");
            break;
        }

        // Copy received row to the matrix
        memcpy(matrix[num_rows_received], row, sizeof(row));
        num_rows_received++;

        printf("Received row %d: ", num_rows_received);
        for (int i = 0; i < MAX_COLS; i++) {
            printf("%d ", matrix[num_rows_received - 1][i]);
        }
        printf("\n");
    }

    printf("Received all rows. Combined matrix:\n");
    for (int i = 0; i < num_rows_received; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    close(sockfd);

    return 0;
}