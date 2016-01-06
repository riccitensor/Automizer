#ifndef OCR_H
#define OCR_H

#include "stdafx.h"

#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <gdiplus.h>

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <tuple>
#include <vector>   
#include <map>
#include <chrono>
#include <thread>

#include <wchar.h>



#ifdef linux
#include <termios.h>
#include <sys/io.h>
#else
#include <io.h>
#include <windows.h>
#include <conio.h>
#endif

#include <stdlib.h>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <sys/stat.h>
#include <math.h>
#include <time.h>
#include <algorithm>

#include <tlhelp32.h>
#include <winuser.h>

#include <string>
#include <regex>

#undef _UNICODE


using namespace std;
using namespace Gdiplus;


using namespace std;

#include "il.h"

#pragma comment( lib, "DevIL.lib" )
#pragma comment( lib, "gdiplus.lib")



const int MAX_RANGE = 30; //value - pobrana wartosc, mark - ustalona wartosc w excel
int counter = 1;
int counter_dc = 1;


struct tournament_status
{
	//window handle
	HWND hwnd;

	//turniej -- handle moze byc potem uzywany ponownie
	string tournament_id;

	//czy nadal dziala
	int stillGoing = 1;

	//czy oczekuje akcji
	int waitsForAction = 0;


};

map <string, tournament_status> tournament_list;



bool inRange(int value, int mark){
	return value >= (mark - MAX_RANGE) && value <= (mark + MAX_RANGE);
}


vector<int> checkPixel(const char *fName, int x, int y) {

	// Loading an image
	ILboolean result = ilLoadImage(fName);


	if (result)
	{
		//printf("the image loaded successfully\n");
	}
	else
	{
		printf("The image failed to load\n");

		ILenum err = ilGetError();
		printf("the error %d\n", err);
		printf("string is %s\n", ilGetString(err));
	}

	int size = ilGetInteger(IL_IMAGE_SIZE_OF_DATA);
	//printf("Data size:  %d\n", size);
	ILubyte * bytes = ilGetData();

	int w = ilGetInteger(IL_IMAGE_WIDTH);

	int idx = 4 * (w*y + x);

	vector <int> ret;

	ret.push_back(bytes[idx]);
	ret.push_back(bytes[idx + 1]);
	ret.push_back(bytes[idx + 2]);

	return ret;
}

vector <vector<int>> getPixelRGBList(const char *fName, vector<pair<int, int>> pixels) {

	vector <vector<int>> ret;

	for (vector<pair<int, int>>::iterator it = pixels.begin(); it != pixels.end(); ++it) {
		//cout << "Vec: " << it->first << "," << it->second << endl;

		vector<int> temp = checkPixel(fName, it->first, it->second);

		ret.push_back(temp);
	}
	return ret;
}

vector<int> getPixelRGBListForPixel(const char *fName, int x, int y) {

	vector<int> ret;
	ret = checkPixel(fName, x, y);

	return ret;
}


/*
* Czytanie z pliku tupli (sekwencji liczb), wykorzystujemy do obrania equity dla zakresows
*/
vector < tuple <int, int, int, int, int> > readIndicatorsFromFile(const char *fn){

	ifstream file;
	file.open(fn);
	string line;
	int a[5]; int i=0;

	cout << " LETS START" << endl;

	vector < tuple <int, int, int, int, int> > mt;

	while (getline(file, line))
	{
		std::stringstream   linestream(line);
		std::string         value;

		while (getline(linestream, value, ';'))
		{
			std::cout << "Value(" << value << ")\n";
			a[i] = std::stoi(value);
			i++;
		}
		i = 0;

		mt.push_back(make_tuple(a[0],a[1],a[2],a[3],a[4]));

	}

	return mt;
}



