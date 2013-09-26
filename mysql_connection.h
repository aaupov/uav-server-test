#pragma once
#include <string>
#include <mysql/mysql.h>
#include <cstdlib>
#include "logger.h"

using namespace std;

class db_connection
{
    public:
        db_connection( );
        ~db_connection( );

        void query( string);
    private:
        MYSQL *conn;
};
