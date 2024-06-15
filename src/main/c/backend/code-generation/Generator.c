#include "Generator.h"

/* MODULE INTERNAL STATE */

const char _indentationCharacter = ' ';
const char _indentationSize = 4;
static Logger * _logger = NULL;

void initializeGeneratorModule() {
	_logger = createLogger("Generator");
}

void shutdownGeneratorModule() {
	if (_logger != NULL) {
		destroyLogger(_logger);
	}
}

/** PRIVATE FUNCTIONS */
static char * _indentation(const unsigned int indentationLevel);
static void _output(const unsigned int indentationLevel, const char * const format, ...);

/**
 * Creates the epilogue of the generated output, that is, the final lines that
 * completes a valid Latex document.
 */
static void _generateEpilogue(const int value) {
	_output(0, "%s%d%s",
		"            [ $", value, "$, circle, draw, blue ]\n"
		"        ]\n"
		"    \\end{forest}\n"
		"\\end{document}\n\n"
	);
}

static void _generateProgram(Program * program) { //listo
	_generateBlock(program->block);
}

static void _generateBlock(Block * block){ //listo
	switch(block->type){
		case VALUE_BLOCK:
			_generateVariable(block->variable);
			_generateInteger(block->constant);
			_generateRules(block->rules);
			break;
		case TYPE_BLOCK:
			_generateVariable(block->variable1);
			_generateCardTypes(block->cardTypes);
			_generateRules(block->rules1);
			break;
		case GAME_BLOCK:
			_generateVariable(block->variable2);
			_generateGameFunction(block->gameFunction);
			break;
		case DESIGN_BLOCK:
			_generateVariable(block->variable3);
			_generateDesign(block->design1);
			break;
		case RULE_BLOCK:
			_generateVariable(block->variable4);
			_generateRules(block->rules2);
			break;
		default:
			logError(_logger, "The specified block type is unknown: %d", block->type);
			break;
	}
}

static void _generateRules(Rules * rules){ //TODO
	switch(rules->type){
		case STRUCTURES:
			_generateStructures(rules->structures);
			break;
		case RULE_MOVE_CARDS:
			_generateHandRef(rules->leftHandRef);
			_generateHandRef(rules->rightHandRef);
			_generateInteger(rules->constant);
			_generateRules(rules->rule);
			break;
		case RULE_LOOK_AT:
			_generateHandRef(rules->handRef);
			_generateInteger(rules->constant1);
			_generateRules(rules->rule1);
			break;
		case RULE_RESTOCK_DECK:
		case RULE_WIN_GAME:
		case RULE_ACTIVATE_SPECIAL_CARDS:
			_generateRules(rules->rule2);
			break;
		case RULE_WINNER_TYPE:
			_generateVariable(rules->variable);
			_generateRules(rules->rule3);
			break;
		case USER_RULES:
			_generateUserRules(rules->userRules);
			break;
		case TIED_RULE:
			_generateBoolean(rules->tied);
			_generateRules(rules->rule4);
			break;
		case FINISH_RULE:
			_generateBlock(rules->block);
			break;
		default:
			logError(_logger, "The specified rule type is unknown: %d", rules->type);
			break;
	}
}

static void _generateExpression(Expression * expression){ //listo
	switch(expression->type){
		case EXPR_ADD:
		case EXPR_DIV:
		case EXPR_MUL:
		case EXPR_SUB:
		case EXPR_MODULE:
			_generateExpression(expression->leftExpression);
			_generateExpression(expression->rightExpression);
			break;
		case NUMBERS:
			_generateNumbers(expression->numbers);
			break;
		case ATOMIC:
			_generateUserCard(expression->userCard);
			_generateAtomic(expression->atomic);
			break;
		default:
			logError(_logger, "The specified expression type is unknown: %d", expression->type);
			break;
	}
}

static void _generateUserRules(UserRules * userRules){ //listo
	switch(userRules->type){
		case NUMBER_ASSIG:
			_generateUserScore(userRules->userScore);
			_generateAsignations(userRules->asignations);
			_generateNumbers(userRules->numbers);
			_generateRules(userRules->rule);
			break;
		case CARD_ASSIG:
			_generateUserScore(userRules->userScore3);
			_generateAsignations(userRules->asignations3);
			_generateUserCard(userRules->userCard);
			_generateRules(userRules->rule4);
			break;
		case ARITHMETIC_ASSIG:
			_generateUserScore(userRules->userScore1);
			_generateAsignations(userRules->asignations1);
			_generateNumbers(userRules->leftNumber);
			_generateArithmetic(userRules->arithmetic);
			_generateNumbers(userRules->rightNumber);
			_generateRules(userRules->rule1);
			break;
		case PMO_ASSIG:
			_generateUserScore(userRules->userScore2);
			_generatePmOne(userRules->pmOne);
			_generateRules(userRules->rule2);
			break;
		case GETTER_ASSIG:
			_generateGetters(userRules->leftGetter);
			_generateAsignations(userRules->asignations2);
			_generateGetters(userRules->rightGetter);
			_generateRules(userRules->rule3);
			break;
		default:
			logError(_logger, "The specified userRules type is unknown: %d", userRules->type);
			break;
	}
}

