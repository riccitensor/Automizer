#ifndef DC_H
#define DC_H

#include "stdafx.h"
#include "ocr.h"

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




BOOL CALLBACK DataCollector(HWND hwnd, LPARAM lParam)
{
	//ustawaienia: multi-byte zamiast unicode do odczytu danych


	char class_name[80];
	char title[80];

	GetClassName(hwnd, class_name, sizeof(class_name));
	GetWindowText(hwnd, title, sizeof(title));


	//pobranie pozycji okna
	vector<int> cur = getWindowPos(hwnd);

	//czy classname i widoczne okno
	if (IsWindowVisible(hwnd) && strcmp(class_name, "#32770") == 0 && strcmp(title, "Lobby") != 0 && isTournamentWindow(title) && cur[0] >0 && cur[1] >0){



		cout << "Window " << hwnd << " Position: (" << cur[0] << "," << cur[1] << ")" << endl;

		MoveWindow(
			hwnd,//konwertowane na inta z hexa
			cur[0],
			cur[1],
			640,
			461,
			true
			);


		//printScreenSaveToFile(hwnd, counter);
		printDataCollector(hwnd, counter_dc);


		counter_dc++;
	}
	return TRUE;
}


#endif
