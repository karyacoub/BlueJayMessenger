#include "server.h"

using namespace std;

Server::Server()
{
    get_external_ip();
    init_server();
}

// initialize server socket and address
void Server::init_server()
{
    // initialize set of client file descriptors
    for(int i = 0; i < MAX_CLIENTS; i++) { client_sockets[i] = 0; }

    // initialize socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(server_sock < 0)
    {
        cout << "ERROR: Could not instantiate socket" << endl;
        exit(EXIT_FAILURE);
    }

    // set address parameters
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // bind socket to specified port
    if(bind(server_sock, (sockaddr *)&address, sizeof(address)) < 0)
    {
        cout << "ERROR: Could not bind to port " + PORT << endl;
        exit(EXIT_FAILURE);
    }

    cout << "Server Initialized" << endl << endl;
}

char * Server::send_ip_request()
{
    int sockfd;  
    struct addrinfo address_info, *server_info, *p;
    int rv;

    memset(&address_info, 0, sizeof address_info);
    address_info.ai_family = AF_INET;
    address_info.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo("checkip.dyndns.org", "http", &address_info, &server_info)) != 0) 
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        exit(1);
    }

    // loop through all the results and connect to the first we can
    for(p = server_info; p != NULL; p = p->ai_next) 
    {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) 
        {
            perror("socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) 
        {
            perror("connect");
            close(sockfd);
            continue;
        }

        break; // if we get here, we must have connected successfully
    }

    if (p == NULL) 
    {
        // looped off the end of the list with no connection
        fprintf(stderr, "failed to connect\n");
        exit(2);
    }

    char request[] = "GET / HTTP/1.1\r\nHost: checkip.dyndns.org\r\nConnection: close\r\n\r\n";
    char * response = (char*)malloc(1024 * sizeof(char));

    send(sockfd, request, sizeof(request), 0);

    read(sockfd, response, 1024);

    close(sockfd);
    freeaddrinfo(server_info); // all done with this structure

    return response;
}

char * Server::get_external_ip()
{
    char * ip_response = send_ip_request();
    ip_response = strtok(ip_response, "A");

    cout << ip_response << endl;
}

void Server::listen_for_connections()
{
    // listen on specified socket
    if(listen(server_sock, 0) < 0)
    {
        cout << "ERROR: Could not listen on specified port and IP";
        exit(EXIT_FAILURE);
    }

    cout << "Awaiting client connections..." << endl << endl;
}

// helper function for accept_connection(), add new socket to array of client sockets
void Server::add_socket(int new_socket)
{
    for (int i = 0; i < MAX_CLIENTS; i++)
    {  
        //if position is empty 
        if(client_sockets[i] == 0)  
        {  
            client_sockets[i] = new_socket;  
            break;  
        }  
    }
}

void Server::accept_connection()
{
    int client_sock;
    int addrlen = sizeof(address);

    /*if(num_clients >= MAX_CLIENTS)
    {
        cout << "ERROR: Could not accept connection, maximum number of clients reached" << endl << endl;
        break;
    }*/

    client_sock = accept(server_sock, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    if(client_sock < 0)
    {
        cout << "ERROR: Could not accept connection" << endl;
    }
    
    // add new socket to array of client sockets
    add_socket(client_sock);
}

// uses listen() and accept() sys calls to connect to clients
void Server::listen_for_clients()
{
    listen_for_connections();
    accept_connection();
}

void Server::client_disconnect(int * client_socket)
{
    cout << "Client " << *client_socket - 3 << " has disconnected" << endl << endl;
    *client_socket = 0;
}

void Server::relay_message(int source_client)
{
    char * message_with_sender = (char *)malloc(4106 * sizeof(char));
    strcpy(message_with_sender, "Client ");
    strcat(message_with_sender, to_string(source_client - 3).c_str());
    strcat(message_with_sender, ": ");
    strcat(message_with_sender, message);

    for(int i = 0; i < MAX_CLIENTS; i++)
    {
        if(client_sockets[i] != 0 &&  source_client!= client_sockets[i])
        {
            send(client_sockets[i], message_with_sender, 4106, 0);
        }
    }
    memset(message, 0, 4106);
    free(message_with_sender);
}

void Server::listen_for_messages()
{
    int max_sd = 0; // largest socket desriptor, needed for the select funtion
    int activity;

    while(1)
    {
        // clear socket set
        FD_ZERO(&client_set);

        // add server socket to set
        FD_SET(server_sock, &client_set);

        // add child sockets to fd set and check for largest socket descriptor
        for(int i = 0; i < MAX_CLIENTS; i++)
        {
            // if socket is valid, add it to set
            if(client_sockets[i] > 0)
            {
                FD_SET(client_sockets[i], &client_set);
            }

            // check if current socket is the max socket descriptor
            if(client_sockets[i] > max_sd)
            {
                max_sd = client_sockets[i];
            }
        }

        // monitor sockets for activity
        activity = select(max_sd + 1, &client_set, NULL, NULL, NULL);

        // if there is activity on master socket, then there is an incoming connection
        if(FD_ISSET(server_sock, &client_set))
        {
            accept_connection();
            cout << "Client has connected" << endl << endl;
        }

        // check for further activity on all sockets
        for(int i = 0; i < MAX_CLIENTS; i++)
        {
            if(FD_ISSET(client_sockets[i], &client_set))
            {
                read(client_sockets[i], message, 4106);

                if(strcmp(message, "") == 0) // client has disconnected
                {
                    client_disconnect(&(client_sockets[i]));
                }

                else // client sent a message, send that message to all other clients
                {
                    relay_message(client_sockets[i]);
                }
            }
        }
    }
}