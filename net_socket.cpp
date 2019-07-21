/*
Krzysztof Pyrkosz
261282
*/

#include <net_socket.hpp>
#include <stdexcept>
#include <cstring>
#include <deserializer.hpp>

void net_socket::set_ttl(int ttl)
{
  if(setsockopt(sockfd_, IPPROTO_IP, IP_TTL, &ttl, sizeof(int)) != 0)
    throw std::runtime_error(std::string("setsockopt error ") + strerror(errno));
}

void net_socket::send_single_packet(const std::string& raw_data, const sockaddr_in& recipient)
{
  if(sendto(sockfd_, (const u_int8_t*)raw_data.data(), raw_data.size(), 0, (const sockaddr*)&recipient, sizeof(sockaddr_in)) < 0)
    throw std::runtime_error(std::string("sendto error ") + strerror(errno));
}

net_socket::net_socket()
{
  sockfd_ = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
  if(sockfd_ == -1)
    throw std::runtime_error(std::string("socket error ") + strerror(errno));
}

std::vector<reply> net_socket::collect_replies(const std::vector<request>& requests, unsigned sec_timeout, int ttl, const net_actor& final_destination)
{
  set_ttl(ttl);
  for(const auto& req : requests)
    send_single_packet(req.get_as_bytes(), final_destination.get_address());

  u_int8_t buffer[IP_MAXPACKET];
  sockaddr_in sender;
  timeval time_limit = {};
  time_limit.tv_sec = sec_timeout;
  std::vector<reply> replies;

  while(1)
  {
    fd_set sockfd_set;
    FD_ZERO(&sockfd_set);
    FD_SET(sockfd_, &sockfd_set);
    int ready = select(sockfd_ + 1, &sockfd_set, NULL, NULL, &time_limit);

    if(ready == -1)
      throw std::runtime_error(std::string("select error ") + strerror(errno));

    if(ready == 0)
      return replies;

    socklen_t sender_len = sizeof(struct sockaddr_in);
    int bytecount = recvfrom(sockfd_, buffer, IP_MAXPACKET, 0, (struct sockaddr*)&sender, &sender_len);

    if(bytecount == -1)
      throw std::runtime_error(std::string("recvfrom error ") + strerror(errno));

    const icmphdr* header = deserializer::icmphdr_from_raw_packet(buffer, bytecount);
    if(header == nullptr)
      throw std::runtime_error("received packet malformed");

    for(const auto& req : requests)
      if(req.get_unique_id() == header->un.echo.id && req.get_sequence_id() == header->un.echo.sequence)
        replies.push_back(reply(1000 * sec_timeout - time_limit.tv_usec / 1000, sender));

    if(replies.size() == requests.size())
      return replies;
  }
}
