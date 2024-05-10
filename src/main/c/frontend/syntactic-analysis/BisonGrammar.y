%{

#include "BisonActions.h"

%}

%define api.value.union.name SemanticValue

%union {
	/** Terminals. */

	int integer;
	Token token;

	/** Non-terminals. */

	Constant * constant;
	Expression * expression;
	Factor * factor;
	Program * program;
}

/**
 * Destructors. This functions are executed after the parsing ends, so if the
 * AST must be used in the following phases of the compiler you shouldn't used
 * this approach.
 *
 * @see https://www.gnu.org/software/bison/manual/html_node/Destructor-Decl.html
 */
/*
%destructor { releaseConstant($$); } <constant>
%destructor { releaseExpression($$); } <expression>
%destructor { releaseFactor($$); } <factor>
%destructor { releaseProgram($$); } <program>
*/

/** Terminals. */
%token <integer> INTEGER
%token <token> ADD
%token <token> CLOSE_PARENTHESIS
%token <token> DIV
%token <token> MUL
%token <token> OPEN_PARENTHESIS
%token <token> SUB

%token <token> ADD_ONE
%token <token> SUBSTRACT_ONE
%token <token> ADD_EQUAL
%token <token> SUBSTRACT_EQUAL

%token <token> GREATER
%token <token> LOWER
%token <token> EQUAL_EQUAL
%token <token> GREATER_OR_EQUAL
%token <token> LOWER_OR_EQUAL
%token <token> DIFERENT
%token <token> EQUAL

%token <token> COMMA
%token <token> DOT

%token <token> OPEN_BRAKETS
%token <token> CLOSE_BRAKETS

%token <token> MODULE
%token <token> AND
%token <token> OR

%token <token> GAME
%token <token> DESIGN
%token <token> HAS
%token <token> FOR
%token <token> TYPE
%token <token> VALUE
%token <token> COLON //:

%token <token> PLAYER //playing, waiting
%token <token> DECK	
%token <token> IDENTIFIER //user, machine

%token <token> HAND
%token <token> SELECTED_CARD
%token <token> SCORE
%token <token> TIED

%token <token> FOREACH	
%token <token> IF	
%token <token> ELSE	
%token <token> ELIF	

%token <token> NUMBERS_ON_DECK
%token <token> TYPES_OF_CARDS
%token <token> CARDS_BY_PLAYER
%token <token> ROUNDS
%token <token> ROUNDS_TIMER
%token <token> STARTING_SCORE
%token <token> WIN_ROUND_CONDITION
%token <token> WIN_GAME_CONDITION
%token <token> CARDS_DESIGN
%token <token> BACKGROUND_DESIGN

%token <token> MOVE_CARDS
%token <token> LOOK_AT
%token <token> RESTOCK_DECK
%token <token> WIN_GAME
%token <token> WINNER_TYPE
%token <token> SPECIAL_CARDS_ON_PLAY

%token <token> ROUND_BORDERS
%token <token> COLOR_BORDERS
%token <token> BACKGROUND_COLOR

%token <token> VARIABLE

%token <token> UNKNOWN

/** Non-terminals. */
%type <constant> constant
%type <expression> expression
%type <factor> factor
%type <program> program

/**
 * Precedence and associativity.
 *
 * @see https://www.gnu.org/software/bison/manual/html_node/Precedence.html
 */
%left ADD SUB
%left MUL DIV

%%

program: block													{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }
	;

block: variable FOR VALUE constant COLON Rules
	| variable FOR TYPE cardTypes COLON Rules
	| variable GAME HAS COLON GameFunctions
	| variable DESIGN HAS COLON Design
	;

GameFunctions: NUMBERS_ON_DECK OPEN_PARENTHESIS constant CLOSE_PARENTHESIS
				TYPES_OF_CARDS OPEN_PARENTHESIS cardTypes CLOSE_PARENTHESIS
				CARDS_BY_PLAYER OPEN_PARENTHESIS constant CLOSE_PARENTHESIS
				ROUNDS OPEN_PARENTHESIS constant CLOSE_PARENTHESIS
				ROUNDS_TIMER OPEN_PARENTHESIS constant CLOSE_PARENTHESIS
				STARTING_SCORE OPEN_PARENTHESIS constant COMMA constant CLOSE_PARENTHESIS
				WIN_ROUND_CONDITION OPEN_PARENTHESIS variable CLOSE_PARENTHESIS
				WIN_GAME_CONDITION OPEN_PARENTHESIS variable CLOSE_PARENTHESIS
				CARDS_DESIGN OPEN_PARENTHESIS variable CLOSE_PARENTHESIS
				BACKGROUND_DESIGN OPEN_PARENTHESIS variable CLOSE_PARENTHESIS
				;

cardTypes: variable
	| variable COMMA cardTypes
	;

Rules: structures
	| MOVE_CARDS OPEN_PARENTHESIS handRef COMMA handRef COMMA constant CLOSE_PARENTHESIS
	| LOOK_AT OPEN_PARENTHESIS handRef COMMA constant CLOSE_PARENTHESIS
	| RESTOCK_DECK OPEN_PARENTHESIS CLOSE_PARENTHESIS
	| WIN_GAME OPEN_PARENTHESIS IDENTIFIER CLOSE_PARENTHESIS
	| WINNER_TYPE OPEN_PARENTHESIS variable CLOSE_PARENTHESIS
	| SPECIAL_CARDS_ON_PLAY OPEN_PARENTHESIS CLOSE_PARENTHESIS 
	| userRules
	;

