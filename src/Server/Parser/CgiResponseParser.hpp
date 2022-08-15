#if !defined(CgiResponsePaser_hpp)
#define CgiResponsePaser_hpp

#include "Parser.hpp"

class CgiResponseParser : public Parser {
  // Member Variable
 private:
  pid_t _pid;
  // Constructor
 public:
  CgiResponseParser() : Parser(NULL) {}

  // Interface
 public:
  void parse(EventInfo& event_info);
  bool isEnd();
  bool isCgi() { return false; }
};

#endif  // HttpRequestPaser.hpp