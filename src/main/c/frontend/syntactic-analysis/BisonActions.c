#include "BisonActions.h"
#include "../../backend/semantic-analysis/symbolTable.h"

/* MODULE INTERNAL STATE */

static Logger * _logger = NULL;

void initializeBisonActionsModule() {
	_logger = createLogger("BisonActions");
	symbolTableInit();
}

void shutdownBisonActionsModule() {
	if (_logger != NULL) {
		destroyLogger(_logger);
	}
	symbolTableDestroy();
}

/** IMPORTED FUNCTIONS */

extern unsigned int flexCurrentContext(void);

/* PRIVATE FUNCTIONS */

static void _logSyntacticAnalyzerAction(const char * functionName);

/**
 * Logs a syntactic-analyzer action in DEBUGGING level.
 */
static void _logSyntacticAnalyzerAction(const char * functionName) {
	logDebugging(_logger, "%s", functionName);
}

/* PUBLIC FUNCTIONS */

Program * BlockSemanticAction(CompilerState * compilerState, Block * block) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Program * program = calloc(1, sizeof(Program));
	program->block = block;
	compilerState->abstractSyntaxtTree = program;
	if (0 < flexCurrentContext()) {
		logError(_logger, "The final context is not the default (0): %d", flexCurrentContext());
		compilerState->succeed = false;
	}
	else {
		compilerState->succeed = true;
	}
	return program;
}

Block * BlockValueSemanticAction(char * variable, int constant, Rules * rules){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Block * block = calloc(1, sizeof(Block));
	block->variable = variable;
	block->constant = constant;
	block->rules = rules;
	block->type = VALUE_BLOCK;
	
	struct key key;
	key.varname = variable;

	struct value value;
	value.type = VAR_PLAYING; // decirle de que tipo es esto 
	value.metadata.hasValue = true;

	symbolTableInsert(&key, &value);
	
	return block;
} 

Block * BlockTypeSemanticAction(char * variable, CardTypes * cardTypes, Rules * rules){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Block * block = calloc(1, sizeof(Block));
	block->variable1 = variable;
	block->cardTypes = cardTypes;
	block->rules1 = rules;
	block->type = TYPE_BLOCK;
	return block;
}

Block * BlockGameSemanticAction(char * variable, GameFunction * gameFunction){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Block * block = calloc(1, sizeof(Block));
	block->variable2 = variable;
	block->gameFunction = gameFunction;
	block->type = GAME_BLOCK;
	return block;
}

Block * BlockDesignSemanticAction(char * variable, Rules * rules3){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Block * block = calloc(1, sizeof(Block));
	block->variable3 = variable;
	block->rules3 = rules3;
	block->type = DESIGN_BLOCK;
	return block;
}

Block * BlockRuleSemanticAction(char * variable, Rules * rules){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Block * block = calloc(1, sizeof(Block));
	block->variable4 = variable;
	block->rules2 = rules;
	block->type = RULE_BLOCK;
	return block;
}

GameFunction * GameFunctionSemanticAction(int cteNumbersOnDeck, CardTypes * cardTypes, int cteCardsByPlayers, int cteRounds, int cteRoundTimer, int cteUserStartingScore, int cteMachineStartingScore, char * varWinRoundCondition, char * varWinGameCondition, char * varCardDesign, char * varBackDesign, Block * block){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	GameFunction * gameFunction = calloc(1,sizeof(GameFunction));
	gameFunction->cteNumbersOnDeck = cteNumbersOnDeck;
	gameFunction->cardTypes = cardTypes;
	gameFunction->cteCardsByPlayers = cteCardsByPlayers;
	gameFunction->cteRounds = cteRounds;
	gameFunction->cteRoundTimer = cteRoundTimer;
	gameFunction->cteUserStartingScore = cteUserStartingScore;
	gameFunction->cteMachineStartingScore = cteMachineStartingScore;
	gameFunction->varWinRoundCondition = varWinRoundCondition;
	gameFunction->varWinGameCondition=varWinGameCondition;
	gameFunction->varCardDesign = varCardDesign;
	gameFunction->varBackDesign = varBackDesign; 
	gameFunction->block = block;
	return gameFunction;
}