void pixelListTest2(){

	int check = 0;  //zmienna ktora bedzie informowala czy liczba jest 1,2,3 czy 4 cyfrowa, jesli check = 2 to wtedy 2 cyfrowa etc
	int bet_pos_1 = 0; //zmienna oznacza ile podbil gracz na pozycji 1
	vector<pair<int, int>> pixelList;


	//-----------------------------------------------------Ponizej dla gracza na pozycji 2
	pair<int, int> a2check; //sprawdz czy liczba jest 2 czy 3 cyfrowa, zczytuje jakis pixel ktory mi powie z ilu cyfrowa liczba mam do czynienia
	a2check.first = 471;
	a2check.second = 177;
	pixelList.push_back(a2check);

	pair<int, int> ap21z2;
	ap21z2.first = 464;
	ap21z2.second = 177;
	pixelList.push_back(ap21z2);

	pair<int, int> ap22z2;
	ap22z2.first = 469;
	ap22z2.second = 177;
	pixelList.push_back(ap22z2);


	pair<int, int> ap21z3;
	ap21z3.first = 461;
	ap21z3.second = 177;
	pixelList.push_back(ap21z3);

	pair<int, int> ap22z3;
	ap22z3.first = 466;
	ap22z3.second = 177;
	pixelList.push_back(ap22z3);

	pair<int, int> ap23z3;
	ap23z3.first = 471;
	ap23z3.second = 177;
	pixelList.push_back(ap23z3);

	//-----------------------------------------------------Ponizej dla gracza na pozycji 3
	pair<int, int> a3check; //sprawdz czy liczba jest 2 czy 3 cyfrowa, zczytuje jakis pixel ktory mi powie z ilu cyfrowa liczba mam do czynienia
	a3check.first = 414;
	a3check.second = 243;
	pixelList.push_back(a3check);

	pair<int, int> ap31z2;
	ap31z2.first = 407;
	ap31z2.second = 243;
	pixelList.push_back(ap31z2);

	pair<int, int> ap32z2;
	ap32z2.first = 412;
	ap32z2.second = 243;
	pixelList.push_back(ap32z2);


	pair<int, int> ap31z3;
	ap31z3.first = 404;
	ap31z3.second = 243;
	pixelList.push_back(ap31z3);

	pair<int, int> ap32z3;
	ap32z3.first = 409;
	ap32z3.second = 243;
	pixelList.push_back(ap32z3);

	pair<int, int> ap33z3;
	ap33z3.first = 414;
	ap33z3.second = 243;
	pixelList.push_back(ap33z3);


	//-----------------------------------------------------Ponizej dla gracza na pozycji 4
	pair<int, int> a4check; //sprawdz czy liczba jest 2 czy 3 cyfrowa, zczytuje jakis pixel ktory mi powie z ilu cyfrowa liczba mam do czynienia
	a4check.first = 225;
	a4check.second = 243;
	pixelList.push_back(a4check);

	pair<int, int> ap41z2;
	ap41z2.first = 218;
	ap41z2.second = 243;
	pixelList.push_back(ap41z2);

	pair<int, int> ap42z2;
	ap42z2.first = 223;
	ap42z2.second = 243;
	pixelList.push_back(ap42z2);


	pair<int, int> ap41z3;
	ap41z3.first = 215;
	ap41z3.second = 243;
	pixelList.push_back(ap41z3);

	pair<int, int> ap42z3;
	ap42z3.first = 220;
	ap42z3.second = 243;
	pixelList.push_back(ap42z3);

	pair<int, int> ap43z3;
	ap43z3.first = 225;
	ap43z3.second = 243;
	pixelList.push_back(ap43z3);

	//-----------------------------------------------------Ponizej dla gracza na pozycji 5
	pair<int, int> a5check; //sprawdz czy liczba jest 2 czy 3 cyfrowa, zczytuje jakis pixel ktory mi powie z ilu cyfrowa liczba mam do czynienia
	a5check.first = 173;
	a5check.second = 177;
	pixelList.push_back(a5check);

	pair<int, int> ap51z2;
	ap51z2.first = 166;
	ap51z2.second = 177;
	pixelList.push_back(ap51z2);

	pair<int, int> ap52z2;
	ap52z2.first = 171;
	ap52z2.second = 177;
	pixelList.push_back(ap52z2);

	//-------------------------------
	pair<int, int> ap51z3; 
	ap51z3.first = 163;
	ap51z3.second = 177;
	pixelList.push_back(ap51z3);

	pair<int, int> ap52z3;
	ap52z3.first = 168;
	ap52z3.second = 177;
	pixelList.push_back(ap52z3);

	pair<int, int> ap53z3;
	ap53z3.first = 173;
	ap53z3.second = 177;
	pixelList.push_back(ap53z3);


	int c = 0;

	vector <vector<int>> pixels = getPixelRGBList("..\\png\\1.png", pixelList);

	for (int i = 0; i < 4; i++)
	{
		bet_pos_1 = 0;

		if ((pixels[i*6][0] == pixels[i * 6][1]) && (pixels[i * 6][1] == pixels[i * 6][2])) //tu sprawdzam wlasnie z ilu cyfrowa liczba mam do czynienia
		{
			check = 2;
		}
		else
		{

			check = 3;
		} //oczywiscie pozniej beda jeszcze warunki czy jest to liczba 1 cyfrowa, i warunek dla 4 cyfrowej

		if (check == 2) //jesli liczba 2 cyfrowa 
		{// to ponizej sprawdzam jaka to cyfra znajduje siê na miejscu dziesiatek naszej 2 cyfrowej liczby i odpowiednio j¹ przemnazam i przypisuje jakie to podbicie
			if (inRange(pixels[i * 6 + 1][0], 28) && inRange(pixels[i * 6 + 1][1], 114) && inRange(pixels[i * 6 + 1][2], 187)) bet_pos_1 = 0 * 10;
			if (inRange(pixels[i * 6 + 1][0], 152) && inRange(pixels[i * 6 + 1][1], 74) && inRange(pixels[i * 6 + 1][2], 29)) bet_pos_1 = 1 * 10;
			if (inRange(pixels[i * 6 + 1][0], 224) && inRange(pixels[i * 6 + 1][1], 224) && inRange(pixels[i * 6 + 1][2], 158)) bet_pos_1 = 2 * 10;
			if (inRange(pixels[i * 6 + 1][0], 255) && inRange(pixels[i * 6 + 1][1], 187) && inRange(pixels[i * 6 + 1][2], 114)) bet_pos_1 = 3 * 10;
			if (inRange(pixels[i * 6 + 1][0], 151) && inRange(pixels[i * 6 + 1][1], 221) && inRange(pixels[i * 6 + 1][2], 187)) bet_pos_1 = 4 * 10;
			if (inRange(pixels[i * 6 + 1][0], 255) && inRange(pixels[i * 6 + 1][1], 255) && inRange(pixels[i * 6 + 1][2], 186)) bet_pos_1 = 5 * 10;
			if (inRange(pixels[i * 6 + 1][0], 255) && inRange(pixels[i * 6 + 1][1], 255) && inRange(pixels[i * 6 + 1][2], 221)) bet_pos_1 = 6 * 10;
			if (inRange(pixels[i * 6 + 1][0], 224) && inRange(pixels[i * 6 + 1][1], 158) && inRange(pixels[i * 6 + 1][2], 86)) bet_pos_1 = 7 * 10;
			if (inRange(pixels[i * 6 + 1][0], 255) && inRange(pixels[i * 6 + 1][1], 221) && inRange(pixels[i * 6 + 1][2], 151)) bet_pos_1 = 8 * 10;
			if (inRange(pixels[i * 6 + 1][0], 255) && inRange(pixels[i * 6 + 1][1], 255) && inRange(pixels[i * 6 + 1][2], 255)) bet_pos_1 = 9 * 10;
			//tu ponizej sprawdzam jaka cyfra znajduje sie na miejscu jednosci i do podbicia dodaje jenosci
			if (inRange(pixels[i * 6 + 2][0], 28) && inRange(pixels[i * 6 + 2][1], 114) && inRange(pixels[i * 6 + 2][2], 187)) bet_pos_1 = bet_pos_1 + 0;
			if (inRange(pixels[i * 6 + 2][0], 152) && inRange(pixels[i * 6 + 2][1], 74) && inRange(pixels[i * 6 + 2][2], 29)) bet_pos_1 = bet_pos_1 + 1;
			if (inRange(pixels[i * 6 + 2][0], 224) && inRange(pixels[i * 6 + 2][1], 224) && inRange(pixels[i * 6 + 2][2], 158)) bet_pos_1 = bet_pos_1 + 2;
			if (inRange(pixels[i * 6 + 2][0], 255) && inRange(pixels[i * 6 + 2][1], 187) && inRange(pixels[i * 6 + 2][2], 114)) bet_pos_1 = bet_pos_1 + 3;
			if (inRange(pixels[i * 6 + 2][0], 151) && inRange(pixels[i * 6 + 2][1], 221) && inRange(pixels[i * 6 + 2][2], 187)) bet_pos_1 = bet_pos_1 + 4;
			if (inRange(pixels[i * 6 + 2][0], 255) && inRange(pixels[i * 6 + 2][1], 255) && inRange(pixels[i * 6 + 2][2], 186)) bet_pos_1 = bet_pos_1 + 5;
			if (inRange(pixels[i * 6 + 2][0], 255) && inRange(pixels[i * 6 + 2][1], 255) && inRange(pixels[i * 6 + 2][2], 221)) bet_pos_1 = bet_pos_1 + 6;
			if (inRange(pixels[i * 6 + 2][0], 224) && inRange(pixels[i * 6 + 2][1], 158) && inRange(pixels[i * 6 + 2][2], 86)) bet_pos_1 = bet_pos_1 + 7;
			if (inRange(pixels[i * 6 + 2][0], 255) && inRange(pixels[i * 6 + 2][1], 221) && inRange(pixels[i * 6 + 2][2], 151)) bet_pos_1 = bet_pos_1 + 8;
			if (inRange(pixels[i * 6 + 2][0], 255) && inRange(pixels[i * 6 + 2][1], 255) && inRange(pixels[i * 6 + 2][2], 255)) bet_pos_1 = bet_pos_1 + 9;
		}

		if (check == 3)
		{//analogicznie jak powyzej
			if (inRange(pixels[i * 6 + 3][0], 28) && inRange(pixels[i * 6 + 3][1], 114) && inRange(pixels[i * 6 + 3][2], 187)) bet_pos_1 = 0 * 100;
			if (inRange(pixels[i * 6 + 3][0], 152) && inRange(pixels[i * 6 + 3][1], 74) && inRange(pixels[i * 6 + 3][2], 29)) bet_pos_1 = 1 * 100;
			if (inRange(pixels[i * 6 + 3][0], 224) && inRange(pixels[i * 6 + 3][1], 224) && inRange(pixels[i * 6 + 3][2], 158)) bet_pos_1 = 2 * 100;
			if (inRange(pixels[i * 6 + 3][0], 255) && inRange(pixels[i * 6 + 3][1], 187) && inRange(pixels[i * 6 + 3][2], 114)) bet_pos_1 = 3 * 100;
			if (inRange(pixels[i * 6 + 3][0], 151) && inRange(pixels[i * 6 + 3][1], 221) && inRange(pixels[i * 6 + 3][2], 187)) bet_pos_1 = 4 * 100;
			if (inRange(pixels[i * 6 + 3][0], 255) && inRange(pixels[i * 6 + 3][1], 255) && inRange(pixels[i * 6 + 3][2], 186)) bet_pos_1 = 5 * 100;
			if (inRange(pixels[i * 6 + 3][0], 255) && inRange(pixels[i * 6 + 3][1], 255) && inRange(pixels[i * 6 + 3][2], 221)) bet_pos_1 = 6 * 100;
			if (inRange(pixels[i * 6 + 3][0], 224) && inRange(pixels[i * 6 + 3][1], 158) && inRange(pixels[i * 6 + 3][2], 86)) bet_pos_1 = 7 * 100;
			if (inRange(pixels[i * 6 + 3][0], 255) && inRange(pixels[i * 6 + 3][1], 221) && inRange(pixels[i * 6 + 3][2], 151)) bet_pos_1 = 8 * 100;
			if (inRange(pixels[i * 6 + 3][0], 255) && inRange(pixels[i * 6 + 3][1], 255) && inRange(pixels[i * 6 + 3][2], 255)) bet_pos_1 = 9 * 100;

			if (inRange(pixels[i * 6 + 4][0], 28) && inRange(pixels[i * 6 + 4][1], 114) && inRange(pixels[i * 6 + 4][2], 187)) bet_pos_1 = bet_pos_1 + 0;
			if (inRange(pixels[i * 6 + 4][0], 152) && inRange(pixels[i * 6 + 4][1], 74) && inRange(pixels[i * 6 + 4][2], 29)) bet_pos_1 = bet_pos_1 + 10;
			if (inRange(pixels[i * 6 + 4][0], 224) && inRange(pixels[i * 6 + 4][1], 224) && inRange(pixels[i * 6 + 4][2], 158)) bet_pos_1 = bet_pos_1 + 20;
			if (inRange(pixels[i * 6 + 4][0], 255) && inRange(pixels[i * 6 + 4][1], 187) && inRange(pixels[i * 6 + 4][2], 114)) bet_pos_1 = bet_pos_1 + 30;
			if (inRange(pixels[i * 6 + 4][0], 151) && inRange(pixels[i * 6 + 4][1], 221) && inRange(pixels[i * 6 + 4][2], 187)) bet_pos_1 = bet_pos_1 + 40;
			if (inRange(pixels[i * 6 + 4][0], 255) && inRange(pixels[i * 6 + 4][1], 255) && inRange(pixels[i * 6 + 4][2], 186)) bet_pos_1 = bet_pos_1 + 50;
			if (inRange(pixels[i * 6 + 4][0], 255) && inRange(pixels[i * 6 + 4][1], 255) && inRange(pixels[i * 6 + 4][2], 221)) bet_pos_1 = bet_pos_1 + 60;
			if (inRange(pixels[i * 6 + 4][0], 224) && inRange(pixels[i * 6 + 4][1], 158) && inRange(pixels[i * 6 + 4][2], 86)) bet_pos_1 = bet_pos_1 + 70;
			if (inRange(pixels[i * 6 + 4][0], 255) && inRange(pixels[i * 6 + 4][1], 221) && inRange(pixels[i * 6 + 4][2], 151)) bet_pos_1 = bet_pos_1 + 80;
			if (inRange(pixels[i * 6 + 4][0], 255) && inRange(pixels[i * 6 + 4][1], 255) && inRange(pixels[i * 6 + 4][2], 255)) bet_pos_1 = bet_pos_1 + 90;

			if (inRange(pixels[i * 6 + 5][0], 28) && inRange(pixels[i * 6 + 5][1], 114) && inRange(pixels[i * 6 + 5][2], 187)) bet_pos_1 = bet_pos_1 + 0;
			if (inRange(pixels[i * 6 + 5][0], 152) && inRange(pixels[i * 6 + 5][1], 74) && inRange(pixels[i * 6 + 5][2], 29)) bet_pos_1 = bet_pos_1 + 1;
			if (inRange(pixels[i * 6 + 5][0], 224) && inRange(pixels[i * 6 + 5][1], 224) && inRange(pixels[i * 6 + 5][2], 158)) bet_pos_1 = bet_pos_1 + 2;
			if (inRange(pixels[i * 6 + 5][0], 255) && inRange(pixels[i * 6 + 5][1], 187) && inRange(pixels[i * 6 + 5][2], 114)) bet_pos_1 = bet_pos_1 + 3;
			if (inRange(pixels[i * 6 + 5][0], 151) && inRange(pixels[i * 6 + 5][1], 221) && inRange(pixels[i * 6 + 5][2], 187)) bet_pos_1 = bet_pos_1 + 4;
			if (inRange(pixels[i * 6 + 5][0], 255) && inRange(pixels[i * 6 + 5][1], 255) && inRange(pixels[i * 6 + 5][2], 186)) bet_pos_1 = bet_pos_1 + 5;
			if (inRange(pixels[i * 6 + 5][0], 255) && inRange(pixels[i * 6 + 5][1], 255) && inRange(pixels[i * 6 + 5][2], 221)) bet_pos_1 = bet_pos_1 + 6;
			if (inRange(pixels[i * 6 + 5][0], 224) && inRange(pixels[i * 6 + 5][1], 158) && inRange(pixels[i * 6 + 5][2], 86)) bet_pos_1 = bet_pos_1 + 7;
			if (inRange(pixels[i * 6 + 5][0], 255) && inRange(pixels[i * 6 + 5][1], 221) && inRange(pixels[i * 6 + 5][2], 151)) bet_pos_1 = bet_pos_1 + 8;
			if (inRange(pixels[i * 6 + 5][0], 255) && inRange(pixels[i * 6 + 5][1], 255) && inRange(pixels[i * 6 + 5][2], 255)) bet_pos_1 = bet_pos_1 + 9;
		}//analogicznie bedzie trzeba jeszcze zrobic dla liczby 4 cyfrowej, czyli dojdzie extra 40 linijek kodu
		//i to wszystko co powyzej tylko dla pozycji gracza na miejscu 1, a mamy 6 pozycji, czylii 600 linijek kodu, ktore powinno daæ siê jakoœ skrocic
		//wspolrzedne beda ustalane recznie lub przez petlê for

		//a RGB jest juz ustalone na sta³e (oby)
		cout << "Gracz na pozycji "<<i+2<<" podbil o = " << bet_pos_1 << " zetonow" << endl;
	}

}

