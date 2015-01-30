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

static std::vector<Overseer> matches;   // najlepsze instancje
double alpha;                   //alpha, def z klawiatury
int jobQt;                      //ilosc prac, definiowalna z klawiatury

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
     
    if(step < jobQt){
        std::cout << "Algorithm: entering step " << step << std::endl;
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
                brandnew.updatePairs(j);
                int expectedEndTime = rootPairs.at(j).jobLengths.first + rootPairs.at(j).jobLengths.second;
                int endTime = brandnew.doJobs(step);
                int difference = endTime - expectedEndTime;
                brandnew.l.push_back(difference); 
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
        std::cout << "Algorithm: finished at step " << step-1 << std::endl;
        matches = candidates;
        return 0;
    }
};

bool algorithm(std::vector<jobPair> pairArr, std::vector<int> holePos){
	
        std::vector<Overseer> overseers;
        std::vector<Overseer> bestMatch;
        std::vector<int> differences;
        
        const int nrOfPairs = pairArr.size(); // poczatkowa liczba par
        
        
	for( int i = 0; i < nrOfPairs; i++){            //stworz dla kazdej pary odpowiadajacego overseera czyli taka inicjalizacja
            Machine first = Machine(1);
            Machine second = Machine(2, holePos);
            Overseer brandnew = Overseer(first,second, i, pairArr);
            brandnew.first.addJob(pairArr.at(i).jobLengths.first, pairArr.at(i).jobIdent.first );
            brandnew.second.addJob(pairArr.at(i).jobLengths.second, pairArr.at(i).jobIdent.second );
            brandnew.updatePairs(i);
            int expectedEndTime = pairArr.at(i).expectedTime;   // czas oczekiwany
            int endTime = brandnew.doJobs(0);
            int difference = endTime - expectedEndTime;
            differences.push_back(difference);
            brandnew.l.push_back(difference); 
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
    int hole_t;
    int hole_l;
    
    cout << "Give me length of hole: (recommended is 2)" << std::endl;
    cin >> hole_l;
    
    cout << "Give me interval between holes: (recommended is 4)" << std::endl;
    cin >> hole_t;
    
	// generowanie dziur	
    cout << "Generator: generating holes for hole_l = " << hole_l << ", hole_t = " << hole_t << endl;

    vector<int> holePos = generateHoles(hole_t, hole_l); // deklaracja i inicjacja tablicy pozycji dziur

    srand(time(NULL));
    cout << "Give me alpha: " << std::endl;
    cin >> alpha;
      
    int pairNr; 
    cout << "How many job pairs do you want to create?" << std::endl;
    cin >> pairNr;
    std::vector<jobPair> pairArr;
    for(int i = 0; i < pairNr; i++){
        unsigned int l1, l2, ex;
        cout << "Input j" << i + 1 << " first task length " << std::endl;
        cin >> l1;
        cout << "Input j" << i + 1 << " second task length " << std::endl;
        cin >> l2;
        cout << "Input j" << i + 1 << " expected time " << std::endl;
        cin >> ex;
        pairArr.push_back(jobPair(make_pair(l1,l2), make_pair(i+1,i+1), ex));
    };
    
    for( int i = 0; i < pairNr; i++){
        cout << "j" << i+1 << ": <" << pairArr.at(i).jobLengths.first << "," << pairArr.at(i).jobLengths.second << ">, ex time= " << pairArr.at(i).expectedTime << std::endl;
    };
    
    jobQt = pairNr;
    
    algorithm(pairArr, holePos);

    return 0;
};
