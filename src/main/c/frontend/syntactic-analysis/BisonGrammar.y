%{

#include "BisonActions.h"

%}

%define api.value.union.name SemanticValue

%union {
	/** Terminals. */

	int integer;
	char * variable;

	Token token;

	/** Non-terminals. */

	Expression * expression;
	Program * program;
	Block * block;
	Rules * rules;
	UserScore * userScore;
	GameFunction * gameFunction;
	CardTypes * cardTypes;
	UserCard * userCard;
	Numbers * numbers;
	UserRules * userRules;
	Arithmetic * arithmetic;
	Asignations * asignations;
	PmOne * pmOne;
	Structures * structures;
	InBrakets * inBrakets;
	HandRef * handRef;
	Deck * deck;
	User * user;
	Ifs * ifs;
	InIf * inIf;
	Comparison * comparison;
	Atomic * atomic;
	With * with;
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

%token <token> IFS	
%token <token> ELSE	
%token <token> ELIF	
%token <token> WITH

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

%token <token> COLOR_BORDERS
%token <token> BACKGROUND_COLOR

%token <variable> VARIABLE

%token <token> UNKNOWN

/** Non-terminals. */
%type <expression> expression
%type <program> program
%type <block> block
%type <rules> rules
%type <userScore> userScore
%type <gameFunction> gameFunction
%type <cardTypes> cardTypes
%type <userCard> userCard
%type <numbers> numbers
%type <userRules> userRules
%type <arithmetic> arithmetic
%type <asignations> asignations
%type <pmOne> pmOne
%type <structures> structures
%type <inBrakets> inBrakets
%type <handRef> handRef
%type <deck> deck
%type <user> user
%type <ifs> ifs
%type <inIf> inIf
%type <comparison> comparison
%type <atomic> atomic
%type <with> with

/**
 * Precedence and associativity.
 *
 * @see https://www.gnu.org/software/bison/manual/html_node/Precedence.html
 */
%left ADD SUB
%left MUL DIV
%left MODULE
%left AND OR
%left EQUAL DIFERENT
%left GREATER GREATER_OR_EQUAL LOWER LOWER_OR_EQUAL

%precedence ELSE
%precedence ELIF
%precedence IFS

%%

program: block													{ $$ = BlockSemanticAction(currentCompilerState(), $1); }
	;

block: VARIABLE FOR VALUE INTEGER COLON rules					{ $$ = BlockValueSemanticAction($1, $4, $6); }
	| VARIABLE FOR TYPE cardTypes COLON rules					{ $$ = BlockTypeSemanticAction($1, $4, $6); }
	| VARIABLE GAME HAS COLON gameFunction                      { $$ = BlockGameSemanticAction($1, $5); }
	| VARIABLE DESIGN HAS COLON rules							{ $$ = BlockDesignSemanticAction($1, $5); }
	| VARIABLE FOR GAME COLON rules								{ $$ = BlockRuleSemanticAction($1, $5); }
	;

gameFunction: NUMBERS_ON_DECK OPEN_PARENTHESIS INTEGER CLOSE_PARENTHESIS
			   TYPES_OF_CARDS OPEN_PARENTHESIS cardTypes CLOSE_PARENTHESIS
			   CARDS_BY_PLAYER OPEN_PARENTHESIS INTEGER CLOSE_PARENTHESIS
			   ROUNDS OPEN_PARENTHESIS INTEGER CLOSE_PARENTHESIS
			   ROUNDS_TIMER OPEN_PARENTHESIS INTEGER CLOSE_PARENTHESIS
			   STARTING_SCORE OPEN_PARENTHESIS INTEGER COMMA INTEGER CLOSE_PARENTHESIS
			   WIN_ROUND_CONDITION OPEN_PARENTHESIS VARIABLE CLOSE_PARENTHESIS
			   WIN_GAME_CONDITION OPEN_PARENTHESIS VARIABLE CLOSE_PARENTHESIS
			   CARDS_DESIGN OPEN_PARENTHESIS VARIABLE CLOSE_PARENTHESIS
			   BACKGROUND_DESIGN OPEN_PARENTHESIS VARIABLE CLOSE_PARENTHESIS block           { $$ = GameFunctionSemanticAction($3, $7, $11, $15, $19, $23, $25, $29, $33, $37, $41, $43); }
			; 

cardTypes: VARIABLE                                             { $$ = CardTypeRuleSemanticAction($1); }
	| VARIABLE COMMA cardTypes									{ $$ = MultipleCardTypesRuleSemanticAction($1, $3); }
	;

rules: structures                                                                              { $$ = RuleStrcuturesSemanticAction($1); }
    | MOVE_CARDS OPEN_PARENTHESIS handRef COMMA handRef COMMA INTEGER CLOSE_PARENTHESIS rules  { $$ = RuleMoveCardsSemanticAction($3, $5, $7, $9); }
    | LOOK_AT OPEN_PARENTHESIS handRef COMMA INTEGER CLOSE_PARENTHESIS rules                   { $$ = RuleLookAtSemanticAction($3, $5, $7); }
    | RESTOCK_DECK OPEN_PARENTHESIS CLOSE_PARENTHESIS rules                                    { $$ = RuleRestockDeckSemanticAction($4); }
    | WIN_GAME OPEN_PARENTHESIS user CLOSE_PARENTHESIS rules                             	   { $$ = RuleWinGameSemanticAction($3, $5); }
    | WINNER_TYPE OPEN_PARENTHESIS VARIABLE COMMA VARIABLE CLOSE_PARENTHESIS rules             { $$ = RuleWinnerTypeSemanticAction($3, $5, $7); }
	| COLOR_BORDERS OPEN_PARENTHESIS VARIABLE COMMA VARIABLE CLOSE_PARENTHESIS rules		   { $$ = ColorBordersDesignSemanticAction($3, $5, $7); }
	| BACKGROUND_COLOR OPEN_PARENTHESIS VARIABLE CLOSE_PARENTHESIS rules					   { $$ = BackColorDesignSemanticAction($3, $5); }
    | userRules                                                                                { $$ = RuleUserSemanticAction($1); }
    | block                                                                  				   { $$ = RuleFinishedSemanticAction($1); }
    | %empty {$$ = NULL;}
    ;
															
userScore: user DOT SCORE											{ $$ = UserScoreSemanticAction($1); }
	;

userCard: user DOT SELECTED_CARD									{ $$ = UserCardSemanticAction($1); }
	;

numbers: INTEGER													{ $$ = NumberConstSemanticAction($1); }	 			
	| userScore														{ $$ = NumberUserSemanticAction($1); }
	;

expression: expression ADD expression								{ $$ = ExpressionArithmeticSemanticAction($1, $3, EXPR_ADD); }
	| expression DIV expression										{ $$ = ExpressionArithmeticSemanticAction($1, $3, EXPR_DIV); }
	| expression MUL expression										{ $$ = ExpressionArithmeticSemanticAction($1, $3, EXPR_MUL); }
	| expression SUB expression										{ $$ = ExpressionArithmeticSemanticAction($1, $3, EXPR_SUB); }
	| expression MODULE expression									{ $$ = ExpressionArithmeticSemanticAction($1, $3, EXPR_MODULE); }
	| numbers														{ $$ = ExpressionNumberSemanticAction($1); }
	| userCard DOT atomic											{ $$ = ExpressionAtomicSemanticAction($1, $3); }
	| VALUE															{ $$ = ExpressionValueSemanticAction(); }
	;

userRules: userScore asignations numbers rules								  { $$ = UserRuleNumberSemanticAction($1, $2, $3, $4); }
	| userScore asignations userCard DOT VALUE rules						  { $$ = UserRuleCardSemanticAction($1, $2, $3, $6); }
	| userScore asignations numbers arithmetic numbers rules 				  { $$ = UserRuleArithmeticSemanticAction($1, $2, $3, $4, $5, $6); }
	| userScore pmOne rules													  { $$ = UserRulePMOneSemanticAction($1, $2, $3); }
	;

arithmetic: ADD														{ $$ = ArithmeticSemanticAction(ARIT_ADD); }
	| DIV															{ $$ = ArithmeticSemanticAction(ARIT_DIV); }
	| MUL															{ $$ = ArithmeticSemanticAction(ARIT_MUL); }
	| SUB															{ $$ = ArithmeticSemanticAction(ARIT_SUB); }
	| MODULE														{ $$ = ArithmeticSemanticAction(ARIT_MODULE); }
	;

asignations: EQUAL													{ $$ = AsignationsSemanticAction(ASIG_EQUAL); }
	| ADD_EQUAL 													{ $$ = AsignationsSemanticAction(ASIG_ADD_EQUAL); }
	| SUBSTRACT_EQUAL												{ $$ = AsignationsSemanticAction(SUB_EQUAL); }
	;

pmOne: ADD_ONE														{ $$ = PMOneSemanticAction(INCREASE); }
	| SUBSTRACT_ONE													{ $$ = PMOneSemanticAction(DECREASE); }
	;

structures: IFS OPEN_PARENTHESIS ifs CLOSE_PARENTHESIS inBrakets	{ $$ = StructureIfSemanticAction($3, $5, IF_STRUCTURE); }
	| ELIF OPEN_PARENTHESIS ifs CLOSE_PARENTHESIS inBrakets			{ $$ = StructureIfSemanticAction($3, $5, ELIF_STRUCTURE); }
	| ELSE inBrakets												{ $$ = StructureElseSemanticAction($2); }
	| WITH OPEN_PARENTHESIS with CLOSE_PARENTHESIS inBrakets		{ $$ = StructureWithSemanticAction($3, $5); }
	;

with: VALUE INTEGER		{ $$ = WithValueSemanticAction($2); }
	| TYPE VARIABLE		{ $$ = WithTypeSemanticAction($2); }
	;

inBrakets: OPEN_BRAKETS rules CLOSE_BRAKETS rules					{ $$ = MultipleBraketsSemanticAction($2, $4); }
	;

handRef: user DOT HAND												{ $$ = UserHandRefSemanticAction($1); }
	| deck															{ $$ = DeckRefSemanticAction($1); }
	;

deck: DECK															{ $$ = DeckSemanticAction(); }
	;

user: PLAYER														{ $$ = UserSemanticAction(USER_PLAYER); }
	| IDENTIFIER													{ $$ = UserSemanticAction(USER_IDENTIFIER); }
	;

ifs: inIf															{ $$ = IfSemanticAction($1); }
	| inIf AND inIf													{ $$ = IfChainSemanticAction($1, $3, AND_IF); }
	| inIf OR inIf													{ $$ = IfChainSemanticAction($1, $3, OR_IF); }
	;
	
inIf: TYPE comparison VARIABLE										{ $$ = InIfVariableSemanticAction($2, $3); }
	| expression comparison expression								{ $$ = InIfComparisonExpressionSemanticAction($1, $2, $3); }
	;

comparison: GREATER													{ $$ = ComparisonSemanticAction(COMP_GREATER); }
	| LOWER															{ $$ = ComparisonSemanticAction(COMP_LOWER); }
	| EQUAL_EQUAL													{ $$ = ComparisonSemanticAction(COMP_EQUAL_EQUAL); }
	| GREATER_OR_EQUAL												{ $$ = ComparisonSemanticAction(COMP_GREATER_OR_EQUAL); }
	| LOWER_OR_EQUAL												{ $$ = ComparisonSemanticAction(COMP_LOWER_OR_EQUAL); }
	| DIFERENT														{ $$ = ComparisonSemanticAction(COMP_DIFERENT); }
	;

atomic: VALUE														{ $$ = AtomicSemanticAction(ATOMIC_VALUE); }
	| TYPE															{ $$ = AtomicSemanticAction(ATOMIC_TYPE); }
	;

%%
