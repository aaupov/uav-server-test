#include "logger.h"

log_base::log_base( )
{
    time = std::time( NULL);
    tmp = std::localtime( &time);
    std::strftime( timestr, sizeof( timestr), "[%c] ", tmp);
}

log_base::~log_base( )
{
}

