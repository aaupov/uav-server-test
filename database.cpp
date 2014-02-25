#include "database.h"

database::database():
    driver(sql::mysql::get_driver_instance()),
    /* Using the Driver to create a connection */
    con(driver->connect("localhost", "webdev", "guL9toh3le"))
{
    con->setSchema("bpla");
    log_norm() << "mysql connect";
    /*last_read_command = 0;*/
    unsent_commands_pstmt = 
        mkstmt("select * from commands where sent is null");
}

database::~database()
{
    delete unsent_commands_pstmt;
}

unique_ptr<sql::ResultSet>
database::query(string q)
{
    unique_ptr<sql::ResultSet> res;
	try {
        unique_ptr<sql::Statement> stmt(con->createStatement());
        res.reset(stmt->executeQuery(q));
	} catch (sql::SQLException &e) {
        log_err() << e.what();
    }

    return res;
}

void
database::command_poll()
{
    log_norm() << "Database command polling started";
    enum msg_dcp_types type;
    try {
    sql::ResultSet* res = unsent_commands_pstmt->executeQuery();
    while (res->next())
    {
        base_command* cmd;
        type = static_cast<enum msg_dcp_types>(res->getUInt("type"));
        unsigned int num = res->getUInt("num");
        log_norm() << "Command " << num << ", type " << type;

        switch (type)
        {
            case Msg_NewRoute:
                cmd = parse_route();
                break;
            case Msg_CleanRoute:
                cmd = new cleanRoute;
                break;
            case Msg_UpdatePoint:
                cmd = parse_updcpt(num);
                break;
            case Msg_Emergency:
                cmd = new emergency;
                break;
            case Msg_HandOn:
                cmd = new setManualMode;
                break;
            case Msg_HandOff:
                cmd = new setAutomaticMode;
                break;
            case Msg_ZeroBaroAlt:
                cmd = parse_zerobaroalt(num);
                break;
            default: 
                log_err() << "Command " 
                          << num 
                          << ": invalid type" 
                          << type;
                throw std::exception();
        }
        /* update plane state */
        /* send msg */
        /* mark msg as sent */
        //mark_sent(num);
        delete cmd;
    }
    } catch (sql::SQLException &e) {
        log_err() << "# ERR: SQLException in " << __FILE__
            << "(" << __FUNCTION__ << ") on line " << __LINE__;
        log_err() << "# ERR: " << e.what()
            << " (MySQL error code: " << e.getErrorCode()
            << ", SQLState: " << e.getSQLState() << " )" ;
    }
    log_norm() << "No unsent messages";
}

updateCheckpoint* 
database::parse_updcpt(unsigned int num)
{
    struct checkpoint pt;
    sql::PreparedStatement* update_cpt_pstmt = 
        mkstmt("select * from msg_updcpt where num=?");
    update_cpt_pstmt->setUInt(1, num);
    sql::ResultSet* res = update_cpt_pstmt->executeQuery();

    /* parse result set */
    unsigned int route = res->getUInt("routenum");
    pt.speed = res->getUInt("speed");
    pt.altitude = res->getUInt("altitude");
    pt.position.longitude = res->getDouble("position_longitude");
    pt.position.latitude = res->getDouble("position_latitude");
    pt.emergency.longitude = res->getDouble("emergency_longitude");
    pt.emergency.latitude = res->getDouble("emergency_latitude");

    updateCheckpoint* cpt = new updateCheckpoint(route, pt);
    delete res;
    delete update_cpt_pstmt;
    return cpt;
}

newRoute* 
database::parse_route()
{
    /* dummy function f.t.b */
    return new newRoute(0, NULL);
}

correctZeroBaroAlt*
database::parse_zerobaroalt(unsigned int num)
{
    sql::PreparedStatement* update_zba_pstmt = 
        mkstmt("select zerobaroalt from msg_zerobaroalt where num=?");
    update_zba_pstmt->setUInt(1, num);
    sql::ResultSet* res = update_zba_pstmt->executeQuery();

    unsigned int zero = res->getUInt("zerobaroalt");
    correctZeroBaroAlt* zba = new correctZeroBaroAlt(zero);
    delete res;
    delete update_zba_pstmt;
    return zba;
}

sql::PreparedStatement*
database::mkstmt(string str)
{
    return con->prepareStatement(str);
}

void
database::mark_sent(unsigned int num)
{
    sql::PreparedStatement* mark_sent_pstmt = 
        mkstmt("update commands set sent=1 where num=?");
    mark_sent_pstmt->setUInt(1, num);
    mark_sent_pstmt->executeUpdate();
    delete mark_sent_pstmt;
}
