#include <iostream>
#include <string>
#include <algorithm>
#include <utility>
#include "classes.hpp"

int Overseer::doJobs(int jobNr) {

    std::cout << "Overseer: started tasks " << jobNr << std::endl;

    if (jobNr == 0) {
        first_t.push_back(0);
    };
    if (jobNr > 0) {
        
        first_t.push_back(first_d.at(jobNr - 1));
        
    }
    std::cout << "Overseer: time of start of job " << jobNr + 1 << " for first machine equals " << first_t.at(jobNr) << std::endl;
    int f_exec_t = first.doJob(jobNr + 1); //czas egzekucji pierwszego zadania
    int f_exec_d = f_exec_t + first_t.at(jobNr); //zakonczenie pierwszego zadania
    first_d.push_back(f_exec_d); //wrzucenie tego do tablic zakonczen
    std::cout << "Overseer: time of end of job " << jobNr + 1 << " for first machine equals " << f_exec_d << std::endl;

    int s_exec_last_d = 0; //czas zakonczenia egzekucji ostatniego zdania
    if (jobNr > 0) {
        s_exec_last_d = second_d.at(jobNr - 1);
    }
    int s_exec_start = std::max(f_exec_d, s_exec_last_d); //czas rozpoczecia zadania na drugiej maszynie

    std::cout << "Overseer: time of start of job " << jobNr + 1 << " for second machine equals " << s_exec_start << std::endl;

    second_t.push_back(s_exec_start);

    int s_exec_t = second.doJobWithHoles(jobNr + 1, s_exec_start);
    int s_exec_d = s_exec_t + second_t.at(jobNr);
    second_d.push_back(s_exec_d);
    std::cout << "Overseer: time of end of job " << jobNr + 1 << " for second machine equals " << s_exec_d << std::endl;
    
    return std::max(s_exec_d, f_exec_d); //zwroc czas wykonania dluzszego zadania
};

int Overseer::getId(){
    return id;
}

void Overseer::updatePairs(jobPair taken){    // skasuj te pary ktore juz wykorzystalo 
    int job1 = taken.jobIdent.first;
    int job2 = taken.jobIdent.second;
    
    for(int i = 0; i < pairs.size(); i++){
        int ident1 = pairs.at(i).jobIdent.first;
        int ident2 = pairs.at(i).jobIdent.second;
        if(( ident1 == job1) || ( ident1 == job2) || (ident2 == job1) || (ident2 == job2)){
            pairs.erase(pairs.begin() + i);
        };
    };
    //std::cout << "Overseer: Updated pair " << job1 << " " << job2 << std::endl;
};

std::vector<jobPair> Overseer::getPairs(){
    return pairs;
};

Overseer::Overseer(Machine _first, Machine _second, int _id, std::vector<jobPair> _pairs) : first(_first), second(_second), id(_id), pairs(_pairs){};

jobPair::jobPair(std::pair<int, int> f, std::pair<int, int> s){
	jobLengths = f;
	jobIdent = s;
};
