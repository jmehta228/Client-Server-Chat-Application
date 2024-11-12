#include "client.h"

int main(int argc, char const *argv[]) {
    int clientSocket = initializeSocket();
    if (clientSocket == -1) {
        return -1;
    }

    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(9001);
    servAddr.sin_addr.s_addr = INADDR_ANY;

    if (connectToServer(clientSocket, &servAddr) == -1) {
        close(clientSocket);
        return -1;
    }

    FILE *transcriptFile = fopen("transcript.txt", "w");
    if (!transcriptFile) {
        printf("Failed to open transcript file\n");
        close(clientSocket);
        return -1;
    }

    handleCommunication(clientSocket, transcriptFile);
    closeConnection(clientSocket, transcriptFile);

    return 0;
}