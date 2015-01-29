#include <vector>
#include <utility>
#include <string>
#pragma once



class jobPair{ // para par xD generalnie chodzi o to że nie chce stracic numerku pracy ktory mam na poczatku (j1,j2,j3,j4,j5,j6)
	public:
		std::pair<int, int> jobLengths;
		std::pair<int, int> jobIdent;
                int expectedTime;
		jobPair(std::pair<int, int>, std::pair<int, int>);
                jobPair(std::pair<int, int>, std::pair<int, int>, int);
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
        std::vector<jobPair> pairs;
        int id;
	public:
            std::vector<int> l;
            Machine first;
            Machine second;
            void updatePairs(jobPair);
            void printValues() const;
            std::vector<jobPair> getPairs();
            int getId() const;
            int doJobs(int);
            Overseer(Machine, Machine, int, std::vector<jobPair>);
            bool operator<(const Overseer& b) const;
};




