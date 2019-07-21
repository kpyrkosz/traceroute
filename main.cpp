/*
Krzysztof Pyrkosz
261282
*/

#include <traceroute.hpp>
#include <stdexcept>
#include <iostream>

int main(int argc, char** argv)
{
  if(argc != 2)
  {
    std::cerr << "Usage: " << argv[0] << " ip\n";
    return EXIT_FAILURE;
  }
  try
  {
    net_actor destination(argv[1]);
    traceroute tr(destination);
    tr.run();
    return 0;
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
    return -1;
  }
  return 0;
}
