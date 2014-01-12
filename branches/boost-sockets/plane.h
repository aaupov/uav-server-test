#include "dcp.h"
#include "command.h"
#include "network.h"

enum command_state_e
{
    STATE_NONE,
    STATE_CONFIRM_PENDING,
    STATE_CONFIRMED
};

class plane
{
    unsigned int id;
    command_state_e command_state;
    struct state state;
public:
    plane();
    unsigned int getId();
    command_state_e getCommandState();
    bool setCommandState(command_state_e st);
    void send(class command cmd);
    void updateDBRecord();
};
