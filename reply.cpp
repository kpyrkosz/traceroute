/*
Krzysztof Pyrkosz
261282
*/

#include <reply.hpp>

reply::reply(unsigned ms_round_trip_time, const sockaddr_in& sender_ip)
  : ms_round_trip_time_(ms_round_trip_time),
    sender_(sender_ip)
{
}

const net_actor& reply::get_sender() const
{
  return sender_;
}

unsigned reply::get_ms_rtt() const
{
  return ms_round_trip_time_;
}
