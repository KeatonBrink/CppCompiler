CXXFLAGS := -std=c++11
# extra tough syntax error and bad code style warning checking
CXXFLAGS := $(CXXFLAGS) -Wall -Wpedantic -Wextra -Werror

all: tester

tester: tester.o Token.o
	g++ $(CXXFLAGS) -o tester tester.o Token.o

tester.o: tester.cpp Token.cpp Token.h
	g++ $(CXXFLAGS) -c tester.cpp

Token.o: Token.cpp Token.h
	g++ $(CXXFLAGS) -c Token.cpp