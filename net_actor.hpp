/*
Krzysztof Pyrkosz
261282
*/

#pragma once

#include <string>
extern "C"
{
#include <netinet/ip.h>
}

class net_actor
{
    sockaddr_in address_;

  public:

    net_actor(const sockaddr_in& address);
    net_actor(const std::string& text_ip);
    const sockaddr_in& get_address() const;
    std::string ip_as_string() const;
};
