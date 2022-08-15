#if !defined(Sender_hpp)
#define Sender_hpp

#include <fcntl.h>
#include <netinet/in.h>
#include <sys/event.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>

#include "CgiResponseParser.hpp"
#include "CgiToHttpTransformer.hpp"
#include "EventInfo.hpp"

class Sender {
 private:
  int                   _kq;
  CgiResponseParser*    _crp;
  CgiToHttpTransformer* _ctht;

  // Constructor
 public:
  Sender(int kq, CgiResponseParser* crp, CgiToHttpTransformer* ctht) : _kq(kq), _crp(crp), _ctht(ctht) {}

  // Method
 private:
  void _registerEvent(int to_fd, int from_fd);
  void _deleteEvent(EventInfo& event_info);

  // Interface
 public:
  void sendClient(std::vector<EventInfo*>& event_list);
  void callCgi(EventInfo& event_info);
};

#endif  // Sender_hpp
