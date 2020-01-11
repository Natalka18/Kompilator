// odpowiada komórce pamięci lub grupie komórek w przypadku tablicy, przechowuje jej indeks, nazwę zmiennej,
// której wartość jest w niej zapisana oraz informację o tym, czy przechowywana w komórce
// wartość jest elementem tablicy oraz rozmiar tej tablicy

#pragma once

#include<string>


class MemoryItem {
	public:
		long long index; // numer komórki pamięci. Jeśli zmienna jest tablicą,
						// to index oznacza numer komórki pamięci, w której
						// znajduje się pierwszy element tablicy
		bool isArray; // czy element w tej komórce jest elementem tablicy
		long long size; // rozmiar tablicy, do której należy ta komórka
		long long begin; // początkowy indeks tablicy
		long long end; // końcowy indeks tablicy
		string name; // nazwa zmiennej, której wartość jest zapisana w tej komórce
		
		long long additionalCell; // numer komórki, w której przechowywana jest wartość 
		//index - begin potrzebna do obliczania, w której komórce znajduje się element
		// tablicy przy odwołaniu typu tablica(zmienna)
		
		MemoryItem(long long index, bool isArray, long long size, string name,
					long long begin, long long end) {
			this->index = index;
			this->isArray=isArray;
			this->size = size;
			this->name = name;
			this->begin = begin;
			this->end = end;
		}
		
		MemoryItem(long long index, string name) {
			this->index = index;
			this->name = name;
			this->isArray = false;
			this->size = 1;
			this->begin = 1;
			this->end = 1;
		}
		
		// zwraca numer komórki, w której znajduje się element tablicy o indeksie i
		long long getMemoryIndexOf(long long i) {
			return index+i-begin;
		}
};
