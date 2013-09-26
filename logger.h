#pragma once
#include <iostream>
#include <sstream>
#include <ctime>

class log_err 
{
    private:
        std::ostringstream oss;
        std::time_t time; 
        struct tm *tmp;
        char timestr[64];

    public: 
        log_err( );
        ~log_err( );

        /* template implementation must be in header */
        template< class T>
        log_err& operator<<(const T &x)
        {
            oss << x;
            return *this;
        }
};

