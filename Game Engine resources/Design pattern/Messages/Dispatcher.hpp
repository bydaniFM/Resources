
#include "Message.hpp"

class Dispatcher
{
public:

	struct Listener
	{
		virtual     ~Listener() {}		
		virtual void handle  (const Message & ) = 0;
	};

private:

	typedef std::unordered_map< int, std::list< Listener * > > Listener_Map;

};