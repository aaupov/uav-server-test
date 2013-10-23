#include "handler.h"

void heartbeat( void* buf, db_connection* conn)
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
          << (int)hb->st.status << ", "
          << hb->st.roll << ", "
          << hb->st.pitch << ")";

    conn->query( query.str( ));
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

/** Nasty bytes manipulation */
uint32_t byte_repres( const uint8_t* obj, size_t size)
{
    uint32_t result = 0;
    for ( const uint8_t* tmp = obj; tmp < obj + size; result += *tmp++ );

    return result;
}
