#include "server.h"

void error(const char *msg)
{
    perror(msg);
    exit(1);
}
int Server::set_server_fd(int sockID)
{
    this->server_socket = sockID;
    return 0;
}

int Server::get_server_fd(void)
{
    return this->server_socket;
}

int Server::Create_server_fd()
{
    cout << "creating Server's fd... ";
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd < 0)
        error("cannot create server");
    return server_fd;
}