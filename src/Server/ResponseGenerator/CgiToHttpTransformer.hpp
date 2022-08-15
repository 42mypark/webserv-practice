#if !defined(CgiToHttpTransformer_hpp)
#define CgiToHttpTransformer_hpp

#include "ResponseGenerator.hpp"

class EventInfo;

class CgiToHttpTransformer : public ResponseGenerator {
  // Interface
 public:
  void response(EventInfo& event_info);
};

#endif  // CgiToHttpTransformer