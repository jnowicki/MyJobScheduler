#include <vector>
#include <utility>
#pragma once

class jobPair{
	public:
		std::pair<int, int> jobLengths;
		std::pair<int, int> jobIdent;
		jobPair(std::pair<int, int>, std::pair<int, int>);
};

class Machine{
	int machineNumber; 									// numer maszyny
	std::vector<int> jobs;
        std::vector<int> idents;        // tablica zadan
	std::vector<int> holePos; 										// ostatnie zadanie wykonane na tej maszynie
	public:
		int doJobWithHoles(int,int);
		int doJob(int);
                void addJob(int, int);                // wykonaj nastepne zadanie na tej maszynie 							
		Machine (int); 					// konstruktorek
		Machine (int, std::vector<int>); // konstruktorek dla maszyny z dziura
};

class Overseer{
	std::vector<int> first_d;							//czasy zakonczenia prac na pierwszej maszynie
	std::vector<int> second_d;							// na drugiej
	std::vector<int> first_t;							//czas startu prac na pierwszej maszynie
	std::vector<int> second_t;							//czas startu na drugiej
	std::vector<int> jobs;	
        int id;
	public:
            Machine first;
            Machine second;
            int getId();
            int doJobs(int);
            Overseer(Machine, Machine, int);
};