HWND g_HWND = NULL;




//robi sccreen okna
void printScreenWindow(){

	RECT rc;

	rc.left = 0;
	rc.top = 0;
	rc.right = 1000;
	rc.bottom = 1000;

	HWND hWnd = GetActiveWindow();

	//create
	HDC hdcScreen = GetDC(hWnd);
	HDC hdc = CreateCompatibleDC(hdcScreen);
	HBITMAP hbmp = CreateCompatibleBitmap(hdcScreen,
		rc.right - rc.left, rc.bottom - rc.top);
	SelectObject(hdc, hbmp);


	//Print to memory hdc
	PrintWindow(hWnd, hdc, PW_CLIENTONLY);

	//copy to clipboard
	OpenClipboard(NULL);
	EmptyClipboard();
	SetClipboardData(CF_BITMAP, hbmp);
	CloseClipboard();

}


//select gfx file encoder
int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes

	ImageCodecInfo* pImageCodecInfo = NULL;

	GetImageEncodersSize(&num, &size);
	if (size == 0)
		return -1;  // Failure

	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
		return -1;  // Failure

	GetImageEncoders(num, size, pImageCodecInfo);

	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  // Success
		}
	}
	free(pImageCodecInfo);
	return -1;  // Failure
}

//saving screenshots
void saveScreenshotToFile(const wchar_t *fName, HBITMAP hBitmap) {

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	Bitmap *image = new Bitmap(hBitmap, NULL);

	CLSID myClsId;
	int retVal = GetEncoderClsid(L"image/png", &myClsId);



	image->Save(fName, &myClsId, NULL);
	delete image;

	GdiplusShutdown(gdiplusToken);

}



