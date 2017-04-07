CXXFLAGS = -c -g -std=c++11 -Wall -W -pedantic

count:	lineCount.o
	g++ lineCount.o -o count

lineCount.o:	lineCount.cpp
	g++ $(CXXFLAGS) lineCount.cpp

clean:
	rm count *.o
