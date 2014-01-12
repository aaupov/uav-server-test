#include "mysql_connection.h"

void db_connection::query( string q)
{
    /* check whether connection is alive */
    if ( mysql_ping( conn) )
    {
        log_err() << "Reconnecting to mysql server";
        db_connection::close_connection( );
        conn = db_connection::open_connection( );
    }

    /* perform actual query */
    if ( mysql_query( conn, q.c_str( )) )
    {
        log_err() << q << " failed: " << mysql_error( conn);
    }
}

MYSQL* db_connection::open_connection( )
{
    if ( ( conn = mysql_init( NULL)) == NULL ) 
    {
        log_err() << "mysql_init() failed: " << mysql_error( conn);
        exit( EXIT_FAILURE);
    }
    //if ( mysql_real_connect( conn, "localhost", "webdev", 
    if ( mysql_real_connect( conn, "62.76.179.84", "webdev", 
                             "guL9toh3le", "bpla", 0, NULL, 0) == NULL ) 
    {
        log_err() << "connect failed: " << mysql_error( conn);
        exit( EXIT_FAILURE);
    } else {
        log_norm() << "Successfully connected to MySQL";
    }
    return conn;
}

void db_connection::close_connection( )
{
    mysql_close( conn);
}
