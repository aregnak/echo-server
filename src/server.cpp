#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

int main()
{
    int sSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (sSocket < 0)
    {
        std::cout << "Socket creation failed" << std::endl;
        return -1;
    }

    // specifying address
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(4444);
    //serverAddr.sin_addr.s_addr = INADDR_ANY;

    // localhost address
    if (inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr) <= 0)
    {
        std::cerr << "Invalid address or address not supported!" << std::endl;
        return -1;
    }

    // binding socket.
    if (bind(sSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
    {
        std::cerr << "Failed to bind" << std::endl;
        return -1;
    }

    // listening to the assigned socket
    listen(sSocket, 5);

    // accepting connection request
    int cSocket = accept(sSocket, nullptr, nullptr);

    while (1)
    {
        // recieving message
        char buffer[1024] = { 0 };
        recv(cSocket, buffer, sizeof(buffer), 0);

        // sending message
        send(cSocket, buffer, sizeof(buffer), 0);
        // cout << "Message from client: " << buffer << endl;
    }
    // closing the socket.
    close(sSocket);

    return 0;
}
