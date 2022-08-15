#if !defined(HttpRequest_hpp)
#define HttpRequest_hpp
#include <string>

#include "ResponseMaterial.hpp"

class HttpRequest : public ResponseMaterial {
  // Member Variable
 private:
  std::string _target;
  bool        _end;

  // Constructor
 public:
  HttpRequest() : _end(false) {}

  // Interface
 public:
  bool&        end() { return _end; }
  std::string& target() { return _target; }
};

#endif  // HttpRequest
