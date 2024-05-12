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



/*
Constant * IntegerConstantSemanticAction(const int value) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Constant * constant = calloc(1, sizeof(Constant));
	constant->value = value;
	return constant;
}

Expression * ArithmeticExpressionSemanticAction(Expression * leftExpression, Expression * rightExpression, ExpressionType type) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * expression = calloc(1, sizeof(Expression));
	expression->leftExpression = leftExpression;
	expression->rightExpression = rightExpression;
	expression->type = type;
	return expression;
}

Expression * FactorExpressionSemanticAction(Factor * factor) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * expression = calloc(1, sizeof(Expression));
	expression->factor = factor;
	expression->type = FACTOR;
	return expression;
}

Factor * ConstantFactorSemanticAction(Constant * constant) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Factor * factor = calloc(1, sizeof(Factor));
	factor->constant = constant;
	factor->type = CONSTANT;
	return factor;
}

Factor * ExpressionFactorSemanticAction(Expression * expression) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Factor * factor = calloc(1, sizeof(Factor));
	factor->expression = expression;
	factor->type = EXPRESSION;
	return factor;
}
*/

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
}/*listo*/

#pragma region Block

Block * BlockValueSemanticAction(Variable * variable, Constant * constant, Rules * rules){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Block * block = calloc(1, sizeof(Block));
	block->variable = variable;
	block->constant = constant;
	block->rules = rules;
	return block;
} /*listo*/

Block * BlockTypeSemanticAction(Variable * variable, CardTypes * cardTypes, Rules * rules){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Block * block = calloc(1, sizeof(Block));
	block->variable1 = variable;
	block->cardTypes = cardTypes;
	block->rules1 = rules;
	return block;
}/*listo*/

Block * BlockGameSemanticAction(Variable * variable, GameFunction * gameFunctions){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Block * block = calloc(1, sizeof(Block));
	block->variable2 = variable;
	block->gameFunctions = gameFunctions;
	return block;
}/*listo*/

Block * BlockDesignSemanticAction(Variable * variable, Design * design){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Block * block = calloc(1, sizeof(Block));
	block->variable3 = variable;
	block->design = design;
	return block;
}/*listo*/

#pragma endregion Block 

GameFunction * GameFunctionSemanticAction(Constant * cteNumbersOnDeck, CardTypes * cardTypes,Constant * cteCardsByPlayers,Constant * cteRounds,Constant * cteRoundTimer, Constant * cteUserStartingScore,Constant * cteMachineStartingScore,Variable * varWinRoundCondition,Variable * varWinGameCondition, Variable * varCardDesign,Variable * varBackDesign)
{
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
}/*listo*/

#pragma region CardTypes

CardTypes * CardTypeRuleSemanticAction(Variable * type ){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	CardTypes * cardTypes = calloc(1, sizeof(CardTypes));
	cardTypes->variable = type;
	return cardTypes;	
}/*listo*/


CardTypes * MultipleCardTypesRuleSemanticAction(Variable * A, CardTypes *  B){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	CardTypes * cardTypes = calloc(1, sizeof(CardTypes));
	cardTypes->variable1 = A;
	cardTypes->cardType = B;
	return cardTypes;	
}/*listo*/
#pragma endregion CardTypes

#pragma region Rules

Rules * RuleStrcuturesSemanticAction(Structures * structures){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Rules * rules = calloc(1, sizeof(Rules));
	rules->structures = structures;
	return rules;
}/*listo*/

Rules * RuleMoveCardsSemanticAction(HandRef * leftHandRef, HandRef * rightHandRef, Constant * constant){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Rules * rules = calloc(1, sizeof(Rules));
	rules->leftHandRef = leftHandRef;
	rules->rightHandRef = rightHandRef;
	rules->constant = constant;
	return rules;
}/*listo*/

Rules * RuleLookAtSemanticAction(HandRef * handRef, Constant * constant){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Rules * rules = calloc(1, sizeof(Rules));
	rules->handRef = handRef;
	rules->constant1 = constant;
	return rules;
}/*listo*/

Rules * RuleRestockDeckSemanticAction(){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Rules * rules = calloc(1, sizeof(Rules));
	return rules;
}/*listo*/

Rules * RuleWinGameSemanticAction(){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Rules * rules = calloc(1, sizeof(Rules));
	return rules;
}/*listo*/

Rules * RuleWinnerTypeSemanticAction(Variable * variable){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Rules * rules = calloc(1, sizeof(Rules));
	rules->variable = variable;
	return rules;
}/*listo*/

Rules * RuleActivateSpecialCardsSemanticAction(){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Rules * rules = calloc(1, sizeof(Rules));
	return rules;
}/*listo*/

Rules * RuleUserSemanticAction(UserRules * userRules){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Rules * rules = calloc(1, sizeof(Rules));
	rules->userRules = userRules;
	return rules;
}/*listo*/

Rules * RuleTiedSemanticAction(Tied * boolean){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Rules * rules = calloc(1, sizeof(Rules));
	rules->tied = boolean;
	return rules;
}/*listo*/
#pragma endregion Rules

#pragma region UserAtomics

UserScore * UserScoreSemanticAction(User * user ){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	UserScore * userScore = calloc(1, sizeof(UserScore));
	userScore->user = user;
	return userScore;	
}

UserCard * UserCardSemanticAction(User * user){
	logSyntacticAnalyzerAction(__FUNCTION__);
	UserCard * userCard = calloc(1, sizeof(UserCard));
	userCard->user = user;
	return userCard;
}

#pragma endregion UserAtomics

