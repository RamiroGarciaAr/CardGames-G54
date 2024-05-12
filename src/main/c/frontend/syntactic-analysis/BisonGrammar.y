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
	
	Program * program;
	Block * block;
	Rules * rules;
	Bool * bool;
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
	Tied * tied;
	InIf * inIf;
	Comparison * comparison;
	Atomic * atomic;
	Design * design;
	Variable * variable;
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
%token <token> IFS	
%token <token> ELSE	
%token <token> ELIF	

%token <token> TRUE
%token <token> FALSE

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
%token <token> ACTIVATE_SPECIAL_CARDS

%token <token> ROUND_BORDERS
%token <token> COLOR_BORDERS
%token <token> BACKGROUND_COLOR


%token <token> VARIABLE

%token <token> UNKNOWN

/** Non-terminals. */
%type <constant> constant
%type <expression> expression
%type <program> program
%type <block> block
%type <rules> rules
%type <bool> bool
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
%type <tied> tied
%type <inIf> inIf
%type <comparison> comparison
%type <atomic> atomic
%type <design> design
%type <variable> variable


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

block: variable FOR VALUE constant COLON rules					{ $$ = BlockValueSemanticAction($1, $4, $6); }
	| variable FOR TYPE cardTypes COLON rules					{ $$ = BlockTypeSemanticAction($1, $4, $6); }
	| variable GAME HAS COLON gameFunction                      { $$ = BlockGameSemanticAction($1, $5); }
	| variable DESIGN HAS COLON design							{ $$ = BlockDesignSemanticAction($1, $5); }
	;

gameFunction: NUMBERS_ON_DECK OPEN_PARENTHESIS constant CLOSE_PARENTHESIS
			   TYPES_OF_CARDS OPEN_PARENTHESIS cardTypes CLOSE_PARENTHESIS
			   CARDS_BY_PLAYER OPEN_PARENTHESIS constant CLOSE_PARENTHESIS
			   ROUNDS OPEN_PARENTHESIS constant CLOSE_PARENTHESIS
			   ROUNDS_TIMER OPEN_PARENTHESIS constant CLOSE_PARENTHESIS
			   STARTING_SCORE OPEN_PARENTHESIS constant COMMA constant CLOSE_PARENTHESIS
			   WIN_ROUND_CONDITION OPEN_PARENTHESIS variable CLOSE_PARENTHESIS
			   WIN_GAME_CONDITION OPEN_PARENTHESIS variable CLOSE_PARENTHESIS
			   CARDS_DESIGN OPEN_PARENTHESIS variable CLOSE_PARENTHESIS
			   BACKGROUND_DESIGN OPEN_PARENTHESIS variable CLOSE_PARENTHESIS            { $$ = GameFunctionSemanticAction($3, $7, $11, $15, $19, $23, $25, $29, $33, $37, $41); }
			; 

cardTypes: variable                                                                      { $$ = CardTypeRuleSemanticAction($1); }
	| variable COMMA cardTypes															 { $$ = MultipleCardTypesRuleSemanticAction($1, $3); }
	;

rules: structures																		 { $$ = RuleStrcuturesSemanticAction($1); }
	| MOVE_CARDS OPEN_PARENTHESIS handRef COMMA handRef COMMA constant CLOSE_PARENTHESIS { $$ = RuleMoveCardsSemanticAction($3, $5, $7); }
	| LOOK_AT OPEN_PARENTHESIS handRef COMMA constant CLOSE_PARENTHESIS                  { $$ = RuleLookAtSemanticAction($3, $5); }
	| RESTOCK_DECK OPEN_PARENTHESIS CLOSE_PARENTHESIS                                    { $$ = RuleRestockDeckSemanticAction(); }
	| WIN_GAME OPEN_PARENTHESIS IDENTIFIER CLOSE_PARENTHESIS                             { $$ = RuleWinGameSemanticAction(); }
	| WINNER_TYPE OPEN_PARENTHESIS variable CLOSE_PARENTHESIS							 { $$ = RuleWinnerTypeSemanticAction($3); }
	| ACTIVATE_SPECIAL_CARDS OPEN_PARENTHESIS CLOSE_PARENTHESIS                  		 { $$ = RuleActivateSpecialCardsSemanticAction(); }
	| userRules																			 { $$ = RuleUserSemanticAction($1); }
	| TIED EQUAL bool																	 { $$ = RuleTiedSemanticAction($3); }
	;

bool: TRUE															{ $$ = BooleanSemanticAction($1); }
	| FALSE															{ $$ = BooleanSemanticAction($1); }
	;
															
userScore: user DOT SCORE											{ $$ = UserScoreSemanticAction($1); }												
	;

userCard: user DOT SELECTED_CARD									{ $$ = UserCardSemanticAction($1); }			
	;

numbers: constant													{ $$ = NumberConstSemanticAction($1); }	 			
	| userScore														{ $$ = NumberUserSemanticAction($1); }
	;

expression: expression arithmetic expression						{ $$ = ExpressionArithmeticSemanticAction($1, $2, $3); }
	| numbers														{ $$ = ExpressionNumberSemanticAction($1); }
	| userCard DOT atomic											{ $$ = ExpressionAtomicSemanticAction($1, $3); }
	/*| constant														{ $$ = ExpressionConstantSemanticAction($1); }*/
	;
	
