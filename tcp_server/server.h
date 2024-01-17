#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>     // exit, atoi
#include <netinet/in.h> // htons
#include <arpa/inet.h>
#include <unistd.h>
#include <map>

#define MAX_CLI 10       // max clients
#define PORT 9999        // server's port
#define BUFFER_SIZE 1024 // to handle messages from client

using namespace std;

void error(const char *msg);

class Server
{
private:
    int server_socket;
    int clients_fd[MAX_CLI];
    int total_clients = 0;
    sockaddr_in server_addr;

public:
    Server()
    {
        this->set_server_fd(this->Create_server_fd());
        cout << "----- TCP Server's socket is " << this->get_server_fd() << " -----" << endl;
    }
    // setters and getters

    int set_server_fd(int sockID);
    int get_server_fd(void);
    int set_client_fd(int pos, int socket);
    int get_client_fd(int pos);
    int get_total_client(void);
    int update_total_client(int num);

    // functions
    int Create_server_fd(void);                                          // function to create server's socket
    int Set_server_addr(void);                                           // function to set address for server
    int Binding_server(void);                                            // function to bind socket to localhost
    int Add_socket_to_socket_set(fd_set *set, int &maxFD);               // function to add client's socket to socket_set
    int Accept_incoming_connection(void);                                // funtion to accept new connection
    int Disconnect_client(int pos);                                      // function to disconnect, close a client's socket
    int Receive_and_echo_message(int sockID, char *buff, int byte_read); // function to receive and echo message to client
    void Print_clients_socket(void);                                     // function to print all clients socket
};

#endif