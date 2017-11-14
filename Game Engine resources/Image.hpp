
typedef uint32_t Rgba8888;
typedef uint32_t Rgba32;

struct Image
{
	unsigned width;
	unsigned height;
	
	Rgba8888 * pixel_buffer;
	
	Image()
	{
		width = height = 0;
		pixel_buffer   = nullptr;
	}
	
	Image(unsigned w, unsigned h) : width(w), height(h)
	{
		pixel_buffer = new Rgba8888[w * h];
	}
	
	bool save (const std::string & path)
	{
		std::ofstream file(path, std::ofstream::binary);
		
		if (file.good ())
		{
			file.write ((char *)&width,  2);
			file.write ((char *)&height, 2);
			
			for (size_t i = 0, size = width * height; i < size; ++i)
			{
				file.write ((char *)&pixel_buffer[i], sizeof(Rgba8888));
			}
			
			return file.good ();
		}
		
		return false;
	}
	
	bool load (const std::string & path)
	{
		std::ifstream file(path, std::ofstream::binary);
		
		if (file.good ())
		{
			uint16_t w, h;
			
			fstream.read ((char *)&w, 2);
			fstream.read ((char *)&h, 2);
			
			Rgba8888 * buffer = new Rgba8888[w * h];
			
			for (size_t i = 0, size = w * h; i < size; ++i)
			{
				file.read ((char *)&buffer[i], sizeof(Rgba8888));
			}
			
			if (file.good ())
			{
				delete [] pixel_buffer;
				
				pixel_buffer = buffer;
				width        = w;
				height       = h;
				
				return true;
			}
		}
		
		return false;
	}
	
};