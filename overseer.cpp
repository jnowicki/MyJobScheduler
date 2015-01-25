#include <iostream>
#include <future>
#include "overseer_machine.hpp"

void Overseer::start(){
	std::cout << "Overseer: started " << std::endl;
	first->doNextJob(this);
};

void Overseer::jobResults(int exec_t, int machineNumber, int jobNr){
	std::cout << "Overseer: got back task " << jobNr << " from Machine nr " << machineNumber << ". Exec time was " << exec_t << std::endl;
	
	if(machineNumber == 1){		
		second->doNextJob(this);	
	} else {	
		first->doNextJob(this);		
	};
}

Overseer::Overseer(Machine * _first, Machine * _second) : first(_first), second(_second){
	timePosition = 0;
};
