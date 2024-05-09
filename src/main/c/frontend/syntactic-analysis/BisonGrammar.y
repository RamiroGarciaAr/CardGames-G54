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

block: VARIABLE FOR VALUE INTEGER COLON Rules
	| VARIABLE FOR TYPE cardTypes COLON
	| VARIABLE GAME HAS COLON GameFunctions
	| VARIABLE DESIGN HAS COLON Design
	;

GameFunctions: NumbersOnDeck OPEN_PARENTHESIS INTEGER CLOSE_PARENTHESIS
				TypesOfCards OPEN_PARENTHESIS cardTypes CLOSE_PARENTHESIS
				CardsByPlayer OPEN_PARENTHESIS INTEGER CLOSE_PARENTHESIS
				Rounds OPEN_PARENTHESIS INTEGER CLOSE_PARENTHESIS
				RoundsTimer OPEN_PARENTHESIS INTEGER CLOSE_PARENTHESIS
				StartingScore OPEN_PARENTHESIS INTEGER COMMA INTEGER CLOSE_PARENTHESIS
				WinRoundCondition OPEN_PARENTHESIS VARIABLE CLOSE_PARENTHESIS
				WinGameCondition OPEN_PARENTHESIS VARIABLE CLOSE_PARENTHESIS

cardTypes: VARIABLE
	| VARIABLE COMMA cardTypes
	;

Rules: IF OPEN_PARENTHESIS if CLOSE_PARENTHESIS
	| FOREACH OPEN_PARENTHESIS inFor CLOSE_PARENTHESIS
	| MoveCards OPEN_PARENTHESIS handRef COMMA handRef COMMA INTEGER  CLOSE_PARENTHESIS
	| LookAt  OPEN_PARENTHESIS handRef COMMA INTEGER CLOSE_PARENTHESIS
	| RestockDeck OPEN_PARENTHESIS CLOSE_PARENTHESIS
	| WinGame OPEN_PARENTHESIS IDENTIFIER CLOSE_PARENTHESIS
	| WinnerType OPEN_PARENTHESIS   VARIABLE  CLOSE_PARENTHESIS //Var o CardTypes?
	| SpecialCardsOnPlay OPEN_PARENTHESIS CLOSE_PARENTHESIS 
	;

handRef: PLAYER DOT HAND
	| DECK
 	| IDENTIFIER DOT HAND	
	;   

if: inIf
	| inIf AND inIf
	| inIf OR inIf

inIf: VALUE COMPARATION INTEGER
	| TYPE COMPARATION VARIABLE
	| VARIABLE
	| IDENTIFIER COLON SCORE COMPARATION INTEGER 
	| PLAYER COLON SCORE COMPARATION INTEGER
	| IDENTIFIER COLON SCORE COMPARATION IDENTIFIER COLON SCORE
	| PLAYER COLON SCORE COMPARATION PLAYER COLON SCORE 
	| IDENTIFIER COLON SELECTED_CARD COLON VALUE COMPARATION INTEGER
	| PLAYER COLON SELECTED_CARD COLON VALUE COMPARATION INTEGER
	| IDENTIFIER COLON SELECTED_CARD COLON TYPE COMPARATION VARIABLE
	| PLAYER COLON SELECTED_CARD COLON TYPE COMPARATION VARIABLE
	| IDENTIFIER COLON SELECTED_CARD COLON VALUE COMPARATION IDENTIFIER COLON SELECTED_CARD COLON VALUE
	| PLAYER COLON SELECTED_CARD COLON VALUE COMPARATION PLAYER COLON SELECTED_CARD COLON VALUE
	| IDENTIFIER COLON SELECTED_CARD COLON TYPE COMPARATION IDENTIFIER COLON SELECTED_CARD COLON TYPE
	| PLAYER COLON SELECTED_CARD COLON TYPE COMPARATION PLAYER COLON SELECTED_CARD COLON TYPE


inFor: VALUE
	| TYPE

Design: RoundBorders
	| ColorBorders
	| BackgroundColor
	;

expression: expression[left] ADD expression[right]					{ $$ = ArithmeticExpressionSemanticAction($left, $right, ADDITION); }
	| expression[left] DIV expression[right]						{ $$ = ArithmeticExpressionSemanticAction($left, $right, DIVISION); }
	| expression[left] MUL expression[right]						{ $$ = ArithmeticExpressionSemanticAction($left, $right, MULTIPLICATION); }
	| expression[left] SUB expression[right]						{ $$ = ArithmeticExpressionSemanticAction($left, $right, SUBTRACTION); }
	| factor														{ $$ = FactorExpressionSemanticAction($1); }
	;

factor: OPEN_PARENTHESIS expression CLOSE_PARENTHESIS				{ $$ = ExpressionFactorSemanticAction($2); }
	| constant														{ $$ = ConstantFactorSemanticAction($1); }
	;

constant: INTEGER													{ $$ = IntegerConstantSemanticAction($1); }
	;

%%
