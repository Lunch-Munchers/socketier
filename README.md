
<a href="https://imgbb.com/"><img src="https://i.ibb.co/XpqJmkj/bootybaby.png" alt="bootybaby" border="0"></a><br />

# Simple Socket Program in C

This repository contains a simple C program for socket communication, providing a basic implementation of a client-server model. The program allows for sending and receiving messages between a client and a server using TCP/IP sockets.

## Features
- **Modular Design:** The code is organized into functions for creating a server socket, accepting client connections, creating a client socket, sending and receiving data, and cleaning up sockets.
- **Usage Flexibility:** The program can be used for both sending and listening, depending on the command-line arguments provided.
- **User Interaction:** For sending messages, the program prompts the user to enter messages until an empty message is provided, while for listening, it continuously receives and displays incoming messages.

## Usage
To compile and run the program, use the following command-line format:

```bash
./simple_socket_program <type (1 for sending, 2 for listening)> <port> [ip]
```


## Examples

Sending Messages:
```bash
./simple_socket_program 1 12345 127.0.0.1
```
Listening for Messages:
```bash
./simple_socket_program 2 12345
```

# Disclamer

This program is intended to be used only for shits and giggles, if you have any suggestions/tips i would greatly appreaciate it,
dm _seasponge on discord for any inquiries 

