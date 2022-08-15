#if !defined(HttpResponseGenerator_hpp)
#define HttpResponseGenerator_hpp
#include "ResponseGenerator.hpp"

class EventInfo;

class HttpResponseGenerator : public ResponseGenerator {
  // Interface
 public:
  void response(EventInfo& event_info);
};

#endif  // HttpResponseGenerator