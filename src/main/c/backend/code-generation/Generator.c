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
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< Updated upstream
				_generateBoolean(rules->tied);
=======
				_output(0, "%s", "tied = ");
				_output(0, "%s", rules->tied? "true" : "false");
>>>>>>> Stashed changes
=======
				_generateBoolean(rules->tied);
>>>>>>> parent of 32fdf70 (Solved last generator errors)
=======
				_generateBoolean(rules->tied);
>>>>>>> parent of 32fdf70 (Solved last generator errors)
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
			_output(0, "%s", ifs->tied);
			//_generateBoolean(ifs->tied);
			break;	
		default:
			logError(_logger, "The specified ifs type is unknown: %d", ifs->type);
			break;
	}
}

static void _generateInIf(InIf * inIf){ //TODO
	switch(inIf->type){
		case TYPE_IF:
			_output(0, "%s", "type");
			_generateComparison(inIf->comparison1);
			_output(0, "%s", inIf->variable);
			break;
		case ACTIVATE_SPECIAL_CARDS_IF:
			_output(0, "%s", "ActivateSpecialCards()");
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
	switch (atomic->type) {
	case ATOMIC_VALUE:
	case ATOMIC_TYPE:
		//IDEM A LOS ANTERIORES
<<<<<<< Updated upstream
	default:
		;
=======
			break;
		default:
			break;
>>>>>>> Stashed changes
	}
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

/**
 * Creates the prologue of the generated output, a Latex document that renders
 * a tree thanks to the Forest package.
 *
 * @see https://ctan.dcc.uchile.cl/graphics/pgf/contrib/forest/forest-doc.pdf
 */
static void _generatePrologue(void) 
{
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< Updated upstream
=======
>>>>>>> parent of 32fdf70 (Solved last generator errors)
=======
>>>>>>> parent of 32fdf70 (Solved last generator errors)
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
<<<<<<< HEAD
<<<<<<< HEAD
=======
	_output(0, "%s", "package com.mygdx.game;\n");
	_output(0, "%s", "import com.badlogic.gdx.ApplicationAdapter;\n");
	_output(0, "%s", "import com.badlogic.gdx.Gdx;\n");
	_output(0, "%s", "import com.badlogic.gdx.audio.Sound;\n");
	_output(0, "%s", "import com.badlogic.gdx.files.FileHandle;\n");
	_output(0, "%s", "import com.badlogic.gdx.graphics.*;\n");
	_output(0, "%s", "import com.badlogic.gdx.graphics.g2d.BitmapFont;\n");
	_output(0, "%s", "import com.badlogic.gdx.graphics.g2d.Sprite;\n");
	_output(0, "%s", "import com.badlogic.gdx.graphics.g2d.SpriteBatch;\n");
	_output(0, "%s", "import com.badlogic.gdx.graphics.glutils.ShapeRenderer;\n");
	_output(0, "%s", "import com.badlogic.gdx.scenes.scene2d.Stage;\n");
	_output(0, "%s", "import com.badlogic.gdx.utils.viewport.FitViewport;\n");
	_output(0, "%s", "import com.badlogic.gdx.utils.viewport.Viewport;\n");
	_output(0, "%s", "import com.mygdx.game.Cards.Card;\n");
	_output(0, "%s", "import com.mygdx.game.Cards.Colors;\n");
	_output(0, "%s", "import com.mygdx.game.Cards.Deck;\n");
	_output(0, "%s", "import com.mygdx.game.Cards.MoveCardsAction;\n");
	_output(0, "%s", "import com.mygdx.game.Managers.MusicPlayer;\n");
	_output(0, "%s", "import com.mygdx.game.Players.AI;\n");
	_output(0, "%s", "import com.mygdx.game.Players.Player;\n");
	_output(0, "%s", "import java.util.ArrayList;\n");
	_output(0, "%s", "import java.util.Random;\n\n");
	_output(0, "%s", "public class MyGdxGame extends ApplicationAdapter{\n");
	_output(0, "%s", "    private SpriteBatch batch;\n");
	_output(0, "%s", "    private BitmapFont font;\n");
	_output(0, "%s", "    private ShapeRenderer shapeRenderer;\n");
	_output(0, "%s", "    private Sound placementSound,highlightSound;\n");
	_output(0, "%s", "    Texture backgroundTexture = null;\n");
	_output(0, "%s", "    private Viewport viewport;\n");
	_output(0, "%s", "    private Camera camera;\n");
	_output(0, "%s", "    private Stage stage;\n\n");
	_output(0, "%s", "    private GameManager gameManager;\n");
	_output(0, "%s", "    private Player player;\n");
	_output(0, "%s", "    private AI machine;\n");
	_output(0, "%s", "    private boolean mouseOverHighlightedCard = false;\n\n");
	_output(0, "%s", "    @Override\n");
	_output(0, "%s", "    public void create() {\n");
	_output(0, "%s", "        camera = new PerspectiveCamera();\n");
	_output(0, "%s", "        viewport = new FitViewport(800, 480,camera);\n");
	_output(0, "%s", "        stage = new Stage(viewport);\n");
	_output(0, "%s", "        batch = new SpriteBatch();\n");
	_output(0, "%s", "        shapeRenderer = new ShapeRenderer();\n");
	_output(0, "%s", "        LoadRandomBackgroundImage();\n");
	_output(0, "%s", "        LoadSounds();\n");
	_output(0, "%s", "        font = new BitmapFont();\n");
	_output(0, "%s", "        font.setColor(Color.WHITE);\n");
	_output(0, "%s", "        MusicPlayer musicPlayer = new MusicPlayer();\n");
	_output(0, "%s", "        musicPlayer.loadSongs(new String[]{\"pookatori_and_friends.mp3\", \"ready_set_play.mp3\",\"threshold.mp3\"});\n");
	_output(0, "%s", "        musicPlayer.play();\n\n\n");
>>>>>>> Stashed changes
=======
>>>>>>> parent of 32fdf70 (Solved last generator errors)
=======
>>>>>>> parent of 32fdf70 (Solved last generator errors)
}

/**
 * Creates the epilogue of the generated output, that is, the final lines that
 * completes a valid Latex document.
 */
static void _generateEpilogue(void) 
{
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< Updated upstream
=======
>>>>>>> parent of 32fdf70 (Solved last generator errors)
=======
>>>>>>> parent of 32fdf70 (Solved last generator errors)
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
<<<<<<< HEAD
<<<<<<< HEAD
=======
	_output(0, "%s", "\n\n        player = new Player(0, numbersOfCardsInHand);\n");
	_output(0, "%s", "        machine = new AI(0, numbersOfCardsInHand);\n\n");
	_output(0, "%s", "        gameManager.dealInitialCards(player, numbersOfCardsInHand, deck);\n");
	_output(0, "%s", "        gameManager.dealInitialCards(machine, numbersOfCardsInHand, deck);\n");
	_output(0, "%s", "    }\n\n");
	_output(0, "%s", "    @Override\n");
	_output(0, "%s", "    public void render() {\n");
	_output(0, "%s", "        Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT);\n");
	_output(0, "%s", "        stage.draw();\n");
	_output(0, "%s", "        // Draw player cards and Background using SpriteBatch\n");
	_output(0, "%s", "        batch.begin();\n");
	_output(0, "%s", "        if (backgroundTexture != null) {\n");
	_output(0, "%s", "            Sprite backgroundSprite = new Sprite(backgroundTexture,Gdx.graphics.getWidth(),Gdx.graphics.getHeight());\n");
	_output(0, "%s", "            backgroundSprite.draw(batch);\n");
	_output(0, "%s", "        }\n");
	_output(0, "%s", "        drawPlayerCardsBatch(player, 50, 0);\n");
	_output(0, "%s", "        batch.end();\n");
	_output(0, "%s", "        // Draw scores\n");
	_output(0, "%s", "        batch.begin();\n");
	_output(0, "%s", "        drawScores();\n");
	_output(0, "%s", "        batch.end();\n\n");
	_output(0, "%s", "        // Resaltar la carta bajo el mouse\n");
	_output(0, "%s", "        highlightCardUnderMouse();\n\n");
	_output(0, "%s", "        // Draw player cards using ShapeRenderer\n");
	_output(0, "%s", "        shapeRenderer.begin(ShapeRenderer.ShapeType.Filled);\n");
	_output(0, "%s", "        drawPlayerCardsShape(player, 50, Gdx.graphics.getHeight() - 450);\n");
	_output(0, "%s", "        shapeRenderer.end();\n");
	_output(0, "%s", "        float mouseX = Gdx.input.getX();\n");
	_output(0, "%s", "        float mouseY = Gdx.graphics.getHeight() - Gdx.input.getY();\n");
	_output(0, "%s", "        // Handle input for playing a round\n");
	_output(0, "%s", "        if (Gdx.input.justTouched()) {\n\n");
	_output(0, "%s", "            Card selectedCard = getSelectedCard(mouseX, mouseY);\n");
	_output(0, "%s", "            if (selectedCard != null){\n");
	_output(0, "%s", "                selectedCard.animateToPosition((float) viewport.getScreenX() /2, (float) viewport.getScreenY() /2,2f);\n");
	_output(0, "%s", "                stage.addActor(selectedCard);\n");
	_output(0, "%s", "                System.out.println(\"Pressed \" + selectedCard.toString());\n");
	_output(0, "%s", "                placementSound.play(0.5f);\n");
	_output(0, "%s", "                gameManager.playRound(selectedCard,player,machine);\n");
	_output(0, "%s", "            }\n");
	_output(0, "%s", "        }\n");
	_output(0, "%s", "    }\n\n");
	_output(0, "%s", "    @Override\n");
	_output(0, "%s", "    public void resize(int width, int height) {\n");
	_output(0, "%s", "        viewport.update(width, height, true);\n");
	_output(0, "%s", "        for (Card card : player.getCardsInHand())\n");
	_output(0, "%s", "            updateCardPosition(card);\n");
	_output(0, "%s", "    }\n\n");
	_output(0, "%s", "    private void updateCardPosition(Card card) {\n");
	_output(0, "%s", "        float initialX = (viewport.getScreenX() - card.getWidth()) / 2f;\n");
	_output(0, "%s", "        float initialY = 10; // bottom of the screen\n");
	_output(0, "%s", "        card.setCardPosition(initialX, initialY);\n");
	_output(0, "%s", "    }\n\n");
	_output(0, "%s", "    //Esto puede ser un metodo abstracto que se crea en al GM\n");
	_output(0, "%s", "    private boolean winGameCondition(Player player) {\n");
	_output(0, "%s", "        return player.getScore() == 2;\n");
	_output(0, "%s", "    }\n\n");
	_output(0, "%s", "    private void LoadRandomBackgroundImage() {\n");
	_output(0, "%s", "        FileHandle folder = Gdx.files.internal(\"assets/Backgrounds/\");\n");
	_output(0, "%s", "        if (folder.exists() && folder.isDirectory()) {\n");
	_output(0, "%s", "            FileHandle[] backgrounds = folder.list();\n");
	_output(0, "%s", "            if (backgrounds.length > 1) {\n");
	_output(0, "%s", "                int index = new Random().nextInt(backgrounds.length);\n");
	_output(0, "%s", "                backgroundTexture = new Texture(backgrounds[index]);\n");
	_output(0, "%s", "            } else backgroundTexture = new Texture(backgrounds[0]);\n");
	_output(0, "%s", "        } else {\n");
	_output(0, "%s", "            Gdx.app.error(\"TextureManager\", \"Backgrounds directory is missing or not found.\");\n");
	_output(0, "%s", "        }\n");
	_output(0, "%s", "    }\n\n");
	_output(0, "%s", "    private void LoadSounds() {\n");
	_output(0, "%s", "        FileHandle SFXfolder = Gdx.files.internal(\"assets/Sounds/SFX\");\n");
	_output(0, "%s", "        if (SFXfolder.exists() && SFXfolder.isDirectory()) {\n");
	_output(0, "%s", "            placementSound = Gdx.audio.newSound(SFXfolder.child(\"card_impact_sfx.wav\"));\n");
	_output(0, "%s", "            highlightSound = Gdx.audio.newSound(SFXfolder.child(\"card_highlight_sfx.wav\"));\n");
	_output(0, "%s", "        }\n");
	_output(0, "%s", "    }\n\n");
	_output(0, "%s", "    private void highlightCardUnderMouse() {\n");
	_output(0, "%s", "        float mouseX = Gdx.input.getX();\n");
	_output(0, "%s", "        float mouseY = Gdx.graphics.getHeight() - Gdx.input.getY(); // Invertir el eje Y\n\n");
	_output(0, "%s", "        shapeRenderer.begin(ShapeRenderer.ShapeType.Line);\n");
	_output(0, "%s", "        shapeRenderer.setColor(Color.YELLOW); // Definir el color una vez fuera del bucle\n\n");
	_output(0, "%s", "        boolean highlightFound = false;\n\n");
	_output(0, "%s", "        for (Card card : player.getCardsInHand()) {\n");
	_output(0, "%s", "            if (card.isTouched(mouseX, mouseY)) {\n");
	_output(0, "%s", "                card.highlightCard(shapeRenderer); // Resaltar la carta sin llamar a begin/end dentro del bucle\n");
	_output(0, "%s", "                highlightFound = true;\n");
	_output(0, "%s", "            }\n");
	_output(0, "%s", "        }\n");
	_output(0, "%s", "        if (highlightFound && !mouseOverHighlightedCard && highlightSound != null) {\n");
	_output(0, "%s", "            highlightSound.play(0.25f);\n");
	_output(0, "%s", "            mouseOverHighlightedCard = true;\n");
	_output(0, "%s", "        } else if (!highlightFound) {\n");
	_output(0, "%s", "            mouseOverHighlightedCard = false;\n");
	_output(0, "%s", "        }\n");
	_output(0, "%s", "        shapeRenderer.end();\n");
	_output(0, "%s", "    }\n\n");
	_output(0, "%s", "    private void drawPlayerCardsBatch(Player player, float startX, float startY) {\n");
	_output(0, "%s", "        float cardSpacing = 20;\n");
	_output(0, "%s", "        float totalWidth = player.getCardsInHand().size() * (Card.CARD_WIDTH + cardSpacing) - cardSpacing;\n");
	_output(0, "%s", "        float currentX = startX + (Gdx.graphics.getWidth() - totalWidth) / 2;\n\n");
	_output(0, "%s", "        for (Card card : player.getCardsInHand()) {\n");
	_output(0, "%s", "            card.setCardPosition(currentX, startY);\n");
	_output(0, "%s", "            card.drawCardBatch(batch, font);\n");
	_output(0, "%s", "            currentX += Card.CARD_WIDTH + cardSpacing;\n");
	_output(0, "%s", "        }\n");
	_output(0, "%s", "    }\n\n");
	_output(0, "%s", "    private void drawPlayerCardsShape(Player player, float startX, float startY) {\n");
	_output(0, "%s", "        float cardSpacing = 20;\n");
	_output(0, "%s", "        float totalWidth = player.getCardsInHand().size() * (Card.CARD_WIDTH + cardSpacing) - cardSpacing;\n");
	_output(0, "%s", "        float currentX = startX + (Gdx.graphics.getWidth() - totalWidth) / 2;\n\n");
	_output(0, "%s", "        for (Card card : player.getCardsInHand()) {\n");
	_output(0, "%s", "            card.setCardPosition(currentX, startY);\n");
	_output(0, "%s", "            //card.drawCardShape(shapeRenderer);\n");
	_output(0, "%s", "            currentX += Card.CARD_WIDTH + cardSpacing;\n");
	_output(0, "%s", "        }\n");
	_output(0, "%s", "    }\n\n");
	_output(0, "%s", "    private Card getSelectedCard(float mouseX,float mouseY) {\n");
	_output(0, "%s", "        for (Card card : player.getCardsInHand()) {\n");
	_output(0, "%s", "            if (card.isTouched(mouseX,mouseY)) return card;\n");
	_output(0, "%s", "        }\n");
	_output(0, "%s", "        return null;\n");
	_output(0, "%s", "    }\n\n");
	_output(0, "%s", "    private void drawScores() {\n");
	_output(0, "%s", "        String playerScoreText = \"Player Score: \" + player.getScore();\n");
	_output(0, "%s", "        String machineScoreText = \"Machine Score: \" + machine.getScore();\n");
	_output(0, "%s", "        font.draw(batch, playerScoreText, 50, 50);\n");
	_output(0, "%s", "        font.draw(batch, machineScoreText, 50, 100);\n");
	_output(0, "%s", "    }\n\n");
	_output(0, "%s", "    @Override\n");
	_output(0, "%s", "    public void dispose() {\n");
	_output(0, "%s", "        batch.dispose();\n");
	_output(0, "%s", "        shapeRenderer.dispose();\n");
	_output(0, "%s", "        font.dispose();\n");
	_output(0, "%s", "    }\n");
	_output(0, "%s", "}\n");
>>>>>>> Stashed changes
=======
>>>>>>> parent of 32fdf70 (Solved last generator errors)
=======
>>>>>>> parent of 32fdf70 (Solved last generator errors)
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
