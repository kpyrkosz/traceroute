/*
Krzysztof Pyrkosz
261282
*/
#pragma once

#include <string>

class request
{
    std::string packet_;
    const unsigned char unique_id_;
    const unsigned char sequence_id_;

  public:

    request(unsigned char unique_id, unsigned char sequence_id);
    const std::string& get_as_bytes() const;
    unsigned char get_unique_id() const;
    unsigned char get_sequence_id() const;
};
