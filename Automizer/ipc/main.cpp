#include "stdafx.h"

#include "ocr.h"
#include "MainEnumWindow.h"
#include "DataCollector.h"

//#include "algo_funkcje.h"

#include "Winner.h"
#include "Randomizer.h"
#include "Place.h"
#include "Hand.h"


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






int main(char ** argv, int argc){

	ilInit();
	printf("DevIL has been initialized\n");

	/*
	* Glowna petla progrmu
	*/
	EnumWindows(EnumWindowsProc, NULL);


	/*

	///DATA COLLECTOR do robienia screenow
	for (int i = 0; i < 10000; i ++ )
	{
	EnumWindows(EnumWindowsProc, NULL);
	EnumWindows(DataCollector, NULL);
	Sleep(5000);
	}*/

	//wczytywanie zakresow
	readRanges();



	//-------------------------------------------------------CALA REKA Z KLASY HAND
	Place places[6];

	//place 0
	places[0].setPosition(0);
	places[0].setStack(300);
	places[0].setRange(range34);
	places[0].setActive(1);//-----------------------------------ACTIVE

	//place 1
	places[1].setPosition(1);
	places[1].setStack(500);
	places[1].setRange(range34);
	places[1].setActive(0);

	//place 2
	places[2].setPosition(2);
	places[2].setStack(222);
	places[2].setRange(range34);
	places[2].setActive(1);//-----------------------------------ACTIVE

	//place 3
	places[3].setPosition(3);
	places[3].setStack(111);
	places[3].setRange(range34);
	places[3].setActive(0);

	//place 4
	places[4].setPosition(4);
	places[4].setStack(345);
	places[4].setRange(range34);
	places[4].setActive(0);

	//place 5
	places[5].setPosition(5);
	places[5].setStack(321);
	places[5].setRange(range34);
	places[5].setActive(1);//-----------------------------------ACTIVE

	int BB = 20;
	int SB = 10;
	int pot = 100;
	int ante = 10;

	vector<int> board;


	
	//NIEAKTYWNI GRACZE MAJA RANGE OD 60 - 100%!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! STRATEGIA ZALEZY OD M
	



	//--------------------------------------------MC--------------------------------------------------

	int iloscProb = 1;
	int whoWon[6] = { 0, 0, 0, 0, 0, 0 };

	for (int i = 0; i < iloscProb; i++){//------------------------------------------------------------------

		//cout << "----------------ILOSC PROB" << i << "------------------------" << endl;


		Hand *hand = new Hand(places, BB, SB, pot, ante, board);


		//MOJE RECE PODANE Z OCR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
		vector <int> myHand;
		myHand.push_back(13);
		myHand.push_back(14);

		//uzywane rece
		vector<int> used;

		//moje rece nie moga byc losowane!!
		used.insert(used.end(), myHand.begin(), myHand.end());

		//cout << "My hand: " << convert(myHand[0]) << " " << convert(myHand[1]) << endl;

		//wszyscy przy stole
		for (int i = 1; i < 6; i++){

			int k1;
			int k2;
			vector<int> h;

			do{
				//pobieramy dla zakresu
				h = randomHandFromRange(hand->getPlaces()[i].getRange());

				//obie kartyz reki
				k1 = h[0];
				k2 = h[1];
				bool test = isInVector(used, h[0]) || isInVector(used, h[1]);
				//cout << "Test;" << convert(k1)  << convert(k2) << "--->" << test<< endl;


			} while (isInVector(used, h[0]) || isInVector(used, h[1]));

			//ustalamy rece graczom
			vector<int> temp;
			temp.push_back(k1);
			temp.push_back(k2);

			//cout << convert(k1) <<" "<< convert(k2) << endl;

			places[i].setHand(temp);

			//dodajemy obie karty reki do USED
			used.push_back(k1);
			used.push_back(k2);



		}


		//5 kart z boardu
		for (int i = 0; i < 5; i++){

			int k;
			//losowanie boardu
			do{

				//pobieramy dla zakresu
				k = rand() % 52 + 2;

				//bool test = isInVector(used, h[0]) || isInVector(used, h[1]);
				//cout << "Test;" << convert(k1)  << convert(k2) << "--->" << test<< endl;


			} while (isInVector(used, k));

			//dodajemy wylosowana karta do used
			used.push_back(k);

			//dodajemy do boardu
			board.push_back(k);
		}
		//ustalamy board
		hand->setBoard(board);

		vector<int> b1 = hand->getBoard();
		//cout << "BOARD" << endl;
		//for (std::vector<int>::size_type i = 0; i != b1.size(); i++) {
		//	cout << convert(b1[i]) << " ";	
		//}
		//cout << endl;




		//board
		vector<int> b = hand->getBoard();




		//rece
		///////////////--------moja reka z dodanym boardem
		myHand.insert(myHand.end(), b.begin(), b.end());

		sort(myHand.begin(), myHand.end());

	//	for (std::vector<int>::size_type i = 0; i != myHand.size(); i++) {
	//	cout << myHand[i] << " - " << convert(myHand[i]) << endl;

	//	}


		//ustawiamy reke 
		places[0].setHand(myHand);

		///////////////--------pozostali gracze
		vector<int> h1 = places[1].getHand();
		h1.insert(h1.end(), b.begin(), b.end());
		sort(h1.begin(), h1.end());

		vector<int> h2 = places[2].getHand();
		h2.insert(h2.end(), b.begin(), b.end());
		sort(h2.begin(), h2.end());

		vector<int> h3 = places[3].getHand();
		h3.insert(h3.end(), b.begin(), b.end());
		sort(h3.begin(), h3.end());

		vector<int> h4 = places[4].getHand();
		h4.insert(h4.end(), b.begin(), b.end());
		sort(h4.begin(), h4.end());

		vector<int> h5 = places[5].getHand();
		h5.insert(h5.end(), b.begin(), b.end());
		sort(h5.begin(), h5.end());


		vector<int> a0 = whatHand(myHand);
		vector<int> a1 = whatHand(h1);
		vector<int> a2 = whatHand(h2);
		vector<int> a3 = whatHand(h3);
		vector<int> a4 = whatHand(h4);
		vector<int> a5 = whatHand(h5);

		
		int ww = whoWins(
		a0,
		a1,
		a2,
		a3,
		a4,
		a5
		);

		whoWon[ww]++;

	




		//czyscimy USED!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		used.clear();
		board.clear();
		hand->clearBoard();
		h1.clear();
		h2.clear();
		h3.clear();
		h4.clear();
		h5.clear();

		myHand.clear();





	}//---------------------------------------------------koniec MC

	cout << "DISTRIBUTION" << endl;

	int equity = 0;
	int sum = 0;
	for (int i = 0; i < 6; i++){
		sum += whoWon[i];
	}

	for (int i = 0; i < 6; i++){
		cout << i << "has " << ((double)whoWon[i] / sum * 100) << "%" << endl;
	}








	//funkcja do pobierania wspolrzednych okna

	/*
		typedef map <string, tournament_status>::const_iterator MapIterator;
	for (MapIterator iter = tournament_list.begin(); iter != tournament_list.end(); iter++)
	{
		cout << "!!!!!!!!!!!!!!Key: " << iter->first << " -->" << iter->second.hwnd << ", "
			<< iter->second.stillGoing << ", " << iter->second.tournament_id
			<< ", " << iter->second.waitsForAction << endl;

	}
	*/


	getchar();
}

