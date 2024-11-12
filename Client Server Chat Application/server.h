#ifndef SERVER_H
#define SERVER_H

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
int bindSocket(int serverSocket, struct sockaddr_in *servAddr);
int listenForClient(int serverSocket);
void handleCommunication(int clientSocket);
void closeConnection(int clientSocket, int serverSocket);


// function definitions
int initializeSocket() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        printf("Socket creation failed\n");
    }
    return serverSocket;
}

int bindSocket(int serverSocket, struct sockaddr_in *servAddr) {
    int bindStatus = bind(serverSocket, (struct sockaddr *)servAddr, sizeof(*servAddr));
    if (bindStatus == -1) {
        printf("Binding failed\n");
    }
    return bindStatus;
}

int listenForClient(int serverSocket) {
    int listenStatus = listen(serverSocket, 1);
    if (listenStatus == -1) {
        printf("Listening failed\n");
    }
    return listenStatus;
}

void handleCommunication(int clientSocket) {
    char message[255];
    char response[255];

    while (1) {
        int recvStatus = recv(clientSocket, message, sizeof(message), 0);
        if (recvStatus <= 0) {
            if (recvStatus == 0) printf("Client disconnected.\n");
            else printf("Receiving message failed\n");
            break;
        }

        message[recvStatus] = '\0';
        printf("Client: %s\n", message);

        if (strcmp(message, "exit") == 0) {
            printf("Client disconnected.\n");
            break;
        }

        printf("Server: ");
        fgets(response, 255, stdin);
        response[strcspn(response, "\n")] = '\0';

        if (send(clientSocket, response, strlen(response), 0) == -1) {
            printf("Sending message failed\n");
            break;
        }

        if (strcmp(response, "exit") == 0) {
            printf("Disconnected from client.\n");
            break;
        }
    }
}

void closeConnection(int clientSocket, int serverSocket) {
    close(clientSocket);
    close(serverSocket);
}

#endif