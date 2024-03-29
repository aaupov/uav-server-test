#pragma once
#include <sstream>
#include <ctime>

class log_base
{
    protected:
        std::ostringstream oss;
        std::time_t time; 
        struct tm *tmp;
        char timestr[64];

    public: 
        log_base( );
        virtual ~log_base( ) = 0;

        template< class T>
        log_base& operator<<(const T &x)
        {
            oss << x;
            return *this;
        }
};

class log_err : public log_base
{
    public:
        virtual ~log_err( );
};

class log_norm : public log_base
{
    public:
        virtual ~log_norm( );
};
