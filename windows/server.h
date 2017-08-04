#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <unistd.h>

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