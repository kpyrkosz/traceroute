# Traceroute

Implementation of traceroute for Linux, using ICMP packets and raw sockets. 

The full specification (in polish language) is given [here](https://github.com/KoncepcyjnyMiliarder/traceroute/blob/master/p1.pdf).

## How to use?

Make sure you have the basic c++ build packages
```
apt install build-essential g++
```

To build, simply run `make`. To clean, either `make clean` or `make distclean`. Running the traceroute requires admin privileges, because it uses raw sockets.

![Run](https://raw.githubusercontent.com/KoncepcyjnyMiliarder/traceroute/master/traceroute.png)
