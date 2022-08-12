#if !defined(Sender_hpp)
#define Sender_hpp

#include <sys/event.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <sstream>
#include <iostream>
#include <vector>
#include "HttpRequestParser.hpp"
#include "EventInfo.hpp"
#include <unistd.h>

class Sender{
    private:
        int _kq;

    // Constructor
    public:
        Sender(int kq) : _kq(kq) {}
    
    // Interface
    public:
        void sendClient(std::vector<EventInfo *>& event_list);
};

#endif // Sender_hpp

