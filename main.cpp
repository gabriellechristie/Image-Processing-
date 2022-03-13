#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "Header.h"
using namespace std;

void part1(void);
void part2(void);
void part3(void);
void part4(void);
void part5(void);
void part6(void);
void part7(void);
void part8(void);
void part9(void);
void part10(void);
void part11(void);
void Subtraction(Image& layer2Image, Image& carImage, Image& subtractedColors);
void Multiply(Image& layer1, Image& pattern2, Image& multipliedColors);
bool CompareImageFiles(string actualFile, string myFile);
char* loadFileBuffer(string filename);
void getHeader(Header& header, char* fileBuffer);
void getImage(Image& image, long imageSize, char* fileBuffer);
void writeHeader(fstream& fileWrite, Header& header);
void writeBonusHeader(fstream& fileWrite, Header& header);
bool Test1();
bool Test2();
bool Test3();
bool Test4();
bool Test5();
bool Test6();
bool Test7();
bool Test8Blue();
bool Test8Green();
bool Test8Red();
bool Test9();
bool Test10();
bool Test11();

int main() {
	part1();
	part2();
	part3();
	part4();
	part5();
	part6();
	part7();
	part8();
	part9();
	part10();
	part11();

	// run tests
	cout << "Running Test #1......" << endl << endl;
	bool testResultFailed = Test1();
	int testPassed=0;
	if (testResultFailed) {
		cout << "Test #1...... Failed!" << endl;
	}
	else {
		testPassed++;
		cout << "Test #1...... Passed!" << endl << endl;
	}

	cout << "Running Test #2......" << endl << endl;
	testResultFailed = Test2();
	if (testResultFailed) {
		cout << "Test #2...... Failed!" << endl << endl;
	}
	else {
		testPassed++;
		cout << "Test #2...... Passed!" << endl << endl;
	}

	cout << "Running Test #3......" << endl << endl;
	testResultFailed = Test3();
	if (testResultFailed) {
		cout << "Test #3...... Failed!" << endl << endl;
	}
	else {
		testPassed++;
		cout << "Test #3...... Passed!" << endl << endl;
	}

	cout << "Running Test #4......" << endl << endl;
	testResultFailed = Test4();
	if (testResultFailed) {
		cout << "Test #4...... Failed!" << endl << endl;
	}
	else {
		testPassed++;
		cout << "Test #4...... Passed!" << endl << endl;
	}

	cout << "Running Test #5......" << endl << endl;
	testResultFailed = Test5();
	if (testResultFailed) {
		cout << "Test #5...... Failed!" << endl << endl;
	}
	else {
		testPassed++;
		cout << "Test #5...... Passed!" << endl << endl;
	}

	cout << "Running Test #6......" << endl << endl;
	testResultFailed = Test6();
	if (testResultFailed) {
		cout << "Test #6...... Failed!" << endl << endl;
	}
	else {
		testPassed++;
		cout << "Test #6...... Passed!" << endl << endl;
	}

	cout << "Running Test #7......" << endl << endl;
	testResultFailed = Test7();
	if (testResultFailed) {
		cout << "Test #7...... Failed!" << endl << endl;
	}
	else {
		testPassed++;
		cout << "Test #7...... Passed!" << endl << endl;
	}

	cout << "Running Test #8......" << endl << endl;
	bool testResultBlueFailed = Test8Blue();
	bool testResultGreenFailed = Test8Green();
	bool testResultRedFailed = Test8Red();

	if (testResultBlueFailed || testResultGreenFailed || testResultRedFailed) {
		cout << "Test #8...... Failed!" << endl;
	}
	else {
		testPassed++;
		cout << "Test #8...... Passed!" << endl << endl;
	}

	cout << "Running Test #9......" << endl << endl;
	testResultFailed = Test9();
	if (testResultFailed) {
		cout << "Test #9...... Failed!" << endl;
	}
	else {
		testPassed++;
		cout << "Test #9...... Passed!" << endl << endl;
	}

	cout << "Running Test #10......" << endl << endl;
	testResultFailed = Test10();
	if (testResultFailed) {
		cout << "Test #10...... Failed!" << endl;
	}
	else {
		testPassed++;
		cout << "Test #10...... Passed!" << endl << endl;
	}
	cout << "Test Results Passed: " << testPassed << " / 10" << endl;
	
	cout << endl;

	cout << "Running Test Extra Credit #11......" << endl << endl;
	testResultFailed = Test11();
	int bonus = 0;
	if (testResultFailed) {
		cout << "Test #11...... Failed!" << endl;
	}
	else {
		bonus++;
		cout << "Test #11...... Passed!" << endl << endl;
	}
	cout << "Bonus Test Result Passed: " << bonus << " / 1" << endl;
}

void part1(void) {

	string layer1 = "./input/layer1.tga";
	char* layer1FileBuffer = loadFileBuffer(layer1);

	char* layer1FileBufferHead = layer1FileBuffer; 
	Header layer1Header;
	getHeader(layer1Header, layer1FileBuffer);
	layer1FileBuffer += 18; 
	short layer1Width = layer1Header.width;
	short layer1Height = layer1Header.height;
	long layer1ImageSize = (layer1Width * layer1Height) * 3;
	Image layer1Image;
	getImage(layer1Image, layer1ImageSize, layer1FileBuffer);
	delete[] layer1FileBufferHead;

	string pattern1 = "./input/pattern1.tga"; 
	char* pattern1FileBuffer = loadFileBuffer(pattern1);
	char* pattern1FileBufferHead = pattern1FileBuffer; 
	Header pattern1Header;
	getHeader(pattern1Header, pattern1FileBuffer);
	pattern1FileBuffer += 18;
	short pattern1Width = pattern1Header.width;
	short pattern1Height = pattern1Header.height;
	long pattern1ImageSize = (pattern1Width * pattern1Height) * 3;
	Image pattern1Image;
	getImage(pattern1Image, pattern1ImageSize, pattern1FileBuffer);
	delete[] pattern1FileBufferHead;
	
	string fileNameWrite = "./output/part1.tga"; 
	fstream fileWrite(fileNameWrite, ios::out | ios::binary);
	writeHeader(fileWrite, layer1Header);
		
	Image multipliedColors;
	Multiply(layer1Image, pattern1Image, multipliedColors);

	vector<Color*> const multipliedVector = multipliedColors.getColors();
	for (long count = 0; count < multipliedColors.getColorSize(); count++) {
		Color* color = multipliedVector[count];
		fileWrite.write((char*)&color->blue, sizeof(color->blue));
		fileWrite.write((char*)&color->green, sizeof(color->green));
		fileWrite.write((char*)&color->red, sizeof(color->red));
	}
	
	fileWrite.close();
	
}

