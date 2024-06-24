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

static void _generateProgram(Program * program) {
	_generateBlock(program->block);
}

static void _generateBlock(Block * block){
	switch(block->type){
		case VALUE_BLOCK:
			_output(0, "%s", "//Rule ");
			_output(0, "%s", block->variable);
			_output(0, "%s", "\n");
			_output(2, "%s", "deck.AddSpecialAbilityTo(");
			_output(0, "%d", block->constant);
			_output(0, "%s", ", ");
			_generateRules(block->rules);
			break;
		case TYPE_BLOCK:
			_output(0, "%s", "//Rule ");
			_output(0, "%s", block->variable1);
			_output(0, "%s", "\n");
			_output(2, "%s", "deck.AddSpecialAbilityTo(");
			_generateCardTypes(block->cardTypes);
			_output(0, "%s", ", ");
			_generateRules(block->rules1);
			break;
		case GAME_BLOCK:
			_output(0, "%s", "//");
			_output(0, "%s", block->variable2);
			_output(0, "%s", " game has:\n");
			_generateGameFunction(block->gameFunction);
			break;
		case DESIGN_BLOCK:
			_output(0, "%s", "//");
			_output(0, "%s", block->variable3);
			_output(0, "%s", " design has:\n");
			_generateRules(block->rules3);
			break;
		case RULE_BLOCK:
//			if(strcmp(block->variable4, "GlobalRule") == 0){
//				_output(0, "%s", "gameManager = new GameManager(typeNames, numbersOnDeck, rounds, roundTimer) {\n");
//	          	_output(0, "%s", "@Override\n");
//            	_output(0, "%s", "public int compare(Card o1, Card o2) {\n");
//				//_output(0, "%s", block->variable4);
//				_generateRules(block->rules2);
//				_output(0, "%s", "}\n});\n");
//			}else{
				_output(0, "%s", "//");
				_output(0, "%s", block->variable4);
				_output(0, "%s", " for game:\n");
				_generateRules(block->rules2);
//			}
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
				_output(0, "%s", "new MoveCardsAction(");
				_generateHandRef(rules->leftHandRef);
				_output(0, "%s", ", ");
				_generateHandRef(rules->rightHandRef);
				_output(0, "%s", ", ");
				_output(0, "%d", rules->constant);
				_output(0, "%s", "));\n");
				_generateRules(rules->rule);
				break;
			case RULE_LOOK_AT:
				_output(0, "%s", "new LookAtAction(");
				_generateHandRef(rules->handRef);
				_output(0, "%s", ", ");
				_output(0, "%d", rules->constant1);
				_output(0, "%s", "));\n");
				_generateRules(rules->rule1);
				break;
			case RULE_RESTOCK_DECK:
				_output(2, "%s", "deck.generateDeck();\n");
				_generateRules(rules->rule2);
				break;
			case RULE_WIN_GAME:
				_output(2, "%s", "gameManager.winGame(");
				_generateUser(rules->user);
				_output(0, "%s", ");\n");
				_generateRules(rules->rule2);
				break;
			case RULE_WINNER_TYPE:
				_output(2, "%s", "gameManager.addTypeRelation(\"");
				_output(0, "%s", rules->variable2);
				_output(0, "%s", "\", \"");
				_output(0, "%s", rules->variable3);
				_output(0, "%s", "\");\n");
				_generateRules(rules->rule6);
				break;
			case COLOR_BORDERS_DESIGN:
				_output(2, "%s", "deck.assignColorToType(\"");
				_output(0, "%s", rules->variable2);
				_output(0, "%s", "\", Colors.");
				_output(0, "%s", rules->variable3);
				_output(0, "%s", ", true);\n");
				_generateRules(rules->rule6);
				break;
			case BACKGROUND_COLOR_DESIGN:
				_output(2, "%s", "LoadBackgroundImage(\"");
				_output(0, "%s", rules->variable);
				_output(0, "%s", ".png\");\n");
				_generateRules(rules->rule3);
				break;
			case USER_RULES:
				_generateUserRules(rules->userRules);
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

static void _generateExpression(Expression * expression){
	switch(expression->type){
		case EXPR_ADD:
			_generateExpression(expression->leftExpression);
			_output(0, "%s", " + ");
			_generateExpression(expression->rightExpression);
			break;
		case EXPR_DIV:
			_generateExpression(expression->leftExpression);
			_output(0, "%s", " / ");
			_generateExpression(expression->rightExpression);
			break;
		case EXPR_MUL:
			_generateExpression(expression->leftExpression);
			_output(0, "%s", " * ");
			_generateExpression(expression->rightExpression);
			break;
		case EXPR_SUB:
			_generateExpression(expression->leftExpression);
			_output(0, "%s", " - ");
			_generateExpression(expression->rightExpression);
			break;
		case EXPR_MODULE:
			_generateExpression(expression->leftExpression);
			_output(0, "%s", " \% ");
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

static void _generateUserRules(UserRules * userRules){ //Cuando se implemente if
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
		default:
			logError(_logger, "The specified userRules type is unknown: %d", userRules->type);
			break;
	}
}

static void _generateGameFunction(GameFunction * gameFunction){ 
	_output(2, "%s", "numbersOnDeck = ");			
	_output(0, "%d", gameFunction->cteNumbersOnDeck);	
	_output(0, "%s", ";\n");							
	_output(2, "%s", "String[] typeNames = {");		
	_generateCardTypes(gameFunction->cardTypes);	
	_output(0, "%s", "};\n");						
	_output(2, "%s", "numbersOfCardsInHand = ");	
	_output(0, "%d", gameFunction->cteCardsByPlayers);	
	_output(0, "%s", ";\n");							
	_output(2, "%s", "int rounds = ");			
	_output(0, "%d", gameFunction->cteRounds);	
	_output(0, "%s", ";\n");					
	_output(2, "%s", "int roundTimer = ");			
	_output(0, "%d", gameFunction->cteRoundTimer);		
	_output(0, "%s", ";\n");						
	_output(2, "%s", "StartingScore(");						
	_output(0, "%d", gameFunction->cteUserStartingScore);	
	_output(0, "%s", ", ");									
	_output(0, "%d", gameFunction->cteMachineStartingScore);
	_output(0, "%s", ");\n");								
	_output(0, "%s", "//WinRoundCondition(");
	_output(0, "%s", gameFunction->varWinRoundCondition);
	_output(0, "%s", ")\n");
	_output(0, "%s", "//WinGameCondition(");	
	_output(0, "%s", gameFunction->varWinGameCondition);	
	_output(0, "%s", ")\n");
	_output(0, "%s", "//CardsDesign(");
	_output(0, "%s", gameFunction->varCardDesign);
	_output(0, "%s", ")\n");	
	_output(0, "%s", "//BackgroundDesign(");
	_output(0, "%s", gameFunction->varBackDesign);	
	_output(0, "%s", ")\n");
	_output(2, "%s", "Deck deck = new Deck(typeNames, numbersOnDeck);\n"); 
	_output(2, "%s", "deck.generateDeck();\n");
	_output(2, "%s", "gameManager = new GameManager(typeNames, numbersOnDeck, rounds, roundTimer);\n");
	_output(2, "%s", "player = new Player(startingPlayerScore, numbersOfCardsInHand);\n");
	_output(2, "%s", "machine = new AI(startingMachineScore, numbersOfCardsInHand);\n");
	_generateBlock(gameFunction->block); 
}

static void _generateCardTypes(CardTypes * cardTypes){ 
	switch(cardTypes->type){
		case ONE_TYPE:
			_output(0, "%s", "\"");
			_output(0, "%s", cardTypes->variable);
			_output(0, "%s", "\"");
			break;
		case MULTIPLE_TYPE:
			_output(0, "%s", "\"");
			_output(0, "%s", cardTypes->variable1);
			_output(0, "%s", "\", ");
			_generateCardTypes(cardTypes->cardType);
			break;
		default:
			logError(_logger, "The specified cardTypes type is unknown: %d", cardTypes->type);
			break;
	}
}

static void _generateUserCard(UserCard * userCard){
	_generateUser(userCard->user);
	_output(0, "%s", ".getCardsInHand()");
}

static void _generateUserScore(UserScore * userScore){
	_generateUser(userScore->user);
	_output(0, "%s", ".getScore()");
}

static void _generateNumbers(Numbers * numbers){
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

static void _generateArithmetic(Arithmetic * arithmetic){
	switch(arithmetic->type){
		case ARIT_ADD:	
			_output(0, "%s", " + ");
			break;
		case ARIT_DIV:
			_output(0, "%s", " / ");
			break;
		case ARIT_MUL:
			_output(0, "%s", " * ");
			break;
		case ARIT_SUB:
			_output(0, "%s", " - ");
			break;
		case ARIT_MODULE:
			_output(0, "%s", " \% ");
			break;
		default:
			logError(_logger, "The specified arithmetic type is unknown: %d", arithmetic->type);
			break;
	}
}

static void _generateAsignations(Asignations * asignations){
	switch(asignations->type){
		case ASIG_EQUAL:
			_output(0, "%s", " = ");
			break;
		case ASIG_ADD_EQUAL:
			_output(0, "%s", " += ");
			break;
		case SUB_EQUAL:
			_output(0, "%s", " -= ");
			break;
		default:
			logError(_logger, "The specified asignations type is unknown: %d", asignations->type);
			break;
	}
}

static void _generatePmOne(PmOne * pmOne){
	switch(pmOne->type){
		case INCREASE:
			_output(0, "%s", " ++ ");
			break;
		case DECREASE:
			_output(0, "%s", " -- ");
			break;
		default:
			logError(_logger, "The specified pmOne type is unknown: %d", pmOne->type);
			break;	
	}
}

static void _generateStructures(Structures * structures){ //Arreglar problemas de if
	switch(structures->type){
		case IF_STRUCTURE:
			_output(1, "%s", "if(");
			_generateIfs(structures->conditional);
			_output(0, "%s", "){\n");
			_generateInBrakets(structures->inBrakets, 1);
			break;
		case ELIF_STRUCTURE:
			_output(1, "%s", "else if(");
			_generateIfs(structures->conditional);
			_output(0, "%s", "){\n");
			_generateInBrakets(structures->inBrakets, 1);
			break;
		case ELSE_STRUCTURE:
			_output(1, "%s", "else{\n");
			_generateInBrakets(structures->inBrakets2, 1);
			break;
		case WITH_STRUCTURE:
			_generateWith(structures->with);
			_generateInBrakets(structures->inBrakets3, 0);
			break;
		default:
			logError(_logger, "The specified structures type is unknown: %d", structures->type);
			break;
	}
}

static void _generateWith(With * with){
	switch(with->type){
		case VALUE_WITH:
			_output(0, "%d, ", with->constant);
			break;
		case TYPE_WITH:
			_output(0, "%s", "\"");
			_output(0, "%s", with->variable);
			_output(0, "%s", "\", ");
			break;
		default:
			logError(_logger, "The specified with type is unknown: %d", with->type);
			break;
	}
}

static void _generateInBrakets(InBrakets * inBrakets, int noBrakets){
	_generateRules(inBrakets->leftRules);
	_output(0, "%s", noBrakets?"\n}\n":"\n");
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
			break;
		default:
			logError(_logger, "The specified handRef type is unknown: %d", handRef->type);
			break;
	}
}

static void _generateDeck(Deck * deck){
	_output(0, "%s", "deck.getDeck()");
}

static void _generateUser(User * user){
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
			_generateInIf(ifs->leftInIf);
			_output(0, "%s", " && ");
			_generateInIf(ifs->rightInIf);
			break;
		case OR_IF:
			_generateInIf(ifs->leftInIf);
			_output(0, "%s", " || ");
			_generateInIf(ifs->rightInIf);
			break;	
		default:
			logError(_logger, "The specified ifs type is unknown: %d", ifs->type);
			break;
	}
}

static void _generateInIf(InIf * inIf){
	switch(inIf->type){
		case TYPE_IF:
			_output(0, "%s", "strType");
			_generateComparison(inIf->comparison1);
			_output(0, "%s", "\"");
			_output(0, "%s", inIf->variable);
			_output(0, "%s", "\"");
			break;
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

static void _generateComparison(Comparison * comparison){
	switch(comparison->type){
		case COMP_GREATER:
			_output(0, "%s", " > ");
			break;
		case COMP_LOWER:
			_output(0, "%s", " < ");
			break;
		case COMP_EQUAL_EQUAL:
			_output(0, "%s", " == ");
			break;
		case COMP_GREATER_OR_EQUAL:
			_output(0, "%s", " >= ");
			break;
		case COMP_LOWER_OR_EQUAL:
			_output(0, "%s", " <= ");
			break;
		case COMP_DIFERENT:
			_output(0, "%s", " != ");
			break;
		default:
			logError(_logger, "The specified comparison type is unknown: %d", comparison->type);
			break;
	}
}

static void _generateAtomic(Atomic * atomic){ 
	switch(atomic->type){
		case ATOMIC_VALUE:
			_output(0, "%s", ".getValue()");
			break;
		case ATOMIC_TYPE:
			_output(0, "%s", ".getType()");
			break;
		default:
			logError(_logger, "The specified atomic type is unknown: %d", atomic->type);
			break;
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
	_output(0, "%s", "import com.mygdx.game.Cards.*;\n");
	_output(0, "%s", "import com.mygdx.game.Cards.Colors;\n");
	_output(0, "%s", "import com.mygdx.game.Managers.MusicPlayer;\n");
	_output(0, "%s", "import com.mygdx.game.Players.AI;\n");
	_output(0, "%s", "import com.mygdx.game.Players.Player;\n");
	_output(0, "%s", "import java.util.ArrayList;\n");
	_output(0, "%s", "import java.util.Objects;\n");
	_output(0, "%s", "import java.util.Random;\n\n");
	_output(0, "%s", "public class MyGdxGame extends ApplicationAdapter{\n");
	_output(0, "%s", "    private SpriteBatch batch;\n");
	_output(0, "%s", "    private BitmapFont font;\n");
	_output(0, "%s", "    private ShapeRenderer shapeRenderer;\n");
	_output(0, "%s", "    private Sound placementSound,highlightSound;\n");
	_output(0, "%s", "    Texture backgroundTexture = null;\n");
	_output(0, "%s", "    private Viewport viewport;\n");
	_output(0, "%s", "    private Camera camera;\n");
	_output(0, "%s", "    private Stage stage;\n");
	_output(0, "%s", "    private GameManager gameManager;\n");
	_output(0, "%s", "    private Player player;\n");
	_output(0, "%s", "    private AI machine;\n");
	_output(0, "%s", "    private int startingMachineScore=0;\n");
	_output(0, "%s", "    private int startingPlayerScore=0;\n");
	_output(0, "%s", "    private boolean mouseOverHighlightedCard = false;\n");
	_output(0, "%s", "    private int numbersOnDeck = -1;\n");
	_output(0, "%s", "    private int numbersOfCardsInHand = -1;\n\n");
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
}

/**
 * Creates the epilogue of the generated output, that is, the final lines that
 * completes a valid Latex document.
 */
static void _generateEpilogue(void) 
{
	_output(0, "%s", "\n\n\n        deck.generateDeck();\n");
	_output(0, "%s", "        gameManager.dealInitialCards(player, numbersOfCardsInHand, deck);\n");
	_output(0, "%s", "        gameManager.dealInitialCards(machine, numbersOfCardsInHand, deck);\n");
	_output(0, "%s", "    }\n\n");
	_output(0, "%s", "    @Override\n");
	_output(0, "%s", "    public void render() {\n");
	_output(0, "%s", "        Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT);\n");
	_output(0, "%s", "        stage.draw();\n");
	_output(0, "%s", "        batch.begin();\n");
	_output(0, "%s", "        if (backgroundTexture != null) {\n");
	_output(0, "%s", "            Sprite backgroundSprite = new Sprite(backgroundTexture,Gdx.graphics.getWidth(),Gdx.graphics.getHeight());\n");
	_output(0, "%s", "            backgroundSprite.draw(batch);\n");
	_output(0, "%s", "        }\n");
	_output(0, "%s", "        drawPlayerCardsBatch(player, 50, 0);\n");
	_output(0, "%s", "        batch.end();\n");
	_output(0, "%s", "        batch.begin();\n");
	_output(0, "%s", "        drawScores();\n");
	_output(0, "%s", "        batch.end();\n");
	_output(0, "%s", "        // Resaltar la carta bajo el mouse\n");
	_output(0, "%s", "        highlightCardUnderMouse();\n");
	_output(0, "%s", "        // Draw player cards using ShapeRenderer\n");
	_output(0, "%s", "        shapeRenderer.begin(ShapeRenderer.ShapeType.Filled);\n");
	_output(0, "%s", "        drawPlayerCardsShape(player, 50, Gdx.graphics.getHeight() - 450);\n");
	_output(0, "%s", "        shapeRenderer.end();\n");
	_output(0, "%s", "        float mouseX = Gdx.input.getX();\n");
	_output(0, "%s", "        float mouseY = Gdx.graphics.getHeight() - Gdx.input.getY();\n");
	_output(0, "%s", "        // Handle input for playing a round\n");
	_output(0, "%s", "        if (Gdx.input.justTouched()) {\n");
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
	_output(0, "%s", "    private void LoadBackgroundImage(String name) {\n");
	_output(0, "%s", "        FileHandle fileHandle = Gdx.files.internal(\"assets/Backgrounds/\" + name);\n");
	_output(0, "%s", "        if (fileHandle.exists()){\n");
	_output(0, "%s", "            if (fileHandle.extension().equals(\".png\") || fileHandle.extension().equals(\".jpg\")){\n");
	_output(0, "%s", "                backgroundTexture = new Texture(fileHandle);\n");
	_output(0, "%s", "            }\n");
	_output(0, "%s", "        }\n");
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
	_output(0, "%s", "        float mouseY = Gdx.graphics.getHeight() - Gdx.input.getY(); // Invertir el eje Y\n");
	_output(0, "%s", "        shapeRenderer.begin(ShapeRenderer.ShapeType.Line);\n");
	_output(0, "%s", "        shapeRenderer.setColor(Color.YELLOW); // Definir el color una vez fuera del bucle\n");
	_output(0, "%s", "        boolean highlightFound = false;\n");
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
	_output(0, "%s", "    private void StartingScore(int playerScore,int machineScore){\n");
	_output(0, "%s", "        this.startingPlayerScore = playerScore;\n");
	_output(0, "%s", "        this.startingMachineScore = machineScore;\n");
	_output(0, "%s", "    }\n\n");
	_output(0, "%s", "    private void drawPlayerCardsBatch(Player player, float startX, float startY) {\n");
	_output(0, "%s", "        float cardSpacing = 20;\n");
	_output(0, "%s", "        float totalWidth = player.getCardsInHand().size() * (Card.CARD_WIDTH + cardSpacing) - cardSpacing;\n");
	_output(0, "%s", "        float currentX = startX + (Gdx.graphics.getWidth() - totalWidth) / 2;\n");
	_output(0, "%s", "        for (Card card : player.getCardsInHand()) {\n");
	_output(0, "%s", "            card.setCardPosition(currentX, startY);\n");
	_output(0, "%s", "            card.drawCardBatch(batch, font);\n");
	_output(0, "%s", "            currentX += Card.CARD_WIDTH + cardSpacing;\n");
	_output(0, "%s", "        }\n");
	_output(0, "%s", "    }\n\n");
	_output(0, "%s", "    private void drawPlayerCardsShape(Player player, float startX, float startY) {\n");
	_output(0, "%s", "        float cardSpacing = 20;\n");
	_output(0, "%s", "        float totalWidth = player.getCardsInHand().size() * (Card.CARD_WIDTH + cardSpacing) - cardSpacing;\n");
	_output(0, "%s", "        float currentX = startX + (Gdx.graphics.getWidth() - totalWidth) / 2;\n");
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
