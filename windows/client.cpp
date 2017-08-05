#include "client.h"

using namespace std;

// constructor to be used when hosting a server
Client::Client()
{
    init_socket();
    strcpy_s(ip, 16, "127.0.0.1");
}

// constructor to be used when joining a preexisting server
Client::Client(char * invite_code)
{
    init_socket();
}

// uses the socket() sys call to initialize socket and sets server address parameters
void Client::init_socket()
{
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if(sock == INVALID_SOCKET)
    {
        cout << "ERROR: Could not instantiate client socket" << endl;
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
}

// attempt to connect to server using given ip
int Client::connect_to_server()
{
    // convert string-ized ip to type sockaddr_in so that it can be used with connect sys call
    if(inet_pton(AF_INET, ip, &address.sin_addr) <= 0) 
    {
        cout << "ERROR: Could not use IP address/IP address not supported" << endl;
        exit(EXIT_FAILURE);
    }

    // attempt to connect to server
    int i = 0; // an increment is used here so that an error message only prints once if connection fails 
    while(connect(sock, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        if(i == 0)
        {
            cout << "ERROR: Connection failed. Retrying..." << endl;
            i++;
        }
    }

    cout << "Connection Successful" << endl << endl;

	return sock;
}

// uses main thread to send messages to server
void Client::send_messages()
{
    message = (char*)malloc(4106 * sizeof(char));

    while(strcmp(message, "//exit")!=0)
    {
        memset(message, 0, 4106);

        fgets(message, 4106, stdin);
        strtok_s(NULL, "\n", &message);
        
        send(sock, message, 4106, 0);
    }


    free(message);
}

// function to be used with second thread
void Client::recieve_thread()
{
    char str[4106];
    while(1)
    {
        recv(sock, str, 4106, 0);
        if(strcmp(str, "") != 0)
        {
            cout  << str << endl;
        }
        memset(str, 0, 4106);
    }
}

// creates a second thread that's always looking to recieve new messages
void Client::recieve_messages()
{
    std::thread recv_thread(&Client::recieve_thread, this);
    recv_thread.detach();
}

// starts sending and recieving messages
void Client::send_and_recieve()
{
    recieve_messages();
    send_messages();
}