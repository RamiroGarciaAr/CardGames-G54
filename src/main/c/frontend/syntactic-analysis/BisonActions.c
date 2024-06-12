#include "BisonActions.h"

/* MODULE INTERNAL STATE */

static Logger * _logger = NULL;

void initializeBisonActionsModule() {
	_logger = createLogger("BisonActions");
}

void shutdownBisonActionsModule() {
	if (_logger != NULL) {
		destroyLogger(_logger);
	}
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
	return block;
} 

Block * BlockTypeSemanticAction(char * variable, CardTypes * cardTypes, Rules * rules){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Block * block = calloc(1, sizeof(Block));
	block->variable1 = variable;
	block->cardTypes = cardTypes;
	block->rules1 = rules;
	return block;
}

Block * BlockGameSemanticAction(char * variable, GameFunction * gameFunction){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Block * block = calloc(1, sizeof(Block));
	block->variable2 = variable;
	block->gameFunction = gameFunction;
	return block;
}

Block * BlockDesignSemanticAction(char * variable, Design * design1){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Block * block = calloc(1, sizeof(Block));
	block->variable3 = variable;
	block->design1 = design1;
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
	return cardTypes;	
}

CardTypes * MultipleCardTypesRuleSemanticAction(char * A, CardTypes *  B){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	CardTypes * cardTypes = calloc(1, sizeof(CardTypes));
	cardTypes->variable1 = A;
	cardTypes->cardType = B;
	return cardTypes;	
}

Rules * RuleStrcuturesSemanticAction(Structures * structures){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Rules * rules = calloc(1, sizeof(Rules));
	rules->structures = structures;
	return rules;
}

Rules * RuleMoveCardsSemanticAction(HandRef * leftHandRef, HandRef * rightHandRef, int constant, Rules * rule){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Rules * rules = calloc(1, sizeof(Rules));
	rules->leftHandRef = leftHandRef;
	rules->rightHandRef = rightHandRef;
	rules->constant = constant;
	rules->rule = rule;
	return rules;
}

Rules * RuleLookAtSemanticAction(HandRef * handRef, int constant, Rules * rule){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Rules * rules = calloc(1, sizeof(Rules));
	rules->handRef = handRef;
	rules->constant1 = constant;
	rules->rule1 = rule;
	return rules;
}

Rules * RuleRestockDeckSemanticAction(Rules * rule){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Rules * rules = calloc(1, sizeof(Rules));
	rules->rule2 = rule;
	return rules;
}

Rules * RuleWinGameSemanticAction(Rules * rule){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Rules * rules = calloc(1, sizeof(Rules));
	rules->rule2 = rule;
	return rules;
}

Rules * RuleWinnerTypeSemanticAction(char * variable, Rules * rule){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Rules * rules = calloc(1, sizeof(Rules));
	rules->variable = variable;
	rules->rule3 = rule;
	return rules;
}

Rules * RuleActivateSpecialCardsSemanticAction(Rules * rule){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Rules * rules = calloc(1, sizeof(Rules));
	rules->rule2 = rule;
	return rules;
}

Rules * RuleUserSemanticAction(UserRules * userRules){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Rules * rules = calloc(1, sizeof(Rules));
	rules->userRules = userRules;
	return rules;
}

Rules * RuleTiedSemanticAction(bool boolean, Rules * rule){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Rules * rules = calloc(1, sizeof(Rules));
	rules->tied = boolean;
	rules->rule4 = rule; 
	return rules;
}

Rules * RuleFinishedSemanticAction(Block * block){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Rules * rules = calloc(1, sizeof(Rules));
	rules->block = block;
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
	return numbers;
}

Numbers * NumberUserSemanticAction(UserScore * userScore ){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Numbers * numbers  = calloc(1, sizeof(Numbers));
	numbers->userScore = userScore;
	return numbers;
}

Expression * ExpressionArithmeticSemanticAction(Expression * expression1, Expression * expression2 ){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * expression = calloc(1, sizeof(Expression));
	expression->leftExpression = expression1;
	expression->rightExpression = expression2;
	return expression;
}

Expression * ExpressionNumberSemanticAction(Numbers * numbers){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * expression = calloc(1, sizeof(Expression));
	expression->numbers = numbers;
	return expression;
}

Expression * ExpressionAtomicSemanticAction(UserCard * usercard, Atomic * atomic){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * expression = calloc(1, sizeof(Expression));
	expression->userCard = usercard;
	expression->atomic = atomic;
	return expression;
}

