#if !defined(Receiver_hpp)
#define Receiver_hpp

#include <fcntl.h>
#include <netinet/in.h>
#include <sys/event.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>

#include "EventInfo.hpp"
#include "HttpRequestParser.hpp"
#include "HttpResponseGenerator.hpp"
#include "Log.hpp"
#include "macro.hpp"

class Receiver {
 private:
  int                    _kq;
  int                    _listen_fd;
  HttpRequestParser*     _hrp;
  HttpResponseGenerator* _hrg;
  timespec               _wait;

  // Constructor
 public:
  Receiver(int kq, int listen_fd, HttpRequestParser* hrp, HttpResponseGenerator* hrg);

  // Method
 private:
  void _deleteEvent(struct kevent* ev, EventInfo& event_info);
  void _acceptEvent();
  void _readEvent(std::vector<EventInfo*>& event_list, EventInfo& event_info);

  // Interface
 public:
  void listen(std::vector<EventInfo*>& event_list);
};

#endif  // Receiver_hpp
