#include "CgiToHttpTransformer.hpp"

#include "CgiResponse.hpp"
#include "EventInfo.hpp"

void CgiToHttpTransformer::response(EventInfo& event_info) {  // !
  CgiResponse& cgi_response = dynamic_cast<CgiResponse&>(*event_info.responseMaterial());
  return;
}