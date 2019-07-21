/*
Krzysztof Pyrkosz
261282
*/

#pragma once

#include <request.hpp>
#include <net_actor.hpp>
#include <reply.hpp>
#include <vector>

class net_socket
{
    int sockfd_;

    void set_ttl(int ttl);
    void send_single_packet(const std::string& raw_data, const sockaddr_in& recipient);

  public:

    net_socket();
    std::vector<reply> collect_replies(const std::vector<request>& requests, unsigned sec_timeout, int ttl, const net_actor& final_destination);
};
