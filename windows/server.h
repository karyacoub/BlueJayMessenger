#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <string>

#pragma comment (lib, "Ws2_32.lib")

#define PORT 8080
#define MAX_CLIENTS 100

class Server
{
    private:
        int server_sock;
        int client_sockets[MAX_CLIENTS];
        char message[4106];
        struct sockaddr_in address;
        fd_set client_set;

        void init_server();
        void listen_for_connections();
        void accept_connection();
        void add_socket(int new_socket);
        void client_disconnect(int * client_socket);
        void relay_message(int source_client);

    public:
        Server();
        void listen_for_clients();
        void listen_for_messages();
};