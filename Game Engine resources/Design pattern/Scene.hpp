#include <Entity.hpp>

class Scene
{
	
	Kernel kernel;
	map< string, shared_ptr< Entity > > entities;
	
public:

	Scene(const std::string & scene_file_path)
	{
		load_scene (scene_file_path);
		
		Read_Input_Task 	read_input_task;
		Update_Physics_Task update_physics_task;
		...
		
		kernel.add(&read_input_task);
		kernel.add(&update_physics_task);
		...		
	}
	
	void run ()
	{
		kernel.execute ();
	}
	
private:

	void load_scene (const string & scene_file_path);
	
	void init_kernel ()
	{
		for (auto & module : modules)
		{
			Task * task = module->get_task ();
			
			if (task)
			{
				kernel.add_task (task);
			}
		}
	}
	
};

-----------------------------------------------------------

bool Scene::load_scene (const string & scene_file_path)
{
	// SE LEE EL CONTENIDO DEL ARCHIVO:
	
    fstream xml_file(scene_file_path, fstream::in);

    if (xml_file.good ())
    {
        vector< char > xml_content;

        bool finished = false;

        do
        {
            int character = xml_file.get ();

            if (character != -1)
            {
                xml_content.push_back ((char)character);
            }
            else
                finished = true;
        }
        while (!finished);

		// SE AÑADE UN CARACTER NULO AL FINAL:

        xml_content.push_back (0);
		
		// SE CREA EL MODELO DE DOCUMENTO (DOM):
		
		xml_document< > document;

        document.parse< 0 > (xml_content.data ());
		
		// SE COMPRUEBA QUE EL PARSEO HA FUNCIONADO:

        xml_node< > * root = document.first_node ();
		
		if (root && string(root->name ()) == "scene")
		{
			parse_scene (root);
		}	
	}
	
	return false;
}

bool Scene::parse_scene (xml_node<> * scene_node)
{
	for (xml_node<> * child = scene_node->first_node (); child; child = child->next_sibling ())
	{
		if (child->type () == node_element)
		{
			if (string(child->name ()) == "entities")
			{
				parse_entities (child);
			}
			else
			if (string(child->name ()) == "config")
			{
				parse_config (child);
			}
			...
		}
	}
}

bool Scene::parse_entities(xml_node<> * entities_node)
{
	const string name;
	
	for
	(
		xml_attribute<> * attribute = component_tag->first_attribute();
		attribute;
		attribute = attribute->next_attribute()
	)
	{
		if (string(attribute->name ()) == "name")
		{
			name = attribute->value ();
		}
	}

	if (name.empty ()) return false;
	
	for (xml_node<> * entity_tag = entities_node->first_node (); entity_tag; entity_tag = entity_tag->next_sibling ())
	{
		if (entity_tag->type () == node_element)
		{
			if (string(entity_tag->name ()) != "entity") return false;
			
			shared_ptr< Entity > entity(new Entity(this));
			
			for (xml_node<> * child = entity_tag->first_node (); child; child = child->next_sibling ())
			{
				if (child->type () == node_element)
				{
					if (string(entity->name ()) == "components")
					{
						if (!parse_components (child, *entity)) return false;
					}
				}
			}
			
			entities[name] = entity;
		}
	}
}

bool Scene::parse_components(xml_node<> * component_tag, Entity & entity)
{
	const string type;
	
	for
	(
		xml_attribute<> * attribute = component_tag->first_attribute();
		attribute;
		attribute = attribute->next_attribute()
	)
	{
		if (string(attribute->name ()) == "type")
		{
			type = attribute->value ();
		}
	}
	
	if (type.empty ()) return false;
	
	// SI NO EXISTE UN MÓDULO QUE SE NECESITA, SE CREA Y SE GUARDA:
	
	if (modules.count (type) == 0)
	{
		modules[type].reset (Module::create (type, this));
	}
	
	// SE CACHEA EL PUNTERO AL MÓDULO QUE SE VA A USAR:
	
	Module * module = modules[type].get ();
	
	if (!module) return false;

	// SE CREA EL COMPONENTE:
	
	shared_ptr< Component > component(module->create_componet (&entity));
	
	if (!component) return false;
	
	if (!component->parse (component_tag)) return false;
	
	entity.add_component (type, component);
}
	
	
	
	
}