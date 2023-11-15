#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define MAX_ROWS 10
#define MAX_COLS 10
#define PORT 12345

void sendMatrixRow(int sockfd, struct sockaddr_in serverAddr, int matrixRow[MAX_COLS]) {
    // Convert integer array to a buffer
    char buffer[sizeof(int) * MAX_COLS];
    memcpy(buffer, matrixRow, sizeof(matrixRow));

    // Send the buffer to the server
    if (sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Error in sending data");
        exit(EXIT_FAILURE);
    }
}

int main() {
    int sockfd;
    struct sockaddr_in serverAddr;

    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    int matrix[MAX_ROWS][MAX_COLS] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        // Add more rows as needed
    };

    // Send each row of the matrix to the server
    for (int i = 0; i < MAX_ROWS; i++) {
        sendMatrixRow(sockfd, serverAddr, matrix[i]);
        printf("Sent row %d\n", i + 1);
    }

    close(sockfd);
    return 0;
}
