#pragma once
#include <sstream>
#include <cstring>
#include <stdexcept>
#include "dcp.h"
#include "logger.h"
#include "database.h"

class handler
{
    /* DB connection */
    database* conn;
    /* Cast buffer pointer to specified message type pointer */
    template<typename T> const T* typecast(const char* buf) const;
    /* Checksum verification */
    template<typename T> bool okchecksum(const T* msg) const;
    /* Utility function for checksum computation */
    uint32_t byte_repres(const uint8_t*, size_t) const;

    /* Handler functions for different message types */
    void heartbeat(const struct msg_heartbeat* msg) const;
    void conf_request(const struct msg_reqconfirm* msg) const;
    void confirm(const struct msg_confirm* msg) const;
    void report(const struct msg_report* msg) const;

public:
    handler(database* db);
    /* Deduce type for buffer and call appropriate handler */
    void deduce_type(const char* buf) const;
};


template<typename T>
bool 
handler::okchecksum(const T* msg) const
{
    uint32_t checksum, reference = msg->msg.checksum;
    T msg_with_zero_checksum = *msg;

    msg_with_zero_checksum.msg.checksum = 0;
    checksum = byte_repres(
            reinterpret_cast<const uint8_t*>(&msg_with_zero_checksum), 
            sizeof(T));

    if (reference == checksum)
        return true;

    log_err() << "Incorrect checksum: "
              << checksum 
              << ", reference= "
              << reference;
    return false;
}

template<typename T> 
const T* 
handler::typecast(const char* buf) const
{
    const T* obj = reinterpret_cast<const T*>(buf);
    okchecksum<T>(obj);
    return obj;
}
