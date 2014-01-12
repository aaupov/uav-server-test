//#pragma once
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include "handler.h"

using boost::asio::ip::udp;

class udp_server
{
    static const int kPort = 51000;

public:
    /* Initialise a socket to listen on UDP port kPort. */
    udp_server(boost::asio::io_service& io_service, handler net_disp) : 
        socket_(io_service, udp::endpoint(udp::v4(), kPort))
    {
        network_dispatcher = net_disp;
        start_receive();
    }

private:
    /* Asynchronously receive messages */
    void start_receive();
    /* Service the received message */
    void handle_receive(const boost::system::error_code&, /*error*/
            std::size_t /*bytes transferred*/);
    /* Asynchronously send messages */
    void start_send();
    /* handle_send is invoked after the service request has been completed. */
    void handle_send(boost::shared_ptr<std::string>, /*message*/
            const boost::system::error_code&, /*error*/
            std::size_t /*bytes transferred*/);

    static const int kMaxMessageSize = 256;
    udp::socket socket_;
    udp::endpoint remote_endpoint_;
    boost::array<char, kMaxMessageSize> recv_buffer_;
    handler network_dispatcher;
};
