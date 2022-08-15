#if !defined(Parser_hpp)
#define Parser_hpp

#include <vector>
#include "EventInfo.hpp"

class Parser {
	private:
	// Interface
	public:
		void parse(std::vector<EventInfo *>& event_list);
};

void Parser::parse(std::vector<EventInfo *>& event_list)
{
	std::vector<EventInfo *>::iterator it = event_list.begin();
	for(; it != event_list.end(); ++it)	{
		EventInfo& event_info = **it;
		Paser& paser = *event_info.paser();
	}
}


#endif // PARSER

