#include <vector>
#pragma once

class Machine;

class Overseer{
	int timePosition;
	Machine * first;
	Machine * second;
	public:
		void start();
		void jobResults(int exec_t, int machineNumber, int jobNr);
		Overseer(Machine*, Machine*);
};

class Machine{
	int machineNumber; 									// numer maszyny
	std::vector<int> jobs; 									// tablica zadan
	int lastJobNr; 										// ostatnie zadanie wykonane na tej maszynie
	public:
		void doNextJob(Overseer*); 								// wykonaj nastepne zadanie na tej maszynie
		static int timePosition; 						// pozycja w czasie, static to znaczy ze wszystkie obiekty typu maszyna dzielą tą zmienną	
		Machine (int, std::vector<int>); 					// konstruktorek
};
