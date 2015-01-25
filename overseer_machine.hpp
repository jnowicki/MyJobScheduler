#include <vector>
#pragma once

class Machine;

class Overseer{
	int timePosition;
	std::vector<int> first_d;							//czasy zakonczenia prac na pierwszej maszynie
	std::vector<int> second_d;							// na drugiej
	std::vector<int> first_t;							//czas startu prac na pierwszej maszynie
	std::vector<int> second_t;							//czas startu na drugiej
	Machine * first;
	Machine * second;
	public:
		void start(int);
		void jobResults(int exec_t, int machineNumber, int jobNr);
		Overseer(Machine*, Machine*);
};

class Machine{
	int machineNumber; 									// numer maszyny
	std::vector<int> jobs; 									// tablica zadan
	std::vector<int> holePos;
	int lastJobNr; 										// ostatnie zadanie wykonane na tej maszynie
	public:
		int doJobWithHoles(int,int);
		int doJob(int); 								// wykonaj nastepne zadanie na tej maszynie
		static int timePosition; 						// pozycja w czasie, static to znaczy ze wszystkie obiekty typu maszyna dzielą tą zmienną	
		Machine (int, std::vector<int>); 					// konstruktorek
		Machine (int, std::vector<int>, std::vector<int>); // konstruktorek dla maszyny z dziura
};
