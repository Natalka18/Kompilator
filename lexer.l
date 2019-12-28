%option noyywrap
%option yylineno
%{
	#include<iostream>
	#include"grammar.hpp"
	
	using namespace std;
	
	int yylex();
%}

num				[-]?[0-9]+
pidentifier		[_a-z]+
white			[ \t]*

%s COMMENT

%%

{num}				{ return num; }
{pidentifier}		{ return pidentifier; }
{white}				;
"\n"				;

","					{ return comma; }
";"					{ return semicolon; }
":"					{ return colon; }
"("					{ return left_bracket; }
")"					{ return right_bracket; }

"DECLARE"			{ return DECLARE; }
"BEGIN"				{ return BEGIN_TOKEN; }
"END"				{ return END; }
"ASSIGN"			{ return ASSIGN; }
"IF"				{ return IF; }
"THEN"				{ return THEN; }
"ELSE"				{ return ELSE; }
"ENDIF"				{ return ENDIF; }
"WHILE"				{ return WHILE; }
"DO"				{ return DO; }
"ENDWHILE"			{ return ENDWHILE; }
"ENDDO"				{ return ENDDO; }
"FOR"				{ return FOR; }
"FROM"				{ return FROM; }
"TO"				{ return TO; }
"ENDFOR"			{ return ENDFOR; }
"DOWNTO"			{ return DOWNTO; }
"READ"				{ return READ; }
"WRITE"				{ return WRITE; }
"PLUS"				{ return PLUS; }	
"MINUS"				{ return MINUS; }
"TIMES"				{ return TIMES; }
"DIV"				{ return DIV; }
"MOD"				{ return MOD; }
"EQ"				{ return EQ; }
"NEQ"				{ return NEQ; }
"LE"				{ return LE; }
"GE"				{ return GE; }
"LEQ"				{ return LEQ; }
"GEQ"				{ return GEQ; }


"["					{ BEGIN(COMMENT); }
<COMMENT>"]"		{ BEGIN(INITIAL); }
<COMMENT>.			;


.					{ 
							cout << "Line " << yylineno << \
							 ": unrecognized character " << yytext <<endl; 
							return ERROR; 
					}

%%


