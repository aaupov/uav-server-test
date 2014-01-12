#include "dcp.h"
#include <cstdlib>

class base_command
{
protected:
    enum msg_dcp_types type;
};

class raw_command : public base_command
{
protected:
    struct msg_raw* message;
};

class newRoute : base_command
{
    struct msg_route* message;
public:
    newRoute(uint16_t count, struct checkpoint* queue);
    ~newRoute()
    {
        free(message);
    }
};

class cleanRoute : raw_command
{
public:
    cleanRoute();
};

class updateCheckpoint : base_command
{
    struct msg_updcpt* message;
public:
    updateCheckpoint(uint16_t routenum, struct checkpoint pt);
    updateCheckpoint()
    {
        free(message);
    }
};

class correctZeroBaroAlt : base_command
{
    struct msg_zerobaroalt* message;
public:
    correctZeroBaroAlt(uint16_t zerobaroalt);
    ~correctZeroBaroAlt()
    {
        free(message);
    }
};

class confirmRequest : base_command
{
    struct msg_reqconfirm* message;
public:
    confirmRequest(uint16_t cmdnum);
    ~confirmRequest()
    {
        free(message);
    }
};

class confirm : base_command
{
    struct msg_confirm* message;
public:
    confirm(uint16_t cmdnum, uint8_t status);
    ~confirm()
    {
        free(message);
    }
};

class report : base_command
{
    struct msg_report* message;
public:
    report(uint16_t cmdnum, uint8_t report);
    ~report()
    {
        free(message);
    }
};

class setManualMode : raw_command
{
public:
    setManualMode();
};

class setAutomaticMode : raw_command
{
public:
    setAutomaticMode();
};
