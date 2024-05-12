#include "FlexActions.h"

/* MODULE INTERNAL STATE */

static Logger * _logger = NULL;
static boolean _logIgnoredLexemes = true;

void initializeFlexActionsModule() {
	_logIgnoredLexemes = getBooleanOrDefault("LOG_IGNORED_LEXEMES", _logIgnoredLexemes);
	_logger = createLogger("FlexActions");
}

void shutdownFlexActionsModule() {
	if (_logger != NULL) {
		destroyLogger(_logger);
	}
}

/* PRIVATE FUNCTIONS */

static void _logLexicalAnalyzerContext(const char * functionName, LexicalAnalyzerContext * lexicalAnalyzerContext);

/**
 * Logs a lexical-analyzer context in DEBUGGING level.
 */
static void _logLexicalAnalyzerContext(const char * functionName, LexicalAnalyzerContext * lexicalAnalyzerContext) {
	char * escapedLexeme = escape(lexicalAnalyzerContext->lexeme);
	logDebugging(_logger, "%s: %s (context = %d, length = %d, line = %d)",
		functionName,
		escapedLexeme,
		lexicalAnalyzerContext->currentContext,
		lexicalAnalyzerContext->length,
		lexicalAnalyzerContext->line);
	free(escapedLexeme);
}

/* PUBLIC FUNCTIONS */

void BeginMultilineCommentLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	if (_logIgnoredLexemes) {
		_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	}
}

void EndMultilineCommentLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	if (_logIgnoredLexemes) {
		_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	}
}

void BeginOnelineCommentLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext){
	if (_logIgnoredLexemes) {
		_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	}
}

void EndOnelineCommentLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	if (_logIgnoredLexemes) {
		_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	}
}

void IgnoredLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	if (_logIgnoredLexemes) {
		_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	}
}

Token ArithmeticOperatorLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token;
	switch (lexicalAnalyzerContext->lexeme[0]) {
		case '-': token = SUB; break;
		case '*': token = MUL; break;
		case '/': token = DIV; break;
		case '+': token = ADD; break;
	}
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}

Token IntegerLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->integer = atoi(lexicalAnalyzerContext->lexeme);
	return INTEGER;
}

Token VariablePatternAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->variable = VARIABLE;
	return VARIABLE;
}

/*
Token VariablePatternAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->variable = strdup(lexicalAnalyzerContext->lexeme);
	return VARIABLE;
}
*/

Token ParenthesisLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token;
	switch (lexicalAnalyzerContext->lexeme[0]) {
		case '(': token = OPEN_PARENTHESIS; break;
		case ')': token = CLOSE_PARENTHESIS; break;
	}
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}

Token UnknownLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	return UNKNOWN;
}

Token TypeLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token;
	if (strcmp(lexicalAnalyzerContext->lexeme, "game") == 0) {
		token = GAME;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "design") == 0) {
		token = DESIGN;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "has") == 0) {
		token = HAS;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "for") == 0) {
		token = FOR;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "type") == 0) {
		token = TYPE;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "value") == 0) {
		token = VALUE;
	}
	return token;
}

Token PunctuationLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token;
	switch (lexicalAnalyzerContext->lexeme[0]){
		case ':': token = COLON; break;
		case ',': token = COMMA; break;
		case '.': token = DOT; break;
	}
	return token;
}

Token BraketsLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token;
	switch (lexicalAnalyzerContext->lexeme[0]){
		case '{': token = OPEN_BRAKETS; break;
		case '}': token = CLOSE_BRAKETS; break;
	}
	return token;
}

Token LanguageFunctionLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token;
	if (strcmp(lexicalAnalyzerContext->lexeme, "NumbersOnDeck") == 0) {
		token = NUMBERS_ON_DECK;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "TypesOfCards") == 0) {
		token = TYPES_OF_CARDS;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "CardsByPlayer") == 0) {
		token = CARDS_BY_PLAYER;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "Rounds") == 0) {
		token = ROUNDS;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "RoundsTimer") == 0) {
		token = ROUNDS_TIMER;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "StartingScore") == 0) {
		token = STARTING_SCORE;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "WinRoundCondition") == 0) {
		token = WIN_ROUND_CONDITION;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "WinGameCondition") == 0) {
		token = WIN_GAME_CONDITION;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "CardsDesign") == 0) {
		token = CARDS_DESIGN;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "BackgroundDesign") == 0) {
		token = BACKGROUND_DESIGN;
	}
	return token;
}

