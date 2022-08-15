#if !defined(ResponseGenerator_hpp)
#define ResponseGenerator_hpp

#include <vector>

class EventInfo;

class ResponseGenerator {
  // Constructor
 public:
  ResponseGenerator() {}
  // Interface
 public:
  void         response(std::vector<EventInfo*>& event_info);
  virtual void response(EventInfo& event_info) {}
};

#endif  // ResponseGenerator
