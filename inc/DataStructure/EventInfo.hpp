#if !defined(EventInfo_hpp)
#define EventInfo_hpp

#include <sstream>

#include "Parser.hpp"
#include "ResponseGenerator.hpp"

class EventInfo {
 private:
  const int          _to_fd;
  int                _from_fd;
  std::stringstream  _storage;
  bool               _empty_line;
  Parser*            _parser;
  ResponseGenerator* _response_generator;
  ResponseMaterial*  _response_material;

 public:
  EventInfo(int to_fd, int from_fd, Parser* p, ResponseGenerator* rg)
      : _to_fd(to_fd), _from_fd(from_fd), _empty_line(false), _parser(p), _response_generator(rg), _response_material(NULL) {}
  const int           toFd() const { return _to_fd; }
  int&                fromFd() const { return _from_fd; }
  bool&               emptyLine() const { return _empty_line; }
  Parser*&            parser() const { return _parser; }
  ResponseGenerator*& responseGenerator() const { return _response_generator; }
  ResponseMaterial*&  responseMaterial() const { return _response_material; }
  std::stringstream&  storage() const { return _storage; }
};

#endif  // EventInfo_hpp