userScore: user DOT SCORE
	;

userCard: user DOT SELECTED_CARD
	;
	
userRules: userScore asignations constant
	| userScore asignations userCard DOT VALUE
	| userScore pmOne
	| userScore EQUAL INTEGER arithmetic INTEGER
	| userScore EQUAL INTEGER arithmetic userScore
	| userScore EQUAL INTEGER arithmetic userCard DOT VALUE
	| userScore EQUAL userScore arithmetic INTEGER
	| userScore EQUAL userScore arithmetic userScore
	| userScore EQUAL userScore arithmetic userCard DOT VALUE
	| userScore EQUAL userCard DOT VALUE arithmetic INTEGER
	| userScore EQUAL userCard DOT VALUE arithmetic userScore
	| userScore EQUAL userCard DOT VALUE arithmetic userCard DOT VALUE
	;

arithmetic: ADD
	| DIV
	| MUL
	| SUB
	| MODULE
	;

asignations: EQUAL
	| ADD_EQUAL 
	| SUBSTRACT_EQUAL
	;

pmOne: ADD_ONE
	| SUBSTRACT_ONE
	;

structures: IF OPEN_PARENTHESIS if CLOSE_PARENTHESIS inBrakets
	| FOREACH OPEN_PARENTHESIS atomic CLOSE_PARENTHESIS inBrakets
	| ELIF OPEN_PARENTHESIS if CLOSE_PARENTHESIS inBrakets
	| ELSE inBrakets
	;

inBrakets: OPEN_BRAKETS Rules CLOSE_BRAKETS
	| OPEN_BRAKETS Rules CLOSE_BRAKETS Rules
	;

handRef: user DOT HAND
	| DECK
	;

user: PLAYER
	| IDENTIFIER
	;

if: inIf
	| inIf AND inIf
	| inIf OR inIf
	;

inIf: VALUE comparation constant
	| TYPE comparation variable
	| variable
	| userScore comparation constant 
	| userScore comparation userScore
	| userCard DOT atomic comparation constant
	| userCard DOT atomic comparation variable
	| userCard DOT atomic comparation userCard DOT atomic
	
	| userScore arithmetic userCard DOT VALUE comparation userCard DOT VALUE
	| userScore arithmetic userCard DOT VALUE comparation userScore
	| userScore arithmetic userCard DOT VALUE comparation INTEGER
	
	| userScore arithmetic userScore comparation userCard DOT VALUE
	| userScore arithmetic userScore comparation userScore
	| userScore arithmetic userScore comparation INTEGER

	| userScore arithmetic INTEGER comparation userCard DOT VALUE
	| userScore arithmetic INTEGER comparation userScore
	| userScore arithmetic INTEGER comparation INTEGER

	| userCard DOT VALUE arithmetic userScore comparation userCard DOT VALUE
	| userCard DOT VALUE arithmetic userScore comparation userScore
	| userCard DOT VALUE arithmetic userScore comparation INTEGER

	| userCard DOT VALUE arithmetic userCard DOT VALUE comparation userCard DOT VALUE
	| userCard DOT VALUE arithmetic userCard DOT VALUE comparation userScore
	| userCard DOT VALUE arithmetic userCard DOT VALUE comparation INTEGER
	
	| userCard DOT VALUE arithmetic INTEGER comparation userCard DOT VALUE
	| userCard DOT VALUE arithmetic INTEGER comparation userScore
	| userCard DOT VALUE arithmetic INTEGER comparation INTEGER

	| INTEGER arithmetic userCard DOT VALUE comparation userCard DOT VALUE
	| INTEGER arithmetic userCard DOT VALUE comparation userScore
	| INTEGER arithmetic userCard DOT VALUE comparation INTEGER

	| INTEGER arithmetic userScore comparation userCard DOT VALUE
	| INTEGER arithmetic userScore comparation userScore
	| INTEGER arithmetic userScore comparation INTEGER

	;

comparation: GREATER
	| LOWER
	| EQUAL_EQUAL
	| GREATER_OR_EQUAL
	| LOWER_OR_EQUAL
	| DIFERENT
	;

atomic: VALUE
	| TYPE
	;

Design: ROUND_BORDERS OPEN_PARENTHESIS variable CLOSE_PARENTHESIS
	| COLOR_BORDERS OPEN_PARENTHESIS variable CLOSE_PARENTHESIS
	| BACKGROUND_COLOR OPEN_PARENTHESIS variable CLOSE_PARENTHESIS
	;

/*
expression: expression[left] ADD expression[right]					{ $$ = ArithmeticExpressionSemanticAction($left, $right, ADDITION); }
	| expression[left] DIV expression[right]						{ $$ = ArithmeticExpressionSemanticAction($left, $right, DIVISION); }
	| expression[left] MUL expression[right]						{ $$ = ArithmeticExpressionSemanticAction($left, $right, MULTIPLICATION); }
	| expression[left] SUB expression[right]						{ $$ = ArithmeticExpressionSemanticAction($left, $right, SUBTRACTION); }
	| factor														{ $$ = FactorExpressionSemanticAction($1); }
	;

factor: OPEN_PARENTHESIS expression CLOSE_PARENTHESIS				{ $$ = ExpressionFactorSemanticAction($2); }
	| constant														{ $$ = ConstantFactorSemanticAction($1); }
	;
*/

constant: INTEGER													{ $$ = IntegerConstantSemanticAction($1); }
	;

variable: VARIABLE													/*{ $$ = IntegerConstantSemanticAction($1); }*/
	;

%%
