#include <stdlib.h>
#include <time.h>
#include <vector>
#include <iostream>
#include "overseer_machine.hpp"

#define JOBS_QUANTITY 6 	// ilosc zadan
#define MAX_JOB_LENGTH 4 	// maksymalna dlugosc zadania
#define HOLE_T 4 			// czas pomiedzy dziurami
#define HOLE_L 2 			// dlugosc dziury
#define TIMELINE_EX_L 100	// spodziewana szacowana dlugosc linii czasu

using namespace std;

vector<int> generateHoles(int h_interval, int h_length){ 
																		//generowanie dziur na linii czasu.											
	vector<int> arr;													// przy domyślnych ustawieniach h_interval = 4, h_length = 2.
	for(int i = h_interval + 1; i < TIMELINE_EX_L; i += h_interval + h_length){ 		
		arr.push_back(i);						
		arr.push_back(i+1);
		cout << "Generator: " << i << ", " << i+1 << endl;
	};
	return arr;
};

vector<int> generateJobs(int jobsQt){
	vector<int> generated;									
	for(int i=1; i <= jobsQt; i++){										// generowanie losowych dlugosci zadan
		int random = rand() % MAX_JOB_LENGTH + 1;	
		generated.push_back(random);			
		cout << "Generator: <" << i << ", " << random << ">" << endl;	
	};
	return generated;
};

std::vector<Overseer*> nextStep(std::vector<Overseer*) candidates, int step){
    if(step < 3){
        
        step++;
        
    }
};

void algorithm(std::vector<int> jobs, std::vector<int> holePos){
	
	std::vector<jobPair> pairArr;
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
	
        std::vector<Overseer> overseers;
        
	for( int i = 0; i < nrOfPairs; i++){            //stworz dla kazdej pary odpowiadajacego overseera czyli taka inicjalizacja
            Machine first = Machine(1);
            Machine second = Machine(2, holePos);
            Overseer brandnew = Overseer(first,second, i, pairArr);
            overseers.push_back(brandnew);
            std::cout << "Algorithm: Overseer " << i << " created." << std::endl; 
	};
        
        //tutaj musze zrobic fora ktory tyle ile jest zadan w jednej maszynie przewertuje to
        
        std::vector<int> differences;       //matryca roznic
        
        for( int i = 0; i < nrOfPairs; i++) {           
            Overseer boss = overseers.at(i);
            boss.first.addJob(pairArr.at(i).jobLengths.first, pairArr.at(i).jobIdent.first );
            boss.second.addJob(pairArr.at(i).jobLengths.second, pairArr.at(i).jobIdent.second );
            int expectedEndTime = pairArr.at(i).jobLengths.first + pairArr.at(i).jobLengths.second;
            int endTime = boss.doJobs(0);
            int difference = endTime - expectedEndTime;
            differences.push_back(difference);
            std::cout << "Algorithm: difference for " << i << " is " << difference << std::endl;
        };
        int bestTime = differences.at(0);
        for(int i = 0; i < differences.size(); i++ ){                                   // znajdz najlepszy czas
            if(bestTime > differences.at(i)) bestTime = differences.at(i);
            std::cout << "Algorithm: difference for " << i << " is " << differences.at(i) << std::endl;
        };
        
        std::vector<Overseer*> bestOverseers; //wskazniki bo po co robic nowe overseery
        
        for(int i = 0; i < nrOfPairs; i++){
            if(differences.at(i) == bestTime) { 
                bestOverseers.push_back(&overseers.at(i));
                std::cout << "Algorithm: Overseer " << overseers.at(i).getId() << " selected as best" << std::endl; 
            };
        };
	
}

int main(){	
	// generowanie dziur	
	cout << "Generator: generating holes" << endl;
	cout << "Generator: position1, position2" << endl;
	
	vector<int> holePos = generateHoles(HOLE_T, HOLE_L);					// deklaracja i inicjacja tablicy pozycji dziur
	
	srand (time(NULL));
	
	algorithm(generateJobs(JOBS_QUANTITY), holePos);
	
	return 0;
};
