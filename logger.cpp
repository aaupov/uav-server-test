#include "logger.h"

log_err::log_err( )
{
    time = std::time( NULL);
    tmp = std::localtime( &time);
    std::strftime( timestr, sizeof( timestr), "[%c]", tmp);
}

log_err::~log_err( )
{
    std::cerr << timestr << " " <<  oss.str( ) << std::endl;
}

