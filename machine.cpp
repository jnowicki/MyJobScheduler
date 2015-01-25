#include <vector>
#include <iostream>
#include <future>

#include "overseer_machine.hpp"

int Machine::timePosition; 						// deklaracja zmiennej statycznej

Machine::Machine(int a, std::vector<int> b) { 		// definicja konstruktora
	machineNumber = a;
	jobs = b;
	lastJobNr = 0;
};

void Machine::doNextJob (Overseer * boss) { 					//definicja wykonywania nastepnej pracy
	
	unsigned int jobNr = lastJobNr + 1;
	if( jobs.size() >= jobNr ) { 	// czy istnieje zadanie na tej maszynie
		unsigned int jobLength = jobs.at(jobNr - 1);
		std::cout << "Machine " << machineNumber << ": task " << jobNr << " finished with time " << jobLength << std::endl;
		lastJobNr = jobNr; 
		boss->jobResults(jobLength, machineNumber, jobNr);	
		
	} else {
		std::cout << "Machine " << machineNumber << ": end of tasks." << std::endl;
	}
};
