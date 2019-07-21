# Traceroute

Implementation of traceroute for Linux, using ICMP packets and raw sockets. 

The full specification (in polish language) is given [here](https://github.com/KoncepcyjnyMiliarder/traceroute/blob/master/p1.pdf).

## How to use?

To build, simply run `make`. To clean, either `make clean` or `make distclean`. Running the traceroute requires admin privileges, because it uses raw sockets.

![Run](https://raw.githubusercontent.com/KoncepcyjnyMiliarder/traceroute/master/traceroute.png)
