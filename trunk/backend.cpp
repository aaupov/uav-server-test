#include "dcp.h"
#include "handler.h"
#include "mysql_connection.h"
#include "logger.h"
#include "socket.h"
#include <cstring>

int main() {
    char* buf;
    struct message* header = new struct message;
    db_connection* conn = new db_connection;
    net_connection* net_conn = new net_connection;

    while ( 1 ){
        buf = net_conn->receive( );
        memcpy( header, buf, sizeof( struct message));

        /**
         * Parse header
         */

        /** Only allow DCP messages */
        if ( header->proto != Proto_Dispatcher )
        {
            log_err() << header->num << ": unhandled protocol " << header->proto;
            continue;
        }

        /** 
         * Distinguish messages by type, 
         * then pass buffer to appropriate handler, calculate checksum there.
         */
        switch ( header->type )
        {
            case Msg_Heartbeat:
                if ( checksum<struct msg_heartbeat>( (const uint8_t*)buf) )
                {
                    log_err() << "Incorrect checksum";
                    continue;
                }
                heartbeat( buf, conn);
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
                log_err() << header->num << ": unhandled message type " << header->type;
                continue;
        }
        delete buf;
    }

    log_norm() << "Server terminated";
    return 0;
}

