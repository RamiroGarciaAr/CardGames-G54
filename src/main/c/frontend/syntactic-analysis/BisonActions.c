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

#pragma region Block

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

Block * BlockDesignSemanticAction(char * variable, Design * design){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Block * block = calloc(1, sizeof(Block));
	block->variable3 = variable;
	block->design = design;
	return block;
}

#pragma endregion Block 

GameFunction * GameFunctionSemanticAction(int cteNumbersOnDeck, CardTypes * cardTypes, int cteCardsByPlayers, int cteRounds, int cteRoundTimer, int cteUserStartingScore, int cteMachineStartingScore, char * varWinRoundCondition, char * varWinGameCondition, char * varCardDesign, char * varBackDesign){
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
	return gameFunction;
}

#pragma region CardTypes

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
#pragma endregion CardTypes

#pragma region Rules

Rules * RuleStrcuturesSemanticAction(Structures * structures){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Rules * rules = calloc(1, sizeof(Rules));
	rules->structures = structures;
	return rules;
}

Rules * RuleMoveCardsSemanticAction(HandRef * leftHandRef, HandRef * rightHandRef, int constant){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Rules * rules = calloc(1, sizeof(Rules));
	rules->leftHandRef = leftHandRef;
	rules->rightHandRef = rightHandRef;
	rules->constant = constant;
	return rules;
}

Rules * RuleLookAtSemanticAction(HandRef * handRef, int constant){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Rules * rules = calloc(1, sizeof(Rules));
	rules->handRef = handRef;
	rules->constant1 = constant;
	return rules;
}

Rules * RuleRestockDeckSemanticAction(){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Rules * rules = calloc(1, sizeof(Rules));
	return rules;
}

Rules * RuleWinGameSemanticAction(){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Rules * rules = calloc(1, sizeof(Rules));
	return rules;
}

Rules * RuleWinnerTypeSemanticAction(char * variable){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Rules * rules = calloc(1, sizeof(Rules));
	rules->variable = variable;
	return rules;
}

Rules * RuleActivateSpecialCardsSemanticAction(){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Rules * rules = calloc(1, sizeof(Rules));
	return rules;
}

Rules * RuleUserSemanticAction(UserRules * userRules){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Rules * rules = calloc(1, sizeof(Rules));
	rules->userRules = userRules;
	return rules;
}

Rules * RuleTiedSemanticAction(bool boolean){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Rules * rules = calloc(1, sizeof(Rules));
	rules->tied = boolean;
	return rules;
}
#pragma endregion Rules

#pragma region UserAtomics

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

#pragma endregion UserAtomics

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

#pragma region Expresions

Expression * ExpressionArithmeticSemanticAction(Expression * expression1 ,Arithmetic * arithmetic ,Expression * expression2 ){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * expression = calloc(1, sizeof(Expression));
	expression->leftExpression = expression1;
	expression->arithmetic  = arithmetic;
	expression->rightExpression = expression2;
	return expression;
}

Expression * ExpressionNumberSemanticAction(Numbers * numbers){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * expression = calloc(1, sizeof(Expression));
	expression->numbers = numbers;
	return expression;
}

Expression * ExpressionAtomicSemanticAction(UserCard * usercard , Atomic * atomic){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * expression = calloc(1, sizeof(Expression));
	expression->userCard = usercard;
	expression->atomic = atomic;
	return expression;
}

#pragma endregion Expresions



#pragma region UserRules
UserRules * UserRuleNumberSemanticAction(UserScore * userScore, Asignations * asignations,Numbers * numbers)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	UserRules * userRules = calloc(1,sizeof(UserRules));
	userRules->userScore = userScore;
	userRules->asignations = asignations;
	userRules->numbers = numbers;
	return userRules;
}
UserRules * UserRuleArithmeticSemanticAction(UserScore * userScore, Asignations * asignations, Numbers * leftNum, Arithmetic * arithmetic, Numbers * rightNum){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	UserRules * userRules = calloc(1,sizeof(UserRules));
	userRules->userScore1 = userScore;
	userRules->asignations1 = asignations;
	userRules->numbers = leftNum;
	userRules->arithmetic = arithmetic;
	userRules->numbers = rightNum;
	return userRules;
}
UserRules * UserRulePMOneSemanticAction(UserScore * userScore,PmOne * pmOne)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	UserRules * userRules = calloc(1,sizeof(UserRules));
	userRules->userScore2 = userScore;
	userRules->pmOne = pmOne;
	return userRules;
}

#pragma endregion UserRules


#pragma region Structures

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

#pragma endregion Structures

#pragma region Brackets
InBrakets * BraketsSemanticAction(Rules * rules){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	InBrakets * inBrakets = calloc(1, sizeof(InBrakets));
	inBrakets->rules = rules;
	return inBrakets;
}

InBrakets * MultipleBraketsSemanticAction(Rules * leftRules, Rules * rightRules){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	InBrakets * inBrakets = calloc(1, sizeof(InBrakets));
	inBrakets->leftRules = leftRules;
	inBrakets->rightRules = rightRules;
	return inBrakets;
}

#pragma endregion Brackets

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

#pragma region handRef

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

#pragma endregion handRef


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


#pragma region if


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

#pragma endregion if

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

Design * RoundBordersDesignSemanticAction(char * variable){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Design * design = calloc(1, sizeof(Design));
	design->roundBorders = variable;
	return design;
}
Design * ColorBordersDesignSemanticAction(char * variable)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Design * design = calloc(1, sizeof(Design));
	design->colorBorders = variable;
	return design;
}
Design * BackColorDesignSemanticAction(char * variable)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Design * design = calloc(1, sizeof(Design));
	design->backgroundColor = variable;
	return design;
}