void part2(void)
{
	string layer2 = "./input/layer2.tga"; 
	char* layer2FileBuffer = loadFileBuffer(layer2);
	char* layer2FileBufferHead = layer2FileBuffer; 
	Header layer2Header;
	getHeader(layer2Header, layer2FileBuffer);
	layer2FileBuffer += 18; 
	short layer2Width = layer2Header.width;
	short layer2Height = layer2Header.height;
	long layer2ImageSize = (layer2Width * layer2Height) * 3;
	Image layer2Image;
	getImage(layer2Image, layer2ImageSize, layer2FileBuffer);
	delete[] layer2FileBufferHead;

	string carFile = "./input/car.tga";
	char* carFileBuffer = loadFileBuffer(carFile);
	char* carFileBufferHead = carFileBuffer; 
	Header carHeader;
	getHeader(carHeader, carFileBuffer);
	carFileBuffer += 18; 
	short carWidth = carHeader.width;
	short carHeight = carHeader.height;
	long carImageSize = (carWidth * carHeight) * 3;
	Image carImage;
	getImage(carImage, carImageSize, carFileBuffer);
	delete[] carFileBufferHead;

	string part2NameWrite = "./output/part2.tga";
	fstream part2Write(part2NameWrite, ios::out | ios::binary);
	writeHeader(part2Write, layer2Header);

	Image subtractedColors;
	Subtraction(layer2Image, carImage, subtractedColors);

	vector<Color*> const subtractedVector = subtractedColors.getColors();
	for (long subCount = 0; subCount < subtractedColors.getColorSize(); subCount++) {
		Color* subColor = subtractedVector[subCount];
		part2Write.write((char*)&subColor->blue, sizeof(subColor->blue));
		part2Write.write((char*)&subColor->green, sizeof(subColor->green));
		part2Write.write((char*)&subColor->red, sizeof(subColor->red));
	}

	part2Write.close();
}

void Subtraction(Image& fileImage1, Image& fileImage2, Image& subtractedColors)
{
	vector<Color*> const file1Colors = fileImage1.getColors();
	vector<Color*> const file2Colors = fileImage2.getColors();
	long file1ColorsSize = file1Colors.size();
	long file2ColorsSize = file2Colors.size();

	Color* file1ColorPtr;
	Color* file2ColorsPtr;

	int file1ColorB = 0;
	int file1ColorG = 0;
	int file1ColorR = 0;
	int file2ColorB = 0;
	int file2ColorG = 0;
	int file2ColorR = 0;

	for (int count = 0; count < file1Colors.size(); count++) {
		file1ColorPtr = file1Colors[count];
		file1ColorB = file1ColorPtr->blue;
		file1ColorG = file1ColorPtr->green;
		file1ColorR = file1ColorPtr->red;

		file2ColorsPtr = file2Colors[count];
		file2ColorB = file2ColorsPtr->blue;
		file2ColorG = file2ColorsPtr->green;
		file2ColorR = file2ColorsPtr->red;

		int subtractedBlue = file2ColorB - file1ColorB;
		int subtractedGreen = file2ColorG - file1ColorG;
		int subtractedRed = file2ColorR - file1ColorR;

		if (subtractedBlue < 0) {
			subtractedBlue = 0;
		}
		if (subtractedGreen < 0) {
			subtractedGreen = 0;
		}
		if (subtractedRed < 0) {
			subtractedRed = 0;
		}

		Color* subtractedColorPtr = new Color();
		subtractedColorPtr->blue = subtractedBlue;
		subtractedColorPtr->green = subtractedGreen;
		subtractedColorPtr->red = subtractedRed;

		subtractedColors.Add(subtractedColorPtr);
	}
}

void part3(void)
{
	string layer1 = "./input/layer1.tga"; 
	char* layer1FileBuffer = loadFileBuffer(layer1);
	char* layer1FileBufferHead = layer1FileBuffer;
	Header layer1Header;
	getHeader(layer1Header, layer1FileBuffer);
	layer1FileBuffer += 18; 
	short layer1Width = layer1Header.width;
	short layer1Height = layer1Header.height;
	long layer1ImageSize = (layer1Width * layer1Height) * 3;
	Image layer1Image;
	getImage(layer1Image, layer1ImageSize, layer1FileBuffer);
	delete[] layer1FileBufferHead;

	string pattern2 = "./input/pattern2.tga";
	char* pattern2FileBuffer = loadFileBuffer(pattern2);
	char* pattern2FileBufferHead = pattern2FileBuffer; 
	Header pattern2Header;
	getHeader(pattern2Header, pattern2FileBuffer);
	pattern2FileBuffer += 18; 
	short pattern2Width = pattern2Header.width;
	short pattern2Height = pattern2Header.height;
	long pattern2ImageSize = (pattern2Width * pattern2Height) * 3;
	Image pattern2Image;
	getImage(pattern2Image, pattern2ImageSize, pattern2FileBuffer);
	delete[] pattern2FileBufferHead;

	Image multipliedColors;
	Multiply(layer1Image, pattern2Image, multipliedColors);

	string text = "./input/text.tga";
	char* textBuffer = loadFileBuffer(text);
	char* textBufferHead = textBuffer; 
	Header textHeader;
	getHeader(textHeader, textBuffer);
	textBuffer += 18; 
	short textWidth = textHeader.width;
	short textHeight = textHeader.height;
	long textImageSize = (textWidth * textHeight) * 3;
	Image textImage;
	getImage(textImage, textImageSize, textBuffer);
	delete[] textBufferHead;

	vector<Color*> const textColors = textImage.getColors();
	vector<Color*> const multipliedVector = multipliedColors.getColors();
	long textColorsSize = textColors.size();
	long multipliedVectorSize = multipliedVector.size();

	Color* textColorPtr;
	Color* multipliedVectorPtr;

	float textColorB = 0.0;
	float textColorG = 0.0;
	float textColorR = 0.0;
	float part3MultColorB = 0.0;
	float part3MultColorG = 0.0;
	float part3MultColorR = 0.0;

	Image screen;
	for (int screenCount = 0; screenCount < textColors.size();screenCount++ ) {
		Color* screenColorsPtr = new Color();
		textColorPtr = textColors[screenCount];
		textColorB = textColorPtr->blue;
		textColorG = textColorPtr->green;
		textColorR = textColorPtr->red;

		float textBlue = textColorB / 255;
		float textGreen = textColorG / 255;
		float textRed = textColorR / 255;

		multipliedVectorPtr = multipliedVector[screenCount];
		part3MultColorB = multipliedVectorPtr->blue;
		part3MultColorG = multipliedVectorPtr->green;
		part3MultColorR = multipliedVectorPtr->red;

		float part3MultColorBlue = part3MultColorB / 255;
		float part3MultColorGreen = part3MultColorG / 255;
		float part3MultColorRed = part3MultColorR / 255;

		float screenBlue = 1 - (1 - textBlue) * (1 - part3MultColorBlue);
		float screenGreen = 1 - (1 - textGreen) * (1 - part3MultColorGreen);
		float screenRed = 1 - (1 - textRed) * (1 - part3MultColorRed);

		screenBlue *= 255;
		screenGreen *= 255;
		screenRed *= 255;

		screenBlue += 0.5f;
		screenGreen += 0.5f;
		screenRed += 0.5f;

		screenColorsPtr->blue = screenBlue;
		screenColorsPtr->green = screenGreen;
		screenColorsPtr->red = screenRed;

		screen.Add(screenColorsPtr);
	}

	string part3NameWrite = "./output/part3.tga"; 
	fstream part3Write(part3NameWrite, ios::out | ios::binary);
	writeHeader(part3Write, layer1Header);

	vector<Color*> const screenColorsVector = screen.getColors();
	for (long count = 0; count < screen.getColorSize(); count++) {
		Color* screenColors = screenColorsVector[count];
		part3Write.write((char*)&screenColors->blue, sizeof(screenColors->blue));
		part3Write.write((char*)&screenColors->green, sizeof(screenColors->green));
		part3Write.write((char*)&screenColors->red, sizeof(screenColors->red));
	}
	part3Write.close();
}

