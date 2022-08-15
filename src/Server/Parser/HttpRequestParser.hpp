#if !defined(HttpRequestPaser_hpp)
#define HttpRequestPaser_hpp

#include "HttpRequest.hpp"
#include "Parser.hpp"
#include "Sender.hpp"

class HttpRequestParser : public Parser {
  // Member Variable
 private:
  bool _end;
  bool _cgi;
  // Constructor
 public:
  HttpRequestParser(Sender* sender) : Parser(sender), _end(false), _cgi(false) {}

  // Method
 private:
  void parse(std::vector<EventInfo*>& event_list) {}
  bool _isHeaderEnd(HttpRequest& req, const std::string& line);
  bool _isBodyEnd() { return true; }
  bool _isCgi(HttpRequest& req);

  // Interface
 public:
  void parse(EventInfo& event_info);
  bool isEnd() { return _end; }
  bool isCgi() { return _cgi; }
};

#endif  // HttpRequestPaser.hpp
