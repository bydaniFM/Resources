
#include "Messages.hpp"

class Message
{

	int action_id;
	
	typedef std::unordered_map< int, Variant > Paramer_List;
	
	Paramer_List parameters;

public:

	Message(int id) : action_id(id)
	{
	}
	
	Variant & operator [] (int key)
	{
		return parameters[key];
	}
	
	const Variant & operator [] (int key) const
	{
		return parameters[key];
	}
	
	bool operator == (const Message & other) const
	{
		return this->action_id == other.action_id;
	}
	
	bool operator != (const Message & other) const
	{
		return this->action_id != other.action_id;
	}
	
	operator int () const
	{
		return action_id;
	}
	
};

class Messages
{
	enum m{
		MSG_type1, MSG_type2, MSG_type3
	};
};


----------------------------------------------------

#include "Messages.hpp"

Message m(MSG_TRIGGER_TRAP));


if (MSG_TRIGGER_TRAP == m)
{
}


constexpr int hash(const char * s)
{
	int hash_value = 0;
	
	while (*s)
	{
		hash_value *= *(s++);
	}
	
	return hash_value;
}













