#include "mysql_connection.h"

db_connection::db_connection( )
{
    if ( ( conn = mysql_init(NULL)) == NULL ) 
    {
        log_err() << "mysql_init() failed: " << mysql_error( conn);
        exit( EXIT_FAILURE);
    }                                                                           
    if ( mysql_real_connect( conn, "localhost", "webdev", 
                             "guL9toh3le", "bpla", 0, NULL, 0) == NULL ) 
    {
        log_err() << "connect failed: " << mysql_error( conn);
        exit( EXIT_FAILURE);
    }                                                                           
}

db_connection::~db_connection( )
{
    mysql_close( conn);
}

void db_connection::query( string q)
{
    /* check whether connection is alive */
    if ( mysql_ping( conn) )
    {
        log_err() << "Reconnecting to mysql server failed";
        exit( EXIT_FAILURE);
    }

    /* perform actual query */
    if ( mysql_query( conn, q.c_str( )) )
    {
        log_err() << q << " failed: " << mysql_error( conn);
    }
}
