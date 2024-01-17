#include "server.h"

using namespace std;

int main(void)
{
    int maxFD;
    int activity;
    fd_set socket_set; // this is the list of file descriptors
    Server tcp_server;
    int server_fd = tcp_server.get_server_fd();

    char buff[BUFFER_SIZE];

    // intialize the list of client's file descriptor
    for (int i = 0; i < MAX_CLI; i++)
    {
        tcp_server.set_client_fd(i, 0);
    }

    if (tcp_server.Set_server_addr() != 0)
    {
        error("Cannot create server's address");
        exit(1);
    }

    if (tcp_server.Binding_server() != 0)
    {
        error("*** Cannot Bind Server ***");
        exit(1);
    }

    while (true)
    {
        // reset the list of file descriptors
        FD_ZERO(&socket_set);
        // Add Server's File descriptor to the socket_set
        FD_SET(server_fd, &socket_set);

        maxFD = server_fd;

        // Add current clients to list of file descriptor
        tcp_server.Add_socket_to_socket_set(&socket_set, maxFD);

        // wait and check for activities on all the sockets, waite indefinitely
        activity = select(maxFD + 1, &socket_set, NULL, NULL, NULL);

        if ((activity < 0) && (errno != EINTR))
        {
            error("** ERROR in SELECT **\n");
        }

        // check if that is incoming connection
        if (FD_ISSET(server_fd, &socket_set))
        {
            if (tcp_server.Accept_incoming_connection() != 0)
            {
                error("** CANNOT ACCEPT NEW CONNECTION **\n");
            }
            tcp_server.Print_clients_socket();
        }
    }
    close(server_fd);
    return 0;
}