static void _generateUserScore(UserScore * userScore){ //listo
	_generateUser(userScore->user);
}

static void _generateGameFunction(GameFunction * gameFunction){ //listo
	_generateInteger(gameFunction->cteNumbersOnDeck);
	_generateCardTypes(gameFunction->cardTypes);
	_generateInteger(gameFunction->cteCardsByPlayers);
	_generateInteger(gameFunction->cteRounds);
	_generateInteger(gameFunction->cteRoundTimer);		
	_generateInteger(gameFunction->cteUserStartingScore);	
	_generateInteger(gameFunction->cteMachineStartingScore);
	_generateVariable(gameFunction->varWinRoundCondition);
	_generateVariable(gameFunction->varWinRoundCondition);	
	_generateVariable(gameFunction->varWinGameCondition);	
	_generateVariable(gameFunction->varCardDesign);	
	_generateVariable(gameFunction->varBackDesign);	
	_generateBlock(gameFunction->block); 
}

static void _generateCardTypes(CardTypes * cardTypes){ //listo
	switch(cardTypes->type){
		case ONE_TYPE:
			_generateVariable(cardTypes->variable);
			break;
		case MULTIPLE_TYPE:
			_generateVariable(cardTypes->variable1);
			_generateCardTypes(cardTypes->cardType);
			break;
		default:
			logError(_logger, "The specified cardTypes type is unknown: %d", cardTypes->type);
			break;
	}
}

static void _generateUserCard(UserCard * userCard){ //listo
	_generateUser(userCard->user);
}

static void _generateNumbers(Numbers * numbers){ //listo
	switch(numbers->type){
		case CONSTANT:
			_generateInteger(numbers->constant);
			break;
		case USER_SCORE:
			_generateUserScore(numbers->userScore);
			break;
		default:
			logError(_logger, "The specified numbers type is unknown: %d", numbers->type);
			break;	
	}
}

static void _generateGetters(Getters * getters){
	switch(getters->type){
		case GETTER_LOSER:
		case GETTER_WINNER:
			_generateVariable(getters->variable);
			break;
		default:
			logError(_logger, "The specified getters type is unknown: %d", getters->type);
			break;
	}
}

static void _generateArithmetic(Arithmetic * arithmetic){ //TODO
	switch(arithmetic->type){
		case ARIT_ADD:	
		case ARIT_DIV:
		case ARIT_MUL:
		case ARIT_SUB:
		case ARIT_MODULE:
			break;
			//NO ENTIENDO BIEN PORQUE EL EN STRUCT ARITHMETIC SOLO ESTA EL TYPE
			//ESTA BIEN EL BREAK A SECAS Y QUE LA FUNCION NO HAGA NADA?? 
		default:
			logError(_logger, "The specified arithmetic type is unknown: %d", arithmetic->type);
			break;
	}
}

static void _generateAsignations(Asignations * asignations){ //TODO
	switch(asignations->type){
		case ASIG_EQUAL:
		case ASIG_ADD_EQUAL:
		case SUB_EQUAL:
		default:
		//IDEM A LO ANTERIOR
	}
}

static void _generatePmOne(PmOne * pmOne){ //TODO
	switch(pmOne->type){
		case INCREASE:
		case DECREASE:
		default:
		//IDEM A LO ANTERIOR
	}
}

static void _generateStructures(Structures * structures){ //listo
	switch(structures->type){
		case IF_STRUCTURE:
		case ELIF_STRUCTURE:
			_generateIfs(structures->conditional);
			_generateInBrakets(structures->inBrakets);
			break;
		case FOREACH_STRUCTURE:
			_generateAtomic(structures->atomic);
			_generateInBrakets(structures->inBrakets1);
			break;
		case ELSE_STRUCTURE:
			_generateInBrakets(structures->inBrakets2);
		default:
			logError(_logger, "The specified structures type is unknown: %d", structures->type);
			break;
	}
}

static void _generateInBrakets(InBrakets * inBrakets){ //listo
	switch(inBrakets->type){
		case MULTIPLE_RULES:
			_generateRules(inBrakets->leftRules);
			_generateRules(inBrakets->rightRules);
			break;
		case MULTIPLE_DESIGNS:
			_generateDesign(inBrakets->leftDesign);
			_generateDesign(inBrakets->rightDesign);
			break;
		default:
			logError(_logger, "The specified inBrakets type is unknown: %d", inBrakets->type);
			break;
	}
}

static void _generateHandRef(HandRef * handRef){
	switch(handRef->type){
		case USER:
			_generateUser(handRef->user);
			break;
		case HAND_DECK:
			_generateDeck(handRef->deck);
			break;
		default:
			logError(_logger, "The specified handRef type is unknown: %d", handRef->type);
			break;
	}
}

static void _generateDeck(Deck * deck){ //no se que onda esta
	_generateDeck(deck->deck);
}

static void _generateUser(User * user){ //TODO
	switch(user->type){
		case USER_PLAYER:
		case USER_IDENTIFIER:
		default:
		//IDEM A LAS ANTERIORES
	}
}

