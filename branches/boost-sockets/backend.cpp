#include "logger.h"
#include "network.h"
#include "handler.h"

int main() {
    try
    {
        /* Create network message handler object */
        handler network_dispatcher;
        /* Create a server object to accept incoming client requests, 
         * and run the io_service object. */
        boost::asio::io_service io_service;
        udp_server server(io_service, network_dispatcher);
        io_service.run();
    }
    catch (std::exception& e)
    {
        log_err() << e.what();
    }

    log_norm() << "Server terminated";
    return 0;
}
