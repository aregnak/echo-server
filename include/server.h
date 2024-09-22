#include <cstdint>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>

class Server
{
public:
    Server()
        : _port(4444)
        , _ipAddr("127.0.0.1")
        , cSocket(-1)
        , sSocket(-1)
        , bytesReceived(0)
    {
        sSocket = socket(AF_INET, SOCK_STREAM, 0);

        if (sSocket < 0)
        {
            std::cout << "Socket creation failed" << std::endl;
            exit(1);
        }

        // specifying address
        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(_port);

        // localhost address
        if (inet_pton(AF_INET, _ipAddr, &serverAddr.sin_addr) <= 0)
        {
            std::cerr << "Invalid address or address not supported!" << std::endl;
            exit(1);
        }

        // binding socket.
        if (bind(sSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
        {
            std::cerr << "Failed to bind" << std::endl;
            exit(1);
        }

        // listening to the assigned socket
        listen(sSocket, 5);

        // accepting connection request
        cSocket = accept(sSocket, nullptr, nullptr);
    }

    void echo()
    {
        // receiving message
        char buffer[1024] = { '0' };
        bytesReceived = recv(cSocket, buffer, sizeof(buffer), 0);

        // calculate num of bytes received to not send more than is required.
        if (bytesReceived < 0)
        {
            std::cerr << "Failed to reveive message." << std::endl;
        }

        // exit code to close sever
        std::string message(buffer, bytesReceived);
        if (message == "exit!")
        {
            exitMessage = "Exit code received, closing...";
            send(cSocket, exitMessage.c_str(), exitMessage.size(), 0);
            std::cout << exitMessage << std::endl;

            close(sSocket);
            close(cSocket);
            exit(1);
        }

        // sending message
        send(cSocket, buffer, bytesReceived, 0);
    }

    ~Server()
    {
        close(sSocket);
        close(cSocket);
    }

private:
    int cSocket;
    int sSocket;

    uint16_t _port;
    const char* _ipAddr;

    std::string exitMessage;
    ssize_t bytesReceived;
};