static void _generateIfs(Ifs * ifs){
	switch(ifs->type){
		case INIF:
			_generateInIf(ifs->inIf);
			break;
		case AND_IF:
		case OR_IF:
			_generateInIf(ifs->leftInIf);
			_generateInIf(ifs->rightInIf);
			break;
		case TIED_IF:
			_generateBoolean(ifs->tied);
			break;	
		default:
			logError(_logger, "The specified ifs type is unknown: %d", ifs->type);
			break;
	}
}

static void _generateInIf(InIf * inIf){ //TODO
	switch(inIf->type){
		case TYPE_IF:
			_generateComparison(inIf->comparison1);
			_generateVariable(inIf->variable);
			break;
		case ACTIVATE_SPECIAL_CARDS_IF:
		//IDEM A LOS ANTERIORES
		case EXPRESSION_IF:
			_generateExpression(inIf->leftExpression);
			_generateComparison(inIf->comparison2);
			_generateExpression(inIf->rightExpression);
			break;
		default:
			logError(_logger, "The specified inIf type is unknown: %d", inIf->type);
			break;
	}
}

static void _generateComparison(Comparison * comparison){ //TODO
	switch(comparison->type){
		case COMP_GREATER:
		case COMP_LOWER:
		case COMP_EQUAL_EQUAL:
		case COMP_GREATER_OR_EQUAL:
		case COMP_LOWER_OR_EQUAL:
		case COMP_DIFERENT:
		default:
		//IDEM A LOS ANTERIORES
	}
}

static void _generateAtomic(Atomic * atomic){ //TODO
	switch(atomic->type){
		case ATOMIC_VALUE:
		case ATOMIC_TYPE:
		//IDEM A LOS ANTERIORES
		default:
	}
}

static void _generateDesign(Design * design){
	switch(design->type){
		case ROUND_BORDERS_DESIGN:
			_generateInteger(design->constant);
			_generateDesign(design->design2);
			break;
		case COLOR_BORDERS_DESIGN:
		case BACKGROUND_COLOR_DESIGN:
			_generateVariable(design->variable);
			_generateDesign(design->design1);
			break;
		case FINISHED_DESIGN:
			_generateBlock(design->block);
			break;
		case STRUCTURES_DESIGN:
			_generateStructures(design->structures);
			break;
		default:
			logError(_logger, "The specified design type is unknown: %d", design->type);
			break;
	}
}

static void _generateBoolean(bool boolean){

}

static void _generateVariable(char * variable){

}

static void _generateInteger(int constant){

}

/**
 * Converts and expression type to the proper character of the operation
 * involved, or returns '\0' if that's not possible.
 */
//static const char _expressionTypeToCharacter(const ExpressionType type) {
//	switch (type) {
//		case ADDITION: return '+';
//		case DIVISION: return '/';
//		case MULTIPLICATION: return '*';
//		case SUBTRACTION: return '-';
//		default:
//			logError(_logger, "The specified expression type cannot be converted into character: %d", type);
//			return '\0';
//	}
//}

/**
 * Generates the output of a constant.
 */
//static void _generateConstant(const unsigned int indentationLevel, Constant * constant) {
//	_output(indentationLevel, "%s", "[ $C$, circle, draw, black!20\n");
//	_output(1 + indentationLevel, "%s%d%s", "[ $", constant->value, "$, circle, draw ]\n");
//	_output(indentationLevel, "%s", "]\n");
//}

/**
 * Creates the prologue of the generated output, a Latex document that renders
 * a tree thanks to the Forest package.
 *
 * @see https://ctan.dcc.uchile.cl/graphics/pgf/contrib/forest/forest-doc.pdf
 */
static void _generatePrologue(void) {
	_output(0, "%s",
		"\\documentclass{standalone}\n\n"
		"\\usepackage[utf8]{inputenc}\n"
		"\\usepackage[T1]{fontenc}\n"
		"\\usepackage{amsmath}\n"
		"\\usepackage{forest}\n"
		"\\usepackage{microtype}\n\n"
		"\\begin{document}\n"
		"    \\centering\n"
		"    \\begin{forest}\n"
		"        [ \\text{$=$}, circle, draw, purple\n"
	);
}

/**
 * Generates an indentation string for the specified level.
 */
static char * _indentation(const unsigned int level) {
	return indentation(_indentationCharacter, level, _indentationSize);
}

/**
 * Outputs a formatted string to standard output.
 */
static void _output(const unsigned int indentationLevel, const char * const format, ...) {
	va_list arguments;
	va_start(arguments, format);
	char * indentation = _indentation(indentationLevel);
	char * effectiveFormat = concatenate(2, indentation, format);
	vfprintf(stdout, effectiveFormat, arguments);
	free(effectiveFormat);
	free(indentation);
	va_end(arguments);
}

/** PUBLIC FUNCTIONS */

void generate(CompilerState * compilerState) {
	logDebugging(_logger, "Generating final output...");
	_generatePrologue();
	_generateProgram(compilerState->abstractSyntaxtTree);
	_generateEpilogue(compilerState->value);
	logDebugging(_logger, "Generation is done.");
}
