#if !defined(CgiToHttpTransformer_hpp)
#define CgiToHttpTransformer_hpp

#include "ResponseGenerator.hpp"
#include "Log.hpp"

namespace ft {
extern Log logger;
}  // namespace ft

class EventInfo;

class CgiToHttpTransformer : public ResponseGenerator {
  // Interface
 public:
  void response(EventInfo& event_info);
};

#endif  // CgiToHttpTransformer