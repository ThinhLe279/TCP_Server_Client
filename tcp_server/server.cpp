#include "server.h"

void error(const char *msg)
{
    cerr << msg << endl;
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

int Server::get_total_client(void)
{
    return this->total_clients;
}

int Server::update_total_client(int num)
{
    this->total_clients = num;
    return 0;
}

int Server::Create_server_fd()
{
    cout << "Creating Server's fd... " << endl;
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd < 0)
    {
        error("Cannot create server");
        exit(1);
    }
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
        error("** Setsockopt FAILED **");
        return 1;
    }
    // Binding
    if (bind(this->get_server_fd(), (struct sockaddr *)&this->server_addr, sizeof(this->server_addr)) < 0)
    {
        error("** Binding FAILED **");
        return 1;
    }
    // listen to clients
    if (listen(this->get_server_fd(), MAX_CLI) < 0)
    {
        error("** Listening FAILED **");
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

int Server::Accept_incoming_connection(void)
{
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);
    // accept new client
    int new_client_fd = accept(this->get_server_fd(), (struct sockaddr *)&client_addr, &addr_len);

    if (this->get_total_client() == MAX_CLI)
    {
        error("** TOO MANY CLIENTS **");
        close(new_client_fd);
        return 1;
    }
    // check if new client is succesfully connected
    if (new_client_fd < 0)
    {
        error("** ERROR in ACCEPTING new Client **");
        return 1;
    }
    // add to list of Clients
    for (int i = 0; i < MAX_CLI; i++)
    {
        if (this->get_client_fd(i) == 0)
        {
            this->set_client_fd(i, new_client_fd);
            int new_total = this->get_total_client() + 1;
            this->update_total_client(new_total);
            break;
        }
    }
    // get Client's address;
    char client_IP[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &client_addr.sin_addr, client_IP, INET6_ADDRSTRLEN);

    cout << "--- New Client is Connected: " << client_IP << ", PORT: " << ntohs(client_addr.sin_port)
         << ", FILE DESCRIPTOR: " << new_client_fd << " ---" << endl;
    cout << "total Clients: " << this->get_total_client() << endl;
    return 0;
}

void Server::Print_clients_socket(void)
{
    cout << "All Clients Socket ID: ";
    for (int i = 0; i < MAX_CLI; i++)
    {
        cout << this->get_client_fd(i) << " ";
    }
    cout << endl;
}
