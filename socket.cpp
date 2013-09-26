#include "socket.h"
#include "logger.h"
#include <errno.h>
#include <cstring>
#include <netinet/in.h>
#include <cstdlib>

socket_listener::socket_listener( )
{
    struct sockaddr_in addr_sr = {0};
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    addr_sr.sin_family = AF_INET;
    addr_sr.sin_port = htons(51000);
    addr_sr.sin_addr.s_addr = INADDR_ANY;

    if ( bind (sock, reinterpret_cast<const struct sockaddr*>(&addr_sr), 
               sizeof addr_sr) )
    {
        log_err() << "Unable to bind: " << strerror( errno);
        exit( EXIT_FAILURE);
    }
}

socket_listener::~socket_listener( )
{
    close( sock);
}

char* socket_listener::get_buffer( )
{
    char* buf = new char[256];
    if ( recvfrom( sock, buf, 256, 0, NULL, NULL) == -1 )
    {
        log_err() << "Error while listening to socket:" << strerror( errno);
        exit( EXIT_FAILURE);
    }
    return buf;
}
