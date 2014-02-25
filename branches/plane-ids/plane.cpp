#include "plane.h"

plane::plane()
{
    id = 1;
    command_state = STATE_NONE;
    last_command = 0;
    route = 0;
}

unsigned int
plane::getId()
{
    return id;
}

command_state_e 
plane::getCommandState()
{
    return command_state;
}

bool
plane::setCommandState(command_state_e st)
{
    return true;
}

void
plane::send(base_command* cmd)
{
    /* Send to associated endpoint */
}

unsigned int 
plane::getLastCommand()
{
    return last_command;
}
