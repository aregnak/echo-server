#include <iostream>
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

    // sending message
    const char* message = "ping";
    send(cSocket, message, strlen(message), 0);

    // recieving message
    char buffer[1024] = { 0 };
    recv(cSocket, buffer, sizeof(buffer), 0);
    std::cout << "Return from server: " << buffer << std::endl;

    close(cSocket);

    return 0;
}
