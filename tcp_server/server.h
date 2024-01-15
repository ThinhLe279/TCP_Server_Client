#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>     // exit, atoi
#include <netinet/in.h> // htons
#include <arpa/inet.h>
#include <map>

#define MAX_CLI 10  // max clients
#define PORT        // server's port
#define BUFFER_SIZE // to handle messages from client

using namespace std;

void error(const char *msg);

class Server
{
private:
    int server_socket;
    int online_clients[MAX_CLI];
    sockaddr_in server_addr;

public:
    Server()
    {
        this->set_server_fd(this->Create_server_fd());
        cout << "----- TCP Server's socket is " << this->get_server_fd() << " -----" << endl;
    }

    int set_server_fd(int sockID);
    int get_server_fd(void);
    int Create_server_fd(void);
};

#endif