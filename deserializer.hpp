/*
Krzysztof Pyrkosz
261282
*/

#pragma once

extern "C"
{
#include <netinet/ip_icmp.h>
}

namespace deserializer
{
const icmphdr* icmphdr_from_raw_packet(const u_int8_t* buffer, int length);
}
