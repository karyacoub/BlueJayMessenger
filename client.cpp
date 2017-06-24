#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

using namespace std;

int main()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;
    char welcome_str[32];
    char * message;
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);

    if(sock < 0)
    {
        cout << "ERROR: Could not instantiate socket" << endl;
        exit(EXIT_FAILURE);
    }

    // convert string to ip address so that it can be used with connect sys call
    if(inet_pton(AF_INET, "127.0.0.1", &address.sin_addr) <= 0) 
    {
        cout << "ERROR: Could not use IP address/IP address not supported" << endl;
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while(connect(sock, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        if(i == 0)
            cout << "ERROR: Connection failed. Retrying..." << endl;
            i++;
    }

    // recieve and print out welcome string from server
    read(sock, welcome_str, 128);
    cout << welcome_str << endl;

    message = (char*)malloc(4096 * sizeof(char));
    
    while(1)
    {
        cout << "TYPE MESSAGE TO SERVER: ";
        fgets(message, 4096, stdin);
        strtok(message, "\n");
        
        send(sock, message, 4096, 0);

        memset(message, 0, 4096);
    }

    free(message);
}