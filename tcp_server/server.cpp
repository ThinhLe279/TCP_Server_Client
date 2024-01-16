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

int Server::set_client_fd(int pos, int socket)
{
    return this->clients_fd[pos] = socket;
}

int Server::get_client_fd(int pos)
{
    return this->clients_fd[pos];
}

int Server::Create_server_fd()
{
    cout << "Creating Server's fd... " << endl;
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd < 0)
        error("Cannot create server");
    return server_fd;
}

int Server::Set_server_addr(void)
{
    this->server_addr.sin_family = AF_INET;
    this->server_addr.sin_addr.s_addr = INADDR_ANY;
    this->server_addr.sin_port = htons(PORT);
    return 0;
}

int Server::Binding_server(void)
{
    // enable the reuse of local address and port
    int opt_val = 1;
    if (setsockopt(this->get_server_fd(), SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt_val, sizeof(opt_val)) != 0)
    {
        cout << "** Setsockopt FAILED **" << endl;
        return 1;
    }
    // Binding
    if (bind(this->get_server_fd(), (struct sockaddr *)&this->server_addr, sizeof(this->server_addr)) < 0)
    {
        cout << "** Binding FAILED **" << endl;
        return 1;
    }
    // listen to clients
    if (listen(this->get_server_fd(), MAX_CLI) < 0)
    {
        cout << "** Listening FAILED **" << endl;
        return 1;
    }
    cout << " Waiting for connection......." << endl;
    return 0;
}

int Server::Add_socket_to_socket_set(fd_set *set, int &maxFD)
{
    int fd = -1;
    for (int i = 0; i < MAX_CLI; i++)
    {
        fd = this->get_client_fd(i);

        if (fd > 0)
        {
            FD_SET(fd, set);
        }
        if (fd > maxFD)
        {
            maxFD = fd;
        }
    }
    return 0;
}