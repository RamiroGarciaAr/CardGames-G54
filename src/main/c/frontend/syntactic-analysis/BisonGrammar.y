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

%token <token> COMPARATION

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

%token <token> SELECTED_CARD
%token <token> SCORE

%token <token> FOREACH	
%token <token> IF	
%token <token> ELSE	
%token <token> ELIF	
%token <token> HAND	

%token <token> VARIABLE

%token <token> UNKNOWN

/** Non-terminals. */
%type <constant> constant
%type <expression> expression
%type <factor> factor
%type <program> program

%type <NumbersOnDeck> NumbersOnDeck
%type <TypesOfCards> TypesOfCards
%type <CardsByPlayer> CardsByPlayer
%type <Rounds> Rounds
%type <RoundsTimer> RoundsTimer
%type <StartingScore> StartingScore
%type <WinRoundCondition> WinRoundCondition
%type <WinGameCondition> WinGameCondition
%type <CardsDesign> CardsDesign
%type <BackgroundDesign> BackgroundDesign

%type <MoveCards> MoveCards
%type <LookAt> LookAt
%type <RestockDeck> RestockDeck
%type <WinGame> WinGame
%type <WinnerType> WinnerType
%type <SpecialCardsOnPlay> SpecialCardsOnPlay

%type <RoundBorders> RoundBorders
%type <ColorBorders> ColorBorders
%type <BackgroundColor> BackgroundColor

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

GameFunctions: NumbersOnDeck OPEN_PARENTHESIS constant CLOSE_PARENTHESIS
				TypesOfCards OPEN_PARENTHESIS cardTypes CLOSE_PARENTHESIS
				CardsByPlayer OPEN_PARENTHESIS constant CLOSE_PARENTHESIS
				Rounds OPEN_PARENTHESIS constant CLOSE_PARENTHESIS
				RoundsTimer OPEN_PARENTHESIS constant CLOSE_PARENTHESIS
				StartingScore OPEN_PARENTHESIS constant COMMA constant CLOSE_PARENTHESIS
				WinRoundCondition OPEN_PARENTHESIS variable CLOSE_PARENTHESIS
				WinGameCondition OPEN_PARENTHESIS variable CLOSE_PARENTHESIS
				;

cardTypes: variable
	| variable COMMA cardTypes
	;

Rules: IF OPEN_PARENTHESIS if CLOSE_PARENTHESIS
	| FOREACH OPEN_PARENTHESIS atomic CLOSE_PARENTHESIS
	| MoveCards OPEN_PARENTHESIS handRef COMMA handRef COMMA constant CLOSE_PARENTHESIS
	| LookAt OPEN_PARENTHESIS handRef COMMA constant CLOSE_PARENTHESIS
	| RestockDeck OPEN_PARENTHESIS CLOSE_PARENTHESIS
	| WinGame OPEN_PARENTHESIS IDENTIFIER CLOSE_PARENTHESIS
	| WinnerType OPEN_PARENTHESIS variable CLOSE_PARENTHESIS
	| SpecialCardsOnPlay OPEN_PARENTHESIS CLOSE_PARENTHESIS 
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

inIf: VALUE COMPARATION constant
	| TYPE COMPARATION variable
	| variable
	| user COLON SCORE COMPARATION constant 
	| user COLON SCORE COMPARATION user COLON SCORE
	| user COLON SELECTED_CARD COLON atomic COMPARATION constant
	| user COLON SELECTED_CARD COLON atomic COMPARATION variable
	| user COLON SELECTED_CARD COLON atomic COMPARATION user COLON SELECTED_CARD COLON atomic
	;


atomic: VALUE
	| TYPE
	;

Design: RoundBorders
	| ColorBorders
	| BackgroundColor
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
