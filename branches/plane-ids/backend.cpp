#include "logger.h"
#include "network.h"
#include "handler.h"
#include <thread>

void db_poll(database* db)
{
    while (true)
    {
        db->command_poll();
        sleep(1);
    }
}

int main() {
    /* Database connection */
    database* db = new database;
    try
    {
        /* Create network message handler object */
        handler network_dispatcher(db);
        /* Create a server object to accept incoming client requests, 
         * and run the io_service object. */
        boost::asio::io_service io_service;
        udp_server server(io_service, network_dispatcher);
        /* Run DB poller, in a loop :( */
        std::thread db_poll_thread(db_poll, db);
        db_poll_thread.join();
        io_service.run();
    }
    catch (std::exception& e)
    {
        log_err() << e.what();
    }

    log_norm() << "Server terminated";
    return 0;
}

