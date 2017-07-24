#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>

#define PORT 8080

class Client
{
    private:
        int sock;
        char ip[16];
        char * message;
        struct sockaddr_in address;

        void init_socket();
        void recieve_messages();
        void recieve_thread();
        void send_messages();

    public:
        Client();
        Client(char * invite_code);
        int connect_to_server();
        void send_and_recieve();
};