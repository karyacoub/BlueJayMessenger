#include "client.h"

using namespace std;

Client::Client()
{
    init_socket();
}

// uses the socket() sys call to initialize socket
int Client::init_socket()
{
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if(sock < 0)
    {
        cout << "ERROR: Could not instantiate client socket" << endl;
        exit(EXIT_FAILURE);
    }

    return sock;
}

// attemp to connect to server (currently uses 127.0.0.1 temporarily)
int Client::connect_to_server()
{
    struct sockaddr_in address;

    // convert string-ized ip to type sockaddr_in so that it can be used with connect sys call
    if(inet_pton(AF_INET, "127.0.0.1", &address.sin_addr) <= 0) 
    {
        cout << "ERROR: Could not use IP address/IP address not supported" << endl;
        exit(EXIT_FAILURE);
    }

    // attempt to connect to server
    int i = 0; // an increment is used here so that an error message only prints once if connection fails 
    while(connect(sock, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        if(i == 0)
            cout << "ERROR: Connection failed. Retrying..." << endl;
            i++;
    }

    cout << "Connectioon Successful. Welcome to Purpl.!" << endl << endl;
}

// uses main thread to send messages to server
void Client::send_messages()
{
    message = (char*)malloc(4096 * sizeof(char));

    do
    {
        memset(message, 0, 4096);

        fgets(message, 4096, stdin);
        strtok(message, "\n");
        
        send(sock, message, 4096, 0);
    } while(strcmp(message, "//exit")!=0);


    free(message);
}

// function to be used with second thread
void recieve_thread(void * client_socket)
{
    int sock_int = *(int*)(client_socket);
    char str[4096];
    while(1)
    {
        read(sock_int, str, 4096);
        cout << "MESSAGE FROM CLIENT: " << str << endl;
        memset(str, 0, 4096);
    }
}

// creates a new thread that's always looking to recieve new messages
void Client::recieve_messages()
{
    std::thread recv_thread(&recieve_thread, &sock);
}

// starts sending and recieving messages
void Client::send_and_recieve()
{
    recieve_messages();
    send_messages();
}