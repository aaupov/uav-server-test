#pragma once
#include <string>
#include <iostream>
#include <mysql/mysql.h>
#include <cstdlib>

using namespace std;

class db_connection
{
    public:
        db_connection();
        ~db_connection();

        void query( string);
    private:
        MYSQL *conn;
};