/*saving screenshots
fName - file name
amount - how many times
interval - amount of secs
hBitmap - bitmap handle
*/
void saveScreenshot1(const wchar_t *fName, int amount, unsigned int interval, HBITMAP hBitmap, int pf = 0) {

	std::wstring s(fName);
	wchar_t val[256];

	swprintf_s(val, L"%d", pf);
	wchar_t val1[256];

	s += std::wstring(val);

	swprintf_s(val1, L".png");

	s += std::wstring(val1);
	const wchar_t *a = s.c_str();

	saveScreenshotToFile(a, hBitmap);

	//saveScreenshotToFile(szName, hBitmap);
	std::this_thread::sleep_for(std::chrono::milliseconds(interval));


}


HBITMAP GetScreenShot(void)
{
	int x1, y1, x2, y2, w, h;

	// get screen dimensions
	x1 = GetSystemMetrics(SM_XVIRTUALSCREEN);
	y1 = GetSystemMetrics(SM_YVIRTUALSCREEN);
	x2 = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	y2 = GetSystemMetrics(SM_CYVIRTUALSCREEN);
	w = x2 - x1;
	h = y2 - y1;

	// copy screen to bitmap
	HDC     hScreen = GetDC(NULL);
	HDC     hDC = CreateCompatibleDC(hScreen);
	HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, w, h);
	HGDIOBJ old_obj = SelectObject(hDC, hBitmap);
	BOOL    bRet = BitBlt(hDC, 0, 0, w, h, hScreen, x1, y1, SRCCOPY);

	return hBitmap;
}



