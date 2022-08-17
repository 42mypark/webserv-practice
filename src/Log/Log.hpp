#if !defined(Log_hpp)
#define Log_hpp

#include <sys/event.h>

#include <fstream>
#include <iostream>

namespace ft {

class Log : public std::fstream {
 public:
  Log(const std::string& file_name);
  int  operator()(int ret, const std::string& tag, const std::string& msg = "Done");
  void operator()(struct kevent& ev, const std::string& tag);
  // std::ofstream& operator<<(const std::string& msg);
};

}  // namespace ft

#endif  // Log_hpp
