#pragma once
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
    unsigned int last_command;
    /* Current route, corresponds to last 'route_flushes' in table 'route' */
    unsigned int route;
public:
    plane();
    unsigned int getId();
    command_state_e getCommandState();
    bool setCommandState(command_state_e st);
    void send(base_command* cmd);
    void updateDBRecord();
    unsigned int getLastCommand();
};
