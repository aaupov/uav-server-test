#include "handler.h"

handler::handler()
{
    conn = new db_connection;
}

handler::~handler()
{
    delete conn;
}

void 
handler::deduce_type(const char* buf) const
{
    struct message* header = new struct message;
    memcpy( header, buf, sizeof( struct message));

    /** Only allow DCP messages */
    if (header->proto != Proto_Dispatcher)
    {
        log_err() << header->num 
                  << ": unhandled protocol " 
                  << header->proto;
        return;
    }
    log_norm() << header->num 
               << ": " 
               << header->type;

    switch ( header->type )
    {
        case Msg_Heartbeat:{
            const struct msg_heartbeat* hb = typecast<struct msg_heartbeat>(buf);
            if (okchecksum(hb))
                heartbeat(hb);
            break;
            }

        case Msg_ReqConfirm:{
            const struct msg_reqconfirm* rc = typecast<struct msg_reqconfirm>(buf);
            if (okchecksum(rc))
                conf_request(rc);
            break;
            }

        case Msg_Confirm:{
            const struct msg_confirm* conf = typecast<struct msg_confirm>(buf);
            if (okchecksum(conf))
                confirm(conf);
            break;
            }

        case Msg_Report:{
            const struct msg_report* rep = typecast<struct msg_report>(buf);
            if (okchecksum(rep))
                report(rep);
            break;
            }

        default:
            log_err() << header->num 
                      << ": unhandled message type " 
                      << header->type;
            return;
    }
    
    delete header;
}

void 
handler::heartbeat(const struct msg_heartbeat* msg) const
{
    std::stringstream query;
    /* create query message */
    query << "insert into msg_heartbeat values (" 
          << msg->msg.num << ", "
          << msg->st.longitude << ", "
          << msg->st.latitude << ", "
          << msg->st.heading << ", "
          << msg->st.baroaltabs << ", "
          << msg->st.baroaltrel << ", "
          << msg->st.gpsalt << ", "
          << msg->st.temperature << ", "
          << msg->st.voltage << ", "
          << msg->st.current << ", "
          << msg->st.boardtime << ", "
          << (int)msg->st.gsmlevel  << ", "
          << msg->st.last_msgnum << ", "
          << (int)msg->st.denial << ", "
          << msg->st.srv.channel[0]  << ", "
          << msg->st.srv.channel[1]  << ", "
          << msg->st.srv.channel[2]  << ", "
          << msg->st.srv.channel[3]  << ", "
          << msg->st.srv.channel[4]  << ", "
          << msg->st.srv.channel[5]  << ", "
          << msg->st.gpsspeed  << ", "
          << (int)msg->st.status << ", "
          << msg->st.roll << ", "
          << msg->st.pitch << ")";

    /* push data into db */
    conn->query( query.str( ));

    return;
}

void 
handler::conf_request(const struct msg_reqconfirm* msg) const
{
    return;
}

void 
handler::confirm(const struct msg_confirm* msg) const
{
}

void 
handler::report(const struct msg_report* msg) const
{
}

/** Nasty bytes manipulation */
uint32_t 
handler::byte_repres(const uint8_t* obj, size_t size) const
{
    uint32_t result = 0;
    for ( const uint8_t* tmp = obj; tmp < obj + size; result += *tmp++ );

    return result;
}
