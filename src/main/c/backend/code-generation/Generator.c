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

static void _generateBlock(Block * block){
	switch(block->type){
		case VALUE_BLOCK:
			_generateVariable(block->variable);
			_generateInteger(block->constant);
			_generateRule(block->rules);
			break;
		case TYPE_BLOCK:
			_generateVariable(block->variable1);
			_generateCardTypes(block->cardTypes);
			_generateRule(block->rules1);
			break;
		case GAME_BLOCK:
		case DESIGN_BLOCK:
		case RULE_BLOCK:
		default:
			logError(_logger, "The specified block type is unknown: %d", block->type);
			break;
	}
}

static void _generateRules(Rules * rules){
	switch(rules->type){
		case STRUCTURES:
		case RULE_MOVE_CARDS:
		case RULE_LOOK_AT:
		case RULE_WINNER_TYPE:
		case USER_RULES:
		case TIED_RULE:
		case FINISH_RULE:
			_generateBlock(rules->block);
			break;
		default:
			logError(_logger, "The specified rule type is unknown: %d", rules->type);
			break;
	}
}

static void _generateExpression(Expression * expression){
	switch(expression->type){
		case ARIT_ADD:
		case ARIT_DIV:
		case ARIT_MUL:
		case ARIT_SUB:
		case ARIT_MODULE:
		case NUMBERS:
		case ATOMIC:
		default:
			logError(_logger, "The specified expression type is unknown: %d", expression->type);
			break;
	}
}

static void _generateUserRules(UserRules * userRules){
	switch(userRules->type){
		case NUMBER_ASSIG:
		case CARD_ASSIG:
		case ARITHMETIC_ASSIG:
		case PMO_ASSIG:
		case GETTER_ASSIG:
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

static void _generateCardTypes(CardTypes * cardTypes){
	switch(cardTypes->type){
		case ONE_TYPE:
		case MULTIPLE_TYPE:
		default:
	}
}

static void _generateUserCard(UserCard * userCard){ //listo
	_generateUser(userCard->user);
}

static void _generateNumbers(Numbers * numbers){
	switch(numbers->type){
		case CONSTANT:
		case USER_SCORE:
		default:
	}
}

static void _generateGetters(Getters * getters){
	switch(getters->type){
		case GETTER_LOSER:
		case GETTER_WINNER:
		default:
	}
}

static void _generateArithmetic(Arithmetic * arithmetic){
	switch(arithmetic->type){
		case ARIT_ADD:	
		case ARIT_DIV:
		case ARIT_MUL:
		case ARIT_SUB:
		case ARIT_MODULE:
		default:
	}
}

static void _generateAsignations(Asignations * asignations){
	switch(asignations->type){
		case ASIG_EQUAL:
		case ASIG_ADD_EQUAL:
		case SUB_EQUAL:
		default:
	}
}

static void _generatePmOne(PmOne * pmOne){
	switch(pmOne->type){
		case INCREASE:
		case DECREASE:
		default:
	}
}

static void _generateStructures(Structures * structures){
	switch(structures->type){
		case IF_STRUCTURE:
		case FOREACH_STRUCTURE:
		case ELIF_STRUCTURE:
		case ELSE_STRUCTURE:
		default:
	}
}

static void _generateInBrakets(InBrakets * inBrakets){
	switch(inBrakets->type){
		case MULTIPLE_RULES:
		case MULTIPLE_DESIGNS:
		default:
	}
}

static void _generateHandRef(HandRef * handRef){
	switch(handRef->type){
		case USER:
		case HAND_DECK:
		default:
	}
}

static void _generateDeck(Deck * deck){ //no se que onda esta
	_generateDeck(deck->deck);
}

static void _generateUser(User * user){
	switch(user->type){
		case USER_PLAYER:
		case USER_IDENTIFIER:
		default:
	}
}

static void _generateIfs(Ifs * ifs){
	switch(ifs->type){
		case INIF:
		case AND_IF:
		case OR_IF:
		case TIED_IF:
		default:
	}
}

static void _generateInIf(InIf * inIf){
	switch(inIf->type){
		case TYPE_IF:
		case ACTIVATE_SPECIAL_CARDS_IF:
		case EXPRESSION_IF:
		default:
	}
}

static void _generateComparison(Comparison * comparison){
	switch(comparison->type){
		case COMP_GREATER:
		case COMP_LOWER:
		case COMP_EQUAL_EQUAL:
		case COMP_GREATER_OR_EQUAL:
		case COMP_LOWER_OR_EQUAL:
		case COMP_DIFERENT:
		default:
	}
}

static void _generateAtomic(Atomic * atomic){
	switch(atomic->type){
		case ATOMIC_VALUE:
		case ATOMIC_TYPE:
		default:
	}
}

static void _generateDesign(Design * design){
	switch(design->type){
		case ROUND_BORDERS_DESIGN:
		case COLOR_BORDERS_DESIGN:
		case BACKGROUND_COLOR_DESIGN:
		case FINISHED_DESIGN:
		case STRUCTURES_DESIGN:
		default:
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
