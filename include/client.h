#include <cstdint>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <cstring>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

class Client
{
public:
    Client()
        : _port(4444)
        , _ipAddr("127.0.0.1")
        , cSocket(-1)
    {
        cSocket = socket(AF_INET, SOCK_STREAM, 0);

        if (cSocket < 0)
        {
            std::cerr << "Socket creation error!" << std::endl;
            exit(1);
        }

        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(_port);

        // localhost address
        if (inet_pton(AF_INET, _ipAddr, &serverAddr.sin_addr) <= 0)
        {
            std::cerr << "Invalid address." << std::endl;
            exit(1);
        }

        if (connect(cSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
        {
            std::cerr << "Connection failed." << std::endl;
            exit(1);
        }
    }

    void sendMessage()
    {
        std::cout << "Enter message to send: ";
        std::getline(std::cin, message);
        send(cSocket, message.c_str(), message.size(), 0);

        // recieving message
        char buffer[1024] = { 0 };
        recv(cSocket, buffer, sizeof(buffer), 0);
        std::cout << "Server: " << buffer << std::endl;

        // exit code to close client
        if (message == "exit!")
        {
            close(cSocket);
            exit(1);
        }
    }

    ~Client()
    {
        close(cSocket);
        //
    }

private:
    int cSocket;
    uint16_t _port;
    const char* _ipAddr;
    std::string message;
};