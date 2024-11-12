# Client-Server-Chat-Application

This C program implements a simple client-server chat application using TCP sockets, allowing a client to connect to a server and exchange messages interactively.

## Structure and Components

The program is organized into four files:
1. **client.h** - Defines functions for the client’s socket initialization, connection, message handling, and disconnection.
2. **client.c** - Main file for the client, establishing the connection to the server and facilitating message exchange.
3. **server.h** - Defines functions for the server’s socket initialization, binding, listening for client connections, message handling, and disconnection.
4. **server.c** - Main file for the server, waiting for and handling client connections and message exchange.

## Key Functions

- **initializeSocket**: Creates a socket for communication on both client and server.
- **connectToServer (client)**: Connects the client to the server using a specified address and port.
- **bindSocket (server)**: Binds the server to a specific address and port.
- **listenForClient (server)**: Sets the server to listen for incoming client connections.
- **handleCommunication**: Manages the message exchange between client and server. Both the client and server can type messages to send to each other and exit the chat by typing "exit."
- **closeConnection**: Closes the socket and cleans up resources on both client and server sides.

## How It Works

1. **Server Side**:
   - The server initializes a socket, binds to an address and port (9001), and waits for incoming connections.
   - Once a client connects, the server enters a loop to handle message exchange with the client until one party sends "exit" or disconnects.

2. **Client Side**:
   - The client initializes a socket and attempts to connect to the server on port 9001.
   - Once connected, the client and server can exchange messages in a loop until "exit" is sent or a disconnection occurs.
   - The client records all messages in a `transcript.txt` file, logging both sent and received messages.

## Usage

1. Start the server by running `server.c`.
2. Start the client by running `client.c`.
3. Both client and server can type messages and view each other's responses.
4. To exit the chat, either party can type "exit".
