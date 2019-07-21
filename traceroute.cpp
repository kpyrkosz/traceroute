/*
Krzysztof Pyrkosz
261282
*/

#include <traceroute.hpp>
#include <unistd.h>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <set>

traceroute::traceroute(const net_actor& destination)
  : destination_(destination)
{
}

void traceroute::run()
{
  int unique_id = getpid();
  for(int ttl = 1; ttl < 32; ++ttl)
  {
    std::vector<request> requests;
    for(int i = 0; i < 3; ++i)
      requests.push_back(request(unique_id, 3 * ttl + i));

    std::vector<reply> replies = socket_.collect_replies(requests, 1, ttl, destination_);
    std::cout << ttl << ". ";
    if(replies.empty())
    {
      std::cout << "*\n";
      continue;
    }

    unsigned average_time = std::accumulate(replies.begin(), replies.end(), 0, [](unsigned acc, const reply & r)
    {
      return acc + r.get_ms_rtt();
    }) / replies.size();

    std::set<std::string> unique_reply_ips;
    for (const auto& rep : replies)
    {
      std::string sender_ip = rep.get_sender().ip_as_string();
      if (unique_reply_ips.insert(sender_ip).second)
        std::cout << sender_ip.c_str() << ' ';
    }

    if(replies.size() == requests.size())
      std::cout << average_time << " ms\n";
    else
      std::cout << "???\n";

    if(unique_reply_ips.find(destination_.ip_as_string()) != unique_reply_ips.end())
      return;
  }
}
