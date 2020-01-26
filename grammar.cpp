/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "grammar.ypp" /* yacc.c:339  */

	#include<iostream>
	#include<fstream>
	#include<string>
	#include<vector>
	#include<map>
	#include<stack>
	
	#include"Instruction.hpp"
	//#include"Value.hpp"
	#include"MemoryItem.hpp"
	
	using namespace std;
	
	int yylex();
	int yyerror(string);
	extern int yylineno;
	
	// odpowiada nieterminalom identifier i value
	struct value {
		bool isArray; // czy nieterminal odpowiada elementowi tablicy
		bool isVariable; // czy nieterminal odpowiada zwykłej zmiennej
		bool isNumber; // czy nieterminal odpowiada zwykłej liczbie
		bool isIterator; // czy nieterminal odnosi się do iteratora
		string name; // nazwa zmiennej (lub tablicy)
		string index; // nazwa zmiennej, która jest indeksem elementu tablicy.
					  // Jeśli to nie jest tablica, to index=""
		long long index_long; // indeks elementu tablicy, któremu odpowiada ta struktura
							  // Jeśli to nie jest tablica, to index_long=-1
		long long num; //wartość liczby, jeśli isNumber=true
	};
	
	// oznacza numer komórki pamięci
	struct cell {
		long long cell; // oznacza numer komórki
		bool containsValue; // true, jeśli cell oznacza numer komórki, w której przechowywana
							// jest dana wartość
		bool containsIndex; // true, jeśli cell oznacza numer komórki, której znajduje się
							// numer komórki, w której znajduje się dana wartość
		bool valueIsNumber; // true, jeśli value było num
	};
	
	// odpowiada warunkowi condition
	struct cond {
		struct value* value1;
		struct value* value2;
		string op; // rodzaj porównania (EQ, NEQ, LE itd.)
	};
	
	// stos służący do przechowywania numerów instrukcji w celu ominięcia poleceń
	// znajdujących się wewnątrz ifa (lub else'a).
	// Przechowywane są numery jumpów, żeby móc później zmienić ich argument
	stack<long long> ifLinePointerStack;
	
	// stos przechowujący numery instrukcji, do których trzeba skoczyć w celu powrotu
	// do sprawdzenia warunku pętli
	stack<long long> whileConditionPointerStack;
	
	// stos przechowujący numery instrukcji, w których są jumpy (które przenoszą za pętlę).
	// Potrzebne do późniejszej zmiany argumentu jumpów
	stack<long long> whileLinePointerStack;
	
	// przechowuje miejsca, do których trzeba skoczyć, żeby wrócić do początku DO
	// w pętli DO WHILE
	stack<long long> doWhileLinePointerStack;
	
	// tak jak dla while
	stack<long long> forLinePointerStack;
	// tu są umieszczane numery komórki, w której umieszczamy wartość iteratora
	stack<long long> forIteratorCellStack;
	// tu są umieszczane numery komórki, w której umieszczamy licznik pętli
	stack<long long> forCounterCellStack;
	// nazwy iteratorów
	stack<string> iteratorNameStack;
	
	void yyset_out(FILE* out_str);
	FILE* yyget_out();
	
	long long memory_pointer = 1; //zmienić to
	vector<Instruction*> instructions; // wektor przechowujący kolejne instrukcje assemblerowe
	map<string,MemoryItem*> variables; // mapa przechwująca pary (nazwa zmiennej, komórka pamięci)
	
	void printInstructions();
	// funkcja dodaje do wektora variables nową zmienną. Zwraca true, jeśli operacja się powiedzie
	bool declareVariable(string name, bool isIterator);
	// funkcja wczytuje wartość oraz zapisuje ją w zmiennej o nazwie name.
	// Zwraca true, jeśli operacja się powiedzie. Dodaje odpowiednie instrukcje assemblera
	bool loadValueToVariable(struct value* value);
	void printValue(struct value* value);
	// funkcja dodaje do wektora variables nową zmienną tablicową o początkowym
	// indeksie begin i końcowym indeksie end
	bool declareArray(string name, long long begin, long long end);
	// generuje instrukcje assemblerowe, które wygenerują liczbę number
	// i umieszczą ją w komórce pamięci o numerze cell
	void generateNumberAndStore(long long number, long long cell);
	// generuje instrukcje, które umieszczą w akumulatorze numer komórki,
	// w której przechowywana jest wartość elementu o indeksie variable 
	// tablicy array
	void calculateIndexOfArrayElement(string array, string variable);
	// generuje instrukcje, które umieszczą w akumulatorze wartość odpowiadającą
	// strukturze value
	void loadValueToAccumulator(struct value* value);
	// generuje instrukcje, które umieszczą w value wartość z komórki
	// o numerze cell.
	// Odpowiednik funkcji loadValueToVariable, ale tam zapisywana jest w zmiennej
	// wartość z akumulatora, a tu z dowolnej komórki.
	// Służy do zapisywania wartości z komórki cell w zmiennej, której odpowiada
	// struktura value.
	void storeValueFromCell(struct value* value, long long cell);
	// zwraca cell, która odpowiada danej wartości value
	struct cell* findValueInMemory(struct value* value);
	// dodaje liczby z value1 i value2 i umieszcza wynik w komórce o numerze result_cell
	void add(struct value* value1, struct value* value2, long long result_cell);
	// odejmuje liczby z value1 i value2 i umieszcza wynik w komórce o numerze result_cell
	void subtract(struct value* value1, struct value* value2, long long result_cell);
	// mnoży liczby z value1 i value2 i umieszcza wynik w komórce o numerze result_cell
	void multiply(struct value* value1, struct value* value2, long long result_cell);
	// dzieli liczby z value1 i value2 i umieszcza wynik w komórce o numerze result_cell.
	// Jeśli mod jest true, to zamiast wyniku dzielenia umieszcza resztę w result_cell
	void divide(struct value* value1, struct value* value2, long long result_cell, bool mod);
	// umieszcza w akumulatorze wartość do sprawdzenia (value1-value2), następnie wykonuje 
	// skok do instrukcji o numerze k
	void checkConditionNegation(struct cond* c, long long k); // if, while
	void checkCondition(struct cond* c, long long k); // do while

#line 192 "grammar.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "grammar.hpp".  */
#ifndef YY_YY_GRAMMAR_HPP_INCLUDED
# define YY_YY_GRAMMAR_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    DECLARE = 258,
    BEGIN_TOKEN = 259,
    END = 260,
    ASSIGN = 261,
    IF = 262,
    THEN = 263,
    ELSE = 264,
    ENDIF = 265,
    WHILE = 266,
    DO = 267,
    ENDWHILE = 268,
    ENDDO = 269,
    FOR = 270,
    FROM = 271,
    TO = 272,
    ENDFOR = 273,
    DOWNTO = 274,
    READ = 275,
    WRITE = 276,
    PLUS = 277,
    MINUS = 278,
    TIMES = 279,
    DIV = 280,
    MOD = 281,
    EQ = 282,
    NEQ = 283,
    LE = 284,
    GE = 285,
    LEQ = 286,
    GEQ = 287,
    num = 288,
    pidentifier = 289,
    comma = 290,
    semicolon = 291,
    colon = 292,
    left_bracket = 293,
    right_bracket = 294,
    ERROR = 295
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 130 "grammar.ypp" /* yacc.c:355  */

	char* string;
	int integer;
	long long long_long;
	struct value* value_struct;
	struct result* result_struct;
	struct cond* cond_struct;

#line 282 "grammar.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_GRAMMAR_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 299 "grammar.cpp" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
# define YYCOPY_NEEDED 1
#endif


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   211

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  17
/* YYNRULES -- Number of rules.  */
#define YYNRULES  43
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  108

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   295

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   189,   189,   193,   199,   202,   205,   208,   213,   217,
     220,   224,   227,   224,   243,   243,   267,   267,   278,   278,
     342,   342,   406,   409,   414,   414,   424,   432,   445,   450,
     455,   460,   465,   472,   480,   488,   496,   504,   512,   522,
     535,   540,   561,   591
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DECLARE", "BEGIN_TOKEN", "END",
  "ASSIGN", "IF", "THEN", "ELSE", "ENDIF", "WHILE", "DO", "ENDWHILE",
  "ENDDO", "FOR", "FROM", "TO", "ENDFOR", "DOWNTO", "READ", "WRITE",
  "PLUS", "MINUS", "TIMES", "DIV", "MOD", "EQ", "NEQ", "LE", "GE", "LEQ",
  "GEQ", "num", "pidentifier", "comma", "semicolon", "colon",
  "left_bracket", "right_bracket", "ERROR", "$accept", "program",
  "declarations", "commands", "command", "$@1", "$@2", "$@3", "$@4", "$@5",
  "$@6", "end_if", "$@7", "expression", "condition", "value", "identifier", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295
};
# endif

