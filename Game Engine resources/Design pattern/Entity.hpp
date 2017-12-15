
#include "Component.h++"

class Scene;

class Entity
{
	map< string, shared_ptr< Component > > components;
	
	Scene * parent;
	
public:

	Entity(Scene * scene) : parent(scene)
	{
	}

	void initialize ()
	{
		for (auto & component : components)
		{
			component->initialize (this);
		}
	}
	
	void update (float deltaTime)
	{
		for (auto & component : components)
		{
			component->update (deltaTime);
		}
	}

	void add_component (const string & name, shared_ptr< Component > & component)
	{
		components[name] = component;
	}

}