CardTypes * CardTypeRuleSemanticAction(char * type){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	CardTypes * cardTypes = calloc(1, sizeof(CardTypes));
	cardTypes->variable = type;
	cardTypes->type = ONE_TYPE;
	return cardTypes;	
}

CardTypes * MultipleCardTypesRuleSemanticAction(char * A, CardTypes *  B){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	CardTypes * cardTypes = calloc(1, sizeof(CardTypes));
	cardTypes->variable1 = A;
	cardTypes->cardType = B;
	cardTypes->type = MULTIPLE_TYPE;
	return cardTypes;	
}

Rules * RuleStrcuturesSemanticAction(Structures * structures){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Rules * rules = calloc(1, sizeof(Rules));
	rules->structures = structures;
	rules->type = STRUCTURES;
	return rules;
}

Rules * RuleMoveCardsSemanticAction(HandRef * leftHandRef, HandRef * rightHandRef, int constant, Rules * rule){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Rules * rules = calloc(1, sizeof(Rules));
	rules->leftHandRef = leftHandRef;
	rules->rightHandRef = rightHandRef;
	rules->constant = constant;
	rules->rule = rule;
	rules->type = RULE_MOVE_CARDS;
	return rules;
}

Rules * RuleLookAtSemanticAction(HandRef * handRef, int constant, Rules * rule){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Rules * rules = calloc(1, sizeof(Rules));
	rules->handRef = handRef;
	rules->constant1 = constant;
	rules->rule1 = rule;
	rules->type = RULE_LOOK_AT;
	return rules;
}

Rules * RuleRestockDeckSemanticAction(Rules * rule){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Rules * rules = calloc(1, sizeof(Rules));
	rules->rule2 = rule;
	rules->type = RULE_RESTOCK_DECK;
	return rules;
}

Rules * RuleWinGameSemanticAction(Rules * rule){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Rules * rules = calloc(1, sizeof(Rules));
	rules->rule2 = rule;
	rules->type = RULE_WIN_GAME;
	return rules;
}

Rules * RuleWinnerTypeSemanticAction(char * variable, Rules * rule){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Rules * rules = calloc(1, sizeof(Rules));
	rules->variable = variable;
	rules->rule3 = rule;
	rules->type = RULE_WINNER_TYPE;
	return rules;
}

Rules * RuleActivateSpecialCardsSemanticAction(Rules * rule){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Rules * rules = calloc(1, sizeof(Rules));
	rules->rule2 = rule;
	rules->type = RULE_ACTIVATE_SPECIAL_CARDS;
	return rules;
}

Rules * RuleUserSemanticAction(UserRules * userRules){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Rules * rules = calloc(1, sizeof(Rules));
	rules->userRules = userRules;
	rules->type = USER_RULES;
	return rules;
}

Rules * RuleTiedSemanticAction(bool boolean, Rules * rule){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Rules * rules = calloc(1, sizeof(Rules));
	rules->tied = boolean;
	rules->rule4 = rule; 
	rules->type = TIED_RULE;
	return rules;
}

Rules * RuleFinishedSemanticAction(Block * block){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Rules * rules = calloc(1, sizeof(Rules));
	rules->block = block;
	rules->type = FINISH_RULE;
	return rules;
}

UserScore * UserScoreSemanticAction(User * user ){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	UserScore * userScore = calloc(1, sizeof(UserScore));
	userScore->user = user;
	return userScore;	
}

UserCard * UserCardSemanticAction(User * user){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	UserCard * userCard = calloc(1, sizeof(UserCard));
	userCard->user = user;
	return userCard;
}

Numbers * NumberConstSemanticAction(int constant){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Numbers * numbers  = calloc(1, sizeof(Numbers));
	numbers->constant  = constant;
	numbers->type = CONSTANT;
	return numbers;
}

Numbers * NumberUserSemanticAction(UserScore * userScore ){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Numbers * numbers  = calloc(1, sizeof(Numbers));
	numbers->userScore = userScore;
	numbers->type = USER_SCORE;
	return numbers;
}

Expression * ExpressionArithmeticSemanticAction(Expression * expression1, Expression * expression2, ExpressionType type){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * expression = calloc(1, sizeof(Expression));
	expression->leftExpression = expression1;
	expression->rightExpression = expression2;
	expression->type = type;
	return expression;
}

