#if !defined(Parser_hpp)
#define Parser_hpp

#include <vector>

class Sender;
class EventInfo;

class Parser {
 private:
  Sender* _sender;
  // Constructor
 public:
  Parser() : _sender(NULL) {}
  Parser(Sender* sender) : _sender(sender) {}

  // Method
 private:
  void _eraseElementOnIter(std::vector<EventInfo*>::iterator& it,
                           std::vector<EventInfo*>&           event_list);
  // Interface
 public:
  void         parse(std::vector<EventInfo*>& event_list);
  virtual void parse(EventInfo& event_info) { return; }
  virtual bool isEnd() { return false; }
  virtual bool isCgi() { return false; }
};

#endif  // PARSER
