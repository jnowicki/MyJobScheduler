#include <stdlib.h>
#include <time.h>
#include <vector>
#include <iostream>
#include <map>

#include "classes.hpp"

#define JOBS_QUANTITY 6 	// ilosc zadan

#define HOLE_T 4 			// czas pomiedzy dziurami
#define HOLE_L 2 			// dlugosc dziury

#define TIMELINE_EX_L 100	// spodziewana szacowana dlugosc linii czasu
#define MAX_JOB_LENGTH 4 	// maksymalna dlugosc zadania

static std::vector<Overseer> matches;

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


bool nextStep(std::vector<Overseer> candidates, int step, std::vector<int> holePos){
    std::cout << "Algorithm: entering step " << step << std::endl;
    
    if(step < 3){    
        std::vector<Overseer> bestOverseers;
        std::map<Overseer, int> results;       //matryca roznic
        int bestTime;
        
        for( int i = 0; i < candidates.size(); i++) {
            Overseer root = candidates.at(i);
            std::vector<jobPair> rootPairs = root.getPairs();
            for( int j = 0; j < rootPairs.size(); j++) {
                Overseer brandnew = root;             
                brandnew.first.addJob(rootPairs.at(j).jobLengths.first, rootPairs.at(j).jobIdent.first );
                brandnew.second.addJob(rootPairs.at(j).jobLengths.second, rootPairs.at(j).jobIdent.second);
                brandnew.updatePairs(rootPairs.at(j));
                int expectedEndTime = rootPairs.at(j).jobLengths.first + rootPairs.at(j).jobLengths.second;
                int endTime = brandnew.doJobs(step);
                int difference = endTime - expectedEndTime;
                results.insert ( std::make_pair(brandnew, difference) );
            }
            std::cout << "Algorithm: created all children for candidate " << candidates.at(i).getId() << std::endl;

        };
        bestTime = 1000;
        for (std::map<Overseer, int>::iterator it = results.begin(); it != results.end(); ++it) {
            if(bestTime > it->second) bestTime = it->second;
            std::cout << "Algorithm: difference for Overseer " << it->first.getId() << " is " << it->second << std::endl;
        };
        
        std::cout << "Algorithm: best time in this iteration is " << bestTime << std::endl;

        for(std::map<Overseer, int>::iterator it = results.begin(); it != results.end(); ++it){
            if(it->second == bestTime){
                bestOverseers.push_back(it->first); 
                std::cout << "Algorithm: Overseer " << it->first.getId() << " with time " << it->second <<" selected as best(best time = " << bestTime << ")" << std::endl;
            };
        };
        
        step++;
        nextStep(bestOverseers, step, holePos);
    } else {
        matches = candidates;
        return 0;
    }
};

bool algorithm(std::vector<int> jobs, std::vector<int> holePos){
	
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
        
	std::cout << "Algorithm: pair generated:" << std::endl;
	for( int i = 0; i < nrOfPairs; i++){
		std::cout << "Algorithm: " << i+1 << ". j" << pairArr.at(i).jobIdent.first << "- " << pairArr.at(i).jobLengths.first << ", j";
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
	
        nextStep(bestOverseers,1, holePos);
        std::cout << "Algorithm: Selected best matches" << std::endl;
        for(int i = 0; i < matches.size(); i++){
            Overseer tmp = matches.at(i);
            tmp.printValues();
            
        }
        return 0;
}

using namespace std;

int main(){	
	// generowanie dziur	
    cout << "Generator: generating holes" << endl;
    cout << "Generator: position1, position2" << endl;

    vector<int> holePos = generateHoles(HOLE_T, HOLE_L); // deklaracja i inicjacja tablicy pozycji dziur

    srand(time(NULL));
    /*
    std::vector<int> jobs = generateJobs(JOBS_QUANTITY);
    std::vector<jobPair> pairArr;
    for (int i = 0; i < pairArr.size(); i++) {
        for (int j = 0; j < jobs.size(); j++) {
            if (i != j) {
                std::pair <int, int> lengths(jobs.at(i), jobs.at(j));
                std::pair <int, int> idents(i + 1, j + 1);
                jobPair newPair(lengths, idents);
                pairArr.push_back(newPair);
            }
        };
    };

    Machine first = Machine(1);
    Machine second = Machine(2, holePos);
    Overseer test(first, second, 1, pairArr);



    for (int i = 0; i < 3; i++) {
        test.first.addJob(jobs.at(i%2), i%2);
        test.second.addJob(jobs.at(i%2+1), i%2+1);
        test.doJobs(i);
    };
     */
    algorithm(generateJobs(JOBS_QUANTITY), holePos);

    return 0;
};
