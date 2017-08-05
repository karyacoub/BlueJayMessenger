#define WIN32_LEAN_AND_MEAN
#pragma comment (lib, "Ws2_32.lib")

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <thread>
#include <Windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define PORT 8080

class Client
{
private:
	SOCKET sock;
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
	void connect_to_server();
	void send_and_recieve();
};
