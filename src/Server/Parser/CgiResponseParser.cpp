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
  int ret = waitpid(_pid, &ws, WNOHANG);  // cgi fail?
  if (ret == -1) {
    std::cout << "Server: CGI Execution Error: waitpid" << std::endl;  // log
  } else if (ret == 0) {
    return false;
  }
  return true;
}
