#pragma once
#include <sstream>
#include <cstring>
#include "dcp.h"
#include "mysql_connection.h"

void heartbeat( void* buf, db_connection* conn);
void conf_request( void* buf);
void confirm( void* buf);
void report( void* buf);