#define YYPACT_NINF -29

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-29)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      17,   -28,   165,    10,   -25,     0,    -8,    -8,   -29,   -19,
     -17,    -8,    -7,     7,   -29,    32,   -29,    11,   165,    -1,
     -29,   -29,    40,   -29,   -29,   165,    24,     9,    13,    -4,
     -29,   -29,    -8,     6,    43,    14,    39,    -8,    -8,    -8,
      -8,    -8,    -8,    44,   177,    -8,   -29,   -29,    12,    20,
      25,    64,    29,   -29,    42,   165,   -29,   -29,   -29,   -29,
     -29,   -29,   165,    -8,   -12,   -29,   -29,   -29,    -8,    -8,
      -8,    -8,    -8,    37,    41,   165,   110,    65,    -8,    -8,
     -29,   -29,   -29,   -29,   -29,   -29,    47,    27,   -29,   -29,
     -29,   -29,    52,   -29,   -29,   -29,    69,    83,   -29,   165,
     165,   165,   117,   141,   153,   -29,   -29,   -29
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     6,     0,     0,     0,    16,     0,
       0,     0,    41,     0,     9,     0,     1,     0,     0,     0,
      39,    11,     0,    40,    14,     0,     0,     0,     0,     0,
       3,     8,     0,     0,     0,     4,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    22,    23,     0,     0,
       0,    27,     0,     2,     0,     0,    33,    34,    35,    36,
      37,    38,     0,     0,     0,    43,    42,    10,     0,     0,
       0,     0,     0,     0,     0,    12,     0,    14,     0,     0,
      28,    29,    30,    31,    32,     7,     0,     0,    15,    17,
      18,    20,     0,    24,    26,    13,     0,     0,     5,     0,
       0,     0,     0,     0,     0,    25,    19,    21
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -29,   -29,   -29,   -16,   -10,   -29,   -29,   -29,   -29,   -29,
     -29,   -29,   -29,   -29,    -6,    71,    -2
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     5,    13,    14,    36,    87,    43,    25,    96,
      97,    95,    99,    50,    21,    22,    23
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      15,    24,    34,    31,    18,    78,     4,    79,    27,    44,
      16,    15,    30,    17,     6,    26,    15,    12,     7,     8,
       1,     2,     9,    15,    31,    20,    12,    10,    11,    48,
      49,    29,    15,    35,    31,    19,    93,    94,    32,    75,
      45,    12,    15,    52,    33,    46,    76,    55,    53,    47,
       6,    65,    54,    15,     7,     8,    62,    77,     9,    66,
      15,    67,    73,    10,    11,    31,    31,    37,    38,    39,
      40,    41,    42,    15,    15,    74,    85,    12,    86,    89,
      92,   100,    28,   102,   103,   104,    68,    69,    70,    71,
      72,    98,    31,    31,    31,   101,     0,    15,    15,    15,
      15,    15,    15,    51,     0,     0,     0,     0,    56,    57,
      58,    59,    60,    61,     0,     0,    64,     6,     0,     0,
       0,     7,     8,    88,     6,     9,     0,   105,     7,     8,
      10,    11,     9,     0,     0,     0,     0,    10,    11,    80,
      81,    82,    83,    84,    12,     0,     0,     0,     6,    90,
      91,    12,     7,     8,     0,     0,     9,     0,     0,   106,
       6,    10,    11,     0,     7,     8,     0,     0,     9,     0,
       0,   107,     6,    10,    11,    12,     7,     8,     0,     0,
       9,     0,     0,     0,     6,    10,    11,    12,    63,     8,
       0,     0,     9,     0,     0,     0,     0,    10,    11,    12,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    12
};

