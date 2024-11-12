#include "server.h"

int main(int argc, char const *argv[]) {
    int serverSocket = initializeSocket();
    if (serverSocket == -1) {
        return -1;
    }
    
    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(9001);
    servAddr.sin_addr.s_addr = INADDR_ANY;

    if (bindSocket(serverSocket, &servAddr) == -1) {
        close(serverSocket);
        return -1;
    }

    if (listenForClient(serverSocket) == -1) {
        close(serverSocket);
        return -1;
    }

    printf("Waiting for client...\n");
    int clientSocket = accept(serverSocket, NULL, NULL);
    if (clientSocket == -1) {
        printf("Client connection acceptance failed\n");
        close(serverSocket);
        return -1;
    }

    handleCommunication(clientSocket);
    closeConnection(clientSocket, serverSocket);

    return 0;
}