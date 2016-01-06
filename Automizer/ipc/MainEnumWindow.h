#ifndef MAIN_H
#define MAIN_H

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



using namespace std;
using namespace Gdiplus;


using namespace std;




BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	//ustawaienia: multi-byte zamiast unicode do odczytu danych


	char class_name[80];
	char title[80];

	GetClassName(hwnd, class_name, sizeof(class_name));
	GetWindowText(hwnd, title, sizeof(title));



	//czy lobby turniejow -- ZOSTAWIAMY TYLKO GLOWNE LOBBY
	if (IsWindowVisible(hwnd) && strcmp(class_name, "#32770") == 0 && strcmp(title, "Lobby") != 0 && !isTournamentWindow(title) && isTournamentLobbyWindow(title)){
		cout << "---------------------------------------------------------------------------------------" << endl;
		cout << "---LOBBY--- Hwnd: " << hwnd << endl;
		cout << "---LOBBY--- Window title: " << title << endl;
		cout << "---LOBBY--- Class name: " << class_name << endl << endl;
		//close lobby windows
		PostMessage(hwnd, WM_CLOSE, 0, 0);
	}

	//czy okno reklamowe
	if (is888(title) && strcmp(title, "Lobby") != 0 && !isTournamentWindow(title) && !isTournamentLobbyWindow(title)){
		cout << "---------------------------------------------------------------------------------------" << endl;
		cout << "---ADVERTISEMENT--- Hwnd: " << hwnd << endl;
		cout << "---ADVERTISEMENT--- Window title: " << title << endl;
		cout << "---ADVERTISEMENT--- Class name: " << class_name << endl << endl;
		//close ads
		PostMessage(hwnd, WM_CLOSE, 0, 0);
	}


	//sprawdzanie otwartych turniejow
	//czy classname i widoczne okno
	if (IsWindowVisible(hwnd) && strcmp(class_name, "#32770") == 0 && strcmp(title, "Lobby") != 0 && isTournamentWindow(title) && !IsIconic(hwnd)){
		cout << "---------------------------------------------------------------------------------------" << endl;
		cout << "---TABLE--- Hwnd: " << hwnd << endl;
		cout << "---TABLE--- Window title: " << title << endl;
		cout << "---TABLE--- Class name: " << class_name << endl << endl;

		//tournament id
		string id = getTournamentId(title);
		//blind vals
		getBlinds(title);

		//create a tournament
		tournament_status ts;
		ts.hwnd = hwnd;
		//NADAL W GRZE   -------- domyslnie TAK
		ts.stillGoing = 1;
		//CZEKA NA AKCJE -------- domyslnie NIE?
		ts.waitsForAction = 0;
		//id turnieju
		ts.tournament_id = id;


		//add to tournament list
		tournament_list[id] = ts;

		//cout << "-----> TEST WIELKOSCI KOLEJKI" << tournament_list.size() << endl;

		//pobranie pozycji okna
		vector<int> cur = getWindowPos(hwnd);

		MoveWindow(
			hwnd,//konwertowane na inta z hexa
			cur[0],
			cur[1],
			640,
			461,
			true
			);

		//ustawianie kursora
		int x_off = 20, y_off = 80;
		moveMouseInWindow(hwnd, x_off, y_off);

		//mouse click
		//mouseClick(hwnd, x_off, y_off);

		//zapisanie screenshota
		printScreenSaveToFile(hwnd, counter);



		//////////////Paamietaj nazwe screenshota
		string s = "..\\png\\";
		string s2 = "_1.png";
		string h = to_string((int)hwnd);

		//handle in the file name
		s += h;
		//_1.png in the file name
		s += s2;

		if (isMyTurn(hwnd)){
			cout << "Moja kolej, klikam fold" << endl;

			int c;
			cout << "CO WYBIERASZ? 1 - allin, 9 - fold " << endl;
			cin >> c;
			if (c == 1){
				clickAllIn(hwnd, s);

			}
			else{
				clickFold(hwnd);
			}

		}



		counter++;
	}
	return TRUE;
}



#endif