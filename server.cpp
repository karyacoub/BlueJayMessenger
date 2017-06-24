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
#define MAX_CLIENTS 30

using namespace std;

int main()
{
    int master_sock = socket(AF_INET, SOCK_STREAM, 0);
    int new_sock, client_socks[MAX_CLIENTS];
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    fd_set sockset;
    int opt = 1;

    char welcome_str[32] = "Welcome to Purpl.!";
    char message[4096];

    cout << "PURPL. v0.1" << endl << endl;
    cout << "STARTING UP SERVER..." << endl;

    // zero out all client sock fds
    for(int i = 0; i < MAX_CLIENTS; i++) { client_socks[i] = 0; }

    // create socket file descriptor
    if(master_sock < 0)
    {
        cout << "ERROR: Could not instantiate socket" << endl;
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    // bind socket to port 9065
    if(bind(master_sock, (sockaddr *)&address, addrlen) < 0)
    {
        cout << "ERROR: Could not bind to port " + PORT << endl;
        exit(EXIT_FAILURE);
    }

    cout << "SUCCESS" << endl << endl;
    cout << "AWAITING CLIENT CONNECTIONS..." << endl << endl;

    // listen for on specified socket
    if(listen(master_sock, 5) < 0)
    {
        cout << "ERROR: Could not listen on specified port and IP";
        exit(EXIT_FAILURE);
    }

    int max_sd; // largest socket desriptor, needed for the select funtion
    int activity; // to be used with select function to check for activity on any of the sockets

    while(1)
    {
        // clear socket set
        FD_ZERO(&sockset);

        // add master socket to set
        FD_SET(master_sock, &sockset);
        max_sd = master_sock;

        // add child sockets to fd set and check for largest socket descriptor
        for(int i = 0; i < MAX_CLIENTS; i++)
        {
            // if socket is valid, add it to set
            if(client_socks[i] > 0)
            {
                FD_SET(client_socks[i], &sockset);
            }

            // check if current socket is the max socket descriptor
            if(client_socks[i] > max_sd)
            {
                max_sd = client_socks[i];
            }
        }

        // wait for activity on one of the sockets
        activity = select(max_sd + 1, &sockset, NULL, NULL, NULL);

        // if there is activity on master socket, then there is an incoming connection
        if(FD_ISSET(master_sock, &sockset))
        {
            // accept connection from client
            new_sock = accept(master_sock, (struct sockaddr *)&address, (socklen_t *)&addrlen);
            if(new_sock < 0)
            {
                cout << "ERROR: Could not accept connection" << endl;
                exit(EXIT_FAILURE);
            }

            cout << "CLIENT " << new_sock - 3 << " CONNECTED SUCCESSFULLY" << endl << endl;

            // send welcome message to client
            send(new_sock, welcome_str, sizeof(welcome_str), 0);

            // add new socket to array of sockets
            for (int i = 0; i < MAX_CLIENTS; i++)
            {  
                //if position is empty 
                if(client_socks[i] == 0)  
                {  
                    client_socks[i] = new_sock;  
                    break;  
                }  
            }
        }
        
        // check for further activity on the socket
        for(int i = 0; i < MAX_CLIENTS; i++)
        {
            // if there is activity on a socket, either a message has been sent or client has disconnected
            if(FD_ISSET(client_socks[i], &sockset))
            {
                read(client_socks[i], message, 4096);

                if(strcmp(message, "") == 0) // client has disconnected
                {
                    cout << "CLIENT " << client_socks[i] - 3 << " HAS DISCONNECTED" << endl << endl;
                    client_socks[i] = 0;
                }
                else // client sent a message
                {
                    cout << "MESSAGE FROM CLIENT " << client_socks[i] - 3 << ": " << message << endl;
                    memset(message, 0, 4096);
                }
            }
        }

    }
}