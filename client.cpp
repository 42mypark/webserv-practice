#include <sys/socket.h>
#include "macro.hpp"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <unistd.h>

int main(int argc, char **argv){
    if (argc != 2)  {
        std::cout<< "plz input only port!" << std::endl;
        return 1;
    }

    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    int ret;

    sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(std::atoi(argv[1]));

    ret = connect(client_fd, SOCKADDR(server_addr), sizeof(server_addr));
    if (ret == -1){
        std::cout << "Client: connection fail" << std::endl;
        return 1;
    }
    std::cout << "Client: connected!" << std::endl;

    std::string line;
    char buffer[BUFFER_SIZE];
    while (1)
    {
        bzero(buffer, BUFFER_SIZE);
        std::cout << "input : ";
        std::getline(std::cin, line);
        std::cout << "Client: send to server: '" << line <<"' length: " << line.length() << std::endl;
        send(client_fd, line.c_str(), line.length(), 0);
        recv(client_fd, buffer, BUFFER_SIZE, 0);
        write(1, "Client: receive from server: ", strlen("Client: receive from server: "));
        write(1, buffer, BUFFER_SIZE);
        write(1, "\n", 1);
    }
}