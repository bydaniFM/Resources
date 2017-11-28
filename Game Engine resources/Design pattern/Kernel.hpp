
class Kernel
{
	typedef std::list< Task * > Task_List;
	
	Task_List task_list;
	bool      exit;
	
public:

	void execute ()
	{
		// LLAMAR AL MÉTODO INITIALIZE() DE TODAS LAS TASK
		
		exit = false;
		
		while (!exit)
		{
			for (auto & task : task_list)
			{
				task->run ();
				
				if (task->is_finished ())
				{
					task->finalize ();
					task_list.erase (task);
				}
			}
		}
		
		// LLAMAR AL MÉTODO FINALIZE() DE TODAS LAS TASK
	}
	
	void stop ()
	{
		exit = true;
	}
	
	void add (Task & task)
	{
		// Se añade la tarea a la lista de tareas:
		
		task_list.push_back (&task);		
		
		// Se reordena la lista por prioridad de ejecución
		// de las tareas:
		
		task_list.sort< compare > ();
	}
	
	static bool compare (const Task * a, const Task * b)
	{
		return *a < *b;
	}
	
};


int main ()
{
	// initialize
	
	Scene menu_scene("scenes/main-menu.xml");

	menu_scene.run();

	// cleanup
	
	return 0;
}