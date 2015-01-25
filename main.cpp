#include <stdlib.h>
#include <time.h>
#include <vector>
#include <iostream>
#include <future>
#include "overseer_machine.hpp"

#define JOBS_QUANTITY 3 	// ilosc zadan w jednej maszynie
#define MAX_JOB_LENGTH 4 	// maksymalna dlugosc zadania
#define HOLE_T 4 			// czas pomiedzy dziurami
#define HOLE_L 2 			// dlugosc dziury
#define TIMELINE_EX_L 100	// spodziewana szacowana dlugosc linii czasu

using namespace std;

vector<int> generateHoles(int h_interval, int h_length){ 
																		//generowanie dziur na linii czasu.											
	vector<int> arr;													// przy domyślnych ustawieniach h_interval = 4, h_length = 2.
	for(int i = h_interval + 1; i < TIMELINE_EX_L; i += h_interval + h_length){ 		
		arr.push_back(i);						
		arr.push_back(i+1);
		cout << "Generator: " << i << ", " << i+1 << endl;
	};
	return arr;
};

vector<int> generateJobs(int jobsQt){
	vector<int> generated;									
	for(int i=1; i <= jobsQt; i++){										// generowanie losowych dlugosci zadan
		int random = rand() % MAX_JOB_LENGTH + 1;	
		generated.push_back(random);			
		cout << "Generator: <" << i << ", " << random << ">" << endl;	
	};
	return generated;
};

int main(){
	
	// generowanie losowe dlugosci zadan dla poszczegolnych maszyn
	
	srand (time(NULL));
	
	cout << "Generator: generating jobs for first machine " << endl;	
	cout << "Generator: <job nr, job length>" << endl;
	
	Machine first = Machine(1, generateJobs(JOBS_QUANTITY));				//generateJobs zwraca map<int, int> w ktorej jest id zadania
	
	cout << "Generator: generating jobs for second machine " << endl;
	cout << "Generator: <job nr, job length>" << endl;
	
	Machine second = Machine(2, generateJobs(JOBS_QUANTITY));
	
	// -------------------------------------------------------------
	// generowanie dziur
	
	cout << "Generator: generating holes" << endl;
	cout << "Generator: position1, position2" << endl;
	
	vector<int> holePos = generateHoles(HOLE_T, HOLE_L);					// deklaracja i inicjacja tablicy pozycji dziur
	
	// ---------------------------------------------------------------
	
	Overseer boss = Overseer(&first, &second);								// przypisanie maszyn i inicjacja overseera
	
	boss.start(JOBS_QUANTITY);
	
	return 0;
};
