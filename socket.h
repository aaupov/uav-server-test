#pragma once

class socket_listener
{
    private:
        int sock;
    public:
        char* get_buffer( );
        socket_listener( );
        ~socket_listener( );
};
