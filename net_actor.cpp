/*
Krzysztof Pyrkosz
261282
*/

#include <net_actor.hpp>
#include <stdexcept>
#include <cstring>
#include <arpa/inet.h>

net_actor::net_actor(const sockaddr_in& address)
  : address_(address)
{
}

net_actor::net_actor(const std::string& text_ip)
{
  bzero(&address_, sizeof(address_));
  address_.sin_family = AF_INET;
  if(inet_pton(AF_INET, text_ip.c_str(), &address_.sin_addr) != 1)
    throw std::invalid_argument("inet_pton - input string is not a valid IP address");
}

const sockaddr_in& net_actor::get_address() const
{
  return address_;
}

std::string net_actor::ip_as_string() const
{
  std::string result;
  result.resize(INET_ADDRSTRLEN);
  if(inet_ntop(AF_INET, &(address_.sin_addr), &result[0], INET_ADDRSTRLEN) == nullptr)
    throw std::runtime_error(std::string("inet_ntop error ") + strerror(errno));
  return result;
}