void part4(void)
{
	string layer2 = "./input/layer2.tga";
	char* layer2Buffer = loadFileBuffer(layer2);
	char* layer2BufferHead = layer2Buffer; 
	Header layer2Header;
	getHeader(layer2Header, layer2Buffer);
	layer2Buffer += 18;
	short layer2Width = layer2Header.width;
	short layer2Height = layer2Header.height;
	long layer2ImageSize = (layer2Width * layer2Height) * 3;
	Image layer2Image;
	getImage(layer2Image, layer2ImageSize, layer2Buffer);
	delete[] layer2BufferHead;
	
	string circle = "./input/circles.tga"; 
	char* circleBuffer = loadFileBuffer(circle);
	char* circleBufferHead = circleBuffer; 
	Header circleHeader;
	getHeader(circleHeader, circleBuffer);
	circleBuffer += 18; 
	short circleWidth = circleHeader.width;
	short circleHeight = circleHeader.height;
	long circleImageSize = (circleWidth * circleHeight) * 3;
	Image circleImage;
	getImage(circleImage, circleImageSize, circleBuffer);
	delete[] circleBufferHead;

	Image multiplyColors;
	Multiply(layer2Image, circleImage, multiplyColors);

	string pattern2 = "./input/pattern2.tga";
	char* pattern2Buffer = loadFileBuffer(pattern2);
	char* pattern2BufferHead = pattern2Buffer;
	Header pattern2Header;
	getHeader(pattern2Header, pattern2Buffer);
	pattern2Buffer += 18;
	short pattern2Width = pattern2Header.width;
	short pattern2Height = pattern2Header.height;
	long pattern2ImageSize = (pattern2Width * pattern2Height) * 3;
	Image pattern2Image;
	getImage(pattern2Image, pattern2ImageSize, pattern2Buffer);
	delete[] pattern2BufferHead;

	Image subColors;
	Subtraction(pattern2Image, multiplyColors, subColors);

	string part4NameWrite = "./output/part4.tga";
	fstream part4Write(part4NameWrite, ios::out | ios::binary);
	writeHeader(part4Write, pattern2Header);

	vector<Color*> const subtractedVector = subColors.getColors();
	for (long subCount = 0; subCount < subColors.getColorSize(); subCount++) {
		Color* subColor = subtractedVector[subCount];
		part4Write.write((char*)&subColor->blue, sizeof(subColor->blue));
		part4Write.write((char*)&subColor->green, sizeof(subColor->green));
		part4Write.write((char*)&subColor->red, sizeof(subColor->red));
	}
	part4Write.close();
}

void part5(void)
{
	string layer1 = "./input/layer1.tga";
	char* layer1Buffer = loadFileBuffer(layer1);
	char* layer1BufferHead = layer1Buffer;
	Header layer1Header;
	getHeader(layer1Header, layer1Buffer);
	layer1Buffer += 18;
	short layer1Width = layer1Header.width;
	short layer1Height = layer1Header.height;
	long layer1ImageSize = (layer1Width * layer1Height) * 3;
	Image layer1Image;
	getImage(layer1Image, layer1ImageSize, layer1Buffer);
	delete[] layer1BufferHead;

	string pattern1 = "./input/pattern1.tga";
	char* pattern1FileBuffer = loadFileBuffer(pattern1);
	char* pattern1FileBufferHead = pattern1FileBuffer;
	Header pattern1Header;
	getHeader(pattern1Header, pattern1FileBuffer);
	pattern1FileBuffer += 18;
	short pattern1Width = pattern1Header.width;
	short pattern1Height = pattern1Header.height;
	long pattern1ImageSize = (pattern1Width * pattern1Height) * 3;
	Image pattern1Image;
	getImage(pattern1Image, pattern1ImageSize, pattern1FileBuffer);
	delete[] pattern1FileBufferHead;

	vector<Color*> const layer1Vector = layer1Image.getColors();
	vector<Color*> const pattern1Vector = pattern1Image.getColors();
	long layer1VectorSize = layer1Vector.size();
	long pattern1VectorSize = pattern1Vector.size();

	Color* layer1Ptr;
	Color* pattern1Ptr;

	float layer1ColorB = 0.0;
	float layer1ColorG = 0.0;
	float layer1ColorR = 0.0;
	float pattern1ColorB = 0.0;
	float pattern1ColorG = 0.0;
	float pattern1ColorR = 0.0;

	Image multipliedColors;
	for (int count = 0; count < layer1VectorSize; count++) {
		Color* multipliedColorsPtr = new Color();
		layer1Ptr = layer1Vector[count];
		layer1ColorB = layer1Ptr->blue;
		layer1ColorG = layer1Ptr->green;
		layer1ColorR = layer1Ptr->red;

		float layer1Blue = layer1ColorB / 255;
		float layer1Green = layer1ColorG / 255;
		float layer1Red = layer1ColorR / 255;


		pattern1Ptr = pattern1Vector[count];
		pattern1ColorB = pattern1Ptr->blue;
		pattern1ColorG = pattern1Ptr->green;
		pattern1ColorR = pattern1Ptr->red;

		float pattern1Blue = pattern1ColorB / 255;
		float pattern1Green = pattern1ColorG / 255;
		float pattern1Red = pattern1ColorR / 255;

		float multipliedBlue = 0.0;
		float multipliedGreen = 0.0;
		float multipliedRed = 0.0;

		if (pattern1Blue <= 0.5) {
			multipliedBlue = 2.0*((float)layer1Blue * pattern1Blue);
		}
		else {
			multipliedBlue = 1 - (2.0 * ((1.0 - layer1Blue) * (1.0 - pattern1Blue)));
		}

		if (pattern1Green <= 0.5) {
			multipliedGreen = 2.0 * ((float)layer1Green * pattern1Green);
		}
		else {
			multipliedGreen = 1 - (2.0 * ((1.0 - layer1Green) * (1.0 - pattern1Green)));
		}

		if (pattern1Red <= 0.5) {
			multipliedRed = 2.0 * ((float)layer1Red * pattern1Red);
		}
		else {
			multipliedRed = 1 - (2.0 * ((1.0 - layer1Red) * (1.0 - pattern1Red)));
		}

		multipliedBlue *= 255;
		multipliedGreen *= 255;
		multipliedRed *= 255;

		multipliedBlue += 0.5f;
		multipliedGreen += 0.5f;
		multipliedRed += 0.5f;

		multipliedColorsPtr->blue = multipliedBlue;
		multipliedColorsPtr->green = multipliedGreen;
		multipliedColorsPtr->red = multipliedRed;

		multipliedColors.Add(multipliedColorsPtr);
	}
	string part5NameWrite = "./output/part5.tga";
	fstream part5Write(part5NameWrite, ios::out | ios::binary);
	writeHeader(part5Write, pattern1Header);

	vector<Color*> const multiplyVector = multipliedColors.getColors();
	for (long count = 0; count < multipliedColors.getColorSize(); count++) {
		Color* color = multiplyVector[count];
		part5Write.write((char*)&color->blue, sizeof(color->blue));
		part5Write.write((char*)&color->green, sizeof(color->green));
		part5Write.write((char*)&color->red, sizeof(color->red));
	}
	part5Write.close();
}

