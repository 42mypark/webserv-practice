#include "Log.hpp"

#include <errno.h>

ft::Log::Log(const std::string& file_name) : std::fstream(file_name) {}

int ft::Log::operator()(int ret, const std::string& tag, const std::string& message) {
  if (ret == -1) {
    *this << tag << " Error: " << message << " errno " << strerror(errno) << std::endl;
  } else {
    *this << tag << message << std::endl;
  }
  return ret;
}

void ft::Log::operator()(struct kevent& ev, const std::string& tag) {
  *this << tag << " ident " << ev.ident << std::endl;
}

// std::ofstream& Log::operator<<(const std::string& msg) {
//   log << msg;
//   return *this;
// }
