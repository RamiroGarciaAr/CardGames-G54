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

static void _generateBlock(Block * block){ //listo
	switch(block->type){
		case VALUE_BLOCK:
			_output(0, "%s", block->variable);
			_output(0, "%s", " for value ");
			_output(0, "%d", block->constant);
			_output(0, "%s", ":\n");
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
			_generateRules(block->rules3);
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

static void _generateArithmetic(Arithmetic * arithmetic){ 
	switch(arithmetic->type){
		case ARIT_ADD:	
			_output(0, "%s", "+");
			break;
		case ARIT_DIV:
			_output(0, "%s", "/");
			break;
		case ARIT_MUL:
			_output(0, "%s", "*");
			break;
		case ARIT_SUB:
			_output(0, "%s", "-");
			break;
		case ARIT_MODULE:
			_output(0, "%s", "%");
			break;
		default:
			logError(_logger, "The specified arithmetic type is unknown: %d", arithmetic->type);
			break;
	}
}

static void _generateAsignations(Asignations * asignations){ //Creo que esta
	switch(asignations->type){
		case ASIG_EQUAL:
			_output(0, "%s", "=");
			break;
		case ASIG_ADD_EQUAL:
			_output(0, "%s", "+=");
			break;
		case SUB_EQUAL:
			_output(0, "%s", "-=");
			break;
		default:
			logError(_logger, "The specified asignations type is unknown: %d", asignations->type);
			break;
	}
}

static void _generatePmOne(PmOne * pmOne){ 
	switch(pmOne->type){
		case INCREASE:
			_output(0, "%s", "++");
			break;
		case DECREASE:
			_output(0, "%s", "--");
			break;
		default:
			logError(_logger, "The specified pmOne type is unknown: %d", pmOne->type);
			break;	
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
	_generateRules(inBrakets->leftRules);
	_generateRules(inBrakets->rightRules);
}

static void _generateHandRef(HandRef * handRef){
	switch(handRef->type){
		case USER:
			_generateUser(handRef->user);
			_output(0, "%s", ".getCardsInHand()");
			break;
		case HAND_DECK:
			_generateDeck(handRef->deck);
			_output(0, "%s", ".getDeck()");
			break;
		default:
			logError(_logger, "The specified handRef type is unknown: %d", handRef->type);
			break;
	}
}

static void _generateDeck(Deck * deck){  
	_output(0, "%s", "deck");
}

static void _generateUser(User * user){ //TODO
	switch(user->type){
		case USER_PLAYER:
			_output(0, "%s", "player");
			break;
		case USER_IDENTIFIER:
			_output(0, "%s", "machine");
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
	switch (comparison->type) {
	case COMP_GREATER:
		_output(1,"%s","<");
		break;
	case COMP_LOWER:
		_output(1,"%s",">");
		break;
	case COMP_EQUAL_EQUAL:
		_output(1,"%s","==");
		break;
	case COMP_GREATER_OR_EQUAL:
		_output(1,"%s",">=");
		break;
	case COMP_LOWER_OR_EQUAL:
		_output(1,"%s","<=");
		break;
	case COMP_DIFERENT:
		_output(1,"%s","!=");
		break;
	default:
		_output(1,"%s","!");
	}
}

static void _generateAtomic(Atomic * atomic){ //TODO
	switch (atomic->type) {
	case ATOMIC_VALUE:
	case ATOMIC_TYPE:
		//IDEM A LOS ANTERIORES
	default:
		;
	}
}

static void _generateBoolean(bool boolean){
	_output(1, "%s", "boolean\n");
	printf("boolean\n"); 
}

static void _generateVariable(char * variable){
	_output(1, "%s", "variable de output\n");
	printf("variable\n"); 
}

static void _generateInteger(int constant){
	_output(1, "%s", "INTEGRER de output\n");
	printf("INTEGRER\n"); 
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
	/*
	fprintf(file,"=================================PROLOGUE========================================");
	fprintf(file, "package com.mygdx.game;\n\n");
    fprintf(file, "import com.badlogic.gdx.ApplicationAdapter;\n");
    fprintf(file, "import com.badlogic.gdx.Gdx;\n");
    fprintf(file, "import com.badlogic.gdx.audio.Sound;\n");
    fprintf(file, "import com.badlogic.gdx.files.FileHandle;\n");
    fprintf(file, "import com.badlogic.gdx.graphics.Color;\n");
    fprintf(file, "import com.badlogic.gdx.graphics.GL20;\n");
    fprintf(file, "import com.badlogic.gdx.graphics.Texture;\n");
    fprintf(file, "import com.badlogic.gdx.graphics.g2d.BitmapFont;\n");
    fprintf(file, "import com.badlogic.gdx.graphics.g2d.Sprite;\n");
    fprintf(file, "import com.badlogic.gdx.graphics.g2d.SpriteBatch;\n");
    fprintf(file, "import com.badlogic.gdx.graphics.glutils.ShapeRenderer;\n");
    fprintf(file, "import java.util.Random;\n\n");
    fprintf(file, "public class MyGdxGame extends ApplicationAdapter {\n");
    fprintf(file, "    private SpriteBatch batch;\n");
    fprintf(file, "    private BitmapFont font;\n");
    fprintf(file, "    private ShapeRenderer shapeRenderer;\n");
    fprintf(file, "    private GameManager gameManager;\n");
    fprintf(file, "    private Player player;\n");
    fprintf(file, "    private AI machine;\n");
    fprintf(file, "    private float mouseX, mouseY;\n");
    fprintf(file, "    private Sound placementSound, highlightSound;\n");
    fprintf(file, "    private static final int NUM_CARDS_IN_HAND = 3;\n");
    fprintf(file, "    private boolean mouseOverHighlightedCard = false;\n");
    fprintf(file, "    Texture backgroundTexture = null;\n");
    fprintf(file, "    private boolean gameEnded = false;\n");
    fprintf(file, "    private boolean playerWon;\n");
    fprintf(file, "}\n");
*/
}

/**
 * Creates the epilogue of the generated output, that is, the final lines that
 * completes a valid Latex document.
 */
static void _generateEpilogue(void) 
{
	// fprintf(file,"=================================EPILOGUE========================================");
    // fprintf(file, "    private void LoadRandomBackgroundImage() {\n");
    // fprintf(file, "        FileHandle folder = Gdx.files.internal(\"assets/Backgrounds/\");\n");
    // fprintf(file, "        if (folder.exists() && folder.isDirectory()) {\n");
    // fprintf(file, "            FileHandle[] backgrounds = folder.list();\n");
    // fprintf(file, "            if (backgrounds.length > 1) {\n");
    // fprintf(file, "                int index = new Random().nextInt(backgrounds.length);\n");
    // fprintf(file, "                backgroundTexture = new Texture(backgrounds[index]);\n");
    // fprintf(file, "            } else backgroundTexture = new Texture(backgrounds[0]);\n");
    // fprintf(file, "        } else {\n");
    // fprintf(file, "            Gdx.app.error(\"TextureManager\", \"Backgrounds directory is missing or not found.\");\n");
    // fprintf(file, "        }\n");
    // fprintf(file, "    }\n\n");

    // fprintf(file, "    private void LoadSounds() {\n");
    // fprintf(file, "        FileHandle SFXfolder = Gdx.files.internal(\"assets/Sounds/SFX\");\n");
    // fprintf(file, "        if (SFXfolder.exists() && SFXfolder.isDirectory()) {\n");
    // fprintf(file, "            placementSound = Gdx.audio.newSound(SFXfolder.child(\"card_impact_sfx.wav\"));\n");
    // fprintf(file, "            highlightSound = Gdx.audio.newSound(SFXfolder.child(\"card_highlight_sfx.wav\"));\n");
    // fprintf(file, "        }\n");
    // fprintf(file, "    }\n\n");

    // fprintf(file, "    private void highlightCardUnderMouse() {\n");
    // fprintf(file, "        float mouseX = Gdx.input.getX();\n");
    // fprintf(file, "        float mouseY = Gdx.graphics.getHeight() - Gdx.input.getY(); // Invertir el eje Y\n\n");

    // fprintf(file, "        shapeRenderer.begin(ShapeRenderer.ShapeType.Line);\n");
    // fprintf(file, "        shapeRenderer.setColor(Color.YELLOW); // Definir el color una vez fuera del bucle\n\n");

    // fprintf(file, "        boolean highlightFound = false;\n\n");

    // fprintf(file, "        for (Card card : player.getCardsInHand()) {\n");
    // fprintf(file, "            if (card.isTouched(mouseX, mouseY)) {\n");
    // fprintf(file, "                card.highlightCard(shapeRenderer); // Resaltar la carta sin llamar a begin/end dentro del bucle\n");
    // fprintf(file, "                highlightFound = true;\n");
    // fprintf(file, "            }\n");
    // fprintf(file, "        }\n");
    // fprintf(file, "        if (highlightFound && !mouseOverHighlightedCard && highlightSound != null) {\n");
    // fprintf(file, "            highlightSound.play(0.25f);\n");
    // fprintf(file, "            mouseOverHighlightedCard = true;\n");
    // fprintf(file, "        } else if (!highlightFound) {\n");
    // fprintf(file, "            mouseOverHighlightedCard = false;\n");
    // fprintf(file, "        }\n\n");

    // fprintf(file, "        shapeRenderer.end();\n");
    // fprintf(file, "    }\n\n");

    // fprintf(file, "    private void drawPlayerCardsBatch(Player player, float startX, float startY) {\n");
    // fprintf(file, "        float cardSpacing = 20;\n");
    // fprintf(file, "        float totalWidth = player.getCardsInHand().size() * (Card.CARD_WIDTH + cardSpacing) - cardSpacing;\n");
    // fprintf(file, "        float currentX = startX + (Gdx.graphics.getWidth() - totalWidth) / 2;\n\n");

    // fprintf(file, "        for (Card card : player.getCardsInHand()) {\n");
    // fprintf(file, "            card.setCardPosition(currentX, startY);\n");
    // fprintf(file, "            card.drawCardBatch(batch, font);\n");
    // fprintf(file, "            currentX += Card.CARD_WIDTH + cardSpacing;\n");
    // fprintf(file, "        }\n");
    // fprintf(file, "    }\n\n");

    // fprintf(file, "    private void drawPlayerCardsShape(Player player, float startX, float startY) {\n");
    // fprintf(file, "        float cardSpacing = 20;\n");
    // fprintf(file, "        float totalWidth = player.getCardsInHand().size() * (Card.CARD_WIDTH + cardSpacing) - cardSpacing;\n");
    // fprintf(file, "        float currentX = startX + (Gdx.graphics.getWidth() - totalWidth) / 2;\n\n");

    // fprintf(file, "        for (Card card : player.getCardsInHand()) {\n");
    // fprintf(file, "            card.setCardPosition(currentX, startY);\n");
    // fprintf(file, "            //card.drawCardShape(shapeRenderer);\n");
    // fprintf(file, "            currentX += Card.CARD_WIDTH + cardSpacing;\n");
    // fprintf(file, "        }\n");
    // fprintf(file, "    }\n\n");

    // fprintf(file, "    private Card getSelectedCard(float mouseX, float mouseY) {\n");
    // fprintf(file, "        for (Card card : player.getCardsInHand()) {\n");
    // fprintf(file, "            if (card.isTouched(mouseX, mouseY)) return card;\n");
    // fprintf(file, "        }\n");
    // fprintf(file, "        return null;\n");
    // fprintf(file, "    }\n\n");

    // fprintf(file, "    private void drawScores() {\n");
    // fprintf(file, "        String playerScoreText = \"Player Score: \" + player.getScore();\n");
    // fprintf(file, "        String machineScoreText = \"Machine Score: \" + machine.getScore();\n");
    // fprintf(file, "        font.draw(batch, playerScoreText, 50, 50);\n");
    // fprintf(file, "        font.draw(batch, machineScoreText, 50, 100);\n");
    // fprintf(file, "    }\n\n");

    // fprintf(file, "    @Override\n");
    // fprintf(file, "    public void dispose() {\n");
    // fprintf(file, "        batch.dispose();\n");
    // fprintf(file, "        shapeRenderer.dispose();\n");
    // fprintf(file, "        font.dispose();\n");
    // fprintf(file, "    }\n");
    // fprintf(file, "}\n\n");

    // fprintf(file, "class CardComparator {\n");
    // fprintf(file, "    public static int compare(Card o1, Card o2) {\n");
    // fprintf(file, "        if (o1.getType().canBeat(o2.getType())) {\n");
    // fprintf(file, "            return 1;\n");
    // fprintf(file, "        } else if (o2.getType().canBeat(o1.getType())) {\n");
    // fprintf(file, "            return -1;\n");
    // fprintf(file, "        } else {\n");
    // fprintf(file, "            return o1.compareTo(o2);\n");
    // fprintf(file, "        }\n");
    // fprintf(file, "    }\n");
    // fprintf(file, "}\n");
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
