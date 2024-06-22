#include "Generator.h"

/* MODULE INTERNAL STATE */

const char _indentationCharacter = ' ';
const char _indentationSize = 4;
static Logger * _logger = NULL;

FILE * file;

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

static void _generateProgram(Program * program) { //listo
	_generateBlock(program->block);
}

static void _generateBlock(Block * block){
	switch(block->type){
		case VALUE_BLOCK:
			_output(0, "%s", block->variable);
			_output(0, "%s", " for value ");
			_output(0, "%d", block->constant);
			_output(0, "%s", ":\n");
			_generateRules(block->rules);
			break;
		case TYPE_BLOCK:
			_output(0, "%s", block->variable1);
			_output(0, "%s", " for type ");
			_generateCardTypes(block->cardTypes);
			_output(0, "%s", ":\n");
			_generateRules(block->rules1);
			break;
		case GAME_BLOCK:
			_output(0, "%s", block->variable2);
			_output(0, "%s", " game has:\n");
			_generateGameFunction(block->gameFunction);
			break;
		case DESIGN_BLOCK:
			_output(0, "%s", block->variable3);
			_generateRules(block->rules3);
			break;
		case RULE_BLOCK:
			_output(0, "%s", block->variable4);
			_output(0, "%s", " for game:\n");
			_generateRules(block->rules2);
			break;
		default:
			logError(_logger, "The specified block type is unknown: %d", block->type);
			break;
	}
}

