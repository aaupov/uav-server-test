#include <iostream>
#include <sstream>
#include <cstring>
#include <netinet/in.h>
#include <errno.h>
#include <mysql/mysql.h>
#include "dcp.h"

using std::cout;
using std::cerr;
using std::endl;

void heartbeat( void* buf);
void conf_request( void* buf);
void confirm( void* buf);
void report( void* buf);
MYSQL *conn;

int main() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    char* buf = new char[256];
    struct message* header = new struct message;
    struct sockaddr_in addr_sr = {0};

    addr_sr.sin_family = AF_INET;
    addr_sr.sin_port = htons(51000);
    addr_sr.sin_addr.s_addr = INADDR_ANY;

    bind (sock, reinterpret_cast<const struct sockaddr*>(&addr_sr), sizeof addr_sr);

    if ( ( conn = mysql_init(NULL)) == NULL ) {                                    
        cerr << "mysql_init() failed: " << mysql_error( conn) << endl;
        return 1;                                                               
    }                                                                           
    if ( mysql_real_connect( conn, "localhost", "webdev", "guL9toh3le", "bpla", 0, NULL, 0) == NULL) {
        cerr << "connect failed: " << mysql_error( conn) << endl;
        return 1;                                                               
    }                                                                           

    while ( 1 ){
        if ( recvfrom( sock, buf, 256, 0, NULL, NULL) == -1 )
        {
            cerr << strerror( errno) << endl;
            return 1;
        }
        memcpy( header, buf, sizeof( struct message));

        /**
         * Parse header
         */

        /** Only allow DCP messages */
        if ( header->proto != Proto_Dispatcher )
        {
            cerr << header->num << ": unhandled protocol " << header->proto << endl;
            continue;
        }

        /** Checksum verification? */

        /** 
         * Distinguish messages by type, 
         * then pass buffer to appropriate handler
         */
        switch ( header->type )
        {
            case Msg_Heartbeat:
                heartbeat( buf);
                break;

            case Msg_ReqConfirm:
                conf_request( buf);
                break;

            case Msg_Confirm:
                confirm( buf);
                break;

            case Msg_Report:
                report( buf);
                break;

            default:
                cerr << header->num << ": unhandled message type " << header->type << endl;
                continue;
        }
    }

    delete buf;
    cout << "Server terminated" << endl;
    mysql_close(conn);
    return 0;
}

void heartbeat( void* buf)
{
    struct msg_heartbeat* hb = new struct msg_heartbeat;
    std::stringstream query;

    memcpy( hb, buf, sizeof( struct msg_heartbeat));

    /* push data into db */
    query << "insert into msg_heartbeat values (" 
          << hb->msg.num << ", "
          << hb->st.longitude << ", "
          << hb->st.latitude << ", "
          << hb->st.heading << ", "
          << hb->st.baroaltabs << ", "
          << hb->st.baroaltrel << ", "
          << hb->st.gpsalt << ", "
          << hb->st.temperature << ", "
          << hb->st.voltage << ", "
          << hb->st.current << ", "
          << hb->st.boardtime << ", "
          << (int)hb->st.gsmlevel  << ", "
          << hb->st.last_msgnum << ", "
          << (int)hb->st.denial << ", "
          << hb->st.srv.channel[0]  << ", "
          << hb->st.srv.channel[1]  << ", "
          << hb->st.srv.channel[2]  << ", "
          << hb->st.srv.channel[3]  << ", "
          << hb->st.srv.channel[4]  << ", "
          << hb->st.srv.channel[5]  << ", "
          << hb->st.gpsspeed  << ", "
          << (int)hb->st.status << ")";

    if ( mysql_query( conn, query.str( ).c_str( )) ){
            cerr << query.str( ) << " failed: " << mysql_error( conn) << endl;
    }

    delete hb;

    return;
}

void conf_request( void* buf)
{
    return;
}

void confirm( void* buf)
{
    return;
}

void report( void* buf)
{
    return;
}