UserRules * UserRuleNumberSemanticAction(UserScore * userScore, Asignations * asignations, Numbers * numbers, Rules * rule){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	UserRules * userRules = calloc(1,sizeof(UserRules));
	userRules->userScore = userScore;
	userRules->asignations = asignations;
	userRules->numbers = numbers;
	userRules->rule = rule;
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
	return userRules;
}
UserRules * UserRulePMOneSemanticAction(UserScore * userScore, PmOne * pmOne, Rules * rule){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	UserRules * userRules = calloc(1,sizeof(UserRules));
	userRules->userScore2 = userScore;
	userRules->pmOne = pmOne;
	userRules->rule2 = rule;
	return userRules;
}

Structures * StructureIfSemanticAction(Ifs * conditional, InBrakets * inBrakets){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Structures * structure = calloc(1, sizeof(Structures));
	structure->conditional = conditional;
	structure->inBrakets = inBrakets;
	return structure;
}

Structures * StructureForeachSemanticAction(Atomic * atomic, InBrakets * inBrakets){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Structures * structure = calloc(1, sizeof(Structures));
	structure->atomic = atomic;
	structure->inBrakets1 = inBrakets;
	return structure;
}

Structures * StructureElseSemanticAction(InBrakets * inBrakets){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Structures * structure = calloc(1, sizeof(Structures));
	structure->inBrakets2 = inBrakets;
	return structure;
}

InBrakets * MultipleBraketsSemanticAction(Rules * leftRules, Rules * rightRules){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	InBrakets * inBrakets = calloc(1, sizeof(InBrakets));
	inBrakets->leftRules = leftRules;
	inBrakets->rightRules = rightRules;
	return inBrakets;
}

Arithmetic * ArithmeticSemanticAction(){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Arithmetic * arithmetic = calloc(1,sizeof(Arithmetic));
	return arithmetic;
}

Asignations * AsignationsSemanticAction(){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Asignations * asignations = calloc(1, sizeof(Asignations));
	return asignations;
}

PmOne * PMOneSemanticAction(){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	PmOne * pmOne = calloc(1, sizeof(PmOne));
	return pmOne;
}


HandRef * UserHandRefSemanticAction(User * user)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	HandRef * handRef = calloc(1, sizeof(HandRef));
	handRef->user = user;
	return handRef;
}

HandRef * DeckRefSemanticAction(Deck * deck)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	HandRef * handRef = calloc(1, sizeof(HandRef));
	handRef->deck = deck;
	return handRef;
}

Deck * DeckSemanticAction(){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Deck * deck = calloc(1, sizeof(Deck));
	return deck;
}

User * UserSemanticAction(){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	User * user = calloc(1, sizeof(User));
	return user;
}

Ifs * IfSemanticAction(InIf * inIf){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Ifs * conditional = calloc(1, sizeof(Ifs));
	conditional->inIf = inIf;
	return conditional;
}

Ifs * IfChainSemanticAction(InIf * leftInIf, InIf * rightInIf){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Ifs * conditional = calloc(1, sizeof(Ifs));
	conditional->leftInIf = leftInIf;
	conditional->rightInIf = rightInIf;
	return conditional;
}

Ifs * IfTiedAction(bool tied){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Ifs * conditional = calloc(1, sizeof(Ifs));
	conditional->tied = tied;
	return conditional;
}

InIf * InIfConstantSemanticAction(Comparison * comparison, int constant){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	InIf * inIf = calloc(1, sizeof(InIf));
	inIf->comparison = comparison;
	inIf->constant = constant;
	return inIf;
}

InIf * InIfVariableSemanticAction(Comparison * comparison, char * variable){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	InIf * inIf = calloc(1, sizeof(InIf));
	inIf->comparison1 = comparison;
	inIf->variable = variable;
	return inIf;
}

InIf * InIfSpecialCardsSemanticAction(){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	InIf * inIf = calloc(1, sizeof(InIf));
	return inIf;
}

InIf * InIfComparisonExpressionSemanticAction(Expression * leftExpression, Comparison * comparison, Expression * rightExpression){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	InIf * inIf = calloc(1, sizeof(InIf));
	inIf->leftExpression = leftExpression;
	inIf->comparison2 = comparison;
	inIf->rightExpression = rightExpression;
	return inIf;
}

Comparison * ComparisonSemanticAction(){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Comparison * comparison = calloc(1, sizeof(Comparison));
	return comparison;
}

Atomic * AtomicSemanticAction(){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Atomic * atomic = calloc(1, sizeof(Atomic));
	return atomic;
}

Design * RoundBordersDesignSemanticAction(char * variable, Design * design1){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Design * design = calloc(1, sizeof(Design));
	design->variable = variable;
	design->design1 = design1;
	return design;
}

Design * ColorBordersDesignSemanticAction(char * variable, Design * design1){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Design * design = calloc(1, sizeof(Design));
	design->variable = variable;
	design->design1 = design1;
	return design;
}

Design * BackColorDesignSemanticAction(char * variable, Design * design1){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Design * design = calloc(1, sizeof(Design));
	design->variable = variable;
	design->design1 = design1;
	return design;
}