#include <iostream>
#include <stdlib.h>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>

#define PORT 9065

using namespace std;

int main()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    int new_sock;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int opt = 1;

    // create socket file descriptor
    if(sock < 0)
    {
        cout << "ERROR: Could not instantiate socket" << endl;
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    // bind socket to port 9065
    if(bind(sock, (sockaddr *)&address, addrlen) < 0)
    {
        cout << "ERROR: Could not bind to port " + PORT << endl;
        exit(EXIT_FAILURE);
    }

    // listen for on specified socket
    if(listen(sock, 1) < 0)
    {
        cout << "ERROR: Could not listen on specified port and IP";
        exit(EXIT_FAILURE);
    }

    // wait for and accept client connection client connection
    new_sock = accept(sock, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    if(new_sock < 0)
    {
        cout << "ERROR: Could not accept connection" << endl;
        exit(EXIT_FAILURE);
    }

    char * str = "ayy lmao";

    // send data to client and close socket
    send(new_sock, str, sizeof(str), 0);
}