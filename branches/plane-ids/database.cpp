#include "database.h"

database::database():
    driver(sql::mysql::get_driver_instance()),
    /* Using the Driver to create a connection */
    con(driver->connect("localhost", "webdev", "guL9toh3le"))
{
    /*last_read_command = 0;*/
    unsent_commands_pstmt = con->prepareStatement(
            "SELECT * FROM commands WHERE sent = 0 OR sent IS NULL");
}

database::~database()
{
    delete unsent_commands_pstmt;
}

auto_ptr<sql::ResultSet>
database::query(string q)
{
    auto_ptr<sql::ResultSet> res;
	try {
        auto_ptr<sql::Statement> stmt(con->createStatement());
        res.reset(stmt->executeQuery(q));
	} catch (sql::SQLException &e) {
        log_err() << e.what();
    }

    return res;
}

base_command
database::command_poll()
{
    base_command cmd;
    enum msg_dcp_types type;
    sql::ResultSet* res = unsent_commands_pstmt->executeQuery();
    while (res->next())
    {
        type = static_cast<enum msg_dcp_types>(res->getUInt("type"));
        unsigned int num = res->getUInt("num");

        switch (type)
        {
            case Msg_NewRoute:
            default: 
                log_err() << "Command " 
                          << num 
                          << ": invalid type" 
                          << type;
        }
    }
    return cmd;
}
