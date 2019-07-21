/*
Krzysztof Pyrkosz
261282
*/

#include <request.hpp>
extern "C"
{
#include <netinet/ip_icmp.h>
}

request::request(unsigned char unique_id, unsigned char sequence_id)
  : unique_id_(unique_id),
    sequence_id_(sequence_id)
{
  packet_.resize(sizeof(icmphdr));
  icmphdr* header_to_fill = (icmphdr*)&packet_.front();
  header_to_fill->type = ICMP_ECHO;
  header_to_fill->code = 0;
  header_to_fill->un.echo.id = unique_id;
  header_to_fill->un.echo.sequence = sequence_id;
  header_to_fill->checksum = 0;

  const u_int16_t* ptr = (u_int16_t*)header_to_fill;
  u_int32_t sum = 0;
  for (std::size_t i = 0; i < packet_.size(); i += 2)
    sum += *ptr++;
  sum = (sum >> 16) + (sum & 0xffff);
  header_to_fill->checksum = (u_int16_t)(~(sum + (sum >> 16)));
}

const std::string& request::get_as_bytes() const
{
  return packet_;
}

unsigned char request::get_unique_id() const
{
  return unique_id_;
}

unsigned char request::get_sequence_id() const
{
  return sequence_id_;
}
