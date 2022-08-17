#include "CgiResponseParser.hpp"

#include <iostream>

#include "CgiResponse.hpp"
#include "EventInfo.hpp"

void CgiResponseParser::parse(EventInfo& event_info) {
  _pid = event_info.pid();

  if (event_info.responseMaterial() == NULL)
    event_info.responseMaterial() = new CgiResponse;  // !

  CgiResponse& res = dynamic_cast<CgiResponse&>(*event_info.responseMaterial());
}  // !

bool CgiResponseParser::isEnd() {
  int ws;
  int ret = ft::logger(waitpid(_pid, &ws, WNOHANG), "CgiResponseParser: waitpid:");  // cgi fail?
  if (ret == 0) {
    return false;
  }
  return true;
}
