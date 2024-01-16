#include "server.h"
using namespace std;

int main(void)
{
    int maxFD;
    fd_set socket_set; // this is the list of file descriptors
    Server tcp_server;

    char buff[BUFFER_SIZE] = {0};

    // intialize the list of client's file descriptor
    for (int i = 0; i < MAX_CLI; i++)
    {
        tcp_server.set_client_fd(i, 0);
    }

    if (tcp_server.Set_server_addr() != 0)
    {
        error("Cannot create server's address");
    }

    if (tcp_server.Binding_server() != 0)
    {
        error("*** Cannot Bind Server ***");
    }

    while (true)
    {
        // reset the list of file descriptors
        FD_ZERO(&socket_set);
        // Add Server's File descriptor to the socket_set
        FD_SET(tcp_server.get_server_fd(), &socket_set);

        maxFD = tcp_server.get_server_fd();

        // Add current clients to list of file descriptor
        tcp_server.Add_socket_to_socket_set(&socket_set, maxFD);
    }
    close(tcp_server.get_server_fd());
    return 0;
}