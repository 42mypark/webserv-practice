#include <sstream>
#include <iostream>
#include <cstring>

int main()
{
    std::stringstream ss;
    char buf[10];
    bzero(buf, 10);

    buf[0] = '1';

    ss << buf;

    bzero(buf, 10);

    buf[0] = '2';

    ss << buf;

    std::string out;
    while (!ss.eof()){
        ss >> out;
        std::cout << "out :" << out << " , first :" << out.c_str()[0] << std::endl;
    }
    out = "";
    ss >>out;
    std::cout << "out :" << out << " , first :" << out.c_str()[0] << std::endl;
}