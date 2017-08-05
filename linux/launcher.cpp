// http://checkip.dyndns.org/

#include "client.h"
#include "server.h"

using namespace std;

void client_thread()
{
    Client client;
    client.connect_to_server();
    client.send_and_recieve();
}

int main()
{
    cout << "Welcome to Purpl.!" << endl << endl;
    
    cout << "   1. Host a server" << endl;
    cout << "   2. Join a server" << endl << endl;

    char option;

    cout << "Choose an option (type in 1 or 2): ";
    cin >> option;
    cout << endl;

    // host the server
    if(option == '1')
    {
        //thread t(&client_thread);
        //t.detach();

        Server server;
        server.listen_for_clients();
        server.listen_for_messages();
    }

    // join a preexisting server
    else if(option == '2')
    {
        Client client;
        client.connect_to_server();
        client.send_and_recieve();
    }
}