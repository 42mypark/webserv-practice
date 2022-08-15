#if !defined(EventInfo_hpp)
#define EventInfo_hpp

#include <sys/wait.h>

#include <sstream>

#include "ResponseGenerator.hpp"
#include "ResponseMaterial.hpp"

class Parser;

class EventInfo {
 private:
  const int          _to_fd;
  int                _from_fd;
  std::stringstream  _storage;
  bool               _empty_line;
  Parser*            _parser;
  ResponseGenerator* _response_generator;
  ResponseMaterial*  _response_material;
  pid_t              _pid;

 public:
  EventInfo(int to_fd, int from_fd, Parser* p, ResponseGenerator* rg)
      : _to_fd(to_fd),
        _from_fd(from_fd),
        _empty_line(false),
        _parser(p),
        _response_generator(rg),
        _response_material(NULL) {}
  const int           toFd() const { return _to_fd; }
  pid_t&              pid() { return _pid; }
  int&                fromFd() { return _from_fd; }
  bool&               emptyLine() { return _empty_line; }
  Parser*&            parser() { return _parser; }
  ResponseGenerator*& responseGenerator() { return _response_generator; }
  ResponseMaterial*&  responseMaterial() { return _response_material; }
  std::stringstream&  storage() { return _storage; }
};

#endif  // EventInfo_hpp
