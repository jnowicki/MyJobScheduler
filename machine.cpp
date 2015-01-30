#include <vector>
#include <iostream>
#include <math.h>
#include <algorithm>

#include "classes.hpp"

#define MSG true

extern double alpha;

Machine::Machine(int a) { 		// definicja konstruktora
	machineNumber = a;
};

Machine::Machine(int a, std::vector<int> c) {
	machineNumber = a;
	holePos = c;
};

std::pair<int,int> Machine::getJobAt(int i) const{
  return std::make_pair(jobs.at(i),idents.at(i));  
};

void Machine::addJob(int jobLength, int ident) {
    jobs.push_back(jobLength);
    idents.push_back(ident);
    if(MSG) std::cout << "Machine " << machineNumber << ": added job j" << ident << " of size " << jobLength << std::endl;
}

int Machine::doJob (int jobNr) {
	unsigned int jobLength = jobs.at(jobNr - 1);
	if(MSG) std::cout << "Machine " << machineNumber << ": task " << jobNr << " finished with time " << jobLength << std::endl;
	return jobLength;	
};

int Machine::doJobWithHoles( int jobNr, int start_t) {
	unsigned int jobLength = jobs.at(jobNr - 1);		
	int exec_t = jobLength;
	bool punished = false;
	int wait_t = 0;
        
        std::vector<int> holes;
        
	for(int i = 0; i < holePos.size(); i++){
		int hole = holePos.at(i);
		if(hole > jobLength + start_t) break;
		
		//if(MSG) std::cout << "Machine " << machineNumber << ": task " << jobNr << " hole = " << hole << " ,start_t + 1 = " << start_t + 1 << ", exec_t + start_t + 1 = " << exec_t + start_t + 1 << std::endl;
		
		if(!(hole < start_t + 1) && !(exec_t + start_t + 1 < hole)){
                    if(i%2 == 0) holes.push_back(hole); //dla parzystych indeksow
			exec_t += 1;
			wait_t += 1;
			punished = true;
		}
	};
            
	if(punished){ //jezeli wpadles w dziure
            double jobDoneBeforeHole = 0;      
                for(int i = 0; i < holes.size(); i++ ){
                    jobDoneBeforeHole += holes.at(i) - (start_t + 1);    
                }
		int punishment = std::max(floor(alpha * jobDoneBeforeHole), 0.0); //liczenie ile wynosi kara
		exec_t += punishment;
		if(MSG) std::cout << "Machine " << machineNumber << ": task " << jobNr << " encountered a hole. Lost time due to holes was " << wait_t << " , due to punishment " << punishment << std::endl;	
	};
		
	if(MSG) std::cout << "Machine " << machineNumber << ": task " << jobNr << " finished with time " << exec_t << std::endl;
	return exec_t;	
};
