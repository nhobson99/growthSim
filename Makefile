main:	main.cpp 
	g++ -g -std=c++11 main.cpp -o growthSim -lSDL2
clean: 
	rm growthSim
