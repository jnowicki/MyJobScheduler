#include <stdlib.h>
#include <time.h>
#include <vector>
#include <iostream>
#include "classes.hpp"
#include "algorithm.hpp"

#define JOBS_QUANTITY 6 	// ilosc zadan

#define HOLE_T 4 			// czas pomiedzy dziurami
#define HOLE_L 2 			// dlugosc dziury

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
