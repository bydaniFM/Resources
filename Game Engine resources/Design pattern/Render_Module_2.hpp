
class Render_Module : public Module
{
public:

	class Render_Task : public Task
	{
		Render_Module * module;
		
	public:
	
		Render_Task(Render_Module * module) { ... }
		
		void update (float time) override
		{
			module->get_render_node ().render ();
		}
	};
	
	class Model_Component : public Component
	{
		shared_ptr< glt::Model > model;
		
	public:
	
		shared_ptr< glt::Model > get_model() { return model; }
	};
	
	class Camera_Component : public Component
	{
		shared_ptr< glt::Camera > * camera;
	};
	
	class Light_Component : public Component
	{
		shared_ptr< glt::Light > model;
	};

private:

	Render_Task task;
	Render_Node scene;
	
public:

	Task * get_task ()
	{
		return &task;
	}

	Render_Node & get_render_node ()
	{
		return scene;
	}
	
	shared_ptr< Component > create_component (const string & type, const xml_node & details)
	{
		if (type == "model")
		{
			// PARSEAR LA RUTA DEL ARCHIVO DEL MODEL
		
			shared_ptr< Model_Component > model(path);
			
			scene->add (name, model->get_model ());
			
			return model;
		}
		else
		if (type == "camera")
		{
			...
		}
		...
	}
	

};