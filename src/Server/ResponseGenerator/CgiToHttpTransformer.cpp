#include "CgiToHttpTransformer.hpp"

#include <unistd.h>

#include <iostream>

#include "CgiResponse.hpp"
#include "EventInfo.hpp"
#include "macro.hpp"

void CgiToHttpTransformer::response(EventInfo& event_info) {  // !

  CgiResponse& cgi_response = dynamic_cast<CgiResponse&>(*event_info.responseMaterial());

  int  infd = event_info.fromFd();
  char buffer[BUFFER_SIZE];
  int  read_size = read(infd, buffer, BUFFER_SIZE - 1);
  while (read_size > 0) {
    buffer[read_size] = 0;
    event_info.storage() << buffer;
    read_size = read(infd, buffer, BUFFER_SIZE - 1);
  }

  return;
}