void printScreen(HWND hwnd){

	RECT rc;
	GetClientRect(hwnd, &rc);

	//create
	HDC hdcScreen = GetDC(NULL);
	HDC hdc = CreateCompatibleDC(hdcScreen);
	HBITMAP hbmp = CreateCompatibleBitmap(hdcScreen,
		rc.right - rc.left, rc.bottom - rc.top);
	SelectObject(hdc, hbmp);

	//Print to memory hdc
	PrintWindow(hwnd, hdc, PW_CLIENTONLY);

	//copy to clipboard
	OpenClipboard(NULL);
	EmptyClipboard();
	SetClipboardData(CF_BITMAP, hbmp);

	CloseClipboard();

	//release
	DeleteDC(hdc);
	DeleteObject(hbmp);
	ReleaseDC(NULL, hdcScreen);

}



void printDataCollector(HWND handle, int iter)
{

	RECT rc;
	GetClientRect(handle, &rc);

	//create
	HDC hdcScreen = GetDC(NULL);
	HDC hdc = CreateCompatibleDC(hdcScreen);
	HBITMAP hbmp = CreateCompatibleBitmap(hdcScreen,
		rc.right - rc.left, rc.bottom - rc.top);
	SelectObject(hdc, hbmp);

	//Print to memory hdc
	PrintWindow(handle, hdc, PW_CLIENTONLY);

	//copy to clipboard
	OpenClipboard(NULL);
	EmptyClipboard();
	SetClipboardData(CF_BITMAP, hbmp);
	CloseClipboard();

	//release
	DeleteDC(hdc);
	DeleteObject(hbmp);
	ReleaseDC(NULL, hdcScreen);

	string filename = "..\\png\\testy\\";


	string s = to_string((int)handle);

	//add HWND dirs to path
	filename += s;
	//add backslash
	filename += "_";

	std::wstring widestr = std::wstring(filename.begin(), filename.end());

	const wchar_t* widecstr = widestr.c_str();

	//ITER==1 NOW --REMEMBER ABOUT IT
	saveScreenshot1(widecstr, 1, 1, hbmp, counter_dc);
}

