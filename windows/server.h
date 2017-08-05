#define WIN32_LEAN_AND_MEAN
#pragma comment (lib, "Ws2_32.lib")

#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <stdio.h>
#include <Windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define PORT 8080
#define MAX_CLIENTS 100

class Server
{
private:
	SOCKET server_sock;
	SOCKET client_sockets[MAX_CLIENTS];
	char message[4200];
	struct sockaddr_in address;
	fd_set client_set;

	void init_server();
	void listen_for_connections();
	void accept_connection();
	void add_socket(SOCKET new_socket);
	void client_disconnect(SOCKET * client_socket);
	void relay_message(int source_client);
	char * send_ip_request();
	char * get_external_ip();

public:
	Server();
	void listen_for_clients();
	void listen_for_messages();
};