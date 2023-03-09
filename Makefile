CXXFLAGS := -std=c++11
# extra tough syntax error and bad code style warning checking
CXXFLAGS := $(CXXFLAGS) -Wall -Wpedantic -Wextra -Werror
# gdb inclusion
CXXFLAGS := $(CXXFLAGS) -g

all: testTok mainTest

mainTest: Main.o Scanner.o Token.o StateMachine.o Symbol.o Node.o Parser.o
	g++ $(CXXFLAGS) -o mainTest Main.o Scanner.o Token.o StateMachine.o Symbol.o Node.o Parser.o

Parser.o: Parser.cpp Parser.h
	g++ $(CXXFLAGS) -c Parser.cpp

Node.o: Node.cpp Node.h
	g++ $(CXXFLAGS) -c Node.cpp

Symbol.o: Symbol.cpp Symbol.h
	g++ $(CXXFLAGS) -c Symbol.cpp

Main.o: Main.cpp Scanner.h Scanner.cpp Token.h Token.cpp Symbol.h Symbol.cpp
	g++ $(CXXFLAGS) -c Main.cpp

Scanner.o: Scanner.cpp Scanner.h StateMachine.cpp StateMachine.h Token.cpp Token.h 
	g++ $(CXXFLAGS) -c Scanner.cpp

StateMachine.o: StateMachine.cpp StateMachine.h Token.cpp Token.h
	g++ $(CXXFLAGS) -c StateMachine.cpp



testTok: tester.o Token.o
	g++ $(CXXFLAGS) -o testTok tester.o Token.o

tester.o: tester.cpp Token.cpp Token.h
	g++ $(CXXFLAGS) -c tester.cpp

Token.o: Token.cpp Token.h
	g++ $(CXXFLAGS) -c Token.cpp

clean:
	-rm -f mainTest
	-rm -f testTok
	-rm -f tester
	-rm -f *.o