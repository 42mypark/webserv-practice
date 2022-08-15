#include <cstring>
#include <iostream>
#include <sstream>

int main() {
  std::string       str = "apple        banana     \r\n\r\nhello";
  std::stringstream ss;

  ss << str;

  std::cout << "str :" << str << std::endl;

  std::getline(ss, str);
  std::cout << "line 1 : " << str << ss.eof() << std::endl;

  std::getline(ss, str);
  std::cout << "line 2 : " << str << ss.eof() << (str.c_str()[0] == '\r') << std::endl;
  std::getline(ss, str);
  std::cout << "line 3 : " << str << ss.eof() << std::endl;
  std::getline(ss, str);
  std::cout << "line 4 : " << str << ss.eof() << std::endl;
}