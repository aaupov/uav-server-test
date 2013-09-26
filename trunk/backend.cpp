#include <iostream>
#include <netinet/in.h>
#include <errno.h>
#include "dcp.h"
#include "handler.h"
#include "mysql_connection.h"
#include "logger.h"

using std::cout;
using std::endl;

int main() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    char* buf = new char[256];
    struct message* header = new struct message;
    struct sockaddr_in addr_sr = {0};
    db_connection* conn = new db_connection;

    addr_sr.sin_family = AF_INET;
    addr_sr.sin_port = htons(51000);
    addr_sr.sin_addr.s_addr = INADDR_ANY;

    if ( bind (sock, reinterpret_cast<const struct sockaddr*>(&addr_sr), 
               sizeof addr_sr) )
    {
        log_err() << "Unable to bind: " << strerror( errno);
        return 1;
    }

    while ( 1 ){
        if ( recvfrom( sock, buf, 256, 0, NULL, NULL) == -1 )
        {
            log_err() << "Error while listening to socket:" << strerror( errno);
            return 1;
        }
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

        /** Checksum verification? */

        /** 
         * Distinguish messages by type, 
         * then pass buffer to appropriate handler
         */
        switch ( header->type )
        {
            case Msg_Heartbeat:
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
    }

    delete buf;
    cout << "Server terminated" << endl;
    return 0;
}

