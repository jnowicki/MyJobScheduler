#include <vector>
#include <iostream>
#include <future>
#include <math.h>

#include "overseer_machine.hpp"

int Machine::timePosition; 						// deklaracja zmiennej statycznej

Machine::Machine(int a, std::vector<int> b) { 		// definicja konstruktora
	machineNumber = a;
	jobs = b;
	lastJobNr = 0;
};

Machine::Machine(int a, std::vector<int> b, std::vector<int> c) {
	machineNumber = a;
	jobs = b;
	lastJobNr = 0;
	holePos = c;
};

int Machine::doJob (int jobNr) {
	unsigned int jobLength = jobs.at(jobNr - 1);
	std::cout << "Machine " << machineNumber << ": task " << jobNr << " finished with time " << jobLength << std::endl;
	return jobLength;	
};

int Machine::doJobWithHoles( int jobNr, int start_t) {
	unsigned int jobLength = jobs.at(jobNr - 1);		
	int exec_t = jobLength;
	bool punished = false;
	int wait_t = 0;
	
	for(int i = 0; i < holePos.size(); i++){
		int hole = holePos.at(i);
		if(hole > jobLength + start_t) break;
		
		 if(!(hole < start_t) && !(exec_t + start_t < hole)){
			 exec_t += 1;
			 wait_t += 1;
			 punished = true;
		 }
	};
	
	if(punished){
		int half = floor(jobLength/2.0);		
		exec_t += half;
		wait_t += half;		
		std::cout << "Machine " << machineNumber << ": task " << jobNr << " encountered a hole. Lost time was " << wait_t << std::endl;	
	};
		
	std::cout << "Machine " << machineNumber << ": task " << jobNr << " finished with time " << exec_t << std::endl;
	return exec_t;	
};
