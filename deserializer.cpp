/*
Krzysztof Pyrkosz
261282
*/

#include <deserializer.hpp>

const icmphdr* deserializer::icmphdr_from_raw_packet(const u_int8_t* buffer, int length)
{
  const iphdr* ip_header = (const iphdr*)buffer;
  if(!ip_header)
    return nullptr;
  const u_int8_t* icmp_header = buffer + 4 * ip_header->ihl;
  if(icmp_header + sizeof(icmphdr) > buffer + length )
    return nullptr;
  if(((const icmphdr*)icmp_header)->type == ICMP_TIME_EXCEEDED)
    return icmphdr_from_raw_packet(buffer + 4 * ip_header->ihl + 8, length);
  return (const icmphdr*)icmp_header;
}
