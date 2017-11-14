
typedef uint8_t byte;

class Writer
{

public:

	virtual void write_int16  (int16_t value) = 0;
	virtual void write_int32  (int32_t value) = 0;
	virtual void write_int64  (int64_t value) = 0;
	virtual void write_buffer (byte * data, size_t size) = 0;
	
};

class File_Writer : public Writer
{

	SDL_RWops * handle;

public:

	File_Writer(const File & file)
	{
		handle = SDL_RWFromFile (file.get_path(), "wb");
	}

	void write_int16 (int16_t value)
	{
		SDL_WriteLE16 (handle, value);
	}
	
	void write_int32  (int32_t value)
	void write_int64  (int64_t value)
	void write_buffer (byte * data, size_t size)
};


class Path
class File
class File_Writer : public Writer
class File_Reader : public Reader



