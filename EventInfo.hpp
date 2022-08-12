#if !defined(EventInfo_hpp)
#define EventInfo_hpp


#include "Parser.hpp"
#include <sstream>

class EventInfo {
    private:
        const int _to_fd;
        int _from_fd;
        Parser* _p;
        std::stringstream _storage;
    public:
        EventInfo(int to_fd, int from_fd, Parser* p) : _to_fd(to_fd), _from_fd(from_fd), _p(p){}
        int toFd() { return _to_fd; }
        int& fromFd() { return _from_fd; }
        Parser*& parser() { return _p; }
        std::stringstream& storage() { return _storage; }
};


#endif // EventInfo_hpp
