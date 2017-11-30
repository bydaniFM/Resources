
struct Point2D
{
	float x, y;
};

struct Vector2D
{
	float x, y;
};

size_t clip_polygon
(
	const Point2D * vertices,
		  size_t    vertex_count,
		  Point2D * clip_result,
	const float     width,
	const float     height
)
{
	Point2D clip_aux_a[20];
	Point2D clip_aux_b[20];
	
	vertex_count = clip_polygon_with_line
	(
		vertices,
		vertex_count,
		clip_aux_a,
		Point2D { 0.f, 0.f },
		Vector2D{ 0.f, 1.f }
	);
	
	vertex_count = clip_polygon_with_line
	(
		clip_aux_a,
		vertex_count,
		clip_aux_b,
		Point2D { 0.f, height },
		Vector2D{ 1.f, 0.f    }
	);
	
	vertex_count = clip_polygon_with_line
	(
		clip_aux_b,
		vertex_count,
		clip_aux_a,
		Point2D { width,  0.f },
		Vector2D{   0.f, -1.f }
	);
	
	
	return clip_polygon_with_line
	(
		clip_aux_a,
		vertex_count,
		clip_result,
		Point2D {  0.f, 0.f },
		Vector2D{ -1.f, 0.f }
	);
}

size_t clip_polygon_with_line
(
	const Point2D  * vertices,
	const size_t     vertex_count,
		  Point2D  * result,
	const Point2D  & line_point,
	const Vector2D & line_vector
)
{
}