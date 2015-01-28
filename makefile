app: main.o machine.o overseer.o
	g++ main.o overseer.o machine.o algorithm.o -o app

main.o: main.cpp classes.hpp
	g++ -std=gnu++0x -c main.cpp
	
machine.o: machine.cpp classes.hpp
	g++ -std=gnu++0x -c machine.cpp
	
overseer.o: overseer.cpp classes.hpp
	g++ -std=gnu++0x -c overseer.cpp
	
algorithm.o: algorithm.cpp algorithm.hpp
	g++ -std=gnu++0x -c algorithm.cpp
	
clean:
	rm -rf *.o app.exe 
