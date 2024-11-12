#ifndef CLIENT_H
#define CLIENT_H

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

// function prototypes
int initializeSocket();
int connectToServer(int clientSocket, struct sockaddr_in *servAddr);
void handleCommunication(int clientSocket, FILE *transcriptFile);
void closeConnection(int clientSocket, FILE *transcriptFile);


// function definitions
int initializeSocket() {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        printf("Socket creation failed\n");
    }
    return clientSocket;
}

int connectToServer(int clientSocket, struct sockaddr_in *servAddr) {
    int connectStatus = connect(clientSocket, (struct sockaddr *)servAddr, sizeof(*servAddr));
    if (connectStatus == -1) {
        printf("Connection failed\n");
    }
    return connectStatus;
}

void handleCommunication(int clientSocket, FILE *transcriptFile) {
    char message[255];
    char response[255];

    while (1) {
        printf("Client: ");
        fgets(message, 255, stdin);
        message[strcspn(message, "\n")] = '\0';

        fprintf(transcriptFile, "Client: %s\n", message);

        if (send(clientSocket, message, strlen(message), 0) == -1) {
            printf("Sending message failed\n");
            break;
        }

        if (strcmp(message, "exit") == 0) {
            printf("Disconnected from server.\n");
            break;
        }

        int recvStatus = recv(clientSocket, response, sizeof(response), 0);
        if (recvStatus <= 0) {
            if (recvStatus == 0) printf("Server disconnected.\n");
            else printf("Receiving message failed\n");
            break;
        }

        response[recvStatus] = '\0';
        printf("Server: %s\n", response);
        fprintf(transcriptFile, "Server: %s\n", response);
    }
}

void closeConnection(int clientSocket, FILE *transcriptFile) {
    fclose(transcriptFile);
    close(clientSocket);
}

#endif