void printScreenSaveToFile(HWND handle, int iter)
{

	RECT rc;
	GetClientRect(handle, &rc);

	//create
	HDC hdcScreen = GetDC(NULL);
	HDC hdc = CreateCompatibleDC(hdcScreen);
	HBITMAP hbmp = CreateCompatibleBitmap(hdcScreen,
		rc.right - rc.left, rc.bottom - rc.top);
	SelectObject(hdc, hbmp);

	//Print to memory hdc
	PrintWindow(handle, hdc, PW_CLIENTONLY);

	//copy to clipboard
	OpenClipboard(NULL);
	EmptyClipboard();
	SetClipboardData(CF_BITMAP, hbmp);
	CloseClipboard();

	//release
	DeleteDC(hdc);
	DeleteObject(hbmp);
	ReleaseDC(NULL, hdcScreen);

	string filename = "..\\png\\";


	string s = to_string((int)handle);

	//add HWND dirs to path
	filename += s;
	//add backslash
	filename += "_";

	std::wstring widestr = std::wstring(filename.begin(), filename.end());

	const wchar_t* widecstr = widestr.c_str();

	//ITER==1 NOW --REMEMBER ABOUT IT
	saveScreenshot1(widecstr, 1, 1, hbmp, 1);
}




bool isSubstring(string source, string what){
	if (source.find(what) != std::string::npos) {
		return true;
	}
	return false;
}



string getTournamentId(char* title){

	string ret(title);


	if (isSubstring(ret, "SNG NLH")){
		cout << "Tournament table: " << ret << endl;

		string s1 = "#";
		string s2 = "Blinds:";
		string s3 = "Table";
		std::size_t found1 = ret.find(s1) + 1;
		std::size_t found2 = ret.find(s2);
		std::size_t found3 = ret.find(s3);

		int len1 = found3 - found1 - 1;


		//if (found1 != std::string::npos)
		//	cout << "ID->" << found1 << endl;

		//if (found2 != std::string::npos)
		//	cout << "Blinds->" << found2 << endl;

		ret = ret.substr(found1, len1);
		cout << "ID = " << ret << endl;

		return ret;
	}


	return "NO";
}


