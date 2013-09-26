#include "socket.h"
#include "logger.h"
#include <errno.h>
#include <cstring>
#include <netinet/in.h>
#include <cstdlib>
#include <netdb.h>

/**
 * Bind address for server.
 */
net_connection::net_connection( )
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

/**
 * Close socket.
 */
net_connection::~net_connection( )
{
    close( sock);
}

/**
 * Listen on socket and memorize sender address. 
 */
char* net_connection::receive( )
{
    char* buf = new char[256];
    char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
    socklen_t addr_len = sizeof( struct sockaddr_storage);
    int s;
    
    /** Waiting occurs here. */
    if ( recvfrom( sock, buf, 256, 0, 
                reinterpret_cast< struct sockaddr*>( &plane_addr), 
                &addr_len) == -1 )
    {
        log_err() << "Error while listening on socket: " << strerror( errno);
        exit( EXIT_FAILURE);
    }

    /** Try to resolve address of sender. */
    if ( ( s = getnameinfo( reinterpret_cast< struct sockaddr*>( &plane_addr),
            addr_len, hbuf, sizeof( hbuf), sbuf, sizeof( sbuf), 
            NI_NUMERICHOST | NI_NUMERICSERV)) )
    {
        log_err() << "Error while determining sender address: " 
                  << gai_strerror( s);
    } else
    {
        log_norm() << "Received from " << hbuf << ", " << sbuf;
    }

    return buf;
}

/**
 * Send prepared buffer to client.
 */
void net_connection::send( char* buf)
{
    return;
}
