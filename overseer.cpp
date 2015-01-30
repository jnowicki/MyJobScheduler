#include <iostream>
#include <string>
#include <algorithm>
#include <utility>
#include <sstream>
#include "classes.hpp"

#define MSG false

int Overseer::doJobs(int jobNr) {

    if(MSG) std::cout << "Overseer " << id << ": started tasks " << jobNr << std::endl;

    if (jobNr == 0) {
        first_t.push_back(0);
    };
    if (jobNr > 0) {
        
        first_t.push_back(first_d.at(jobNr - 1));
        
    }
    if(MSG) std::cout << "Overseer" << id << ": time of start of job " << jobNr + 1 << " for first machine equals " << first_t.at(jobNr) << std::endl;
    int f_exec_t = first.doJob(jobNr + 1); //czas egzekucji pierwszego zadania
    int f_exec_d = f_exec_t + first_t.at(jobNr); //zakonczenie pierwszego zadania
    first_d.push_back(f_exec_d); //wrzucenie tego do tablic zakonczen
    if(MSG) std::cout << "Overseer" << id << ": time of end of job " << jobNr + 1 << " for first machine equals " << f_exec_d << std::endl;

    int s_exec_last_d = 0; //czas zakonczenia egzekucji ostatniego zdania
    if (jobNr > 0) {
        s_exec_last_d = second_d.at(jobNr - 1);
    }
    int s_exec_start = std::max(f_exec_d, s_exec_last_d); //czas rozpoczecia zadania na drugiej maszynie

    if(MSG) std::cout << "Overseer" << id << ": time of start of job " << jobNr + 1 << " for second machine equals " << s_exec_start << std::endl;

    second_t.push_back(s_exec_start);

    int s_exec_t = second.doJobWithHoles(jobNr + 1, s_exec_start);
    int s_exec_d = s_exec_t + second_t.at(jobNr);
    second_d.push_back(s_exec_d);
    if(MSG) std::cout << "Overseer" << id << ": time of end of job " << jobNr + 1 << " for second machine equals " << s_exec_d << std::endl;
    
    return std::max(s_exec_d, f_exec_d); //zwroc czas wykonania dluzszego zadania
};

int Overseer::getId() const{
    return id;
}

void Overseer::updatePairs(int i){    // skasuj te pary ktore juz wykorzystalo 
    
    std::cout << "Overseer" << id << ": deleted pair j" << pairs.at(i).jobIdent.first << std::endl;
    pairs.erase(pairs.begin() + i);
};

bool Overseer::operator<(const Overseer& b) const{
    return this->getId() < b.getId();
};

void Overseer::printValues() const{
    std::cout<< "Overseer " << this->getId() << ": first machine: " << std::endl;
    std::cout<< "Overseer " << this->getId() << ": job nr, job length, job finish time, jobPair l" << std::endl;
    for(int j = 0; j < this->first_d.size(); j++ ){      
        std::cout << "Overseer " << this->getId() << ": " <<  this->first.getJobAt(j).second << ", " << this->first.getJobAt(j).first << ", " << this->first_d.at(j) << ", " << this->l.at(j) << std::endl;
    };
    std::cout<< "Overseer " << this->getId() << ": second machine: " << std::endl;
    std::cout<< "Overseer " << this->getId() << ": job nr, job length, job finish time, jobPair l" << std::endl;
    for(int j = 0; j < this->second_d.size(); j++ ){      
        std::cout << "Overseer " << this->getId() << ": " <<  this->second.getJobAt(j).second << ", " << this->second.getJobAt(j).first << ", " << this->second_d.at(j) << ", " << this->l.at(j) << std::endl;
    };
    
    std::cout << "Overseer " << this->getId() << ": " << "total time of execution for this instance is " << std::max(this->first_d.back(), this->second_d.back()) << std::endl;
};


Overseer::Overseer(Machine _first, Machine _second, int _id, std::vector<jobPair> _pairs) : first(_first), second(_second), id(_id), pairs(_pairs){};

std::vector<jobPair> Overseer::getPairs(){
    return pairs;
};

jobPair::jobPair(std::pair<int, int> f, std::pair<int, int> s){
	jobLengths = f;
	jobIdent = s;
};

jobPair::jobPair(std::pair<int, int> f, std::pair<int, int> s, int h){
	jobLengths = f;
	jobIdent = s;
        expectedTime = h;
};
