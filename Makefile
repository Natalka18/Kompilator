all: kompilator

kompilator: lexer.o grammar.o main.o
	$(CXX) $^ -o $@
	strip $@
	
%.o: %.cpp
	$(CXX) -c $^
	
lexer.cpp: lexer.l grammar.hpp
	flex -o $@ $<

grammar.cpp grammar.hpp: grammar.ypp
	bison -Wall -d -o grammar.cpp $^
