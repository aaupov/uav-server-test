#pragma once
#include <sys/types.h>
#include <sys/socket.h>

#define PORT 51000

class net_connection
{
    private:
        int sock;
        struct sockaddr_storage plane_addr;

    public:
        /**
         * Bind address for server.
         */
        net_connection( );

        /**
         * Close socket.
         */
        ~net_connection( );

        /**
         * Listen on socket and memorize sender address. 
         */
        char* receive( );

        /**
         * Send prepared buffer to client.
         */
        void send( char* buf);
};
