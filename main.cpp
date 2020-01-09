// dane wczytuje z pliku, ale jest problem z pisaniem do pliku

#include<iostream>

extern void yyparse();
extern void yyset_in(FILE*);
extern void yyset_out(FILE*);
extern FILE *yyout;

using namespace std;

int main(int argc, char* argv[]) {
	FILE* file_in;
	FILE* file_out;
	
	if(argc == 3) {
		file_in = fopen(argv[1], "r");
		file_out = fopen(argv[2], "w");
		
		if(!file_in || !file_out) {
			if(!file_in) {
				cerr << "Nie można otworzyć pliku " << argv[1] << endl;
			} else {
				cerr << "Nie można otworzyć pliku " << argv[2] << endl;
			}
		} else {
			yyset_in(file_in);
			yyout = file_out;
			//yyset_out(file_out);
			yyparse();
			fclose(file_in);
			fclose(file_out);
		}
	} else {
		cerr << "Sposób wywołania programu: ./kompilator <nazwa pliku wejściowego> <nazwa pliku wyjściowego>" << endl;
	}
	
	return 0;
}

