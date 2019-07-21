/*
Krzysztof Pyrkosz
261282
*/

#pragma once

#include <net_actor.hpp>

class reply
{
    const unsigned ms_round_trip_time_;
    const net_actor sender_;

  public:

    reply(unsigned ms_round_trip_time, const sockaddr_in& sender_ip);
    const net_actor& get_sender() const;
    unsigned get_ms_rtt() const;
};
