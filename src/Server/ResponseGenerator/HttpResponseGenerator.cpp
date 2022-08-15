#include "HttpResponseGenerator.hpp"

#include "EventInfo.hpp"
#include "HttpRequest.hpp"

void HttpResponseGenerator::response(EventInfo& event_info) {
  HttpRequest& request = dynamic_cast<HttpRequest&>(*event_info.responseMaterial());  //  try catch
  return;
}