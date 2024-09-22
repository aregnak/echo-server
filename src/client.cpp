#include <sys/socket.h>
#include <cstring>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "client.h"

int main()
{
    Client client;

    while (1)
    {
        client.sendMessage();
    }
}