Token GameFunctionLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token;
	if (strcmp(lexicalAnalyzerContext->lexeme, "MoveCards") == 0) {
		token = MOVE_CARDS;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "LookAt") == 0) {
		token = LOOK_AT;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "RestockDeck") == 0) {
		token = RESTOCK_DECK;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "WinGame") == 0) {
		token = WIN_GAME;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "WinnerType") == 0) {
		token = WINNER_TYPE;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "SpecialCardsOnPlay") == 0) {
		token = SPECIAL_CARDS_ON_PLAY;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "ActivateSpecialCards") == 0) {
		token = ACTIVATE_SPECIAL_CARDS;
	}
	return token;
}

Token DesignFunctionLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token;
	if (strcmp(lexicalAnalyzerContext->lexeme, "RoundBorders") == 0) {
		token = ROUND_BORDERS;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "ColorBorders") == 0) {
		token = COLOR_BORDERS;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "BackgroundColor") == 0) {
		token = BACKGROUND_COLOR;
	}
	return token;
}

Token OperatorPatternAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token;
	switch(lexicalAnalyzerContext->lexeme[0]) {
		case '+':
			if(lexicalAnalyzerContext->lexeme[1] == '+') {
				token = ADD_ONE;
			}
			if (lexicalAnalyzerContext->lexeme[1] == '='){
				token = ADD;
			}
			break;
		case '-':
			if(lexicalAnalyzerContext->lexeme[1] == '-') {
				token = SUBSTRACT_ONE;
			}
			if (lexicalAnalyzerContext->lexeme[1]=='='){
				token = SUB;	
			}
			break;
	}
	return token;
}

Token ComparationLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token;
	switch(lexicalAnalyzerContext->lexeme[0]) {
		case '>':
			if(lexicalAnalyzerContext->lexeme[1] == '=') {
				token = GREATER_OR_EQUAL;
			}else{
				token = GREATER;
			}
			break;
		case '<':
			if(lexicalAnalyzerContext->lexeme[1] == '=') {
				token = LOWER_OR_EQUAL;
			}else{
				token = LOWER;
			}
			break;
		case '=':
			if(lexicalAnalyzerContext->lexeme[1] == '='){
				token = EQUAL_EQUAL;
			} else{
				token = EQUAL;
			}break;
		case '!':
			if(lexicalAnalyzerContext->lexeme[1] == '='){
				token = DIFERENT;
			} break;
	}
	return token;
}

Token PlayerReferenceLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token;
	if (strcmp(lexicalAnalyzerContext->lexeme, "Hand") == 0) {
		token = HAND;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "SelectedCard") == 0) {
		token = SELECTED_CARD;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "score") == 0) {
		token = SCORE;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "tied") == 0) {
		token = TIED;
	} 
	return token;
}

Token LogicLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token;
	switch(lexicalAnalyzerContext->lexeme[0]) {
		case '%':
			token = MODULE; break;
		case '&':
			if(lexicalAnalyzerContext->lexeme[1] == '&') {
				token = AND;
			} break;
		case '|':
			if(lexicalAnalyzerContext->lexeme[1] == '|'){
				token = OR;
			} break;
	}
	return token;
}

Token GamingLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token;
	if (strcmp(lexicalAnalyzerContext->lexeme, "Playing") == 0) {
		token = PLAYER;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "Waiting") == 0) {
		token = PLAYER;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "Deck") == 0) {
		token = DECK;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "User") == 0) {
		token = IDENTIFIER;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "Machine") == 0) {
		token = IDENTIFIER;
	}
	return token;
}

Token ControlStructureLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token;
	if (strcmp(lexicalAnalyzerContext->lexeme, "foreach") == 0) {
		token = FOREACH;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "if") == 0) {
		token = IFS;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "else") == 0) {
		token = ELSE;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "elif") == 0) {
		token = ELIF;
	}
	return token;
}

Token BooleanLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token;
	if (strcmp(lexicalAnalyzerContext->lexeme, "true") == 0) {
		token = TRUE;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "false") == 0) {
		token = FALSE;
	} 
	return token;
}