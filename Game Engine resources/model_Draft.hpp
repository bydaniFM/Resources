
struct Model
{
	struct Vertex
	{
		Point3  position;
		Vector3 normal;
		Point2  uv;
		float   alpha;
		...
	};

	typedef vector< Vertex > Vertex_Buffer;
	typedef vector< int    >  Index_Buffer;

	Vertex_Buffer vertex_buffer;
	 Index_Buffer  index_buffer;
	
};

struct Scene
{

	list< Model > models;

};


class Renderer
{

public:

	void render (Pixel_Buffer & target, const Scene & scene);

};




