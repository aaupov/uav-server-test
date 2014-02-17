#pragma once
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include <string>
#include <cstdlib>
#include "logger.h"
#include "command.h"
#include "protoskel.h"

using namespace std;

class database
{
public:
    database();
    ~database();
    base_command* command_poll();
    unique_ptr<sql::ResultSet> query(string);

private:
    sql::mysql::MySQL_Driver *driver;
    unique_ptr<sql::Connection> con;

    sql::PreparedStatement* unsent_commands_pstmt;
    //unsigned last_read_command;
};

