
class Module
{

	typedef shared_ptr< Module > (*Module_Factory) (Scene * scene);

	static map< string, Module_Factory >  module_registry;

public:

	static void register (const string & id, Module_Factory factory)
	{
		module_registry[id] = factory;
	}
	
	static shared_ptr< Module > create (const string & id, Scene * scene)
	{
		if (module_registry.count (id))
		{
			return module_registry[id] (scene);
		}
		
		return shared_ptr< Module >();
	}

public:

	virtual shared_ptr< Compoment > create_component (Entity * entity) = 0;




};