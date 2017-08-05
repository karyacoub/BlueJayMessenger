#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <Windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

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