static void _generateRules(Rules * rules){ 
	if(rules != NULL){
		switch(rules->type){
			case STRUCTURES:
				_generateStructures(rules->structures);
				break;
			case RULE_MOVE_CARDS:
				_output(1, "%s", "MoveCards(");
				_generateHandRef(rules->leftHandRef);
				_output(0, "%s", ", ");
				_generateHandRef(rules->rightHandRef);
				_output(0, "%s", ", ");
				_output(0, "%d", rules->constant);
				_output(0, "%s", ")");
				_generateRules(rules->rule);
				break;
			case RULE_LOOK_AT:
				_generateHandRef(rules->handRef);
				_output(0, "%d", rules->constant1);
				_generateRules(rules->rule1);
				break;
			case RULE_RESTOCK_DECK:
			case RULE_WIN_GAME:
			case RULE_ACTIVATE_SPECIAL_CARDS:
				_output(1, "%s", "ActivateSpecialCards()");
				_generateRules(rules->rule2);
				break;
			case RULE_WINNER_TYPE:
				_output(0, "%s", rules->variable);
				_generateRules(rules->rule3);
				break;
			case ROUND_BORDERS_DESIGN:
				//completar
				break;
			case COLOR_BORDERS_DESIGN:
			case BACKGROUND_COLOR_DESIGN:
				//completar
				break;
			case USER_RULES:
				_generateUserRules(rules->userRules);
				break;
			case TIED_RULE:
				_output(0, "%s", "tied = ");
				_output(0, "%s", rules->tied? "true" : "false");
				//_generateBoolean(rules->tied);
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
		case EXPR_VALUE:
			_output(0, "%s", "value");
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
	_output(1, "%s", "NumbersOnDeck(");
	_output(0, "%d", gameFunction->cteNumbersOnDeck);
	_output(0, "%s", ")\n");
	_output(1, "%s", "TypesOfCards(");
	_output(0, "%s", gameFunction->cardTypes);
	_output(0, "%s", ")\n");
	_output(1, "%s", "CardsByPlayer(");
	_output(0, "%d", gameFunction->cteCardsByPlayers);
	_output(0, "%s", ")\n");
	_output(1, "%s", "Rounds(");
	_output(0, "%d", gameFunction->cteRounds);
	_output(0, "%s", ")\n");
	_output(1, "%s", "RoundsTimer(");
	_output(0, "%d", gameFunction->cteRoundTimer);	
	_output(0, "%s", ")\n");	
	_output(1, "%s", "StartingScore(");
	_output(0, "%d", gameFunction->cteUserStartingScore);	
	_output(0, "%s", ", ");
	_output(0, "%d", gameFunction->cteMachineStartingScore);
	_output(0, "%s", ")\n");
	_output(1, "%s", "WinRoundCondition(");
	_output(0, "%s", gameFunction->varWinRoundCondition);
	_output(0, "%s", ")\n");
	_output(1, "%s", "WinGameCondition(");	
	_output(0, "%s", gameFunction->varWinGameCondition);	
	_output(0, "%s", ")\n");
	_output(1, "%s", "CardsDesign(");
	_output(0, "%s", gameFunction->varCardDesign);
	_output(0, "%s", ")\n");	
	_output(1, "%s", "BackgroundDesign(");
	_output(0, "%s", gameFunction->varBackDesign);	
	_output(0, "%s", ")\n");
	_generateBlock(gameFunction->block); 
}

static void _generateCardTypes(CardTypes * cardTypes){ //listo
	switch(cardTypes->type){
		case ONE_TYPE:
			_output(0, "%s", cardTypes->variable);
			break;
		case MULTIPLE_TYPE:
			_output(0, "%s ,", cardTypes->variable1);
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
			_output(0, "%d", numbers->constant);
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
			break;
		case GETTER_WINNER:
			_output(0, "%s", getters->variable);
			break;
		default:
			logError(_logger, "The specified getters type is unknown: %d", getters->type);
			break;
	}
}

static void _generateArithmetic(Arithmetic * arithmetic){ 
	switch(arithmetic->type){
		case ARIT_ADD:	
			break;
			// return '+';
		case ARIT_DIV:
			break;
			// return '/';
		case ARIT_MUL:
			break;
			// return '*';
		case ARIT_SUB:
			break;
			// return '-';
		case ARIT_MODULE:
			break;
			// return '%';
		default:
			logError(_logger, "The specified arithmetic type is unknown: %d", arithmetic->type);
			break;
	}
}

static void _generateAsignations(Asignations * asignations){ 
	switch(asignations->type){
		case ASIG_EQUAL:
			break;
			// return "=";
		case ASIG_ADD_EQUAL:
			break;
			// return "+=";
		case SUB_EQUAL:
			break;
			// return "-=";
		default:
			logError(_logger, "The specified asignations type is unknown: %d", asignations->type);
			break;
	}
}

static void _generatePmOne(PmOne * pmOne){ 
	switch(pmOne->type){
		case INCREASE:
			break;
			// return "++";
		case DECREASE:
			break;
			// return "--";
		default:
			logError(_logger, "The specified pmOne type is unknown: %d", pmOne->type);
			break;	
	}
}

static void _generateStructures(Structures * structures){ //listo
	switch(structures->type){
		case IF_STRUCTURE:
			_output(1, "%s", "if(");
			_generateIfs(structures->conditional);
			_output(0, "%s", "){\n");
			_generateInBrakets(structures->inBrakets);
			break;
		case ELIF_STRUCTURE:
			_output(1, "%s", "elif(");
			_generateIfs(structures->conditional);
			_output(0, "%s", "){\n");
			_generateInBrakets(structures->inBrakets);
			break;
		case FOREACH_STRUCTURE:
			_output(1, "%s", "foreach(");
			_generateAtomic(structures->atomic);
			_output(0, "%s", "){\n");
			_generateInBrakets(structures->inBrakets1);
			break;
		case ELSE_STRUCTURE:
			_output(1, "%s", "else{\n");
			_generateInBrakets(structures->inBrakets2);
			break;
		default:
			logError(_logger, "The specified structures type is unknown: %d", structures->type);
			break;
	}
}

static void _generateInBrakets(InBrakets * inBrakets){ //listo
	_generateRules(inBrakets->leftRules);
	_output(1, "%s", "\n}\n");
	_generateRules(inBrakets->rightRules);
}

static void _generateHandRef(HandRef * handRef){
	switch(handRef->type){
		case USER:
			_generateUser(handRef->user);
			_output(0, "%s", ".Hand");
			break;
		case HAND_DECK:
			_generateDeck(handRef->deck);
			break;
		default:
			logError(_logger, "The specified handRef type is unknown: %d", handRef->type);
			break;
	}
}

static void _generateDeck(Deck * deck){ 
	_output(0, "%s", "Deck");
}

static void _generateUser(User * user){ //TODO
	switch(user->type){
		case USER_PLAYER:
			_output(0, "%s", "Playing");
			break;
		case USER_IDENTIFIER:
			_output(0, "%s", "Machine");
			break;
		default:
			logError(_logger, "The specified user type is unknown: %d", user->type);
			break;
	}
}

static void _generateIfs(Ifs * ifs){
	switch(ifs->type){
		case INIF:
			_generateInIf(ifs->inIf);
			break;
		case AND_IF:
			_generateInIf(ifs->leftInIf);
			_output(0, "%s", " && ");
			_generateInIf(ifs->rightInIf);
			break;
		case OR_IF:
			_generateInIf(ifs->leftInIf);
			_output(0, "%s", " || ");
			_generateInIf(ifs->rightInIf);
			break;
		case TIED_IF:
			_output(0, "%s", ifs->tied? "true" : "false");
			break;	
		default:
			logError(_logger, "The specified ifs type is unknown: %d", ifs->type);
			break;
	}
}

static void _generateInIf(InIf * inIf){ //TODO
	switch(inIf->type){
		case TYPE_IF:
			_output(0, "%s", "type ");
			_generateComparison(inIf->comparison1);
			_output(0, "%s", inIf->variable);
			break;
		case ACTIVATE_SPECIAL_CARDS_IF:
			_output(0, "%s", "SpecialCardsOnPlay()");
			break;
		case EXPRESSION_IF:
			_generateExpression(inIf->leftExpression);  //aca estoy
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
			_output(0, "%s", " == ");
			break;
		case COMP_GREATER_OR_EQUAL:
		case COMP_LOWER_OR_EQUAL:
		case COMP_DIFERENT:
			break;
		default:
			logError(_logger, "The specified inIf type is unknown: %d", comparison->type);
			break;
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

static void _generateBoolean(bool boolean){
	_output(1, "%s", "boolean");
	//printf("boolean\n"); 
}

// static void _generateVariable(char * variable){
// 	_output(1, "%s", "variable de output\n");
// 	printf("variable\n"); 
// }

// static void _generateInteger(int constant){
// 	_output(1, "%s", "INTEGRER de output\n");
// 	printf("INTEGRER\n"); 
// }

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
	fflush(stdout);
	free(effectiveFormat);
	free(indentation);
	va_end(arguments);
}

/**
 * Creates the prologue of the generated output, a Latex document that renders
 * a tree thanks to the Forest package.
 *
 * @see https://ctan.dcc.uchile.cl/graphics/pgf/contrib/forest/forest-doc.pdf
 */
static void _generatePrologue(void) 
{

}

/**
 * Creates the epilogue of the generated output, that is, the final lines that
 * completes a valid Latex document.
 */
static void _generateEpilogue(void) 
{

}

/** PUBLIC FUNCTIONS */

void generate(CompilerState * compilerState) {
	logDebugging(_logger, "Generating final output...");
	//file = fopen("MyGdxGame.java", "w");
	_generatePrologue();
	_generateProgram(compilerState->abstractSyntaxtTree);
	_generateEpilogue();
	//fclose(file);
	logDebugging(_logger, "Generation is done.");
}
