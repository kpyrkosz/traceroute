CXX = g++
CXXFLAGS = -O2 -Wall -Wextra -std=c++11 -Werror -I.
LDLIBS = -lstdc++
TARGETS = traceroute

all: traceroute

traceroute: main.o net_actor.o reply.o request.o net_socket.o deserializer.o traceroute.o

main.o: main.cpp

net_actor.o: net_actor.cpp

reply.o: reply.cpp

request.o: request.cpp

net_socket.o: net_socket.cpp

deserializer.o: deserializer.cpp

traceroute.o: traceroute.cpp

clean:
	rm -f *.o

distclean: clean
	rm -f $(TARGETS)
