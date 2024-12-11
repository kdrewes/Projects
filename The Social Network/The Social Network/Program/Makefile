ALL: Social_Network
CPP=g++

Social_Network: Profile.o main.o Network.o
	$(CPP) -o Social_Network Profile.o main.o Network.o

main.o: main.cpp Profile.hpp Network.hpp
	$(CPP) -c main.cpp

Profile.o: Profile.cpp Profile.hpp Network.hpp
	$(CPP) -c Profile.cpp

Network.o: Network.cpp Network.hpp Profile.hpp
	$(CPP) -c Network.cpp

clean:
	rm -rf *.o *~