void part6(void)
{
	string carFile = "./input/car.tga";
	char* carFileBuffer = loadFileBuffer(carFile);
	char* carFileBufferHead = carFileBuffer;
	Header carHeader;
	getHeader(carHeader, carFileBuffer);
	carFileBuffer += 18;
	short carWidth = carHeader.width;
	short carHeight = carHeader.height;
	long carImageSize = (carWidth * carHeight) * 3;
	Image carImage;
	getImage(carImage, carImageSize, carFileBuffer);
	delete[] carFileBufferHead;

	vector<Color*> const carVector = carImage.getColors();
	long carVectorSize = carVector.size();
	Color* carColorPtr;

	int carColorB = 0;
	int carColorG = 0;
	int carColorR = 0;

	Image add;
	for (int count = 0; count < carVector.size(); count++) {
		carColorPtr = carVector[count];
		carColorB = carColorPtr->blue;
		carColorG = carColorPtr->green;
		carColorR = carColorPtr->red;

		int addBlue = carColorB + 0;
		int addGreen = carColorG + 200;
		int addRed = carColorR + 0;

		if (addBlue > 255) {
			addBlue = 255;
		}
		if (addGreen > 255) {
			addGreen = 255;
		}
		if (addRed > 255) {
			addRed = 255;
		}

		Color* addColorPtr = new Color();
		addColorPtr->blue = addBlue;
		addColorPtr->green = addGreen;
		addColorPtr->red = addRed;

		add.Add(addColorPtr);
	}

	string part6NameWrite = "./output/part6.tga";
	fstream part6Write(part6NameWrite, ios::out | ios::binary);
	writeHeader(part6Write, carHeader);

	vector<Color*> const addVector = add.getColors();
	for (long addCount = 0; addCount < add.getColorSize(); addCount++) {
		Color* addColor = addVector[addCount];
		part6Write.write((char*)&addColor->blue, sizeof(addColor->blue));
		part6Write.write((char*)&addColor->green, sizeof(addColor->green));
		part6Write.write((char*)&addColor->red, sizeof(addColor->red));
	}
	part6Write.close();
}

void part7(void)
{
	string carFile = "./input/car.tga";
	char* carFileBuffer = loadFileBuffer(carFile);
	char* carFileBufferHead = carFileBuffer;
	Header carHeader;
	getHeader(carHeader, carFileBuffer);
	carFileBuffer += 18;
	short carWidth = carHeader.width;
	short carHeight = carHeader.height;
	long carImageSize = (carWidth * carHeight) * 3;
	Image carImage;
	getImage(carImage, carImageSize, carFileBuffer);
	delete[] carFileBufferHead;

	vector<Color*> const carVector = carImage.getColors();
	long carVectorSize = carVector.size();
	Color* carColorPtr;

	float carColorB = 0;
	float carColorG = 0;
	float carColorR = 0;

	Image multiply;
	for (int count = 0; count < carVector.size(); count++) {
		Color* multipliedColorsPtr = new Color();
		carColorPtr = carVector[count];
		carColorB = carColorPtr->blue;
		carColorG = carColorPtr->green;
		carColorR = carColorPtr->red;

		float carBlue = carColorB / 255;
		float carGreen = carColorG / 255;
		float carRed = carColorR / 255;

		float multipliedBlue = carBlue * 0;
		float multipliedGreen = carGreen;
		float multipliedRed = carRed * 4;

		multipliedBlue *= 255;
		multipliedGreen *= 255;
		multipliedRed *= 255;

		multipliedBlue += 0.5f;
		multipliedGreen += 0.5f;
		multipliedRed += 0.5f;

		if (multipliedBlue > 255) {
			multipliedBlue = 255;
		}
		if (multipliedGreen > 255) {
			multipliedGreen = 255;
		}
		if (multipliedRed > 255) {
			multipliedRed = 255;
		}

		multipliedColorsPtr->blue = multipliedBlue;
		multipliedColorsPtr->green = multipliedGreen;
		multipliedColorsPtr->red = multipliedRed;

		multiply.Add(multipliedColorsPtr);
	}
	
	string part7NameWrite = "./output/part7.tga";
	fstream part7Write(part7NameWrite, ios::out | ios::binary);
	writeHeader(part7Write, carHeader);

	vector<Color*> const multiplyVector = multiply.getColors();
	for (long count = 0; count < multiply.getColorSize(); count++) {
		Color* color = multiplyVector[count];
		part7Write.write((char*)&color->blue, sizeof(color->blue));
		part7Write.write((char*)&color->green, sizeof(color->green));
		part7Write.write((char*)&color->red, sizeof(color->red));
	}
	part7Write.close();
}

void part8(void)
{
	string carFile = "./input/car.tga";
	char* carFileBuffer = loadFileBuffer(carFile);
	char* carFileBufferHead = carFileBuffer;
	Header carHeader;
	getHeader(carHeader, carFileBuffer);
	carFileBuffer += 18;
	short carWidth = carHeader.width;
	short carHeight = carHeader.height;
	long carImageSize = (carWidth * carHeight * 3);
	Image carImage;
	getImage(carImage, carImageSize, carFileBuffer);
	delete[] carFileBufferHead;

	vector<Color*> const carVector = carImage.getColors();
	long carVectorSize = carVector.size();
	Color* carColorPtr;

	float carColorB = 0;
	float carColorG = 0;
	float carColorR = 0;

	Image multiply;
	Image red;
	Image blue;
	Image green;

	for (int count = 0; count < carVector.size(); count ++) {
		Color* bluePtr = new Color();
		Color* greenPtr = new Color();
		Color* redPtr = new Color();

		carColorPtr = carVector[count];
		carColorB = carColorPtr->blue;
		carColorG = carColorPtr->green;
		carColorR = carColorPtr->red;

		bluePtr->blue = carColorB;
		blue.Add(bluePtr);
	
		greenPtr->green = carColorG;
		green.Add(greenPtr);

		redPtr->red = carColorR;
		red.Add(redPtr);
	}
	//write blue channel
	string part8BlueNameWrite = "./output/part8_b.tga";
	fstream part8BlueWrite(part8BlueNameWrite, ios::out | ios::binary);
	writeHeader(part8BlueWrite, carHeader);

	vector<Color*> const part8BlueVector = blue.getColors();
	for (long blueCount = 0; blueCount < blue.getColorSize(); blueCount++) {
		Color* blueColor = part8BlueVector[blueCount];
		part8BlueWrite.write((char*)&blueColor->blue, sizeof(blueColor->blue));
		part8BlueWrite.write((char*)&blueColor->blue, sizeof(blueColor->blue));
		part8BlueWrite.write((char*)&blueColor->blue, sizeof(blueColor->blue));
	}
	part8BlueWrite.close();

	//write green channel
	string part8GreenNameWrite = "./output/part8_g.tga";
	fstream part8GreenWrite(part8GreenNameWrite, ios::out | ios::binary);
	writeHeader(part8GreenWrite, carHeader);

	vector<Color*> const part8GreenVector = green.getColors();
	for (long greenCount = 0; greenCount < green.getColorSize(); greenCount++) {
		Color* greenColor = part8GreenVector[greenCount];
		part8GreenWrite.write((char*)&greenColor->green, sizeof(greenColor->green));
		part8GreenWrite.write((char*)&greenColor->green, sizeof(greenColor->green));
		part8GreenWrite.write((char*)&greenColor->green, sizeof(greenColor->green));
	}
	part8GreenWrite.close();

	//write red channel
	string part8RedNameWrite = "./output/part8_r.tga";
	fstream part8RedWrite(part8RedNameWrite, ios::out | ios::binary);
	writeHeader(part8RedWrite, carHeader);

	vector<Color*> const part8RedVector = red.getColors();
	for (long redCount = 0; redCount < red.getColorSize(); redCount++) {
		Color* redColor = part8RedVector[redCount];
		part8RedWrite.write((char*)&redColor->red, sizeof(redColor->red));
		part8RedWrite.write((char*)&redColor->red, sizeof(redColor->red));
		part8RedWrite.write((char*)&redColor->red, sizeof(redColor->red));
	}
	part8RedWrite.close();
}

