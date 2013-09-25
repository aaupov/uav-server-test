#include "mysql_connection.h"

db_connection::db_connection( )
{
    if ( ( conn = mysql_init(NULL)) == NULL ) {                                    
        cerr << "mysql_init() failed: " << mysql_error( conn) << endl;
        exit( EXIT_FAILURE);
    }                                                                           
    if ( mysql_real_connect( conn, "localhost", "webdev", "guL9toh3le", "bpla", 0, NULL, 0) == NULL) {
        cerr << "connect failed: " << mysql_error( conn) << endl;
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
    if ( mysql_ping( conn))
    {
        cerr << "Reconnecting to mysql server" << endl;
    }

    /* perform actual query */
    if ( mysql_query( conn, q.c_str( )) ){
        cerr << q << " failed: " << mysql_error( conn) << endl;
    }
}
