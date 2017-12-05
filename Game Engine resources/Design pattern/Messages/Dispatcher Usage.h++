
#include "Dispatcher.hpp"

class Minion_Control_Component : public Control_Component, public Dispatcher.Listener
{

public:

	void update (float delta)
	{
		Message follow_me(MSG_FOLLOW_MINION);
		
		follow_me[h("x")] = entity.transform.x;
		follow_me[h("y")] = entity.transform.y;
		follow_me[h("z")] = entity.transform.z;
		
		entity.scene.dispatcher.send (follow_me);
	}
	
	void handle(const Message & message)
	{
		switch (int(message))
		{
			case MESSAGE_HIT:
			{
				int target_id = message[h("target_id")].as_int ();
				...
				break;
			}
			
			case MESSAGE_AUTO_KILL:
			{				
				...
				break;
			}
		}
	}

};