void part9(void)
{
	string layerRFile = "./input/layer_red.tga";
	char* layerRFileBuffer = loadFileBuffer(layerRFile);
	char* layerRFileBufferHead = layerRFileBuffer;
	Header layerRHeader;
	getHeader(layerRHeader, layerRFileBuffer);
	layerRFileBuffer += 18;
	short layerRWidth = layerRHeader.width;
	short layerRHeight = layerRHeader.height;
	long layerRImageSize = (layerRWidth * layerRHeight * 3);
	Image layerRImage;
	getImage(layerRImage, layerRImageSize, layerRFileBuffer);
	delete[] layerRFileBufferHead;

	string layerGFile = "./input/layer_green.tga";
	char* layerGFileBuffer = loadFileBuffer(layerGFile);
	char* layerGFileBufferHead = layerGFileBuffer;
	Header layerGHeader;
	getHeader(layerGHeader, layerGFileBuffer);
	layerGFileBuffer += 18;
	short layerGWidth = layerGHeader.width;
	short layerGHeight = layerGHeader.height;
	long layerGImageSize = (layerGWidth * layerGHeight * 3);
	Image layerGImage;
	getImage(layerGImage, layerGImageSize, layerGFileBuffer);
	delete[] layerGFileBufferHead;

	string layerBFile = "./input/layer_blue.tga";
	char* layerBFileBuffer = loadFileBuffer(layerBFile);
	char* layerBFileBufferHead = layerBFileBuffer;
	Header layerBHeader;
	getHeader(layerBHeader, layerBFileBuffer);
	layerBFileBuffer += 18;
	short layerBWidth = layerBHeader.width;
	short layerBHeight = layerBHeader.height;
	long layerBImageSize = (layerBWidth * layerBHeight * 3);
	Image layerBImage;
	getImage(layerBImage, layerBImageSize, layerBFileBuffer);
	delete[] layerBFileBufferHead;

	vector<Color*> const layerBVector = layerBImage.getColors();
	vector<Color*> const layerGVector = layerGImage.getColors();
	vector<Color*> const layerRVector = layerRImage.getColors();

	Color* colorPtrB;
	Color* colorPtrG;
	Color* colorPtrR;	

	int layerBColorB = 0;
	int layerBColorG = 0;
	int layerBColorR = 0;

	int layerGColorB = 0;
	int layerGColorG = 0;
	int layerGColorR = 0;

	int layerRColorB = 0;
	int layerRColorG = 0;
	int layerRColorR = 0;

	Image newColorsImage;
	for (int count = 0; count < layerRVector.size(); count++) {
		Color* newColors = new Color();
		colorPtrB = layerBVector[count];
		layerBColorB = colorPtrB->blue;
		layerBColorG = colorPtrB->green;
		layerBColorR = colorPtrB->red;

		colorPtrG = layerGVector[count];
		layerGColorB = colorPtrG->blue;
		layerGColorG= colorPtrG->green;
		layerGColorR = colorPtrG->red;

		colorPtrR = layerRVector[count];
		layerRColorB = colorPtrR->blue;
		layerRColorG = colorPtrR->green;
		layerRColorR = colorPtrR->red;

		newColors->blue = layerBColorB;
		newColors->green = layerGColorG;
		newColors->red = layerRColorR;
		newColorsImage.Add(newColors);
	}
	string part9NameWrite = "./output/part9.tga";
	fstream part9Write(part9NameWrite, ios::out | ios::binary);
	writeHeader(part9Write, layerGHeader);

	vector<Color*> const newColorsVector = newColorsImage.getColors();
	for (long count = 0; count < newColorsImage.getColorSize(); count++) {
		Color* color = newColorsVector[count];
		part9Write.write((char*)&color->blue, sizeof(color->blue));
		part9Write.write((char*)&color->green, sizeof(color->green));
		part9Write.write((char*)&color->red, sizeof(color->red));
	}
	part9Write.close();
}

void part10(void)
{
	string text2 = "./input/text2.tga";
	char* text2Buffer = loadFileBuffer(text2);
	char* text2BufferHead = text2Buffer;
	Header text2Header;
	getHeader(text2Header, text2Buffer);
	text2Buffer += 18;
	short text2Width = text2Header.width;
	short text2Height = text2Header.height;
	long text2ImageSize = (text2Width * text2Height) * 3;
	Image text2Image;
	getImage(text2Image, text2ImageSize, text2Buffer);
	delete[] text2BufferHead;

	vector<Color*> const textColors = text2Image.getColors();
	Color* textColorPtr;

	float textColorB = 0.0;
	float textColorG = 0.0;
	float textColorR = 0.0;

	Image rotatedImage;
	for (int count = 0; count < textColors.size(); count++) {
		Color* rotatedPtr = new Color();
		textColorPtr = textColors[count];
		textColorB = textColorPtr->blue;
		textColorG = textColorPtr->green;
		textColorR = textColorPtr->red;

		rotatedPtr->blue = textColorB;
		rotatedPtr->green = textColorG;
		rotatedPtr->red = textColorR;

		rotatedImage.Add(rotatedPtr);
	}

	string part10NameWrite = "./output/part10.tga";
	fstream part10Write(part10NameWrite, ios::out | ios::binary);
	writeHeader(part10Write, text2Header);

	vector<Color*> const rotatedColorsVector = rotatedImage.getColors();
	for (long count = rotatedImage.getColorSize(); count > 0; count--) {
		Color* roatedColorsPtr = rotatedColorsVector[count-1];
		part10Write.write((char*)&roatedColorsPtr->blue, sizeof(roatedColorsPtr->blue));
		part10Write.write((char*)&roatedColorsPtr->green, sizeof(roatedColorsPtr->green));
		part10Write.write((char*)&roatedColorsPtr->red, sizeof(roatedColorsPtr->red));
	}
	part10Write.close();
}