Expression * ExpressionNumberSemanticAction(Numbers * numbers){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * expression = calloc(1, sizeof(Expression));
	expression->numbers = numbers;
	expression->type = NUMBERS;
	return expression;
}

Expression * ExpressionAtomicSemanticAction(UserCard * usercard, Atomic * atomic){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * expression = calloc(1, sizeof(Expression));
	expression->userCard = usercard;
	expression->atomic = atomic;
	expression->type = ATOMIC;
	return expression;
}

Expression * ExpressionValueSemanticAction(){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * expression = calloc(1,sizeof(Expression));
	expression->type = EXPR_VALUE;
	return expression;
}

UserRules * UserRuleNumberSemanticAction(UserScore * userScore, Asignations * asignations, Numbers * numbers, Rules * rule){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	UserRules * userRules = calloc(1,sizeof(UserRules));
	userRules->userScore = userScore;
	userRules->asignations = asignations;
	userRules->numbers = numbers;
	userRules->rule = rule;
	userRules->type = NUMBER_ASSIG;
	return userRules;
}

UserRules * UserRuleCardSemanticAction(UserScore * userScore, Asignations * asignation, UserCard * userCard, Rules * rule){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	UserRules * userRules = calloc(1,sizeof(UserRules));
	userRules->userScore3 = userScore;
	userRules->asignations3 = asignation;
	userRules->userCard = userCard;
	userRules->rule4 = rule;
	userRules->type = CARD_ASSIG;
	return userRules;
}

UserRules * UserRuleArithmeticSemanticAction(UserScore * userScore, Asignations * asignations, Numbers * leftNum, Arithmetic * arithmetic, Numbers * rightNum, Rules * rule){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	UserRules * userRules = calloc(1,sizeof(UserRules));
	userRules->userScore1 = userScore;
	userRules->asignations1 = asignations;
	userRules->numbers = leftNum;
	userRules->arithmetic = arithmetic;
	userRules->numbers = rightNum;
	userRules->rule1 = rule;
	userRules->type = ARITHMETIC_ASSIG;
	return userRules;
}
UserRules * UserRulePMOneSemanticAction(UserScore * userScore, PmOne * pmOne, Rules * rule){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	UserRules * userRules = calloc(1,sizeof(UserRules));
	userRules->userScore2 = userScore;
	userRules->pmOne = pmOne;
	userRules->rule2 = rule;
	userRules->type = PMO_ASSIG;
	return userRules;
}

UserRules * UserRuleGetterSemanticAction(Getters * leftGetter, Asignations * asignation, Getters * rightGetter, Rules * rule){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	UserRules * userRules = calloc(1,sizeof(UserRules));
	userRules->leftGetter = leftGetter;
	userRules->asignations2 = asignation;
	userRules->rightGetter = rightGetter;
	userRules->rule3 = rule;
	userRules->type = GETTER_ASSIG;
	return userRules;
}

Getters * GettersSemanticAction(char * variable, GettersType type){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Getters * getter = calloc(1, sizeof(Getters));
	getter->variable = variable;
	getter->type = type;
	return getter;
}

Structures * StructureIfSemanticAction(Ifs * conditional, InBrakets * inBrakets, StructuresType type){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Structures * structure = calloc(1, sizeof(Structures));
	structure->conditional = conditional;
	structure->inBrakets = inBrakets;
	structure->type = type;
	return structure;
}

Structures * StructureForeachSemanticAction(Atomic * atomic, InBrakets * inBrakets){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Structures * structure = calloc(1, sizeof(Structures));
	structure->atomic = atomic;
	structure->inBrakets1 = inBrakets;
	structure->type = FOREACH_STRUCTURE;
	return structure;
}

Structures * StructureElseSemanticAction(InBrakets * inBrakets){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Structures * structure = calloc(1, sizeof(Structures));
	structure->inBrakets2 = inBrakets;
	structure->type = ELSE_STRUCTURE;
	return structure;
}

InBrakets * MultipleBraketsSemanticAction(Rules * leftRules, Rules * rightRules){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	InBrakets * inBrakets = calloc(1, sizeof(InBrakets));
	inBrakets->leftRules = leftRules;
	inBrakets->rightRules = rightRules;
	return inBrakets;
}

