#include "Header.h"

Color::Color()
{
	red = 0;
	green = 0;
	blue = 0;
}

Header::Header()
{
	char idLength = 0;
	char colorMapType = 0;
	char dataTypeCode = 0;
	short colorMapOrigin = 0;
	short colorMapLength = 0;
	char colorMapDepth = 0;
	short xOrigin = 0;
	short yOrigin = 0;
	short width = 0;
	short height = 0;
	char bitsPerPixel = 0;
	char imageDescriptor = 0;
}


void Image::Add(Color *color)
{
	colors.push_back(color);
}