void part11(void)
{
	string carFile = "./input/car.tga";
	char* carFileBuffer = loadFileBuffer(carFile);
	char* carFileBufferHead = carFileBuffer;
	Header carHeader;
	getHeader(carHeader, carFileBuffer);
	carFileBuffer += 18;
	short carWidth = carHeader.width;
	short carHeight = carHeader.height;
	long carImageSize = ((carWidth * carHeight)*3);
	Image carImage;
	getImage(carImage, carImageSize, carFileBuffer);
	delete[] carFileBufferHead;

	string circle = "./input/circles.tga";
	char* circleBuffer = loadFileBuffer(circle);
	char* circleBufferHead = circleBuffer;
	Header circleHeader;
	getHeader(circleHeader, circleBuffer);
	circleBuffer += 18;
	short circleWidth = circleHeader.width;
	short circleHeight = circleHeader.height;
	long circleImageSize = (circleWidth * circleHeight) * 3;
	Image circleImage;
	getImage(circleImage, circleImageSize, circleBuffer);
	delete[] circleBufferHead;

	string pattern1 = "./input/pattern1.tga";
	char* pattern1FileBuffer = loadFileBuffer(pattern1);
	char* pattern1FileBufferHead = pattern1FileBuffer;
	Header pattern1Header;
	getHeader(pattern1Header, pattern1FileBuffer);
	pattern1FileBuffer += 18;
	short pattern1Width = pattern1Header.width;
	short pattern1Height = pattern1Header.height;
	long pattern1ImageSize = (pattern1Width * pattern1Height) * 3;
	Image pattern1Image;
	getImage(pattern1Image, pattern1ImageSize, pattern1FileBuffer);
	delete[] pattern1FileBufferHead;

	string text = "./input/text.tga";
	char* textBuffer = loadFileBuffer(text);
	char* textBufferHead = textBuffer;
	Header textHeader;
	getHeader(textHeader, textBuffer);
	textBuffer += 18;
	short textWidth = textHeader.width;
	short textHeight = textHeader.height;
	long textImageSize = (textWidth * textHeight)*3;
	Image textImage;
	getImage(textImage, textImageSize, textBuffer);
	delete[] textBufferHead;

	long newImageSize = ((1024 * 1024) * 3);
	char* newImageBuffer = new char[newImageSize];
	string extraCredit = "./output/extracredit.tga";
	fstream extraCreditWrite(extraCredit, ios::out | ios::binary);
	carHeader.width = 1024;
	carHeader.height = 1024;
	writeHeader(extraCreditWrite, carHeader);

	// write text image
	vector<Color*> const textVector = textImage.getColors();
	char* newImageBufferPtr = newImageBuffer;
	for (long count = 0, pixelCount=0; count < textImage.getColorSize(); count++) {
		Color* color = textVector[count];
		memcpy(newImageBufferPtr++, &color->blue, sizeof(color->blue));
		memcpy(newImageBufferPtr++, &color->green, sizeof(color->green));
		memcpy(newImageBufferPtr++, &color->red, sizeof(color->red));
		pixelCount += 3;
		if (pixelCount == 1536) {
			pixelCount = 0;
			int skipToNextLineCount = 1536;
			newImageBufferPtr += skipToNextLineCount;
		}
	}

	// write circle image
	vector<Color*> const circleVector = circleImage.getColors();
	newImageBufferPtr = newImageBuffer;
	newImageBufferPtr += 1574400;
	for (long count = 0, pixelCount = 0; count < pattern1Image.getColorSize(); count++) {
		Color* color = circleVector[count];
		memcpy(newImageBufferPtr++, &color->blue, sizeof(color->blue));
		memcpy(newImageBufferPtr++, &color->green, sizeof(color->green));
		memcpy(newImageBufferPtr++, &color->red, sizeof(color->red));
		pixelCount += 3;
		if (pixelCount == 1536) {
			pixelCount = 0;
			int skipToNextLineCount = 1536;
			newImageBufferPtr += skipToNextLineCount;
		}
	}

	// write car image
	vector<Color*> const carVector = carImage.getColors();
	newImageBufferPtr = newImageBuffer;
	newImageBufferPtr += 1572864;
	for (long count = 0, pixelCount = 0; count < pattern1Image.getColorSize(); count++) {
		Color* color = carVector[count];
		memcpy(newImageBufferPtr++, &color->blue, sizeof(color->blue));
		memcpy(newImageBufferPtr++, &color->green, sizeof(color->green));
		memcpy(newImageBufferPtr++, &color->red, sizeof(color->red));
		pixelCount += 3;
		if (pixelCount == 1536) {
			pixelCount = 0;
			int skipToNextLineCount = 1536;
			newImageBufferPtr += skipToNextLineCount;
		}
	}
	
	// write pattern image
	vector<Color*> const pattern1Vector = pattern1Image.getColors();
	newImageBufferPtr = newImageBuffer;
	newImageBufferPtr += 1536; 
	for (long count = 0, pixelCount = 0; count < pattern1Image.getColorSize(); count++) {
		Color* color = pattern1Vector[count];
		memcpy(newImageBufferPtr++, &color->blue, sizeof(color->blue));
		memcpy(newImageBufferPtr++, &color->green, sizeof(color->green));
		memcpy(newImageBufferPtr++, &color->red, sizeof(color->red));
		pixelCount += 3;
		if (pixelCount == 1536) {
			pixelCount = 0;
			int skipToNextLineCount = 1536;
			newImageBufferPtr += skipToNextLineCount;
		}
	}
	extraCreditWrite.write((char*)newImageBuffer, newImageSize);
	extraCreditWrite.close();
	delete[] newImageBuffer;
}

void Multiply(Image& image1, Image& image2, Image& multipliedColors)
{
	vector<Color*> const image1Vector = image1.getColors();
	vector<Color*> const image2Vector = image2.getColors();
	long image1VectorSize = image1Vector.size();
	long image2VectorSize = image2Vector.size();

	Color* image1Ptr;
	Color* image2Ptr;
	
	float image1ColorB = 0.0;
	float image1ColorG = 0.0;
	float image1ColorR = 0.0;
	float image2ColorB = 0.0;
	float image2ColorG = 0.0;
	float image2ColorR = 0.0;

	for (int count = 0; count < image1Vector.size(); count++) {
		Color* multipliedColorsPtr = new Color();
		image1Ptr = image1Vector[count];
		image1ColorB = image1Ptr->blue;
		image1ColorG = image1Ptr->green;
		image1ColorR = image1Ptr->red;

		float image1Blue = image1ColorB / 255;
		float image1Green = image1ColorG / 255;
		float image1Red = image1ColorR / 255;

		image2Ptr = image2Vector[count];
		image2ColorB = image2Ptr->blue;
		image2ColorG = image2Ptr->green;
		image2ColorR = image2Ptr->red;

		float image2Blue = image2ColorB / 255;
		float image2Green = image2ColorG / 255;
		float image2Red = image2ColorR / 255;

		float multipliedBlue = image1Blue * image2Blue;
		float multipliedGreen = image1Green * image2Green;
		float multipliedRed = image1Red * image2Red;

		multipliedBlue *= 255;
		multipliedGreen *= 255;
		multipliedRed *= 255;

		multipliedBlue += 0.5f;
		multipliedGreen += 0.5f;
		multipliedRed += 0.5f;

		multipliedColorsPtr->blue = multipliedBlue;
		multipliedColorsPtr->green = multipliedGreen;
		multipliedColorsPtr->red = multipliedRed;

		multipliedColors.Add(multipliedColorsPtr);
	}
}