static const yytype_int8 yycheck[] =
{
       2,     7,    18,    13,     4,    17,    34,    19,    10,    25,
       0,    13,     5,    38,     7,    34,    18,    34,    11,    12,
       3,     4,    15,    25,    34,    33,    34,    20,    21,    33,
      34,    38,    34,    34,    44,    35,     9,    10,     6,    55,
      16,    34,    44,    37,    33,    36,    62,     8,     5,    36,
       7,    39,    38,    55,    11,    12,    12,    63,    15,    39,
      62,    36,    33,    20,    21,    75,    76,    27,    28,    29,
      30,    31,    32,    75,    76,    33,    39,    34,    37,    14,
      33,    12,    11,    99,   100,   101,    22,    23,    24,    25,
      26,    39,   102,   103,   104,    12,    -1,    99,   100,   101,
     102,   103,   104,    32,    -1,    -1,    -1,    -1,    37,    38,
      39,    40,    41,    42,    -1,    -1,    45,     7,    -1,    -1,
      -1,    11,    12,    13,     7,    15,    -1,    10,    11,    12,
      20,    21,    15,    -1,    -1,    -1,    -1,    20,    21,    68,
      69,    70,    71,    72,    34,    -1,    -1,    -1,     7,    78,
      79,    34,    11,    12,    -1,    -1,    15,    -1,    -1,    18,
       7,    20,    21,    -1,    11,    12,    -1,    -1,    15,    -1,
      -1,    18,     7,    20,    21,    34,    11,    12,    -1,    -1,
      15,    -1,    -1,    -1,     7,    20,    21,    34,    11,    12,
      -1,    -1,    15,    -1,    -1,    -1,    -1,    20,    21,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    34
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,    42,    34,    43,     7,    11,    12,    15,
      20,    21,    34,    44,    45,    57,     0,    38,     4,    35,
      33,    55,    56,    57,    55,    49,    34,    57,    56,    38,
       5,    45,     6,    33,    44,    34,    46,    27,    28,    29,
      30,    31,    32,    48,    44,    16,    36,    36,    33,    34,
      54,    56,    37,     5,    38,     8,    56,    56,    56,    56,
      56,    56,    12,    11,    56,    39,    39,    36,    22,    23,
      24,    25,    26,    33,    33,    44,    44,    55,    17,    19,
      56,    56,    56,    56,    56,    39,    37,    47,    13,    14,
      56,    56,    33,     9,    10,    52,    50,    51,    39,    53,
      12,    12,    44,    44,    44,    10,    18,    18
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    41,    42,    42,    43,    43,    43,    43,    44,    44,
      45,    46,    47,    45,    48,    45,    49,    45,    50,    45,
      51,    45,    45,    45,    53,    52,    52,    54,    54,    54,
      54,    54,    54,    55,    55,    55,    55,    55,    55,    56,
      56,    57,    57,    57
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     5,     3,     3,     8,     1,     6,     2,     1,
       4,     0,     0,     7,     0,     6,     0,     6,     0,    10,
       0,    10,     3,     3,     0,     4,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       1,     1,     4,     4
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      YY_LAC_DISCARD ("YYBACKUP");                              \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

/* Given a state stack such that *YYBOTTOM is its bottom, such that
   *YYTOP is either its top or is YYTOP_EMPTY to indicate an empty
   stack, and such that *YYCAPACITY is the maximum number of elements it
   can hold without a reallocation, make sure there is enough room to
   store YYADD more elements.  If not, allocate a new stack using
   YYSTACK_ALLOC, copy the existing elements, and adjust *YYBOTTOM,
   *YYTOP, and *YYCAPACITY to reflect the new capacity and memory
   location.  If *YYBOTTOM != YYBOTTOM_NO_FREE, then free the old stack
   using YYSTACK_FREE.  Return 0 if successful or if no reallocation is
   required.  Return 1 if memory is exhausted.  */
static int
yy_lac_stack_realloc (YYSIZE_T *yycapacity, YYSIZE_T yyadd,
#if YYDEBUG
                      char const *yydebug_prefix,
                      char const *yydebug_suffix,
#endif
                      yytype_int16 **yybottom,
                      yytype_int16 *yybottom_no_free,
                      yytype_int16 **yytop, yytype_int16 *yytop_empty)
{
  YYSIZE_T yysize_old =
    *yytop == yytop_empty ? 0 : *yytop - *yybottom + 1;
  YYSIZE_T yysize_new = yysize_old + yyadd;
  if (*yycapacity < yysize_new)
    {
      YYSIZE_T yyalloc = 2 * yysize_new;
      yytype_int16 *yybottom_new;
      /* Use YYMAXDEPTH for maximum stack size given that the stack
         should never need to grow larger than the main state stack
         needs to grow without LAC.  */
      if (YYMAXDEPTH < yysize_new)
        {
          YYDPRINTF ((stderr, "%smax size exceeded%s", yydebug_prefix,
                      yydebug_suffix));
          return 1;
        }
      if (YYMAXDEPTH < yyalloc)
        yyalloc = YYMAXDEPTH;
      yybottom_new =
        (yytype_int16*) YYSTACK_ALLOC (yyalloc * sizeof *yybottom_new);
      if (!yybottom_new)
        {
          YYDPRINTF ((stderr, "%srealloc failed%s", yydebug_prefix,
                      yydebug_suffix));
          return 1;
        }
      if (*yytop != yytop_empty)
        {
          YYCOPY (yybottom_new, *yybottom, yysize_old);
          *yytop = yybottom_new + (yysize_old - 1);
        }
      if (*yybottom != yybottom_no_free)
        YYSTACK_FREE (*yybottom);
      *yybottom = yybottom_new;
      *yycapacity = yyalloc;
    }
  return 0;
}

/* Establish the initial context for the current lookahead if no initial
   context is currently established.

   We define a context as a snapshot of the parser stacks.  We define
   the initial context for a lookahead as the context in which the
   parser initially examines that lookahead in order to select a
   syntactic action.  Thus, if the lookahead eventually proves
   syntactically unacceptable (possibly in a later context reached via a
   series of reductions), the initial context can be used to determine
   the exact set of tokens that would be syntactically acceptable in the
   lookahead's place.  Moreover, it is the context after which any
   further semantic actions would be erroneous because they would be
   determined by a syntactically unacceptable token.

   YY_LAC_ESTABLISH should be invoked when a reduction is about to be
   performed in an inconsistent state (which, for the purposes of LAC,
   includes consistent states that don't know they're consistent because
   their default reductions have been disabled).  Iff there is a
   lookahead token, it should also be invoked before reporting a syntax
   error.  This latter case is for the sake of the debugging output.

   For parse.lac=full, the implementation of YY_LAC_ESTABLISH is as
   follows.  If no initial context is currently established for the
   current lookahead, then check if that lookahead can eventually be
   shifted if syntactic actions continue from the current context.
   Report a syntax error if it cannot.  */
#define YY_LAC_ESTABLISH                                         \
do {                                                             \
  if (!yy_lac_established)                                       \
    {                                                            \
      YYDPRINTF ((stderr,                                        \
                  "LAC: initial context established for %s\n",   \
                  yytname[yytoken]));                            \
      yy_lac_established = 1;                                    \
      {                                                          \
        int yy_lac_status =                                      \
          yy_lac (yyesa, &yyes, &yyes_capacity, yyssp, yytoken); \
        if (yy_lac_status == 2)                                  \
          goto yyexhaustedlab;                                   \
        if (yy_lac_status == 1)                                  \
          goto yyerrlab;                                         \
      }                                                          \
    }                                                            \
} while (0)

/* Discard any previous initial lookahead context because of Event,
   which may be a lookahead change or an invalidation of the currently
   established initial context for the current lookahead.

   The most common example of a lookahead change is a shift.  An example
   of both cases is syntax error recovery.  That is, a syntax error
   occurs when the lookahead is syntactically erroneous for the
   currently established initial context, so error recovery manipulates
   the parser stacks to try to find a new initial context in which the
   current lookahead is syntactically acceptable.  If it fails to find
   such a context, it discards the lookahead.  */
#if YYDEBUG
# define YY_LAC_DISCARD(Event)                                           \
do {                                                                     \
  if (yy_lac_established)                                                \
    {                                                                    \
      if (yydebug)                                                       \
        YYFPRINTF (stderr, "LAC: initial context discarded due to "      \
                   Event "\n");                                          \
      yy_lac_established = 0;                                            \
    }                                                                    \
} while (0)
#else
# define YY_LAC_DISCARD(Event) yy_lac_established = 0
#endif

/* Given the stack whose top is *YYSSP, return 0 iff YYTOKEN can
   eventually (after perhaps some reductions) be shifted, return 1 if
   not, or return 2 if memory is exhausted.  As preconditions and
   postconditions: *YYES_CAPACITY is the allocated size of the array to
   which *YYES points, and either *YYES = YYESA or *YYES points to an
   array allocated with YYSTACK_ALLOC.  yy_lac may overwrite the
   contents of either array, alter *YYES and *YYES_CAPACITY, and free
   any old *YYES other than YYESA.  */
static int
yy_lac (yytype_int16 *yyesa, yytype_int16 **yyes,
        YYSIZE_T *yyes_capacity, yytype_int16 *yyssp, int yytoken)
{
  yytype_int16 *yyes_prev = yyssp;
  yytype_int16 *yyesp = yyes_prev;
  YYDPRINTF ((stderr, "LAC: checking lookahead %s:", yytname[yytoken]));
  if (yytoken == YYUNDEFTOK)
    {
      YYDPRINTF ((stderr, " Always Err\n"));
      return 1;
    }
  while (1)
    {
      int yyrule = yypact[*yyesp];
      if (yypact_value_is_default (yyrule)
          || (yyrule += yytoken) < 0 || YYLAST < yyrule
          || yycheck[yyrule] != yytoken)
        {
          yyrule = yydefact[*yyesp];
          if (yyrule == 0)
            {
              YYDPRINTF ((stderr, " Err\n"));
              return 1;
            }
        }
      else
        {
          yyrule = yytable[yyrule];
          if (yytable_value_is_error (yyrule))
            {
              YYDPRINTF ((stderr, " Err\n"));
              return 1;
            }
          if (0 < yyrule)
            {
              YYDPRINTF ((stderr, " S%d\n", yyrule));
              return 0;
            }
          yyrule = -yyrule;
        }
      {
        YYSIZE_T yylen = yyr2[yyrule];
        YYDPRINTF ((stderr, " R%d", yyrule - 1));
        if (yyesp != yyes_prev)
          {
            YYSIZE_T yysize = yyesp - *yyes + 1;
            if (yylen < yysize)
              {
                yyesp -= yylen;
                yylen = 0;
              }
            else
              {
                yylen -= yysize;
                yyesp = yyes_prev;
              }
          }
        if (yylen)
          yyesp = yyes_prev -= yylen;
      }
      {
        int yystate;
        {
          int yylhs = yyr1[yyrule] - YYNTOKENS;
          yystate = yypgoto[yylhs] + *yyesp;
          if (yystate < 0 || YYLAST < yystate
              || yycheck[yystate] != *yyesp)
            yystate = yydefgoto[yylhs];
          else
            yystate = yytable[yystate];
        }
        if (yyesp == yyes_prev)
          {
            yyesp = *yyes;
            *yyesp = yystate;
          }
        else
          {
            if (yy_lac_stack_realloc (yyes_capacity, 1,
#if YYDEBUG
                                      " (", ")",
#endif
                                      yyes, yyesa, &yyesp, yyes_prev))
              {
                YYDPRINTF ((stderr, "\n"));
                return 2;
              }
            *++yyesp = yystate;
          }
        YYDPRINTF ((stderr, " G%d", yystate));
      }
    }
}


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.  In order to see if a particular token T is a
   valid looakhead, invoke yy_lac (YYESA, YYES, YYES_CAPACITY, YYSSP, T).

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store or if
   yy_lac returned 2.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyesa, yytype_int16 **yyes,
                YYSIZE_T *yyes_capacity, yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
       In the first two cases, it might appear that the current syntax
       error should have been detected in the previous state when yy_lac
       was invoked.  However, at that time, there might have been a
       different syntax error that discarded a different initial context
       during error recovery, leaving behind the current lookahead.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      YYDPRINTF ((stderr, "Constructing syntax error message\n"));
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          int yyx;

          for (yyx = 0; yyx < YYNTOKENS; ++yyx)
            if (yyx != YYTERROR && yyx != YYUNDEFTOK)
              {
                {
                  int yy_lac_status = yy_lac (yyesa, yyes, yyes_capacity,
                                              yyssp, yyx);
                  if (yy_lac_status == 2)
                    return 2;
                  if (yy_lac_status == 1)
                    continue;
                }
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
# if YYDEBUG
      else if (yydebug)
        YYFPRINTF (stderr, "No expected tokens.\n");
# endif
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

    yytype_int16 yyesa[20];
    yytype_int16 *yyes;
    YYSIZE_T yyes_capacity;

  int yy_lac_established = 0;
  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  yyes = yyesa;
  yyes_capacity = sizeof yyesa / sizeof *yyes;
  if (YYMAXDEPTH < yyes_capacity)
    yyes_capacity = YYMAXDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    {
      YY_LAC_ESTABLISH;
      goto yydefault;
    }
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      YY_LAC_ESTABLISH;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  YY_LAC_DISCARD ("shift");

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  {
    int yychar_backup = yychar;
    switch (yyn)
      {
          case 2:
#line 189 "grammar.ypp" /* yacc.c:1646  */
    {
	instructions.push_back(new Instruction("HALT"));
	printInstructions();
}
#line 1700 "grammar.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 193 "grammar.ypp" /* yacc.c:1646  */
    {
	instructions.push_back(new Instruction("HALT"));
	printInstructions();
}
#line 1709 "grammar.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 199 "grammar.ypp" /* yacc.c:1646  */
    {
				declareVariable((yyvsp[0].string), false);
				}
#line 1717 "grammar.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 202 "grammar.ypp" /* yacc.c:1646  */
    {
              	declareArray((yyvsp[-5].string), (yyvsp[-3].long_long), (yyvsp[-1].long_long));
              }
#line 1725 "grammar.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 205 "grammar.ypp" /* yacc.c:1646  */
    {
              	declareVariable((yyvsp[0].string), false);
              }
#line 1733 "grammar.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 208 "grammar.ypp" /* yacc.c:1646  */
    {
              	declareArray((yyvsp[-5].string), (yyvsp[-3].long_long), (yyvsp[-1].long_long));
              }
#line 1741 "grammar.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 213 "grammar.ypp" /* yacc.c:1646  */
    {
					//cout<<"commands"<<endl;
					//cout<<instructions.size()<<endl;
				}
#line 1750 "grammar.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 220 "grammar.ypp" /* yacc.c:1646  */
    {
					storeValueFromCell((yyvsp[-3].value_struct), (yyvsp[-1].long_long));
					memory_pointer--; // patrz expression: value
				}
#line 1759 "grammar.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 224 "grammar.ypp" /* yacc.c:1646  */
    {
              		checkConditionNegation((yyvsp[0].cond_struct),0); //narazie nie da się ustalić, dokąd ma być skok
              		ifLinePointerStack.push(instructions.size()-1);
              }
#line 1768 "grammar.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 227 "grammar.ypp" /* yacc.c:1646  */
    {
              		long long jumpIndex = ifLinePointerStack.top();
              		ifLinePointerStack.pop();
              		Instruction* instruction = instructions[jumpIndex];
              		
              		// skok, który skacze instrukcję dalej (k:=k+1)
              		// jeśli później wystąpi else, to zmienimy argument tak,
              		// żeby skakać za else'a
              		instructions.push_back(new Instruction("JUMP",instructions.size() + 1));
              		
              		// dajemy na stos indeks powyższego jumpa
              		ifLinePointerStack.push(instructions.size()-1);
              		
              		instruction->arg = instructions.size();
              		
              }
#line 1789 "grammar.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 243 "grammar.ypp" /* yacc.c:1646  */
    {
              		// póżniej będziemy skakać do początku sprawdzania warunku
              		whileConditionPointerStack.push(instructions.size());
              		
              		checkConditionNegation((yyvsp[0].cond_struct),0); //narazie nie da się ustalić, dokąd ma być skok
              		
              		// na drugim stosie umieszczamy, w której linii znajduje się skok
              		// (JNEG, JZERO, JPOS), w którym trzeba ustalić miejsce skoku
              		whileLinePointerStack.push(instructions.size() - 1);
              		
              }
#line 1805 "grammar.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 253 "grammar.ypp" /* yacc.c:1646  */
    {
              		long long conditionPointer = whileConditionPointerStack.top();
              		whileConditionPointerStack.pop();
              		
              		long long linePointer = whileLinePointerStack.top();
              		whileLinePointerStack.pop();
              		
              		// dodajemy jumpa, który wróci do sprawdzenia warunku
              		instructions.push_back(new Instruction("JUMP",conditionPointer));
              		
              		// jeśli warunek while'a nie jest spełniony, to trzeba skakać
              		// za powyższego jumpa
              		instructions[linePointer]->arg = instructions.size();
              }
#line 1824 "grammar.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 267 "grammar.ypp" /* yacc.c:1646  */
    {
              		doWhileLinePointerStack.push(instructions.size());
              		
              }
#line 1833 "grammar.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 270 "grammar.ypp" /* yacc.c:1646  */
    {
              		checkCondition((yyvsp[-1].cond_struct),0);
              		long long jumpIndex = instructions.size()-1;
              		long long loopBegin = doWhileLinePointerStack.top();
              		doWhileLinePointerStack.pop();
              		
              		instructions[jumpIndex]->arg = loopBegin;
              }
#line 1846 "grammar.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 278 "grammar.ypp" /* yacc.c:1646  */
    {
              		// zadeklarujemy chwilowo iterator jako zmienną
              		// na końcu pętli jest usuwana
              		declareVariable((yyvsp[-4].string), true); // memory_pointer przesunął się tu o jeden
              		long long iteratorCell = memory_pointer - 1; // miejsce iteratora w pamięci
              		forIteratorCellStack.push(iteratorCell);
              		iteratorNameStack.push((yyvsp[-4].string));
              		
              		// umieszczamy początkową wartość iteratora w akumulatorze
              		loadValueToAccumulator((yyvsp[-2].value_struct));
              		// i przypisujemy tę wartość iteratorowi
              		// tzn. umieszczamy wartość akumulatora w komórce, która odpowiada
              		// iteratorowi
              		instructions.push_back(new Instruction("STORE",iteratorCell));
              		
              		// rezerujemy komórkę, która będzie służyć do odliczania iteracji
              		// i umieszczamy w niej różnicę wartości końcowej i początkowej
              		// iteratora
              		subtract((yyvsp[0].value_struct),(yyvsp[-2].value_struct),memory_pointer);
              		long long iterationsCounterCell = memory_pointer;
              		memory_pointer++;
              		forCounterCellStack.push(iterationsCounterCell);
              		
              		instructions.push_back(new Instruction("LOAD",iterationsCounterCell));
              		// jeśli ta różnica jest ujemna, to wychodzimy z pętli
              		// narazie nie da się ustalić, w które miejsce skoczyć,
              		// żeby wyjść z pętli. Więc wrzucamy na stos, w której linii
              		// znajduje się JNEG
              		forLinePointerStack.push(instructions.size());
              		instructions.push_back(new Instruction("JNEG",0));
              		
              }
#line 1883 "grammar.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 309 "grammar.ypp" /* yacc.c:1646  */
    {
              		// tu są wklejone instrukcje z commands.
              		// teraz trzeba zmienić wartość iteratora
              		// i zmniejszyć licznik iteracji
              		long long iteratorCell = forIteratorCellStack.top();
              		forIteratorCellStack.pop();
              		long long iterationsCounterCell = forCounterCellStack.top();
              		forCounterCellStack.pop();
              		
              		instructions.push_back(new Instruction("LOAD",iteratorCell));
              		instructions.push_back(new Instruction("INC"));
              		instructions.push_back(new Instruction("STORE",iteratorCell));
              		
              		instructions.push_back(new Instruction("LOAD",iterationsCounterCell));
              		instructions.push_back(new Instruction("DEC"));
              		instructions.push_back(new Instruction("STORE",iterationsCounterCell));
              		
              		// skok do sprawdzenia warunku pętli (do JNEG)
              		long long jnegPointer = forLinePointerStack.top();
              		forLinePointerStack.pop();
              		instructions.push_back(new Instruction("JUMP",jnegPointer));
              		
              		// skok JNEG musi być za powyższą instrukcję
              		instructions[jnegPointer]->arg = instructions.size();
              
              		// na koniec pętli dodatkowe komórki nie są potrzebne
              		memory_pointer = memory_pointer - 2;
              		
              		// usuwamy też iterator (powinien być zadeklarowany tylko w pętli)
              		string iteratorName = iteratorNameStack.top();
              		iteratorNameStack.pop();
              		variables.erase(iteratorName);
              }
#line 1921 "grammar.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 342 "grammar.ypp" /* yacc.c:1646  */
    {
              		// zadeklarujemy chwilowo iterator jako zmienną
              		// na końcu pętli jest usuwana
              		declareVariable((yyvsp[-4].string), true); // memory_pointer przesunął się tu o jeden
              		long long iteratorCell = memory_pointer - 1; // miejsce iteratora w pamięci
              		forIteratorCellStack.push(iteratorCell);
              		iteratorNameStack.push((yyvsp[-4].string));
              		
              		// umieszczamy początkową wartość iteratora w akumulatorze
              		loadValueToAccumulator((yyvsp[-2].value_struct));
              		// i przypisujemy tę wartość iteratorowi
              		// tzn. umieszczamy wartość akumulatora w komórce, która odpowiada
              		// iteratorowi
              		instructions.push_back(new Instruction("STORE",iteratorCell));
              		
              		// rezerujemy komórkę, która będzie służyć do odliczania iteracji
              		// i umieszczamy w niej różnicę wartości końcowej i początkowej
              		// iteratora
              		subtract((yyvsp[0].value_struct),(yyvsp[-2].value_struct),memory_pointer);
              		long long iterationsCounterCell = memory_pointer;
              		memory_pointer++;
              		forCounterCellStack.push(iterationsCounterCell);
              		
              		instructions.push_back(new Instruction("LOAD",iterationsCounterCell));
              		// jeśli ta różnica jest dodatnie, to wychodzimy z pętli
              		// narazie nie da się ustalić, w które miejsce skoczyć,
              		// żeby wyjść z pętli. Więc wrzucamy na stos, w której linii
              		// znajduje się JNEG
              		forLinePointerStack.push(instructions.size());
              		instructions.push_back(new Instruction("JPOS",0));
              		
              }
#line 1958 "grammar.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 373 "grammar.ypp" /* yacc.c:1646  */
    {
              		// tu są wklejone instrukcje z commands.
              		// teraz trzeba zmienić wartość iteratora
              		// i zmniejszyć licznik iteracji
              		long long iteratorCell = forIteratorCellStack.top();
              		forIteratorCellStack.pop();
              		long long iterationsCounterCell = forCounterCellStack.top();
              		forCounterCellStack.pop();
              		
              		instructions.push_back(new Instruction("LOAD",iteratorCell));
              		instructions.push_back(new Instruction("DEC"));
              		instructions.push_back(new Instruction("STORE",iteratorCell));
              		
              		instructions.push_back(new Instruction("LOAD",iterationsCounterCell));
              		instructions.push_back(new Instruction("INC"));
              		instructions.push_back(new Instruction("STORE",iterationsCounterCell));
              		
              		// skok do sprawdzenia warunku pętli (do JPOS)
              		long long jposPointer = forLinePointerStack.top();
              		forLinePointerStack.pop();
              		instructions.push_back(new Instruction("JUMP",jposPointer));
              		
              		// skok JNEG musi być za powyższą instrukcję
              		instructions[jposPointer]->arg = instructions.size();
              
              		// na koniec pętli dodatkowe komórki nie są potrzebne
              		memory_pointer = memory_pointer - 2;
              		
              		// usuwamy też iterator (powinien być zadeklarowany tylko w pętli)
              		string iteratorName = iteratorNameStack.top();
              		iteratorNameStack.pop();
              		variables.erase(iteratorName);
              }
#line 1996 "grammar.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 406 "grammar.ypp" /* yacc.c:1646  */
    {
              	loadValueToVariable((yyvsp[-1].value_struct));
              }
#line 2004 "grammar.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 409 "grammar.ypp" /* yacc.c:1646  */
    {
              	printValue((yyvsp[-1].value_struct));
              }
#line 2012 "grammar.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 414 "grammar.ypp" /* yacc.c:1646  */
    {
              		
				}
#line 2020 "grammar.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 416 "grammar.ypp" /* yacc.c:1646  */
    {
					// ściągamy ze stosu indeks jumpa, którego argument chcemy zmienić
					// (ma skakać za else'a)
					long long jumpIndex = ifLinePointerStack.top();
              		ifLinePointerStack.pop();
              		Instruction* instruction = instructions[jumpIndex];
              		instruction->arg = instructions.size();
				}
#line 2033 "grammar.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 424 "grammar.ypp" /* yacc.c:1646  */
    {
			  		// nie było else'a po ifie. Ściągamy niepotrzebną daną ze stosu
			  		ifLinePointerStack.pop();
			  }
#line 2042 "grammar.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 432 "grammar.ypp" /* yacc.c:1646  */
    {
					loadValueToAccumulator((yyvsp[0].value_struct));
					
					// umieścimy w wolnej komórce i zwiększymy wskaźnik wolnej komórki
					instructions.push_back(new Instruction("STORE",memory_pointer));
					
					// wartość wyrażenia umieściliśmy w komórce memory_pointer
					(yyval.long_long)=memory_pointer;
					
					memory_pointer++; // póżniej komórka z wartością wyrażenia nie jest potrzebna
									  // trzeba to zmienić
									  // może można w assign zrobić memory_pointer-- ?
				}
#line 2060 "grammar.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 445 "grammar.ypp" /* yacc.c:1646  */
    {
              	add((yyvsp[-2].value_struct),(yyvsp[0].value_struct),memory_pointer);
              	(yyval.long_long)=memory_pointer;
              	memory_pointer++;
              }
#line 2070 "grammar.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 450 "grammar.ypp" /* yacc.c:1646  */
    {
              	subtract((yyvsp[-2].value_struct),(yyvsp[0].value_struct),memory_pointer);
              	(yyval.long_long)=memory_pointer;
              	memory_pointer++;
              }
#line 2080 "grammar.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 455 "grammar.ypp" /* yacc.c:1646  */
    {
              	multiply((yyvsp[-2].value_struct),(yyvsp[0].value_struct),memory_pointer);
              	(yyval.long_long)=memory_pointer;
              	memory_pointer++;
              }
#line 2090 "grammar.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 460 "grammar.ypp" /* yacc.c:1646  */
    {
              	divide((yyvsp[-2].value_struct),(yyvsp[0].value_struct),memory_pointer,false);
              	(yyval.long_long)=memory_pointer;
              	memory_pointer++;
              }
#line 2100 "grammar.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 465 "grammar.ypp" /* yacc.c:1646  */
    {
              	divide((yyvsp[-2].value_struct),(yyvsp[0].value_struct),memory_pointer,true);
              	(yyval.long_long)=memory_pointer;
              	memory_pointer++;
              }
#line 2110 "grammar.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 472 "grammar.ypp" /* yacc.c:1646  */
    {
					cond* c = new cond;
					c->op = "EQ";
					c->value1 = (yyvsp[-2].value_struct);
					c->value2 = (yyvsp[0].value_struct);
					
					(yyval.cond_struct) = c;
				}
#line 2123 "grammar.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 480 "grammar.ypp" /* yacc.c:1646  */
    {
              		cond* c = new cond;
					c->op = "NEQ";
					c->value1 = (yyvsp[-2].value_struct);
					c->value2 = (yyvsp[0].value_struct);
					
					(yyval.cond_struct) = c;
              }
#line 2136 "grammar.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 488 "grammar.ypp" /* yacc.c:1646  */
    {
              		cond* c = new cond;
					c->op = "LE";
					c->value1 = (yyvsp[-2].value_struct);
					c->value2 = (yyvsp[0].value_struct);
					
					(yyval.cond_struct) = c;
              }
#line 2149 "grammar.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 496 "grammar.ypp" /* yacc.c:1646  */
    {
              		cond* c = new cond;
					c->op = "GE";
					c->value1 = (yyvsp[-2].value_struct);
					c->value2 = (yyvsp[0].value_struct);
					
					(yyval.cond_struct) = c;
              }
#line 2162 "grammar.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 504 "grammar.ypp" /* yacc.c:1646  */
    {
              		cond* c = new cond;
					c->op = "LEQ";
					c->value1 = (yyvsp[-2].value_struct);
					c->value2 = (yyvsp[0].value_struct);
					
					(yyval.cond_struct) = c;
              }
#line 2175 "grammar.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 512 "grammar.ypp" /* yacc.c:1646  */
    {
              		cond* c = new cond;
					c->op = "GEQ";
					c->value1 = (yyvsp[-2].value_struct);
					c->value2 = (yyvsp[0].value_struct);
					
					(yyval.cond_struct) = c;
              }
#line 2188 "grammar.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 522 "grammar.ypp" /* yacc.c:1646  */
    {
              	// robimy value z num (num jest long longiem)
              	value* newValue = new value;
				newValue->isArray = false;
				newValue->isVariable = false;
				newValue->isNumber = true;
				newValue->isIterator = false;
				newValue->index = "";
				newValue->index_long = -1;
				newValue->name = "";
				newValue->num = (yyvsp[0].long_long);
				(yyval.value_struct) = newValue;
              }
#line 2206 "grammar.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 535 "grammar.ypp" /* yacc.c:1646  */
    {
              	(yyval.value_struct) = (yyvsp[0].value_struct);
              }
#line 2214 "grammar.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 540 "grammar.ypp" /* yacc.c:1646  */
    {
					// jeśli zmienna pidentifier nie jest zadeklarowana
					if(variables.find((yyvsp[0].string)) == variables.end()) {
              			yyerror(string((yyvsp[0].string)) + " was not declared");
              			return 1;
              		} else if(variables[(yyvsp[0].string)]->isArray) { // jeśli zmienna pidentifier jest tablicą
              			yyerror(string((yyvsp[0].string)) + " is an array");
              			return 1;
              		} else { // jeśli nie ma błędu w odwołaniu do pidentifier
					
						value* newValue = new value;
						newValue->isArray = false;
						newValue->isVariable = true;
						newValue->isNumber = false;
						newValue->isIterator = variables[(yyvsp[0].string)]->isIterator;
						newValue->index = "";
						newValue->index_long = -1;
						newValue->name = (yyvsp[0].string);
						(yyval.value_struct) = newValue;
					}
}
#line 2240 "grammar.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 561 "grammar.ypp" /* yacc.c:1646  */
    {
              		// jeśli tablica nie została zadeklarowana 
              		if(variables.find((yyvsp[-3].string)) == variables.end()) {
              			yyerror(string((yyvsp[-3].string)) + " was not declared");
              			return 1;
              		} else if(!variables[(yyvsp[-3].string)]->isArray) { // jeśli to nie jest tablica
              			yyerror(string((yyvsp[-3].string)) + " is not an array");
              			return 1;
              		} else if(variables.find((yyvsp[-1].string)) == variables.end()) { // jeśli indeks nie jest zadeklarowany
              			yyerror(string((yyvsp[-1].string)) + " was not declared");
              			return 1;
              		} else if(variables[(yyvsp[-1].string)]->isArray) { // jeśli indeks jest tablicą
              			yyerror(string((yyvsp[-1].string)) + " is an array");
              			return 1;
              		}
              		else { // jeśli poprawnie odwołano się do zmiennej
              	
              			value* newValue = new value;
						newValue->isArray = true;
						newValue->isVariable = false;
						newValue->isNumber = false;
						newValue->isIterator = variables[(yyvsp[-3].string)]->isIterator;
						newValue->index = (yyvsp[-1].string);
						newValue->index_long = -1;
						newValue->name = (yyvsp[-3].string);
						(yyval.value_struct) = newValue;
					}
				}
#line 2273 "grammar.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 591 "grammar.ypp" /* yacc.c:1646  */
    {
              
              	if(variables.find((yyvsp[-3].string)) == variables.end()) { // jeśli tablica nie jest zadeklarowana
              			yyerror(string((yyvsp[-3].string)) + " was not declared");
              			return 1;
              		} else if(!variables[(yyvsp[-3].string)]->isArray) { // jeśli to nie jest tablica
              			yyerror(string((yyvsp[-3].string)) + " is not an array");
              			return 1;
              		} else { // jeśli poprawnie odwołano się do tablicy
              			value* newValue = new value;
						newValue->isArray = true;
						newValue->isVariable = false;
						newValue->isNumber = false;
						newValue->isIterator = variables[(yyvsp[-3].string)]->isIterator;
						newValue->index = "";
						newValue->index_long = (yyvsp[-1].long_long);
						newValue->name = (yyvsp[-3].string);
						(yyval.value_struct) = newValue;
				}
              }
#line 2298 "grammar.cpp" /* yacc.c:1646  */
    break;


#line 2302 "grammar.cpp" /* yacc.c:1646  */
        default: break;
      }
    if (yychar_backup != yychar)
      YY_LAC_DISCARD ("yychar change");
  }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyesa, &yyes, &yyes_capacity, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        if (yychar != YYEMPTY)
          YY_LAC_ESTABLISH;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  /* If the stack popping above didn't lose the initial context for the
     current lookahead token, the shift below will for sure.  */
  YY_LAC_DISCARD ("error recovery");

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if 1
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yyes != yyesa)
    YYSTACK_FREE (yyes);
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 613 "grammar.ypp" /* yacc.c:1906  */


int yyerror(string s) {
	cerr << "Line " << yylineno << ": " << s << endl;
	return 0;
}

void printInstructions() {
	for(int i=0; i<instructions.size(); i++) {
		fprintf(yyget_out(), "%s\n", instructions[i]->toString().c_str());
	}
}

bool declareVariable(string name, bool isIterator) {

	// jeśli zmienna o nazwie name nie jest jeszcze zadeklarowana
	if(variables.find(name) == variables.end()) {
		MemoryItem* memory_item = new MemoryItem(memory_pointer, name);
		memory_item->isIterator = isIterator;
		variables[name] = memory_item;
		
		memory_pointer++;
		
		//test
		//cout<<name + ": "<<variables[name]->index<<endl;
		
	} else {
		yyerror("Duplicate variable \"" + name + "\"");
		
		return false;
	}
	
	return true;
}

bool loadValueToVariable(struct value* value) {
		if(value->isVariable) {
			// wczytanie wartość do akumulatora
			instructions.push_back(new Instruction("GET"));
			// zapisanie wartości z akumulatora do komórki o indeksie
			// odpowiadającym zmiennej o nazwie name
			instructions.push_back(new Instruction("STORE", variables[value->name]->index));
		} else {
			if(value->isArray) {
					// jeśli odwołanie do elementu tablicy następuje przez podanie liczby
					// jako numeru indeksu
					if(value->index_long != -1) {
						instructions.push_back(new Instruction("GET"));
						
						MemoryItem* memory_item = variables[value->name];
						
						// numer komórki pamięci, w której należy zapisać
						// wczytaną wartość (w ten sam sposób można ją później
						// znaleźć)
						long long index = memory_item->getMemoryIndexOf(value->index_long);
						
						instructions.push_back(new Instruction("STORE", index));
						
					} else { // jeśli odwołanie następuje przez podanie nazwy zmiennej
							// jako numeru indeksu 
						
						calculateIndexOfArrayElement(value->name, value->index);
						
						// zapisanie tej wartości w wolnej komórce
						instructions.push_back(new Instruction("STORE", memory_pointer));
						// teraz indeks interesującego nas elementu tablicy jest w komórce
						// o numerze memory_pointer
						
						// wczytanie wartości do akumulatora
						instructions.push_back(new Instruction("GET"));
						
						// umieszczenie wczytanej wartości w komórce, która odpowiada
						// interesującemu nas elementowi tablicy
						instructions.push_back(new Instruction("STOREI",memory_pointer));
						
					}
			}
		}
		
		return true;
	
}

void storeValueFromCell(struct value* value, long long cell) {
	if(!value->isIterator) {
	if(value->isVariable) {
			// wczytanie wartość do akumulatora
			instructions.push_back(new Instruction("LOAD",cell));
			// zapisanie wartości z akumulatora do komórki o indeksie
			// odpowiadającym zmiennej o nazwie name
			instructions.push_back(new Instruction("STORE", variables[value->name]->index));
		} else {
			if(value->isArray) {
					// jeśli odwołanie do elementu tablicy następuje przez podanie liczby
					// jako numeru indeksu
					if(value->index_long != -1) {
						instructions.push_back(new Instruction("LOAD", cell));
						
						MemoryItem* memory_item = variables[value->name];
						
						// numer komórki pamięci, w której należy zapisać
						// wczytaną wartość (w ten sam sposób można ją później
						// znaleźć)
						long long index = memory_item->getMemoryIndexOf(value->index_long);
						
						instructions.push_back(new Instruction("STORE", index));
						
					} else { // jeśli odwołanie następuje przez podanie nazwy zmiennej
							// jako numeru indeksu 
						
						calculateIndexOfArrayElement(value->name, value->index);
						
						// zapisanie tej wartości w wolnej komórce
						instructions.push_back(new Instruction("STORE", memory_pointer));
						// teraz indeks interesującego nas elementu tablicy jest w komórce
						// o numerze memory_pointer
						
						// wczytanie wartości do akumulatora
						instructions.push_back(new Instruction("LOAD",cell));
						
						// umieszczenie wczytanej wartości w komórce, która odpowiada
						// iteresującemu nas elementowi tablicy
						instructions.push_back(new Instruction("STOREI",memory_pointer));
						
					}
			} 
		}
		} else {
			// jeśli value odnosi się do jakiegoś iteratora pętli, to błąd
			yyerror("Iterator cannot be modified.");
		}
}


void printValue(struct value* value) {
		
		loadValueToAccumulator(value);
		instructions.push_back(new Instruction("PUT"));
}


bool declareArray(string name, long long begin, long long end) {

	// jeśli zmienna o nazwie name nie jest jeszcze zadeklarowana
	if(variables.find(name) == variables.end()) {
		if(begin > end) {
			yyerror("Declaration of array " + name + " failed");
			return false;
		}
		long long size = end-begin+1;
		MemoryItem* memory_item = new MemoryItem(memory_pointer, true, size,
												name, begin, end);
		variables[name] = memory_item;
		
		//obliczenie wartości numer komórki pamięci, w której jest pierwszy
		// element talicy minus indeks begin tablicy.
		// Ta wartość jest potrzebna przy odwołaniu się do tablica(zmienna)
		long long number = memory_pointer - begin;
		
		// przesunięcie wskazania na wolną komórkę pamięci za tablicę
		memory_pointer = memory_pointer + size;
		
		
		// umieszczenie jej w komórce za tablicą
		generateNumberAndStore(number, memory_pointer);
		memory_item->additionalCell = memory_pointer;
		
		
		// przesunięcie memory_pointer za tę dodatkową komórkę
		memory_pointer++;
		
		// teraz aby obliczyć, w której komórce znajduje się element tablicy,
		// należy dodać do numeru indeksu wartość znajdującą się za tablicą
		
		//test
		//cout<<name + ": "<<variables[name]->index<<endl;
		
	} else {
		yyerror("Duplicate variable \"" + name + "\"");
		return false;
	}
	
	return true;
}


void calculateIndexOfArrayElement(string array, string variable) {
	// miejsce w pamięci, gdzie znajduje się wartość zmiennej
	// określającej indeks tablicy
	long long variableCell = variables[variable]->index;
	
	// ładujemy wartość zmiennej określającej indeks do akumulatora
	instructions.push_back(new Instruction("LOAD",variableCell));
	
	// dodajemy do niej wartość umieszczoną za tablicą (index-begin, 
	// patrz MemoryItem, getMemoryIndexOf)
	instructions.push_back(new Instruction("ADD",variables[array]->additionalCell));
}



// zamienia liczbę dziesiętną dodatnią na binarną i zapisuje ją w stringu
string decToBin(long long number) {
	string b = "";
	
	while(number > 0) {
		int r = number % 2;
		number = (number - r) / 2;
		
		if(r == 1) {
			b = "1" + b;
		} else {
			b = "0" + b;
		}
	}
	
	return b;
}

void generateNumberAndStore(long long number, long long cell) {

	//cout<<number<<endl;

	// umieszczenie zera w akumulatorze
	instructions.push_back(new Instruction("SUB",0));

	if(number == 0) {
		instructions.push_back(new Instruction("STORE",cell));
		
	} else if(number > 0) {
		string b = decToBin(number);
		
		//cout<<b<<endl;
		
		instructions.push_back(new Instruction("INC"));
		
		// wygenerowanie jedynki potrzebnej do shiftów (w komórce memory_pointer)
		// nie jest później potrzebna, więc nie zmieniamy
		// wartości memory_pointer
		instructions.push_back(new Instruction("STORE",memory_pointer));
		
		// w akumulatorze jest 1
		
		for(long long i=1; i<b.size(); i++) {
			instructions.push_back(new Instruction("SHIFT",memory_pointer));
			
			if(b[i] == '1') {
				instructions.push_back(new Instruction("INC"));
			}
		}
		
		instructions.push_back(new Instruction("STORE",cell));
		
	} else {
		number *= -1;
		string b = decToBin(number);
		
		//cout<<b<<endl;
		
		// wygenerowanie jedynki potrzebnej do shiftów (w komórce memory_pointer)
		// nie jest później potrzebna, więc nie zmieniamy
		// wartości memory_pointer
		instructions.push_back(new Instruction("INC"));
		instructions.push_back(new Instruction("STORE",memory_pointer));
		
		instructions.push_back(new Instruction("DEC"));
		instructions.push_back(new Instruction("DEC"));
		
		// w akumulatorze jest -1
		
		for(long long i=1; i<b.size(); i++) {
			instructions.push_back(new Instruction("SHIFT",memory_pointer));
			
			if(b[i] == '1') {
				instructions.push_back(new Instruction("DEC"));
			}
		}
		
		instructions.push_back(new Instruction("STORE",cell));
	}
}

struct cell* findValueInMemory(struct value* value) {
	cell* c = new cell;
	
	if(value->isNumber) {
		c->valueIsNumber = true;
		c->containsValue = false;
		c->containsIndex = false;
		return c;
	} else if(value->isVariable) {
		MemoryItem* memory_item = variables[value->name];
		c->containsValue = true;
		c->valueIsNumber = false;
		c->containsIndex = false;
		c->cell = memory_item->index;
		
		return c;
	} else if(value->isArray) {
		if(value->index_long != -1) { // indeks tablicy był podany jako liczba
			MemoryItem* memory_item = variables[value->name];
						
			// numer komórki pamięci, w której jest zapisane value
			long long index = memory_item->getMemoryIndexOf(value->index_long);
			
			c->cell = index;
			c->containsValue=true;
			c->valueIsNumber = false;
			c->containsIndex = false;
			
			return c;
		} else if(value->index != "") { // indeks tablicy był podany jako nazwa zmiennej
			calculateIndexOfArrayElement(value->name, value->index);
						
			// zapisanie tej wartości w wolnej komórce
			instructions.push_back(new Instruction("STORE", memory_pointer));
			// teraz indeks interesującego nas elementu tablicy jest w komórce
			// o numerze memory_pointer
			
			c->cell = memory_pointer;
			c->containsValue = false;
			c->valueIsNumber = false;
			c->containsIndex = true;
			
			return c;
		}
	}
}

void add(struct value* value1, struct value* value2, long long result_cell) {
	if(value1->isNumber && value2->isNumber) { // jeśli obie wartości to znane liczby
		long long result = value1->num + value2->num;
		
		generateNumberAndStore(result, result_cell);
	} else {
		loadValueToAccumulator(value1);
		instructions.push_back(new Instruction("STORE",memory_pointer));
		// teraz w komórce memory_pointer znajduje się value1
		
		memory_pointer++;
		
		loadValueToAccumulator(value2);
		memory_pointer--;
		
		instructions.push_back(new Instruction("ADD",memory_pointer));
		instructions.push_back(new Instruction("STORE",result_cell));
	}
}

void multiply(struct value* value1, struct value* value2, long long result_cell) {
	if(value1->isNumber && value2->isNumber) { // jeśli obie wartości to znane liczby
		long long result = value1->num * value2->num;
		
		generateNumberAndStore(result, result_cell);
	} else {
		loadValueToAccumulator(value1);
		instructions.push_back(new Instruction("STORE",memory_pointer));
		long long a = memory_pointer;
		// teraz w komórce o numerze a znajduje się value1
		
		memory_pointer++;
		
		loadValueToAccumulator(value2);
		instructions.push_back(new Instruction("STORE",memory_pointer));
		long long b = memory_pointer;
		// teraz w komórce o numerze b znajduje się value2
		
		memory_pointer++;
		
		// generowanie stałych
		instructions.push_back(new Instruction("SUB",0));
		long long zero = memory_pointer; // komórka, w której trzymamy zero
		instructions.push_back(new Instruction("STORE",zero));
		memory_pointer++;
		
		instructions.push_back(new Instruction("INC"));
		long long one = memory_pointer; // komórka, w której trzymamy jedynkę
		instructions.push_back(new Instruction("STORE",one));
		memory_pointer++;
		
		instructions.push_back(new Instruction("DEC"));
		instructions.push_back(new Instruction("DEC"));
		long long minus_one = memory_pointer; // komórka, w której trzymamy minus jedynkę
		instructions.push_back(new Instruction("STORE",minus_one));
		memory_pointer++;
		
		// 
		
		// dodatkowe komórki
		long long c = memory_pointer;
		memory_pointer++;
		long long d = memory_pointer;
		memory_pointer++;
		
		instructions.push_back(new Instruction("LOAD",b));
		instructions.push_back(new Instruction("INC"));
		instructions.push_back(new Instruction("JPOS", instructions.size() + 22));
		
		instructions.push_back(new Instruction("LOAD",a));
		instructions.push_back(new Instruction("INC"));
		instructions.push_back(new Instruction("JPOS", instructions.size() + 13));
		
		instructions.push_back(new Instruction("LOAD",a));
		instructions.push_back(new Instruction("SHIFT",one));
		instructions.push_back(new Instruction("STORE", c));
		instructions.push_back(new Instruction("LOAD",a));
		instructions.push_back(new Instruction("SUB",c));
		instructions.push_back(new Instruction("STORE",a));
		instructions.push_back(new Instruction("LOAD",b));
		instructions.push_back(new Instruction("SHIFT", one));
		instructions.push_back(new Instruction("STORE",c));
		instructions.push_back(new Instruction("LOAD",b));
		instructions.push_back(new Instruction("SUB",c));
		instructions.push_back(new Instruction("STORE",b));
		
		instructions.push_back(new Instruction("LOAD",a));
		instructions.push_back(new Instruction("STORE",c));
		instructions.push_back(new Instruction("LOAD",b));
		instructions.push_back(new Instruction("STORE",a));
		instructions.push_back(new Instruction("LOAD",c));
		instructions.push_back(new Instruction("STORE",b));
		
		instructions.push_back(new Instruction("LOAD",b));
		instructions.push_back(new Instruction("JZERO",instructions.size() + 14));
		instructions.push_back(new Instruction("STORE",d));
		instructions.push_back(new Instruction("SHIFT",minus_one));
		instructions.push_back(new Instruction("STORE",b));
		instructions.push_back(new Instruction("SHIFT",one));
		instructions.push_back(new Instruction("SUB",d));
		instructions.push_back(new Instruction("JZERO",instructions.size() + 4));
		instructions.push_back(new Instruction("LOAD",a));
		instructions.push_back(new Instruction("ADD",zero));
		instructions.push_back(new Instruction("STORE",zero));
		instructions.push_back(new Instruction("LOAD",a));
		instructions.push_back(new Instruction("SHIFT",one));
		instructions.push_back(new Instruction("STORE",a));
		instructions.push_back(new Instruction("JUMP", instructions.size() - 14));
		instructions.push_back(new Instruction("LOAD",zero));
		
		// umieszczenie wyniku we właściwej komórce
		instructions.push_back(new Instruction("STORE",result_cell));
		
		// na końcu odpowiednio zmniejszyć wartość memory_pointer
		memory_pointer = memory_pointer - 7;
	}
}

void divide(struct value* value1, struct value* value2, long long result_cell, bool mod) {
	long long a = memory_pointer;
	loadValueToAccumulator(value1);
	instructions.push_back(new Instruction("STORE",a));
	memory_pointer++;
	
	long long b = memory_pointer;
	loadValueToAccumulator(value2);
	instructions.push_back(new Instruction("STORE",b));
	memory_pointer++;
	
	// przydzielenie numerów komórek do odpowiednich wartości
	
	long long result = memory_pointer;
	memory_pointer++;
	long long one = memory_pointer;
	memory_pointer++;
	long long minus_one = memory_pointer;
	memory_pointer++;
	long long temp = memory_pointer;
	memory_pointer++;
	long long old_b = memory_pointer;
	memory_pointer++;
	long long a_sign = memory_pointer;
	memory_pointer++;
	long long b_sign = memory_pointer;
	memory_pointer++;
	long long pom = memory_pointer;
	memory_pointer++;
	
	// dzielenie z pliku dzielenie2.mr
	
	// wygenerowanie stałych
	instructions.push_back(new Instruction("SUB",0));
	instructions.push_back(new Instruction("STORE",result));
	instructions.push_back(new Instruction("INC"));
	instructions.push_back(new Instruction("STORE",one));
	instructions.push_back(new Instruction("STORE",temp));
	instructions.push_back(new Instruction("STORE",b_sign));
	instructions.push_back(new Instruction("STORE",a_sign));
	instructions.push_back(new Instruction("DEC"));
	instructions.push_back(new Instruction("DEC"));
	instructions.push_back(new Instruction("STORE",minus_one));
	
	// wczytanie wartości, którą trzeba podzielić.
	// w pliku dzielenie2.mr w tym miejscu jest GET
	//loadValueToAccumulator(value1);
	instructions.push_back(new Instruction("LOAD",a));
	instructions.push_back(new Instruction("STORE",a));
	
	// tu zajmujemy się przypadkiem ujemnego a
	instructions.push_back(new Instruction("INC"));
	instructions.push_back(new Instruction("JPOS",instructions.size() + 10));
	instructions.push_back(new Instruction("DEC"));
	instructions.push_back(new Instruction("STORE",a));
	instructions.push_back(new Instruction("SHIFT",one));
	instructions.push_back(new Instruction("STORE",pom));
	instructions.push_back(new Instruction("LOAD",minus_one));
	instructions.push_back(new Instruction("STORE",a_sign));
	instructions.push_back(new Instruction("LOAD",a));
	instructions.push_back(new Instruction("SUB",pom));
	instructions.push_back(new Instruction("STORE",a));
	
	
	// wczytanie wartości dzielnika.
	// w pliku dzielenie2.mr w tym miejscu jest GET
	//loadValueToAccumulator(value2);
	instructions.push_back(new Instruction("LOAD",b));
	instructions.push_back(new Instruction("STORE",b));
	
	instructions.push_back(new Instruction("JZERO",instructions.size() + 45));
	instructions.push_back(new Instruction("STORE",old_b));
	
	// przypadek ujemnego b
	instructions.push_back(new Instruction("INC"));
	instructions.push_back(new Instruction("JPOS",instructions.size() + 11));
	instructions.push_back(new Instruction("DEC"));
	instructions.push_back(new Instruction("STORE",b));
	instructions.push_back(new Instruction("SHIFT",one));
	instructions.push_back(new Instruction("STORE",pom));
	instructions.push_back(new Instruction("LOAD",minus_one));
	instructions.push_back(new Instruction("STORE",b_sign));
	instructions.push_back(new Instruction("LOAD",b));
	instructions.push_back(new Instruction("SUB",pom));
	instructions.push_back(new Instruction("STORE",b));
	instructions.push_back(new Instruction("STORE",old_b));
	
	//pętla 1
	instructions.push_back(new Instruction("LOAD",a));
	instructions.push_back(new Instruction("SUB",b));
	instructions.push_back(new Instruction("JNEG",instructions.size() + 8));
	
	instructions.push_back(new Instruction("LOAD",b));
	instructions.push_back(new Instruction("SHIFT",one));
	instructions.push_back(new Instruction("STORE",b));
	instructions.push_back(new Instruction("LOAD",temp));
	instructions.push_back(new Instruction("SHIFT",one));
	instructions.push_back(new Instruction("STORE",temp));
	instructions.push_back(new Instruction("JUMP",instructions.size() - 9));
	
	//pętla 2
	instructions.push_back(new Instruction("LOAD",a));
	instructions.push_back(new Instruction("SUB",old_b));
	instructions.push_back(new Instruction("JNEG",instructions.size() + 22));
	
	//pętla w pętli 2
	instructions.push_back(new Instruction("LOAD",a));
	instructions.push_back(new Instruction("SUB",b));
	instructions.push_back(new Instruction("INC"));
	instructions.push_back(new Instruction("JPOS",instructions.size() + 8));
	
	instructions.push_back(new Instruction("LOAD",b));
	instructions.push_back(new Instruction("SHIFT",minus_one));
	instructions.push_back(new Instruction("STORE",b));
	instructions.push_back(new Instruction("LOAD",temp));
	instructions.push_back(new Instruction("SHIFT",minus_one));
	instructions.push_back(new Instruction("STORE",temp));
	instructions.push_back(new Instruction("JUMP",instructions.size() - 10));
	
	//dodanie wyniku
	instructions.push_back(new Instruction("LOAD",result));
	instructions.push_back(new Instruction("ADD",temp));
	instructions.push_back(new Instruction("STORE",result));
	instructions.push_back(new Instruction("LOAD",a));
	instructions.push_back(new Instruction("SUB",b));
	instructions.push_back(new Instruction("STORE",a));
	instructions.push_back(new Instruction("JUMP",instructions.size() - 20));
	
	//dzielenie przez zero
	instructions.push_back(new Instruction("SUB",0));
	instructions.push_back(new Instruction("STORE",a));
	instructions.push_back(new Instruction("JUMP",instructions.size() + 42 + 1));
	
	//ustalenie znaku wyniku i reszty
	instructions.push_back(new Instruction("LOAD",a_sign));
	instructions.push_back(new Instruction("JPOS",instructions.size() + 24 + 1));
	instructions.push_back(new Instruction("LOAD",b_sign));
	instructions.push_back(new Instruction("JPOS",instructions.size() + 7 + 1));
	instructions.push_back(new Instruction("LOAD",a));
	instructions.push_back(new Instruction("SHIFT",one));
	instructions.push_back(new Instruction("STORE",pom));
	instructions.push_back(new Instruction("LOAD",a));
	instructions.push_back(new Instruction("SUB",pom));
	instructions.push_back(new Instruction("STORE",a));
	instructions.push_back(new Instruction("JUMP",instructions.size() + 32));
	
	//mały else
	instructions.push_back(new Instruction("LOAD",a));
	instructions.push_back(new Instruction("JZERO",instructions.size() + 7));
	instructions.push_back(new Instruction("LOAD",result));
	instructions.push_back(new Instruction("INC"));
	instructions.push_back(new Instruction("STORE",result));
	instructions.push_back(new Instruction("LOAD",old_b));
	instructions.push_back(new Instruction("SUB",a));
	instructions.push_back(new Instruction("STORE",a));
	
	// po ifie w małym elsie
	instructions.push_back(new Instruction("LOAD",result));
	instructions.push_back(new Instruction("SHIFT",one));
	instructions.push_back(new Instruction("STORE",pom));
	instructions.push_back(new Instruction("LOAD",result));
	instructions.push_back(new Instruction("SUB",pom));
	instructions.push_back(new Instruction("STORE",result));
	instructions.push_back(new Instruction("JUMP",instructions.size() + 17));
	
	//duży else
	instructions.push_back(new Instruction("LOAD",b_sign));
	instructions.push_back(new Instruction("JPOS",instructions.size() + 15));
	instructions.push_back(new Instruction("LOAD",a));
	instructions.push_back(new Instruction("JZERO",instructions.size() + 7));
	instructions.push_back(new Instruction("LOAD",result));
	instructions.push_back(new Instruction("INC"));
	instructions.push_back(new Instruction("STORE",result));
	instructions.push_back(new Instruction("LOAD",a));
	instructions.push_back(new Instruction("SUB",old_b));
	instructions.push_back(new Instruction("STORE",a));
	
	//po drugim ifie w elsie
	instructions.push_back(new Instruction("LOAD",result));
	instructions.push_back(new Instruction("SHIFT",one));
	instructions.push_back(new Instruction("STORE",pom));
	instructions.push_back(new Instruction("LOAD",result));
	instructions.push_back(new Instruction("SUB",pom));
	instructions.push_back(new Instruction("STORE",result));
	
	//wyświetlenie wyniku (tu zamiast wyświetlenia umieszczenie wyniku w odpowiedniej komórce)
	if(!mod) {
		instructions.push_back(new Instruction("LOAD",result));
	} else {
		instructions.push_back(new Instruction("LOAD",a));
	}
	instructions.push_back(new Instruction("STORE",result_cell));
	
	
	// na końcu odpowiednio zmniejszyć wartość memory_pointer
	memory_pointer = memory_pointer - 10;
}

void subtract(struct value* value1, struct value* value2, long long result_cell) {
	if(value1->isNumber && value2->isNumber) { // jeśli obie wartości to znane liczby
		long long result = value1->num - value2->num;
		
		generateNumberAndStore(result, result_cell);
	} else {
		loadValueToAccumulator(value2);
		instructions.push_back(new Instruction("STORE",memory_pointer));
		// teraz w komórce memory_pointer znajduje się value1
		
		memory_pointer++;
		
		loadValueToAccumulator(value1);
		memory_pointer--;
		
		instructions.push_back(new Instruction("SUB",memory_pointer));
		instructions.push_back(new Instruction("STORE",result_cell));
	}
}

void checkConditionNegation(struct cond* c, long long k) {
	struct value* value1 = c->value1;
	struct value* value2 = c->value2;
	string op = c->op;
	
	subtract(value1,value2,0);
	
	if(op == "GE") {
		instructions.push_back(new Instruction("DEC"));
		instructions.push_back(new Instruction("JNEG",0));
	} else if(op == "EQ") {
		instructions.push_back(new Instruction("JPOS",instructions.size() + 4));
		instructions.push_back(new Instruction("STORE",memory_pointer));
		instructions.push_back(new Instruction("SUB",0));
		instructions.push_back(new Instruction("SUB",memory_pointer));
		instructions.push_back(new Instruction("JPOS",0));
	} else if(op == "NEQ") {
		instructions.push_back(new Instruction("JZERO",0));
	} else if(op == "LE") {
		instructions.push_back(new Instruction("INC"));
		instructions.push_back(new Instruction("JPOS",0));
	} else if(op == "LEQ") {
		instructions.push_back(new Instruction("JPOS",0));
	} else if(op == "GEQ") {
		instructions.push_back(new Instruction("JNEG",0));
	}
}

void checkCondition(struct cond* c, long long k) {
	struct value* value1 = c->value1;
	struct value* value2 = c->value2;
	string op = c->op;
	
	subtract(value1,value2,0);
	
	if(op == "GE") {
		instructions.push_back(new Instruction("JPOS",0));
	} else if(op == "EQ") {
		instructions.push_back(new Instruction("JZERO",0));
	} else if(op == "NEQ") {
		instructions.push_back(new Instruction("JPOS",instructions.size() + 4));
		instructions.push_back(new Instruction("STORE",memory_pointer));
		instructions.push_back(new Instruction("SUB",0));
		instructions.push_back(new Instruction("SUB",memory_pointer));
		instructions.push_back(new Instruction("JPOS",0));
	} else if(op == "LE") {
		instructions.push_back(new Instruction("JNEG",0));
	} else if(op == "LEQ") {
		instructions.push_back(new Instruction("DEC"));
		instructions.push_back(new Instruction("JNEG",0));
	} else if(op == "GEQ") {
		instructions.push_back(new Instruction("INC"));
		instructions.push_back(new Instruction("JPOS",0));
	}
}

void loadValueToAccumulator(struct value* value) {

	//test
	//instructions.push_back(new Instruction("loadValueToAccumulator: " + value->name));

	if(value->isVariable) {
		MemoryItem* item = variables[value->name];
		instructions.push_back(new Instruction("LOAD", item->index));
	} else if(value->isArray) {
		// jeśli odwołanie do elementu tablicy następuje przez podanie liczby
		// jako numeru indeksu
		if(value->index_long != -1) {
			
			MemoryItem* memory_item = variables[value->name];
			long long index = memory_item->getMemoryIndexOf(value->index_long);
			instructions.push_back(new Instruction("LOAD", index));
						
		} else { // jeśli odwołanie następuje przez podanie nazwy zmiennej
				// jako numeru indeksu 
						
			calculateIndexOfArrayElement(value->name, value->index);
			// teraz w akumulatorze znajduje się numer komórki,
			// w której przechowywana jest wartość interesuącego nas elementu tablicy
				
			// ładujemy do akumulatora wartość z komórki o numerze równym
			// wartości przechowywanej w akumulatorze
			instructions.push_back(new Instruction("LOADI",0));
		}
	} else if(value->isNumber) {
		// wygenerowanie liczby value->num i umieszczenie w akumulatorze
		generateNumberAndStore(value->num, 0);
	}
}



