#include "plane.h"

plane::plane()
{
    id = 1;
    command_state = STATE_NONE;
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
}

void
plane::send(class command cmd)
{
}
