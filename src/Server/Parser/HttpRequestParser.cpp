#include "HttpRequestParser.hpp"

void HttpRequestParser::parse(EventInfo& event_info) {
  _end = false;
  _cgi = false;

  if (event_info.responseMaterial() == NULL)
    event_info.responseMaterial() = new HttpRequest;  // !

  HttpRequest& req = dynamic_cast<HttpRequest&>(*event_info.responseMaterial());
  std::string  line;
  std::getline(event_info.storage(), line);  // ?
  // somthing good http parsing code

  if (line == "cgi\r")  // !
    req.target() = "cgi";

  if (_isHeaderEnd(req, line) && _isBodyEnd())
    _end = true;
  if (_isCgi(req))
    _cgi = true;
}

bool HttpRequestParser::_isHeaderEnd(HttpRequest& req, const std::string& line) {
  if (line.c_str()[0] == '\r')
    req.end() = true;
  return req.end();
}

bool HttpRequestParser::_isCgi(HttpRequest& req) { return req.target() == "cgi"; }  // !