Arithmetic * ArithmeticSemanticAction(ArithmeticType type){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Arithmetic * arithmetic = calloc(1,sizeof(Arithmetic));
	arithmetic->type = type;
	return arithmetic;
}

Asignations * AsignationsSemanticAction(AsignationsType type){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Asignations * asignations = calloc(1, sizeof(Asignations));
	asignations->type = type;
	return asignations;
}

PmOne * PMOneSemanticAction(PmOneType type){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	PmOne * pmOne = calloc(1, sizeof(PmOne));
	pmOne->type = type;
	return pmOne;
}


HandRef * UserHandRefSemanticAction(User * user)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	HandRef * handRef = calloc(1, sizeof(HandRef));
	handRef->user = user;
	handRef->type = USER;
	return handRef;
}

HandRef * DeckRefSemanticAction(Deck * deck)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	HandRef * handRef = calloc(1, sizeof(HandRef));
	handRef->deck = deck;
	handRef->type = HAND_DECK;
	return handRef;
}

Deck * DeckSemanticAction(){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Deck * deck = calloc(1, sizeof(Deck));
	return deck;
}

User * UserSemanticAction(UserType type){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	User * user = calloc(1, sizeof(User));
	user->type = type;
	return user;
}

Ifs * IfSemanticAction(InIf * inIf){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Ifs * conditional = calloc(1, sizeof(Ifs));
	conditional->inIf = inIf;
	conditional->type = INIF;
	return conditional;
}

Ifs * IfChainSemanticAction(InIf * leftInIf, InIf * rightInIf, IfType type){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Ifs * conditional = calloc(1, sizeof(Ifs));
	conditional->leftInIf = leftInIf;
	conditional->rightInIf = rightInIf;
	conditional->type = type;
	return conditional;
}

Ifs * IfTiedAction(bool tied){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Ifs * conditional = calloc(1, sizeof(Ifs));
	conditional->tied = tied;
	conditional->type = TIED_IF;
	return conditional;
}

InIf * InIfVariableSemanticAction(Comparison * comparison, char * variable){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	InIf * inIf = calloc(1, sizeof(InIf));
	inIf->comparison1 = comparison;
	inIf->variable = variable;
	inIf->type = TYPE_IF;
	return inIf;
}

InIf * InIfSpecialCardsSemanticAction(){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	InIf * inIf = calloc(1, sizeof(InIf));
	inIf->type = ACTIVATE_SPECIAL_CARDS_IF;
	return inIf;
}

InIf * InIfComparisonExpressionSemanticAction(Expression * leftExpression, Comparison * comparison, Expression * rightExpression){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	InIf * inIf = calloc(1, sizeof(InIf));
	inIf->leftExpression = leftExpression;
	inIf->comparison2 = comparison;
	inIf->rightExpression = rightExpression;
	inIf->type = EXPRESSION_IF;
	return inIf;
}

Comparison * ComparisonSemanticAction(ComparisonType type){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Comparison * comparison = calloc(1, sizeof(Comparison));
	comparison->type = type;
	return comparison;
}

Atomic * AtomicSemanticAction(AtomicType type){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Atomic * atomic = calloc(1, sizeof(Atomic));
	atomic->type = type;
	return atomic;
}

Rules * RoundBordersDesignSemanticAction(int constant, Rules * rule){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Rules * rules = calloc(1, sizeof(Rules));
	rules->constant2 = constant;
	rules->rule5 = rule;
	rules->type = ROUND_BORDERS_DESIGN;
	return rules;
}

Rules * ColorBordersDesignSemanticAction(char * variable, Rules * rule){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Rules * rules = calloc(1, sizeof(Rules));
	rules->variable = variable;
	rules->rule3 = rule;
	rules->type = COLOR_BORDERS_DESIGN;
	return rules;
}

Rules * BackColorDesignSemanticAction(char * variable, Rules * rule){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Rules * rules = calloc(1, sizeof(Rules));
	rules->variable = variable;
	rules->rule3 = rule;
	rules->type = BACKGROUND_COLOR_DESIGN;
	return rules;
}