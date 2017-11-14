
typedef uint16_t Rgb565;

class Buffer_Rgb565
{
	unsigned width;
	unsigned height;
	
	std::vector< Rgb565 > buffer;
	
public:

	Buffer_Rgb565(unsigned width, unsigned height)
	:
		width (width),
		height(height),
		buffer(width * height)
	{
	}
	
	unsigned get_width  () const { return width;  }
	unsigned get_height () const { return height; }
	
	/// Retorna un puntero al píxel dentro del buffer
	/// que tiene las coordenadas (x,y) especificadas.
	Rgb565 * get (unsigned x, unsigned y)
	{
		return buffer.data () + y * width + x;
	}

};

void blit
(
	Buffer_Rgb565 & buffer_dst, 
	Buffer_Rgb565 & buffer_src,
	unsigned dst_x,
	unsigned dst_y
)
{
	Rgb565 * src = buffer_src.get (0, 0);
	Rgb565 * dst = buffer_dst.get (dst_x, dst_y);
	
	Rgb565 * src_end = src + buffer_src.get_width () * buffer_src.get_height ();
	Rgb565 * scanline_end = src;

	unsigned delta = buffer_dst.get_width () - buffer_src.get_width ();

	while (src < src_end)
	{
		scanline_end += buffer_src.get_width ();
		
		while (src < scanline_end)
		{
			*dst++ = *src++;
		}
		
		dst += delta;
	}
}


