#include "Sender.hpp"

void Sender::sendClient(std::vector<EventInfo*>& event_list) {
  std::vector<EventInfo*>::iterator it = event_list.begin();

  for (; it != event_list.end(); ++it) {
    EventInfo&  event_info = **it;
    std::string to_send    = event_info.storage().str();
    ft::logger << "Server: send to client: '" << to_send << "' length: " << to_send.length()
               << std::endl;
    ft::logger(send(event_info.toFd(), to_send.c_str(), to_send.length(), 0),
               "Sender: sendClient: send:");
  }
}

void Sender::callCgi(EventInfo& event_info) {
  const std::string& http_request = event_info.storage().str();
  int                fd[2];
  int                pid;
  // char* const        args[3] = {"test_cgi", const_cast<char* const>(http_request.c_str()), 0};

  pipe(fd);      // error check
  pid = fork();  // error check
  if (pid == 0) {
    close(fd[0]);                // error check
    dup2(fd[1], STDOUT_FILENO);  // error check
    close(fd[1]);
    execve("./src/Server/test_cgi", NULL, NULL);  // error check
    exit(1);
  } else {
    ft::logger << "Server: Sender: callCgi: pid = " << pid << std::endl;
    close(fd[1]);  // error check
    _registerEvent(event_info.toFd(), fd[0]);
    _deleteEvent(event_info);
  }
}

void Sender::_registerEvent(int to_fd, int from_fd) {
  fcntl(from_fd, F_SETFL, O_NONBLOCK);
  EventInfo*    event_info = new EventInfo(to_fd, from_fd, _crp, _ctht);
  struct kevent ev;
  EV_SET(&ev, from_fd, EVFILT_READ, EV_ADD, 0, 0, event_info);
  ft::logger(kevent(_kq, &ev, 1, NULL, 0, NULL), "Sender: _registerEvent: kevent:");
  ft::logger(ev, "Sender: _registerEvent:");
}

void Sender::_deleteEvent(EventInfo& event_info) {
  struct kevent ev;
  EV_SET(&ev, event_info.toFd(), EVFILT_READ, EV_DELETE, 0, 0, NULL);
  ft::logger(kevent(_kq, &ev, 1, NULL, 0, NULL), "Sender: _registerEvent: kevent:");
  delete &event_info;
  ft::logger(ev, "Sender: _deleteEvent:");
}