Numbers * NumbersSemanticAction(Constant * constant, UserScore * userScore ){
	logSyntacticAnalyzerAction(__FUNCTION__);
	Numbers * numbers  = calloc(1, sizeof(Numbers));
	numbers->constant  = constant;
	numbers->userScore = userScore;
	return numbers;
}

#pragma region Expresions

Expression * ExpressionAritmethicSemanticAction(Expression * expression1 ,Aritmethic * arithmetic ,Expression * expression2 ){
	logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * expression = calloc(1, sizeof(Expression));
	expression->leftExpression = expression1;
	expression->aritmetic  = arithmetic;
	expression->rightExpression = expression2;
	return expression;
}

Expression * ExpressionNumberSemanticAction(Numbers * numbers){
	logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * expression = calloc(1, sizeof(Expression));
	expression->numbers = numbers;
	return expression;
}

Expression * ExpressionAtomicSemanticAction(UserCard * usercard , Atomic * atomic){
	logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * expression = calloc(1, sizeof(Expression));
	expression->userCard = usercard;
	expression->atomic = atomic;
	return expression;
}

/*Expression * ExpressionConstantSemanticAction(Constant * constant){
	logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * expression = calloc(1, sizeof(Expression));
	expression->constant = constant;
	return expression;
}*/

#pragma endregion Expresions



#pragma region UserRules
/*UserRules * UserRuleConstantSemanticAction(UserScore * userScore, Asignation * asignation,Constant * constant)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	UserRules * userRules = calloc(1,sizeof(UserRules));
	userRules->userScore = userScore;
	userRules->asignation = asignation;
	userRules->constant = constant;
	return userRules;
}*/
UserRules * UserRuleNumberSemanticAction(UserScore * userScore, Asignation * asignation,Numbers * numbers)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	UserRules * userRules = calloc(1,sizeof(UserRules));
	userRules->userScore = userScore;
	userRules->asignation = asignation;
	userRules->numbers = numbers;
	return userRules;
}
UserRules * UserRuleNumberSemanticAction(UserScore * userScore, Asignation * asignation,Numbers * leftNum,Aritmethic * arithmetic,Numbers * rightNum)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	UserRules * userRules = calloc(1,sizeof(UserRules));
	userRules->userScore1 = userScore;
	userRules->asignation1 = asignation;
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

Structures * StructureIfSemanticAction(If * conditional, InBrakets * inBrakets){
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

Aritmethic * ArithmeticExpressionSemanticAction(){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Aritmethic * aritmethic = calloc(1,sizeof(Aritmethic));
	return aritmethic;
	
}

Asignation * AsignationsSemanticAction(){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Asignation * asignations = calloc(1, sizeof(Asignation));
	return asignations;
}

PmOne * PMOneSemanticAction(){
	logSyntacticAnalyzerAction(__FUNCTION__);
	PmOne * pmOne = calloc(1, sizeof(PmOne));
	return pmOne;
}

#pragma region handRef

HandRef * UserHandRefSemanticAction(User * user)
{
	logSyntacticAnalyzerAction(__FUNCTION__);
	HandRef * handRef = calloc(1, sizeof(HandRef));
	handRef->user = user;
	return handRef;
}

HandRef * DeckRefSemanticAction(Deck * deck)
{
	logSyntacticAnalyzerAction(__FUNCTION__);
	HandRef * handRef = calloc(1, sizeof(HandRef));
	handRef->deck = deck;
	return handRef;
}

#pragma endregion handRef


#pragma region if


If * IfSemanticAction(InIf * inIf){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	If * conditional = calloc(1, sizeof(If));
	conditional->inIf = inIf;
	return conditional;
}

If * IfChainSemanticAction(InIf * leftInIf, InIf * rightInIf){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	If * conditional = calloc(1, sizeof(If));
	conditional->leftInIf = leftInIf;
	conditional->rightInIf = rightInIf;
	return conditional;
}

If * IfSemanticAction(Tied * tied){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	If * conditional = calloc(1, sizeof(If));
	conditional->tied = tied;
	return conditional;
}

InIf * InIfConstantSemanticAction(Comparison * comparison, Constant * constant){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	InIf * inIf = calloc(1, sizeof(InIf));
	inIf->comparison = comparison;
	inIf->constant = constant;
	return inIf;
}

InIf * InIfVariableSemanticAction(Comparison * comparison, Variable * variable){
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

/*InIf * InIfComparisonConstantSemanticAction(UserScore * userScore, Comparison * comparison, Constant * constant){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	InIf * inIf = calloc(1, sizeof(InIf));
	inIf->userScore = userScore;
	inIf->comparison = comparison;
	inIf->constant = constant;
	return inIf;
}*/

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

Tied * TiedSemanticAction()
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Tied * tied = calloc(1, sizeof(Tied));
	return tied;
}

Design * RoundBordersDesignSemanticAction(Variable * variable){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Design * design = calloc(1, sizeof(Design));
	design->roundBorders = variable;
	return design;
}
Design * ColorBordersDesignSemanticAction(Variable * variable)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Design * design = calloc(1, sizeof(Design));
	design->colorBorders = variable;
	return design;
}
Design * BackColorDesignSemanticAction(Variable * variable)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Design * design = calloc(1, sizeof(Design));
	design->backgroundColor = variable;
	return design;
}
#pragma region Vars

Constant * IntegerConstantSemanticAction(const int value) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Constant * constant = calloc(1, sizeof(Constant));
	constant->value = value;
	return constant;
}

Variable * VariableSemanticAction(const char * name){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Variable * variable = calloc(1, sizeof(Variable));
	variable->name = name;
	return variable;
}

Bool * BooleanSemanticAction(const boolean value)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Bool * boolean = calloc(1,sizeof(Bool));
	boolean->value = value;
	return boolean;
}

#pragma endregion Vars