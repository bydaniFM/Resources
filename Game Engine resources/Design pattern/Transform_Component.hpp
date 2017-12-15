
#include "Component.h++"

class Transform_Component : public Component
{

	Transform_Component(Entity * entity) : Component(entity)
	{
	}

	void initialize ()
	{
	}
	
	void update (float deltaTime)
	{
	}
	
	bool parse (xml_node<> * node)
	{
	}
	
};