bool isTournamentWindow(char* title){
	string ret(title);
	return (isSubstring(ret, "SNG NLH"));
}

bool isTournamentLobbyWindow(char* title){
	string ret(title);
	return (isSubstring(ret, "Sit & Go"));
}

bool is888(char* title){
	string ret(title);
	return (isSubstring(ret, "888poker"));
}


boolean singleButton(WORD key)
{
	INPUT iip;

	iip.type = INPUT_KEYBOARD;
	iip.ki.wScan = 0; // hardware scan code for key
	iip.ki.time = 0;
	iip.ki.dwExtraInfo = 0;

	// Press the "single" key (wejscie do paska adresu)
	iip.ki.wVk = key;
	iip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &iip, sizeof(INPUT));


	// Release the "single" key
	iip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &iip, sizeof(INPUT));
	return 0;
}

//pozycja okna
vector<int> getWindowPos(HWND hwnd)
{
	RECT lpRect;

	GetWindowRect(
		hwnd,
		&lpRect
		);

	vector<int> a;
	a.push_back(lpRect.left);
	a.push_back(lpRect.top);

	//cout << "Window " << hwnd << " Position: (" << lpRect.left << "," << lpRect.top << ")" << endl;

	return a;
}


vector<int> moveMouseInWindow(HWND hwnd, int x, int y){

	RECT lpRect;

	GetWindowRect(
		hwnd,
		&lpRect
		);

	vector<int> a;
	a.push_back(lpRect.left);
	a.push_back(lpRect.top);

	SetCursorPos(x + lpRect.left, y + lpRect.top);

	return a;
}


void  mouseClick(HWND hwnd, int x, int y){

	SetCursorPos(x, y);


	SetForegroundWindow(hwnd);
	SetActiveWindow(hwnd);


	INPUT    Input = { 0 };
	// left down 
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	::SendInput(1, &Input, sizeof(INPUT));

	// left up
	::ZeroMemory(&Input, sizeof(INPUT));
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	::SendInput(1, &Input, sizeof(INPUT));
}

//uruchom FOLD
void clickFold(HWND hwnd){
	SetForegroundWindow(hwnd);
	singleButton(VK_F5);
}

//uruchom CALL
void clickCall(HWND hwnd){
	SetForegroundWindow(hwnd);
	singleButton(VK_F6);
}

//uruchom BET
void clickBet(HWND hwnd, int size){
	SetForegroundWindow(hwnd);
	SetActiveWindow(hwnd);
	SetFocus(hwnd);

	//SetCursorPos(rect.right - 200, rect.bottom - 200);
}

void clickAllIn(HWND hwnd, string s){

	/*
	Procedura:
	1) pobieramy RGB dla (575;375), jesli !(R=G=B) wtedy ustawiamy tam kursor myszki i klikamy (w tym miejscu jest przycisk max). Pozniej przenosimy kursor na (570;364) i klikamy (to jest przycisk All IN). Dla pewnosci mozemy pobrac kolor przed kliknieciem (jesli R=255 +/- range) to klikamy, jesli R!=255 patrz punkt 3
	2) jesli rgb dla (575;375) R=G=B to wtedy pobieramy kolor dla (570;364), jesli R=255 +/- range to klikamy, jesli nie to patrz punkt 3
	3) pobieramy kolor dla (440,364), jesli R=255 +/-range to klikamy

	jesli nie 1) nie 2) nie 3) to wtedy wystapil ten bardzo rzadki przypadek (lub czegos nie przewidzialem i wyjdzie to w testach)
	*/

	SetForegroundWindow(hwnd);
	SetActiveWindow(hwnd);
	//SetFocus(hwnd);

	//read pos
	vector<int> pos = getWindowPos(hwnd);


	///////---------------------------------------DO WE NEED THIS SCREENSHOT MAKING???
	s = "..\\png\\";
	string s2 = "_1.png";
	string h = to_string((int)hwnd);

	//handle in the file name
	s += h;
	//_1.png in the file name
	s += s2;

	printScreenSaveToFile(hwnd, 1);


	int x1 = 575, y1 = 375;
	int x2 = 570, y2 = 358;
	int x3 = 440, y3 = 358;

	vector<int> rgb = checkPixel(s.c_str(), x1, y1);

	int a = rgb[0];
	int b = rgb[1];
	int c = rgb[2];

	vector<int> p = getWindowPos(hwnd);


	if (!inRange(a - b, 17) || !inRange(a - c, 17)){
		cout << "CZY KLIKNAC MAX " << a << "," << b << endl;

		mouseClick(hwnd, x1 + p[0] + 7, y1 + p[1] + 28);//trzeba do wysokosci dodac 28 px (obramowanie okna), a do szerekosci 7px
		mouseClick(hwnd, x2 + p[0] + 7, y2 + p[1] + 28);
	}
	else{

		vector<int> temp = checkPixel(s.c_str(), x2, y2);

		cout << "NIE BYLO MAXA " << x2 << "," << y2 << endl;

		int r = temp[0];//r
		int g = temp[1];//g

		cout << "x2 = " << x2 << endl;
		cout << "y2 = " << y2 << endl;
		cout << "Wyswietlam R =" << r << endl;
		cout << "Wyswietlam G =" << g << endl;
		if ((inRange(255 - r, 50)) && (r != g)){
			mouseClick(hwnd, x2 + p[0] + 7, y2 + p[1] + 28);

			cout << "NIE BYLO MAXA " << x2 + p[0] + 7 << "," << y2 + p[1] + 28 << endl;
		}
		else{
			cout << "jestem w else" << endl;
			vector<int> temp2 = checkPixel(s.c_str(), x3, y3);

			int r2 = temp2[0];
			int g2 = temp2[1];

			cout << "x3 = " << x3 << endl;
			cout << "y3 = " << y3 << endl;
			cout << "Wyswietlam r2 =" << r2 << endl;
			cout << "Wyswietlam g2 =" << g2 << endl;
			if ((inRange(255 - r2, 50)) && (r2 != g2)){
				cout << "Zielony przycisk x3= " << x3 + p[0] + 7 << ", y3 =" << y3 + p[1] + 28 << endl;
				mouseClick(hwnd, x3 + p[0] + 7, y3 + p[0] + 28);

			}
			else clickCall(hwnd);
			//else button zielony, mozemy zrobic tylko call wiec wywolamy funkcje clickCall

		}

	}


	getchar();


}





