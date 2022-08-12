#if !defined(Sender_hpp)
#define Sender_hpp

#include <sys/event.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <sstream>
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

void Sender::sendClient(std::vector<EventInfo *>& event_list){
    std::vector<EventInfo *>::iterator it = event_list.begin();

    for(; it != event_list.end(); ++it) {
        EventInfo& event_info = **it;
        std::string to_send;
        event_info.storage() >> to_send;
        std::cout << "Server: send to client: '" << to_send <<"' length: " << to_send.length()  << std::endl;
        send(event_info.toFd(), to_send.c_str(), to_send.length(), 0);
    }
}

#endif // Sender_hpp

