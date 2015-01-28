#include <vector>
#include <iostream>
#include <math.h>

#include "classes.hpp"

Machine::Machine(int a) { 		// definicja konstruktora
	machineNumber = a;
};

Machine::Machine(int a, std::vector<int> c) {
	machineNumber = a;
	holePos = c;
};

void Machine::addJob(int jobLength, int ident) {
    jobs.push_back(jobLength);
    idents.push_back(ident);
    std::cout << "Machine " << machineNumber << ": added job j" << ident << " of size " << jobLength << std::endl;
}

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
		
		std::cout << "Machine " << machineNumber << ": task " << jobNr << " hole = " << hole << " ,start_t + 1 = " << start_t + 1 << ", exec_t + start_t + 1 = " << exec_t + start_t + 1 << std::endl;
		
		if(!(hole < start_t + 1) && !(exec_t + start_t + 1 < hole)){
			exec_t += 1;
			wait_t += 1;
			punished = true;
		}
	};
	
	if(punished){
		int half = floor(jobLength/2.0);
		exec_t += half;
		std::cout << "Machine " << machineNumber << ": task " << jobNr << " encountered a hole. Lost time due to holes was " << wait_t << " , due to punishment " << half << std::endl;	
	};
		
	std::cout << "Machine " << machineNumber << ": task " << jobNr << " finished with time " << exec_t << std::endl;
	return exec_t;	
};
