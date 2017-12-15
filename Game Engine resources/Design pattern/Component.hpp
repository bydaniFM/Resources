
class Entity;

class Component
{
protected:
	
	const Entity * parent;

public:

	Component(Entity * entity) : parent(entity)
	{
	}

	virtual void initialize () = 0;
	virtual void update     (float deltaTime) = 0;
	virtual bool parse      (xml_node<> * node) { }

};
