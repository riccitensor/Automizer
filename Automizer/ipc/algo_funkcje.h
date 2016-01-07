#ifndef ALGO_H
#define	ALGO_H



class algo_funkcje {


	public: algo_funkcje(){

	}	

	public: void showVector(vector<int> a){
		for (std::vector<int>::size_type i = 0; i != a.size(); i++) {
			cout << a[i] << endl;
		}
	}




	public: string printCard(int a){


		int rank = (a-1) % 13;
		int col = (a-1) / 13;

		string s_col;
		string s_rank;

		
		if (a <= 14){
			s_col = "h";
		}
		else if (a > 14 && a <= 27){
			s_col = "d";
		}
		else if (a > 27 && a <= 40){
			s_col = "c";
		}
		else if (a > 0 && a <= 53){
			s_col = "s";
		}
		else{
			s_col = "???????????????????????????????????";
		}

		switch (rank){
			case 1:
				s_rank = "2";
				break;

			case 2:
				s_rank = "3";
				break;

			case 3:
				s_rank = "4";
				break;

			case 4:
				s_rank = "5";
				break;

			case 5:
				s_rank = "6";
				break;

			case 6:
				s_rank = "7";
				break;

			case 7:
				s_rank = "8";
				break;

			case 8:
				s_rank = "9";
				break;

			case 9:
				s_rank = "T";
				break;

			case 10:
				s_rank = "J";
				break;

			case 11:
				s_rank = "Q";
				break;

			case 12:
				s_rank = "K";
				break;
			
			case 0:
				s_rank = "A";
				break;

		}

	//	cout << "KARTA:" << s_rank + s_col << endl;
		return s_rank + s_col;
	}

	public: int cardToNum(string card){
		
		int col = -1;
		int offset = -1;
		
		//str Ad
		string first = card.substr(0, 1);
		string second = card.substr(1, 1);

		if (second == "h"){
			col = 0;
		}
		else if (second == "d"){
			col = 1;
		}
		else if (second == "c"){
			col = 2;
		}
		else{
			col = 3;
		}

		if (first == "2"){
			offset = 0;
		}
		else if (first == "3"){
			offset = 1;
		}
		else if (first == "4"){
			offset = 2;
		}		
		else if (first == "5"){
			offset = 3;
		}
		else if (first == "6"){
			offset = 4;
		}
		else if (first == "7"){
			offset = 5;
		}
		else if (first == "8"){
			offset = 6;
		}
		else if (first == "9"){
			offset = 7;
		}
		else if (first == "T" || first == "t"){
			offset = 8;
		}
		else if (first == "J" || first == "j"){
			offset = 9;
		}
		else if (first == "Q" || first == "q"){
			offset = 10;
		}
		else if (first == "K" || first == "k"){
			offset = 11;
		}
		else if (first == "A" || first == "a"){
			offset = 12;
		}
		else{
			cout <<card << " ERROR" << endl;
		}


		///cout << "First: " << first <<endl;
		//cout << "Second: " << second << endl;
		//cout << "First offset: " << offset << endl;
		//cout << "Second color: " << col << endl;


		int num = 0;

		num = 2 + col * 13 + offset;

		//cout << "NUM: " << num << endl;
		return num;
	}

	public: int handToNum(string hand, int debug = 0){
		int num = 0;


		string first = hand.substr(0, 2);
		string second = hand.substr(2, 2);
		int ifirst = cardToNum(first);
		int isec = cardToNum(second);

		num = 100 * (ifirst+10) + (isec+10);

		if (debug)
			cout << "Hand:" << num << endl;

		return num;
	}

	public: string NumToHand(int num, int debug = 0){
		string hand;
		
		int second = num % 100;
		int first = (num - second) / 100;
		second = second - 10;
		first = first - 10;
	
		hand = printCard(first) + printCard(second);
 
		if (debug)
			cout << "Hand:" << hand << endl;

		return hand;
	}



	public: string printHand(int a, int b){

		string c = printCard(a) + printCard(b);
		cout << "KARTA: " << c << endl;
		return c;
	}

	
	public: int whoWins(int k1 = 0, int k2 = 0, int k3 = 0, int k4 = 0, int k5 = 0, 
		int k6 = 0, int k7 = 0

		){
		

		 
		cout << "Flop:" << printCard(k1) + printCard(k2) + printCard(k3) << endl;
		cout << "T:" << printCard(k4) << endl;
		cout << "R:" << printCard(k5) << endl;





		return 1;
	}



	std::vector<std::string> getNextLineAndSplitIntoTokens(std::istream& str)
	{
		std::vector<std::string>   result;
		std::string                line;
		std::getline(str, line);

		std::stringstream          lineStream(line);
		std::string                cell;

		while (std::getline(lineStream, cell, ';'))
		{
			result.push_back(cell);
		}
		return result;
	}

		

	public: std::vector <std::vector<std::string> > readRangesFromFile(){

		std::ifstream      file("powerpush.txt");

		//std::vector <std::vector<std::string> > ranges;
		std::vector <std::vector<std::string> > ranges;


		while (!file.eof()){
			std::vector<std::string> line = getNextLineAndSplitIntoTokens(file);

			//line[1] = line[1].c_str();


			//cout << line[0] << " - " << stoi(line[1]) << endl;
			ranges.push_back(line);
		}
		return ranges;
	}

	public: vector <int> handsForRange(map <int, int> ranges, int range){

		vector <int> v;
		int debug = 0;
		
		for (std::map <int, int>::iterator i = ranges.begin(); i != ranges.end(); ++i){
			if (i->second <= range){
				debug++;
				v.push_back(i->first);
			}

		}
		//cout << "For range:" << range << " lines: " << debug << endl;
		return v;
	}


				

};



#endif