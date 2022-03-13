#pragma once
#include <vector>
using namespace std;

struct Header {
	Header();
	char idLength;
	char colorMapType;
	char dataTypeCode;
	short colorMapOrigin;
	short colorMapLength;
	char colorMapDepth;
	short xOrigin;
	short yOrigin;
	short width;
	short height;
	char bitsPerPixel;
	char imageDescriptor;
};

struct Color {
	Color();
	unsigned char red;
	unsigned char green;
	unsigned char blue;
};

struct Image {
	Image() {};
	void Add(Color *color);
	long const getColorSize() {
		return colors.size();
	}
	vector <Color*> const getColors() {
		return colors;
	}
	~Image() {
		for (int i = 0; i < colors.size(); i++) {
			Color* color = colors[i];
			delete color;
		};
	}

	private:
		vector <Color*> colors;
};




