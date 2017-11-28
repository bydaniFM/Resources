
class Scene
{
	
	Kernel kernel;
	
public:

	Scene(const std::string & scene_description_path)
	{
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
	
};
