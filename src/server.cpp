#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "server.h"

int main()
{
    Server server;

    while (1)
    {
        server.echo();
    }
}
