#pragma once
#include <string>
#include <mysql/mysql.h>
#include <cstdlib>
#include "logger.h"

using namespace std;

class db_connection
{
    public:
        db_connection( ){
            conn = open_connection( );
        }

        ~db_connection( ){
            close_connection( );
        }

        void query( string);
    private:
        MYSQL *conn;
        MYSQL* open_connection( );
        void close_connection( );
};
