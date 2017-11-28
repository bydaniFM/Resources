
class Task
{
	
	int  priority;
	bool finished;
	
public:

	Task(int priority, bool finished = false)
	:
		priority(priority),
		finished(finished)
	{
	}
	
	bool is_finished () const
	{
		return finished;
	}
	
	virtual void initialize () = 0;
	virtual void finalize   () = 0;
	virtual void run        () = 0;
	
	bool operator < (const Task & other) const
	{
		return this->priority < other.priority;
	}
	
	bool operator > (const Task & other) const
	{
		return this->priority > other.priority;
	}
	
	...
};

class Task_Group : public Task
{
protected:
	
	typedef std::list< Task * > Task_List;
	
	Task_List task_list;

public:
	
	Task_Group(int priority) : Task(priority)
	{
	}
	
	void add (Task & task)
	{
		task_list.push_back (&task);		
	}
	
	void initialize ()
	{
		for (auto & task : task_list) task->initialize ();
	}

	void finalize ()
	{
		for (auto & task : task_list) task->finalize ();
	}
};

class Sequential_Task_Group : public Task_Group
{
public:
	
	Sequential_Task_Group(int priority) : Task_Group(priority)
	{
	}

	void run ()
	{
		for (auto & task : task_list)
		{
			task->run ();
			
			// COMPROBAR SI HAY TAREAS FINALIZADAS
		}
	}
};

class Parallel_Task_Group : public Task_Group
{
public:

	Parallel_Task_Group(int priority) : Task_Group(priority)
	{
		// CREAR TANTOS HILOS COMO TAREAS O
		// CREAR UN POOL DE HILOS DE UN TAMAÑO LIMITADO.
	}

	void run ()
	{
		// REPARTIR LAS TAREAS EN LOS HILOS.
		// ESPERAR A QUE SE COMPLETE LA EJECUCIÓN DE
		// TODAS LAS TAREAS.
	}
};

class Read_Input_Task : public Task
{
public:

	Read_Input_Task() : Task(0)
	{
	}

	void run ();
};