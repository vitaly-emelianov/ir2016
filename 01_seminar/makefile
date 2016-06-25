CXX=g++
FLAGS=-std=c++11

all: buildIndex search

buildIndex: 
	$(CXX) $(FLAGS) buildIndex.cpp -o buildIndex src/IndexBuilder.cpp src/SearchRobot.cpp src/Parser.cpp src/Filesystem.cpp

search: 
	$(CXX) $(FLAGS) search.cpp -o search src/IndexBuilder.cpp src/SearchRobot.cpp src/Parser.cpp src/Filesystem.cpp