userRules: userScore asignations numbers							{ $$ = UserRuleNumberSemanticAction($1, $2, $3); }
	/*| userScore asignations constant								{ $$ = UserRuleConstantSemanticAction($1, $2, $3); }*/
	| userScore asignations numbers arithmetic numbers 				{ $$ = UserRuleArithmeticSemanticAction($1, $2, $3, $4, $5); }
	| userScore pmOne												{ $$ = UserRulePMOneSemanticAction($1, $2); }
	;

arithmetic: ADD														{ $$ = ArithmeticSemanticAction(); }
	| DIV															{ $$ = ArithmeticSemanticAction(); }
	| MUL															{ $$ = ArithmeticSemanticAction(); }
	| SUB															{ $$ = ArithmeticSemanticAction(); }
	| MODULE														{ $$ = ArithmeticSemanticAction(); }
	;

asignations: EQUAL													{ $$ = AsignationsSemanticAction(); }
	| ADD_EQUAL 													{ $$ = AsignationsSemanticAction(); }
	| SUBSTRACT_EQUAL												{ $$ = AsignationsSemanticAction(); }
	;

pmOne: ADD_ONE														{ $$ = PMOneSemanticAction(); }
	| SUBSTRACT_ONE													{ $$ = PMOneSemanticAction(); }
	;

structures: IFS OPEN_PARENTHESIS ifs CLOSE_PARENTHESIS inBrakets	{ $$ = StructureIfSemanticAction($3, $5); }
	| FOREACH OPEN_PARENTHESIS atomic CLOSE_PARENTHESIS inBrakets	{ $$ = StructureForeachSemanticAction($3, $5); }
	| ELIF OPEN_PARENTHESIS ifs CLOSE_PARENTHESIS inBrakets			{ $$ = StructureIfSemanticAction($3, $5); }
	| ELSE inBrakets												{ $$ = StructureElseSemanticAction($2); }
	;

inBrakets: OPEN_BRAKETS rules CLOSE_BRAKETS							{ $$ = BraketsSemanticAction($2); }
	| OPEN_BRAKETS rules CLOSE_BRAKETS rules						{ $$ = MultipleBraketsSemanticAction($2, $4); }
	;

handRef: user DOT HAND												{ $$ = UserHandRefSemanticAction($1); }
	| deck															{ $$ = DeckRefSemanticAction($1); }
	;

deck: DECK															{ $$ = DeckSemanticAction(); }
	;

user: PLAYER														{ $$ = UserSemanticAction(); }
	| IDENTIFIER													{ $$ = UserSemanticAction(); }
	;

ifs: inIf															{ $$ = IfSemanticAction($1); }
	| inIf AND inIf													{ $$ = IfChainSemanticAction($1, $3); }
	| inIf OR inIf													{ $$ = IfChainSemanticAction($1, $3); }
	| tied															{ $$ = IfTiedAction($1); }
	;

tied: TIED															{ $$ = TiedSemanticAction(); }
	;
	
inIf: VALUE comparison constant										{ $$ = InIfConstantSemanticAction($2, $3); }
	| TYPE comparison variable										{ $$ = InIfVariableSemanticAction($2, $3); }
	| SPECIAL_CARDS_ON_PLAY OPEN_PARENTHESIS CLOSE_PARENTHESIS		{ $$ = InIfSpecialCardsSemanticAction(); }
	/*| userScore comparison constant 								{ $$ = InIfComparisonConstantSemanticAction($1, $2, $3); }*/
	| expression comparison expression								{ $$ = InIfComparisonExpressionSemanticAction($1, $2, $3); }
	;

comparison: GREATER													{ $$ = ComparisonSemanticAction(); }
	| LOWER															{ $$ = ComparisonSemanticAction(); }
	| EQUAL_EQUAL													{ $$ = ComparisonSemanticAction(); }
	| GREATER_OR_EQUAL												{ $$ = ComparisonSemanticAction(); }
	| LOWER_OR_EQUAL												{ $$ = ComparisonSemanticAction(); }
	| DIFERENT														{ $$ = ComparisonSemanticAction(); }
	;

atomic: VALUE														{ $$ = AtomicSemanticAction(); }
	| TYPE															{ $$ = AtomicSemanticAction(); }
	;

design: ROUND_BORDERS OPEN_PARENTHESIS variable CLOSE_PARENTHESIS	{ $$ = RoundBordersDesignSemanticAction($3); }
	| COLOR_BORDERS OPEN_PARENTHESIS variable CLOSE_PARENTHESIS		{ $$ = ColorBordersDesignSemanticAction($3); }
	| BACKGROUND_COLOR OPEN_PARENTHESIS variable CLOSE_PARENTHESIS	{ $$ = BackColorDesignSemanticAction($3); }
	;

constant: INTEGER													{ $$ = IntegerConstantSemanticAction($1); }
	;

variable: VARIABLE													{ $$ = VariableSemanticAction($1); }
	;

%%

/*																	{ $$ = BlockSemanticAction(currentCompilerState(), $1); }
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
