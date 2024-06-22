CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

SRC = main.cpp 
HEADERS = binary heap.h Dynamic Array.h Graph.h Header.h set.h tests.h ui.h
OBJS = $(SRC:.cpp=.o)
EXEC = main

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

.PHONY: all clean