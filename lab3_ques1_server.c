#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define MAX_ROWS 10
#define MAX_COLS 10
#define PORT 12345

void printMatrix(int matrix[MAX_ROWS][MAX_COLS], int rows, int cols) {
    printf("Received Matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int sockfd;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrLen = sizeof(clientAddr);
    char buffer[sizeof(int) * MAX_COLS]; // Assuming integer matrix elements

    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // Bind socket to the server address
    if (bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    int matrix[MAX_ROWS][MAX_COLS];
    int rowCount = 0;

    while (1) {
        // Receive a row from the client
        int recvBytes = recvfrom(sockfd, buffer, sizeof(buffer), 0,
                                 (struct sockaddr *)&clientAddr, &addrLen);
        if (recvBytes < 0) {
            perror("Error in receiving data");
            exit(EXIT_FAILURE);
        }

        // Convert received buffer to an integer array (assuming integer matrix elements)
        int receivedRow[MAX_COLS];
        memcpy(receivedRow, buffer, sizeof(receivedRow));

        // Copy the received row to the matrix
        memcpy(matrix[rowCount], receivedRow, sizeof(receivedRow));
        rowCount++;

        // Check if the matrix is complete
        if (rowCount == MAX_ROWS) {
            printMatrix(matrix, rowCount, MAX_COLS);
            rowCount = 0; // Reset row count for the next matrix
        }
    }

    close(sockfd);
    return 0;
}
