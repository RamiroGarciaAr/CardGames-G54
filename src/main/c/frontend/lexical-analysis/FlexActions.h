#ifndef FLEX_ACTIONS_HEADER
#define FLEX_ACTIONS_HEADER

#include "../../shared/Environment.h"
#include "../../shared/Logger.h"
#include "../../shared/String.h"
#include "../../shared/Type.h"
#include "../syntactic-analysis/AbstractSyntaxTree.h"
#include "../syntactic-analysis/BisonParser.h"
#include "LexicalAnalyzerContext.h"
#include <stdio.h>
#include <stdlib.h>

/** Initialize module's internal state. */
void initializeFlexActionsModule();

/** Shutdown module's internal state. */
void shutdownFlexActionsModule();

/**
 * Flex lexeme processing actions.
 */

void BeginMultilineCommentLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
void EndMultilineCommentLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
void BeginOnelineCommentLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
void EndOnelineCommentLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
void IgnoredLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token ArithmeticOperatorLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token IntegerLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token VariablePatternAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token ParenthesisLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token UnknownLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

Token TypeLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token PunctuationLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token BraketsLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token LanguageFunctionLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token GameFunctionLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token DesignFunctionLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token OperatorPatternAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token ComparationLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token PlayerReferenceLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token LogicLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token GamingLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token ControlStructureLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
Token BooleanLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

#endif