//czy moja kolej
bool isMyTurn(HWND hwnd){


	//read pos
	vector<int> pos = getWindowPos(hwnd);

	//what pos to check
	int x = 300;
	int y = 360;
	//cout << "XY " << x << " - " << y << endl;


	vector<pair<int, int>> pixelList;

	pair<int, int> px;
	px.first = x;
	px.second = y;
	pixelList.push_back(px);

	string s = "..\\png\\";
	string s2 = "_1.png";
	string h = to_string((int)hwnd);

	//handle in the file name
	s += h;
	//_1.png in the file name
	s += s2;

	printScreenSaveToFile(hwnd, 1);

	vector <vector<int>> pixels = getPixelRGBList(s.c_str(), pixelList);

	cout << "PIXEL:" << pixels[0][0] << " - " << pixels[0][1] << " -" << pixels[0][2] << endl;

	int a = pixels[0][0];//r
	int b = pixels[0][1];//g
	int c = pixels[0][2];//b

	//if NOT close to white
	if (!inRange(a - b, 17) || !inRange(a - c, 17)){
		//	if (!(inRange(pixels[1][0] - pixels[0][0], 0) && inRange(pixels[2][0] - pixels[0][0], 0))){
		pixelList.clear();
		pixels.clear();

		return true;
	}
	else{
		pixelList.clear();
		pixels.clear();
		return false;
	}



}



vector<int> getBlinds(char* title){

	vector<int> blinds;
	string ret(title);


	if (isSubstring(ret, "SNG NLH")){
		//cout << "TOURNAMENT: " << ret << endl;

		string s1 = "$";
		string s2 = "(";
		string s3 = "/";
		string s4 = "($";

		std::size_t found1 = ret.find(s1) + 1;
		std::size_t found2 = ret.find(s2);
		std::size_t found3 = ret.find(s3);
		std::size_t found4 = ret.find(s4);


		int len1 = found3 - found1;
		int len2 = found2 - found3 - 2;
		int len3 = ret.size() - found4 - 3;


		string ret1 = ret.substr(found1, len1);
		string ret2 = ret.substr(found3 + 2, len2);
		string ret3 = ret.substr(found4 + 2, len3);

		cout << "SB = " << ret1 << ", BB = " << ret2 << ",(" << ret3 << ")" << endl;

		/*int a1 = stoi(ret1);
		int a2 = stoi(ret2);
		int a3 = stoi(ret3);

		blinds.push_back(a1);
		blinds.push_back(a2);
		blinds.push_back(a3);*/

	}

	//cout << "SB = " << blinds[0] << ", BB = " << blinds[1] << ",(" << blinds[2] << ")" << endl;

	return blinds;
}

void imBack(HWND hwnd){

	int x = 314;
	int y = 350;

	mouseClick(hwnd, x, y);//---------------------trzeba rozpoznac ze to ten konkretny button
}


bool isTableActive(HWND hwnd){


	return true;
}


#endif