#include <iostream>
#include <string>
#include <sys/socket.h>
#include <cstring>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int cSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (cSocket < 0)
    {
        std::cerr << "Socket creation error!" << std::endl;
        return -1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(4444);
    // serverAddr.sin_addr.s_addr = INADDR_ANY;

    // localhost address
    if (inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr) <= 0)
    {
        std::cerr << "Invalid address." << std::endl;
        return -1;
    }

    if (connect(cSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
    {
        std::cerr << "Connection failed." << std::endl;
        return -1;
    }

    std::string message;
    while (1)
    {
        std::cout << "Enter message to send: ";
        std::getline(std::cin, message);
        // std::cout << message;
        send(cSocket, message.c_str(), strlen(message.c_str()), 0);

        // recieving message
        char buffer[1024] = { 0 };
        recv(cSocket, buffer, sizeof(buffer), 0);
        std::cout << "server: " << buffer << std::endl;

        if (message == "exit!")
        {
            break;
        }
    }

    close(cSocket);

    return 0;
}
