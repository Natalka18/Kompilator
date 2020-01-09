// klasa odpowiadająca instrukcji assemblerowej

#pragma once

#include<iostream>
#include<string>

using namespace std;

class Instruction {
	public:
		string name; // nazwa instrukcji
		long long arg; // wartość argumentu (jeśli -1, to instrukcja nie przyjmuje argumentów)
		Instruction* nextInstruction = NULL; // wskaźnik na następną instrukcję
		
		Instruction(string name, long long arg) {
			this -> name = name;
			this -> arg = arg;
		}
		
		Instruction(string name) {
			this -> name = name;
			this -> arg = -1;
		}
		
		string toString() {
			if(arg == -1) {
				return name;
			} else {
				return name + " " + to_string(arg);
			}
		}
		
		void setNextInstruction(Instruction* next) {
			this -> nextInstruction = next;
		}
};


