#include "logger.h"
#include <iostream>

log_base::log_base( )
{
    time = std::time( NULL);
    tmp = std::localtime( &time);
    std::strftime( timestr, sizeof( timestr), "[%c] ", tmp);
}

log_base::~log_base( )
{ }

log_err::~log_err( )
{
    std::cerr << timestr << oss.str( ) << std::endl;
}

log_norm::~log_norm( )
{
    std::cout << oss.str( ) << std::endl;
}
