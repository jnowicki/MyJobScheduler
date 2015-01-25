#include <iostream>
#include <future>
#include <algorithm>
#include "overseer_machine.hpp"

void Overseer::start(int JobsQt){
	std::cout << "Overseer: started " << std::endl;
	first_t.push_back(0);
	for(int i = 0; i < JobsQt; i++){
		if ( i > 0 ) {
			first_t.push_back ( first_d.at( i - 1));
		}
		std::cout << "Overseer: time of start of job " << i + 1 << " for first machine equals " << first_t.at(i) << std::endl;
		int f_exec_t = first->doJob( i + 1 ); 			//czas egzekucji pierwszego zadania
		int f_exec_d = f_exec_t + first_t.at(i);			//zakonczenie pierwszego zadania
		first_d.push_back(f_exec_d);					//wrzucenie tego do tablic zakonczen
		std::cout << "Overseer: time of end of job " << i + 1 << " for first machine equals " << f_exec_d << std::endl;
		
		int s_exec_last_d = 0;							//czas zakonczenia egzekucji ostatniego zdania
		if( i > 0) {
			s_exec_last_d = second_d.at( i - 1);
		} 
		int s_exec_start = std::max(f_exec_d, s_exec_last_d);
		
		std::cout << "Overseer: time of start of job " << i + 1 << " for second machine equals " << s_exec_start << std::endl;
		
		second_t.push_back(s_exec_start);
		
		int s_exec_t = second->doJob( i + 1);
		int s_exec_d = s_exec_t + second_t.at(i);
		second_d.push_back(s_exec_d);
		std::cout << "Overseer: time of end of job " << i + 1 << " for second machine equals " << s_exec_d << std::endl;
	}
	
};

Overseer::Overseer(Machine * _first, Machine * _second) : first(_first), second(_second){
	timePosition = 0;
};
