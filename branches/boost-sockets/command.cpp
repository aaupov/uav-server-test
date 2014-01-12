#include "command.h"

newRoute::newRoute(uint16_t count, struct checkpoint* queue)
{
    type = Msg_NewRoute;
    message = cmd_route(count, queue);
}

cleanRoute::cleanRoute()
{
    type = Msg_CleanRoute;
    message = cmd_cleanroute();
}

setManualMode::setManualMode()
{
    type = Msg_HandOn;
    message = cmd_handon();
}

setAutomaticMode::setAutomaticMode()
{
    type = Msg_HandOff;
    message = cmd_handoff();
}

updateCheckpoint::updateCheckpoint(uint16_t routenum, struct checkpoint pt)
{
    type = Msg_UpdatePoint;
    message = cmd_updcpd(routenum, pt);
}

report::report(uint16_t cmdnum, uint8_t report)
{
    type = Msg_Report;
    message = cmd_report(cmdnum, report);
}

correctZeroBaroAlt::correctZeroBaroAlt(uint16_t zerobaroalt)
{
    type = Msg_ZeroBaroAlt;
    message = cmd_zerobaroalt(zerobaroalt);
}

confirmRequest::confirmRequest(uint16_t cmdnum)
{
    type = Msg_ReqConfirm;
    message = cmd_reqconfirm(cmdnum);
}

confirm::confirm(uint16_t cmdnum, uint8_t status)
{
    type = Msg_Confirm;
    message = cmd_confirm(cmdnum, status);
}
