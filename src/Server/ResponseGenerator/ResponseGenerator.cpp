#include "ResponseGenerator.hpp"

#include "EventInfo.hpp"

void ResponseGenerator::response(std::vector<EventInfo*>& event_info) {
  std::vector<EventInfo*>::iterator it = event_info.begin();

  for (; it != event_info.end(); ++it) {
    EventInfo&         event_info       = **it;
    ResponseGenerator& actual_generator = *(event_info.responseGenerator());
    actual_generator.response(event_info);
  }
}
