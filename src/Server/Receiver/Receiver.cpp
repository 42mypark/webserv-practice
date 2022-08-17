#include "Receiver.hpp"

#include <errno.h>

// Constructor
Receiver::Receiver(int kq, int listen_fd, HttpRequestParser* hrp, HttpResponseGenerator* hrg)
    : _kq(kq), _listen_fd(listen_fd), _hrp(hrp), _hrg(hrg) {
  _wait.tv_sec  = WAITMS / 1000;
  _wait.tv_nsec = (WAITMS % 1000) * 1000 * 1000;
}

// Method
void Receiver::_acceptEvent() {
  sockaddr_in client_addr;
  bzero(&client_addr, sizeof(client_addr));
  socklen_t addr_len = sizeof(client_addr);

  int client_fd = ft::logger(accept(_listen_fd, SOCKADDR(client_addr), &addr_len),
                             "Receiver: _acceptEvent: accept:");
  fcntl(client_fd, F_SETFL, O_NONBLOCK);
  EventInfo*    event_info = new EventInfo(client_fd, client_fd, _hrp, _hrg);
  struct kevent ev;
  EV_SET(&ev, client_fd, EVFILT_READ, EV_ADD, 0, 0, event_info);
  kevent(_kq, &ev, 1, NULL, 0, NULL);  // ERROR CHECK
  ft::logger(ev, "Receiver: _acceptEvent:");
  ft::logger << "Receiver: _acceptEvent: connection established with fd " << client_fd << std::endl;
}

void Receiver::_deleteEvent(struct kevent* ev, EventInfo& event_info) {
  EV_SET(ev, event_info.fromFd(), EVFILT_READ, EV_DELETE, 0, 0, NULL);
  ft::logger(*ev, "Receiver: _deleteEvent:");
  ft::logger(kevent(_kq, ev, 1, NULL, 0, NULL), "Receiver: _deleteEvent: kevent:");
  delete &event_info;
  ft::logger << "Server: connection destroyed" << std::endl;
}

void Receiver::_readEvent(std::vector<EventInfo*>& event_list, EventInfo& event_info) {
  char buffer[BUFFER_SIZE];
  int  receive_size;
  bzero(buffer, BUFFER_SIZE);
  receive_size = recv(event_info.fromFd(), buffer, BUFFER_SIZE - 1, 0);
  ft::logger << "Receiver: _readEvent: receive from client: '" << buffer
             << "' length: " << strlen(buffer) << std::endl;
  if (event_info.storage().eof()) {
    ft::logger << "Receiver: _readEvent: EventInfo: storage eof error" << std::endl;
    event_info.storage().clear();
  }
  event_info.storage() << buffer;
  event_list.push_back(&event_info);
}

// Interface
void Receiver::listen(std::vector<EventInfo*>& event_list) {
  struct kevent active_event[MAX_EVENT];
  int           invoked =
      ft::logger(kevent(_kq, NULL, 0, active_event, MAX_EVENT, &_wait), "Receiver: listen:");

  for (int i = 0; i < invoked; ++i) {
    int        event      = active_event[i].filter;
    int        flags      = active_event[i].flags;
    EventInfo& event_info = *static_cast<EventInfo*>(active_event[i].udata);
    if (flags & EV_EOF) {
      _deleteEvent(&active_event[i], event_info);
    } else if (event == EVFILT_READ) {
      if (event_info.fromFd() == _listen_fd) {
        _acceptEvent();
      } else {
        _readEvent(event_list, event_info);
      }
    }
  }
  return;
}
