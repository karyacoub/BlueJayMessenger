#include <iostream>
#include <stdlib.h>
#include <string.h>
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
    char welcome_str[128];
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

    // recieve welcome string from server
    while(read(sock, welcome_str, 128))
    {
        cout << welcome_str << endl;
    }

    /*string str;
    while(1)
    {
        cout << "TYPE MESSAGE TO CLIENT: ";
        getline(cin, str);
        
        send(sock, str.c_str(), sizeof(str), 0);

        str.clear();
    }*/
}