char* loadFileBuffer(string filename) {
	fstream layer1file(filename, ios::in | ios::binary | ios::ate);
	long layer1FileSize = layer1file.tellg();
	layer1file.seekg(0, ios::beg);
	char* fileBuffer = new char[layer1FileSize];
	layer1file.read(fileBuffer, layer1FileSize);
	layer1file.close();
	return fileBuffer;
}

void getHeader(Header& header, char *fileBuffer) {
	memcpy(&header.idLength, fileBuffer, sizeof(header.idLength));
	fileBuffer += sizeof(header.idLength);
	memcpy(&header.colorMapType, fileBuffer, sizeof(header.colorMapType));
	fileBuffer += sizeof(header.colorMapType);
	memcpy(&header.dataTypeCode, fileBuffer, sizeof(header.dataTypeCode));
	fileBuffer += sizeof(header.dataTypeCode);
	memcpy(&header.colorMapOrigin, fileBuffer, sizeof(header.colorMapOrigin));
	fileBuffer += sizeof(header.colorMapOrigin);
	memcpy(&header.colorMapLength, fileBuffer, sizeof(header.colorMapLength));
	fileBuffer += sizeof(header.colorMapLength);
	memcpy(&header.colorMapDepth, fileBuffer, sizeof(header.colorMapDepth));
	fileBuffer += sizeof(header.colorMapDepth);
	memcpy(&header.xOrigin, fileBuffer, sizeof(header.xOrigin));
	fileBuffer += sizeof(header.xOrigin);
	memcpy(&header.yOrigin, fileBuffer, sizeof(header.yOrigin));
	fileBuffer += sizeof(header.yOrigin);
	memcpy(&header.width, fileBuffer, sizeof(header.width));
	fileBuffer += sizeof(header.width);
	memcpy(&header.height, fileBuffer, sizeof(header.height));
	fileBuffer += sizeof(header.height);
	memcpy(&header.bitsPerPixel, fileBuffer, sizeof(header.bitsPerPixel));
	fileBuffer += sizeof(header.bitsPerPixel);
	memcpy(&header.imageDescriptor, fileBuffer, sizeof(header.imageDescriptor));
	fileBuffer += sizeof(header.imageDescriptor);
}

void getImage(Image& image, long imageSize, char* fileBuffer) {
	for (long count = 0; count < imageSize; count += 3) {
		Color* color = new Color();
		memcpy(&color->blue, fileBuffer, sizeof(color->blue));
		fileBuffer += sizeof(color->blue);
		memcpy(&color->green, fileBuffer, sizeof(color->green));
		fileBuffer += sizeof(color->green);
		memcpy(&color->red, fileBuffer, sizeof(color->red));
		fileBuffer += sizeof(color->red);
		image.Add(color);
	}
}

