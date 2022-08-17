#include <fcntl.h>

#include <iostream>
#include <sstream>

#include "EventInfo.hpp"
#include "HttpRequestParser.hpp"
#include "HttpResponseGenerator.hpp"
#include "Log.hpp"
#include "Receiver.hpp"
#include "Sender.hpp"

namespace ft {
extern Log logger;
}  // namespace ft

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "plz input only port!" << std::endl;
    return 1;
  }

  int                      kq        = kqueue();
  int                      listen_fd = socket(AF_INET, SOCK_STREAM, 0);
  ResponseGenerator        generator;
  std::vector<EventInfo *> event_list;  // iter -> free
  Parser                   parser;
  HttpResponseGenerator    hrg;
  CgiResponseParser        crp;
  CgiToHttpTransformer     ctht;
  Sender                   sender(kq, &crp, &ctht);
  HttpRequestParser        hrp(&sender);
  Receiver                 receiver(kq, listen_fd, &hrp, &hrg);

  fcntl(listen_fd, F_SETFL, O_NONBLOCK);
  EventInfo    *event_info = new EventInfo(-1, listen_fd, &hrp, &hrg);
  struct kevent ev;
  EV_SET(&ev, listen_fd, EVFILT_READ, EV_ADD, 0, 0, event_info);
  kevent(kq, &ev, 1, NULL, 0, NULL);  // ERROR CHECK

  sockaddr_in server_addr;
  bzero(&server_addr, sizeof(server_addr));
  server_addr.sin_family      = AF_INET;
  server_addr.sin_port        = htons(std::atoi(argv[1]));
  server_addr.sin_addr.s_addr = INADDR_ANY;

  int ret;

  ft::logger(bind(listen_fd, SOCKADDR(server_addr), sizeof(server_addr)), "main: bind: ");
  ft::logger(listen(listen_fd, BACKLOG), "main: listen: ");
  ft::logger << "Server: listening.." << std::endl;

  while (1) {
    receiver.listen(event_list);
    parser.parse(event_list);
    generator.response(event_list);
    sender.sendClient(event_list);
    event_list.clear();
    ft::logger << "Server: Event list clear" << std::endl;
  }
}
