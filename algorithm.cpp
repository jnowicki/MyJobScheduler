#include "classes.hpp"
#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>

#define TIMELINE_EX_L 100	// spodziewana szacowana dlugosc linii czasu
#define MAX_JOB_LENGTH 4 	// maksymalna dlugosc zadania

std::vector<int> generateHoles(int h_interval, int h_length){ 
																		//generowanie dziur na linii czasu.											
	std::vector<int> arr;													// przy domyślnych ustawieniach h_interval = 4, h_length = 2.
	for(int i = h_interval + 1; i < TIMELINE_EX_L; i += h_interval + h_length){ 		
		arr.push_back(i);						
		arr.push_back(i+1);
		std::cout << "Generator: " << i << ", " << i+1 << std::endl;
	};
	return arr;
};

std::vector<int> generateJobs(int jobsQt){
	std::vector<int> generated;									
	for(int i=1; i <= jobsQt; i++){										// generowanie losowych dlugosci zadan
		int random = rand() % MAX_JOB_LENGTH + 1;	
		generated.push_back(random);			
		std::cout << "Generator: <" << i << ", " << random << ">" << std::endl;	
	};
	return generated;
};

std::vector<Overseer> nextStep(std::vector<Overseer> candidates, int step, std::vector<int> holePos){
    std::cout << "Algorithm: entering step " << step << std::endl;
    
    if(step < 3){    
        
        std::vector<Overseer> overseers;
        std::vector<Overseer> bestOverseers;
        std::vector<int> differences;       //matryca roznic
        int bestTime;
        
        for( int i = 0; i < candidates.size(); i++) {
            Overseer root = candidates.at(i);
            std::vector<jobPair> rootPairs = root.getPairs();
            for( int j = 0; j < rootPairs.size(); j++) {
                Overseer brandnew = root;             
                brandnew.first.addJob(rootPairs.at(j).jobLengths.first, rootPairs.at(j).jobIdent.first );
                brandnew.second.addJob(rootPairs.at(j).jobLengths.second, rootPairs.at(j).jobIdent.second);
                brandnew.updatePairs(rootPairs.at(j));
                overseers.push_back(brandnew);
                int expectedEndTime = rootPairs.at(j).jobLengths.first + rootPairs.at(j).jobLengths.second;
                int endTime = brandnew.doJobs(step);
                int difference = endTime - expectedEndTime;
                differences.push_back(difference);
            }
            std::cout << "Algorithm: created all children for candidate " << i << std::endl;

        };
        
        bestTime = differences.at(0);
        for(int i = 0; i < differences.size(); i++ ){                                   // znajdz najlepszy czas
            if(bestTime > differences.at(i)) bestTime = differences.at(i);
            std::cout << "Algorithm: difference for " << i << " is " << differences.at(i) << std::endl;
        };
        
        std::cout << "Algorithm: best time in this iteration is " << bestTime << std::endl;
          
        for(int i = 0; i < overseers.size(); i++){
            if(differences.at(i) == bestTime) { 
                bestOverseers.push_back(overseers.at(i));
                std::cout << "Algorithm: Overseer " << overseers.at(i).getId() << " selected as best" << std::endl; 
            };
        };
        
        step++;
        nextStep(bestOverseers, step, holePos);
    } else {
        return candidates;
    }
};

void algorithm(std::vector<int> jobs, std::vector<int> holePos){
	
        std::vector<Overseer> overseers;
	std::vector<jobPair> pairArr;
        std::vector<Overseer> bestMatch;
        std::vector<int> differences;
	const int nrOfJobs = jobs.size();
        
	for( int i = 0; i < nrOfJobs; i++){
		for ( int j = 0; j < nrOfJobs; j++){
                    if(i != j){
			std::pair <int, int> lengths (jobs.at(i), jobs.at(j));
			std::pair <int, int> idents (i+1, j+1);
			jobPair newPair (lengths, idents);
			pairArr.push_back(newPair);
                    }
		};
	};
        
        const int nrOfPairs = pairArr.size(); // poczatkowa liczba par
        
	//std::cout << "Algorithm: pair generated:" << std::endl;
	for( int i = 0; i < nrOfPairs; i++){
		//std::cout << "Algorithm: " << i+1 << ". j" << pairArr.at(i).jobIdent.first << "- " << pairArr.at(i).jobLengths.first << ", j";
		std::cout << pairArr.at(i).jobIdent.second << "- " << pairArr.at(i).jobLengths.second << std::endl;
	};  
        
	for( int i = 0; i < nrOfPairs; i++){            //stworz dla kazdej pary odpowiadajacego overseera czyli taka inicjalizacja
            Machine first = Machine(1);
            Machine second = Machine(2, holePos);
            Overseer brandnew = Overseer(first,second, i, pairArr);
            brandnew.first.addJob(pairArr.at(i).jobLengths.first, pairArr.at(i).jobIdent.first );
            brandnew.second.addJob(pairArr.at(i).jobLengths.second, pairArr.at(i).jobIdent.second );
            brandnew.updatePairs(pairArr.at(i));
            int expectedEndTime = pairArr.at(i).jobLengths.first + pairArr.at(i).jobLengths.second;
            int endTime = brandnew.doJobs(0);
            int difference = endTime - expectedEndTime;
            differences.push_back(difference);
            overseers.push_back(brandnew);
            //std::cout << "Algorithm: Overseer " << i << " created." << std::endl; 
            //std::cout << "Algorithm: difference for " << i << " is " << difference << std::endl;
	};
        
        std::vector<Overseer> bestOverseers;
               //matryca roznic
        int bestTime;
           
        bestTime = differences.at(0);
        for(int i = 0; i < differences.size(); i++ ){                                   // znajdz najlepszy czas
            if(bestTime > differences.at(i)) bestTime = differences.at(i);
            std::cout << "Algorithm: difference for " << i << " is " << differences.at(i) << std::endl;
        };
        
        std::cout << "Algorithm: best time in this iteration is " << bestTime << std::endl;
        
        for(int i = 0; i < nrOfPairs; i++){
            if(differences.at(i) == bestTime) { 
                bestOverseers.push_back(overseers.at(i));
                std::cout << "Algorithm: Overseer " << overseers.at(i).getId() << " selected as best" << std::endl; 
            };
        };
	
        bestMatch = nextStep(bestOverseers,1, holePos);
        
}
