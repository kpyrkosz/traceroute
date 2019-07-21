/*
Krzysztof Pyrkosz
261282
*/

#pragma once

#include <net_socket.hpp>

class traceroute
{
    net_socket socket_;
    const net_actor destination_;

  public:

    traceroute(const net_actor& destination);
    void run();
};
