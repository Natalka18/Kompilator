// klasa odpowiadająca wartości przechowywanej w danej komórce pamięci


#include<string>

#include"Instruction.hpp"

using namespace std;

class Value {
	public:
		long long value; // przechowywana wartość
		long long index; // numer komórki pamięci, w której wartość jest przechowywana
		
		Value(long long value, long long index) {
			this -> value = value;
			this -> index = index;
		}
		
		// zwraca true, jeśli wartość jest zmienną. False, jeśli to stała
		bool isVariable() {
			return false;
		}
		
		// zwraca wektor instrukcji koniecznych do wygenerowania stałej value
		// i umieszczenie jej w komórce numer index
		//vector<Instruction*> generateNumber() {
			//vector<Instruction*> instructions;
			
			//instructions.push_back(new Instruction("SUB", 0)); // zerujemy akumulator
			
			//return instructions;
		//}
};

