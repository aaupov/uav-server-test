#pragma once
#include <sstream>
#include <cstring>
#include "dcp.h"
#include "mysql_connection.h"

void heartbeat( void* buf, db_connection* conn);
void conf_request( void* buf);
void confirm( void* buf);
void report( void* buf);

extern uint32_t byte_repres( const uint8_t*, size_t);

template< typename T>
int checksum( const uint8_t* buf) 
{
    const T* msg = reinterpret_cast<const T*>( buf); 
    const uint32_t* checksum_offset = &msg->msg.checksum;

    uint32_t checksum = byte_repres( buf, sizeof( T)), 
             reference = *checksum_offset;
    checksum -= byte_repres( ( const uint8_t*)checksum_offset, 
                             sizeof( *checksum_offset));

    return ( reference - checksum );
}

