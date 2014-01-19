#include "network.h"
#include "logger.h"

void 
udp_server::start_receive()
{
    log_norm() << "udp_server::start_receive()";
    /* Listen in the background for a new request. */
    socket_.async_receive_from(
            boost::asio::buffer(recv_buffer_), remote_endpoint_,
            /* Upon receiving a request, invoke handle_receive */
            boost::bind(&udp_server::handle_receive, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred)
            );
}

void 
udp_server::handle_receive(const boost::system::error_code& error,
                           std::size_t /*size*/)
{
    log_norm() << "Received from " 
               << remote_endpoint_.address().to_string();
    if (!error)
    {
        /* Memorize remote_endpoint of current client */
        /* Pass received message to handler */
        network_dispatcher.deduce_type(recv_buffer_.data());
        /* Start listening for the next client request. */
        start_receive();
    } else {
        log_err() << error.message();
    }
}

void
udp_server::start_send()
{
#if 0
        boost::shared_ptr<std::string> message(
                new std::string(make_daytime_string()));

        /* Serve the data to the client. */
        socket_.async_send_to(
                boost::asio::buffer(*message), remote_endpoint_,
                boost::bind(
                    &udp_server::handle_send, this, message,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred)
                );
#endif
}

void 
udp_server::handle_send(boost::shared_ptr<std::string> /*message*/,
                        const boost::system::error_code& error,
                        std::size_t /*bytes_transferred*/)
{
    if (!error)
    {
    } else {
        log_err() << error.message();
    }
}