void writeHeader(fstream& fileWrite, Header& header) {
	fileWrite.write((char*)&header.idLength, sizeof(header.idLength));
	fileWrite.write((char*)&header.colorMapType, sizeof(header.colorMapType));
	fileWrite.write((char*)&header.dataTypeCode, sizeof(header.dataTypeCode));
	fileWrite.write((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
	fileWrite.write((char*)&header.colorMapLength, sizeof(header.colorMapLength));
	fileWrite.write((char*)&header.colorMapDepth, sizeof(header.colorMapDepth));
	fileWrite.write((char*)&header.xOrigin, sizeof(header.xOrigin));
	fileWrite.write((char*)&header.yOrigin, sizeof(header.yOrigin));
	fileWrite.write((char*)&header.width, sizeof(header.width));
	fileWrite.write((char*)&header.height, sizeof(header.height));
	fileWrite.write((char*)&header.bitsPerPixel, sizeof(header.bitsPerPixel));
	fileWrite.write((char*)&header.imageDescriptor, sizeof(header.imageDescriptor));
}

void writeBonusHeader(fstream& fileWrite, Header& header) {
	short p = 20;
	short d = 256;
	short c = 1024;
	fileWrite.write((char*)&header.idLength, sizeof(header.idLength));
	fileWrite.write((char*)&header.colorMapType, sizeof(header.colorMapType));
	fileWrite.write((char*)&header.dataTypeCode, sizeof(header.dataTypeCode));
	fileWrite.write((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
	fileWrite.write((char*)&header.colorMapLength, sizeof(header.colorMapLength));
	fileWrite.write((char*)&header.colorMapDepth, sizeof(header.colorMapDepth));
	fileWrite.write((char*)&p, sizeof(p));
	fileWrite.write((char*)&p, sizeof(p));
	fileWrite.write((char*)&c, sizeof(c));
	fileWrite.write((char*)&c, sizeof(c));
	fileWrite.write((char*)&header.bitsPerPixel, sizeof(header.bitsPerPixel));
	fileWrite.write((char*)&header.imageDescriptor, sizeof(header.imageDescriptor));
}

bool Test1()
{
	string actualTestImageFile = "./examples/EXAMPLE_part1.tga";
	string myTestImageFile = "./output/part1.tga";
	cout << "Calling CompareImageFiles() with " << actualTestImageFile << " and " << myTestImageFile << endl;
	return (CompareImageFiles(actualTestImageFile, myTestImageFile));
}

bool Test2()
{
	string actualTestImageFile = "./examples/EXAMPLE_part2.tga";
	string myTestImageFile = "./output/part2.tga";
	cout << "Calling CompareImageFiles() with " << actualTestImageFile << " and " << myTestImageFile << endl;
	return (CompareImageFiles(actualTestImageFile, myTestImageFile));
}

bool Test3()
{
	string actualTestImageFile = "./examples/EXAMPLE_part3.tga";
	string myTestImageFile = "./output/part3.tga";
	cout << "Calling CompareImageFiles() with " << actualTestImageFile << " and " << myTestImageFile << endl;
	return (CompareImageFiles(actualTestImageFile, myTestImageFile));
}

bool Test4()
{
	string actualTestImageFile = "./examples/EXAMPLE_part4.tga";
	string myTestImageFile = "./output/part4.tga";
	cout << "Calling CompareImageFiles() with " << actualTestImageFile << " and " << myTestImageFile << endl;
	return (CompareImageFiles(actualTestImageFile, myTestImageFile));
}

bool Test5()
{
	string actualTestImageFile = "./examples/EXAMPLE_part5.tga";
	string myTestImageFile = "./output/part5.tga";
	cout << "Calling CompareImageFiles() with " << actualTestImageFile << " and " << myTestImageFile << endl;
	return (CompareImageFiles(actualTestImageFile, myTestImageFile));
}

bool Test6()
{
	string actualTestImageFile = "./examples/EXAMPLE_part6.tga";
	string myTestImageFile = "./output/part6.tga";
	cout << "Calling CompareImageFiles() with " << actualTestImageFile << " and " << myTestImageFile << endl;
	return (CompareImageFiles(actualTestImageFile, myTestImageFile));
}

bool Test7()
{
	string actualTestImageFile = "./examples/EXAMPLE_part7.tga";
	string myTestImageFile = "./output/part7.tga";
	cout << "Calling CompareImageFiles() with " << actualTestImageFile << " and " << myTestImageFile << endl;
	return (CompareImageFiles(actualTestImageFile, myTestImageFile));
}

bool Test8Blue()
{
	string actualTest1ImageFile = "./examples/EXAMPLE_part8_b.tga";
	string myTest1ImageFile = "./output/part8_b.tga";
	cout << "Calling CompareImageFiles() with " << actualTest1ImageFile << " and " << myTest1ImageFile << endl;
	return (CompareImageFiles(actualTest1ImageFile, myTest1ImageFile));
}

bool Test8Green()
{
	string actualTest2ImageFile = "./examples/EXAMPLE_part8_g.tga";
	string myTest2ImageFile = "./output/part8_g.tga";
	cout << "Calling CompareImageFiles() with " << actualTest2ImageFile << " and " << myTest2ImageFile << endl;
	return (CompareImageFiles(actualTest2ImageFile, myTest2ImageFile));
}

bool Test8Red()
{
	string actualTest3ImageFile = "./examples/EXAMPLE_part8_r.tga";
	string myTest3ImageFile = "./output/part8_r.tga";
	cout << "Calling CompareImageFiles() with " << actualTest3ImageFile << " and " << myTest3ImageFile << endl;
	return (CompareImageFiles(actualTest3ImageFile, myTest3ImageFile));
}

bool Test9()
{
	string actualTestImageFile = "./examples/EXAMPLE_part9.tga";
	string myTestImageFile = "./output/part9.tga";
	cout << "Calling CompareImageFiles() with " << actualTestImageFile << " and " << myTestImageFile << endl;
	return (CompareImageFiles(actualTestImageFile, myTestImageFile));
}

bool Test10()
{
	string actualTestImageFile = "./examples/EXAMPLE_part10.tga";
	string myTestImageFile = "./output/part10.tga";
	cout << "Calling CompareImageFiles() with " << actualTestImageFile << " and " << myTestImageFile << endl;
	return (CompareImageFiles(actualTestImageFile, myTestImageFile));
}

bool Test11()
{
	string actualTestImageFile = "./examples/EXAMPLE_extracredit.tga";
	string myTestImageFile = "./output/extracredit.tga";
	cout << "Calling CompareImageFiles() with " << actualTestImageFile << " and " << myTestImageFile << endl;
	return (CompareImageFiles(actualTestImageFile, myTestImageFile));
}

bool CompareImageFiles(string actualFile, string myFile)
{
	char* actualFileBuffer = loadFileBuffer(actualFile);
	char* actualFileBufferHead = actualFileBuffer;
	Header actualHeader;
	getHeader(actualHeader, actualFileBuffer);
	actualFileBuffer += 18; 
	short actualWidth = actualHeader.width;
	short actualHeight = actualHeader.height;
	long actualImageSize = (actualWidth * actualHeight) * 3;
	Image actualImage;
	getImage(actualImage, actualImageSize, actualFileBuffer);
	delete[] actualFileBufferHead;

	char* myFileBuffer = loadFileBuffer(myFile);
	char* myFileBufferHead = myFileBuffer; 
	Header myHeader;
	getHeader(myHeader, myFileBuffer);
	myFileBuffer += 18; 
	short myWidth = myHeader.width;
	short myHeight = myHeader.height;
	long myImageSize = (myWidth * myHeight) * 3;
	Image myImage;
	getImage(myImage, myImageSize, myFileBuffer);
	delete[] myFileBufferHead;

	bool testFailed = false;
	int matchingHeaderCount = 0;
	
	if (actualHeader.idLength != myHeader.idLength) {
		testFailed = true;
	}
	else {
		matchingHeaderCount++;
	}

	if (actualHeader.colorMapType != myHeader.colorMapType) {
		testFailed = true;
	}
	else {
		matchingHeaderCount++;
	}

	if (actualHeader.dataTypeCode != myHeader.dataTypeCode) {
		testFailed = true;
	}
	else {
		matchingHeaderCount++;
	}

	if (actualHeader.colorMapOrigin != myHeader.colorMapOrigin) {
		testFailed = true;
	}
	else {
		matchingHeaderCount++;
	}

	if (actualHeader.colorMapLength != myHeader.colorMapLength) {
		testFailed = true;
	}
	else {
		matchingHeaderCount++;
	}

	if (actualHeader.colorMapDepth != myHeader.colorMapDepth) {
		testFailed = true;
	}
	else {
		matchingHeaderCount++;
	}

	if (actualHeader.xOrigin != myHeader.xOrigin) {
		testFailed = true;
	}
	else {
		matchingHeaderCount++;
	}

	if (actualHeader.yOrigin != myHeader.yOrigin) {
		testFailed = true;
	}
	else {
		matchingHeaderCount++;
	}

	if (actualHeader.width != myHeader.width) {
		testFailed = true;
	}
	else {
		matchingHeaderCount++;
	}

	if (actualHeader.height != myHeader.height) {
		testFailed = true;
	}
	else {
		matchingHeaderCount++;
	}

	if (actualHeader.bitsPerPixel != myHeader.bitsPerPixel) {
		testFailed = true;
	}
	else {
		matchingHeaderCount++;
	}

	if (actualHeader.imageDescriptor != myHeader.imageDescriptor) {
		testFailed = true;
	}
	else {
		matchingHeaderCount++;
	}

	cout << "Comparing image headers..." << endl;
	cout << "Expected result of: " << " 12 identical header fields" << endl;
	cout << "Actual result of: " << matchingHeaderCount << " identical header fields" << endl;
	if (12 != matchingHeaderCount) {
		cout << "Test failed!" << endl << endl;
		testFailed = true;
	}
	else {
		cout << "Test successful!" << endl << endl;
	}

	cout << "Comparing image sizes..." << endl;
	cout << "Expected result of: " << actualImage.getColorSize() << " pixels" << endl;
	cout << "Actual result of: " << myImage.getColorSize() << " pixels" << endl;
	if (actualImage.getColorSize() != myImage.getColorSize()) {
		cout << "Test failed!" << endl << endl;
		testFailed = true;
	} else {
		cout << "Test successful!" << endl << endl;
	}

	cout << "Comparing each image pixel one at a time..." << endl;
	vector<Color*> const actualColors = actualImage.getColors();
	vector<Color*> const myColors = myImage.getColors();
	int matchingColor = 0;
	for (long count = 0; count < actualImage.getColorSize(); count++) {
		Color* actualColor = actualColors[count];
		Color* myColor = myColors[count];
		if (actualColor->blue == myColor->blue) {
			matchingColor++;
		}
		if (actualColor->green == myColor->green) {
			matchingColor++;
		}
		if (actualColor->red == myColor->red) {
			matchingColor++;
		}
	}

	cout << "Expected result of: " << actualImage.getColorSize()*3 << " identical pixels" << endl;
	cout << "Actual result: " << matchingColor  << " identical pixels" << endl;
	if (actualImage.getColorSize()*3 != matchingColor) {
		testFailed = true;
		cout << "Test failed!" << endl << endl;
	}
	else {
		cout << "Test successful!" << endl << endl;
	}
	return testFailed;
}