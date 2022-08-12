#if !defined(Receiver_hpp)
#define Receiver_hpp

#include <sys/event.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <sstream>
#include <vector>
#include "HttpRequestParser.hpp"
#include "EventInfo.hpp"
#include <unistd.h>
#include <iostream>
#include "macro.hpp"
#include <fcntl.h>

class Receiver {
    private:
        int _kq;
        int _listen_fd;
        HttpRequestParser *_hrp;
        timespec _wait;

    // Constructor
    public:
        Receiver(int kq, int listen_fd, HttpRequestParser* hrp);

    // Method
    private:
        void _deleteEvent(struct kevent* ev, EventInfo& event_info);
        void _acceptEvent();
        void _readEvent(std::vector<EventInfo *>& event_list, EventInfo& event_info);

    // Interface
    public:
        std::vector<EventInfo *> listen();
};


#endif // Receiver_hpp
