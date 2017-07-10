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
        char * message;

        int init_socket();
        void recieve_messages();
        void send_messages();

    public:
        Client();
        int connect_to_server();
        void send_and_recieve();
};