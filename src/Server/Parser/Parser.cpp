#include "Parser.hpp"

#include "EventInfo.hpp"
#include "Sender.hpp"

void Parser::_eraseElementOnIter(std::vector<EventInfo*>::iterator& it,
                                 std::vector<EventInfo*>&           event_list) {
  --it;
  event_list.erase(it + 1);
}

void Parser::parse(std::vector<EventInfo*>& event_list) {
  std::vector<EventInfo*>::iterator it = event_list.begin();
  for (; it != event_list.end(); ++it) {
    EventInfo& event_info    = **it;
    Parser&    actual_parser = *(event_info.parser());
    actual_parser.parse(event_info);
    if (actual_parser.isEnd() && actual_parser.isCgi()) {
      _sender->callCgi(event_info);
      _eraseElementOnIter(it, event_list);
    } else if (actual_parser.isEnd() == false) {
      _eraseElementOnIter(it, event_list);
    }
  }
}
