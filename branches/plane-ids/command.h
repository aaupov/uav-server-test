#pragma once
extern "C" 
{
#include "dcp.h"
}
#include <cstdlib>

class base_command
{
protected:
    msg_dcp_types type;
};

class raw_command : public base_command
{
protected:
    struct msg_raw* message;
};

class newRoute : public base_command
{
    struct msg_route* message;
public:
    newRoute(uint16_t count, struct checkpoint* queue);
    ~newRoute()
    {
        free(message);
    }
};

class cleanRoute : public raw_command
{
public:
    cleanRoute();
};

class updateCheckpoint : public base_command
{
    struct msg_updcpt* message;
public:
    updateCheckpoint(uint16_t routenum, struct checkpoint pt);
    ~updateCheckpoint()
    {
        free(message);
    }
};

class correctZeroBaroAlt : public base_command
{
    struct msg_zerobaroalt* message;
public:
    correctZeroBaroAlt(uint16_t zerobaroalt);
    ~correctZeroBaroAlt()
    {
        free(message);
    }
};

class confirmRequest : public base_command
{
    struct msg_reqconfirm* message;
public:
    confirmRequest(uint16_t cmdnum);
    ~confirmRequest()
    {
        free(message);
    }
};

class confirm : public base_command
{
    struct msg_confirm* message;
public:
    confirm(uint16_t cmdnum, uint8_t status);
    ~confirm()
    {
        free(message);
    }
};

class report : public base_command
{
    struct msg_report* message;
public:
    report(uint16_t cmdnum, uint8_t report);
    ~report()
    {
        free(message);
    }
};

class setManualMode : public raw_command
{
public:
    setManualMode();
};

class setAutomaticMode : public raw_command
{
public:
    setAutomaticMode();
};

class emergency : public raw_command
{
public:
    emergency();
};
