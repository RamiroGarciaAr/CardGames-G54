%{

#include "FlexActions.h"

%}

/**
 * Enable start condition manipulation functions.
 */
%option stack

/**
 * Flex contexts (a.k.a. start conditions).
 *
 * @see https://westes.github.io/flex/manual/Start-Conditions.html
 */
%x MULTILINE_COMMENT

alphanumeric    [a-zA-Z0-9_]

/**
 * Reusable patterns.
 *
 * @see https://westes.github.io/flex/manual/Matching.html
 * @see https://westes.github.io/flex/manual/Patterns.html
 */

%%

"/*"								{ BEGIN(MULTILINE_COMMENT); BeginMultilineCommentLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>"*/"				{ EndMultilineCommentLexemeAction(createLexicalAnalyzerContext()); BEGIN(INITIAL); }
<MULTILINE_COMMENT>[[:space:]]+		{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>[^*]+			{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>.				{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }

"-"									{ return ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext()); }
"*"									{ return ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext()); }
"/"									{ return ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext()); }
"+"									{ return ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext()); }

"++"                                { return IncrementPatternAction(createLexicalAnalyzerContext()); }
"--"                                { return DecrementPatternAction(createLexicalAnalyzerContext()); }
"+="                                { return PlusEqualsPatternAction(createLexicalAnalyzerContext()); }
"-="                                { return IncrementPatternAction(createLexicalAnalyzerContext()); }

"<"                                 { return ComparationLexemeAction(createLexicalAnalyzerContext()); }
">"                                 { return ComparationLexemeAction(createLexicalAnalyzerContext()); }
"=="                                { return ComparationLexemeAction(createLexicalAnalyzerContext()); }
"<="                                { return ComparationLexemeAction(createLexicalAnalyzerContext()); }
">="                                { return ComparationLexemeAction(createLexicalAnalyzerContext()); }

"game has:"                         { return TypeLexemeAction(createLexicalAnalyzerContext()); }
"design has:"                       { return TypeLexemeAction(createLexicalAnalyzerContext()); }                    
"for game:"                         { return TypeLexemeAction(createLexicalAnalyzerContext()); }     
"for type"                          { return TypeLexemeAction(createLexicalAnalyzerContext()); }
"for value"                         { return TypeLexemeAction(createLexicalAnalyzerContext()); }
":"                                 { return TypeLexemeAction(createLexicalAnalyzerContext()); }

"type"                              { return TypeLexemeAction(createLexicalAnalyzerContext()); }
"value"                             { return TypeLexemeAction(createLexicalAnalyzerContext()); }

"Playing"                           { return PlayerLexemeAction(createLexicalAnalyzerContext()); }
"Waiting"                           { return PlayerLexemeAction(createLexicalAnalyzerContext()); }
"Deck"                              { return DeckLexemeAction(createLexicalAnalyzerContext()); }
"User"                              { return IdentifierLexemeAction(createLexicalAnalyzerContext()); }
"Machine"                           { return IdentifierLexemeAction(createLexicalAnalyzerContext()); }

"foreach"                           { return ForEachLexemeAction(createLexicalAnalyzerContext()); }
"if"                                { return IfLexemeAction(createLexicalAnalyzerContext()); }
"else"                              { return ElseisLexemeAction(createLexicalAnalyzerContext()); }
"elif"                              { return ElifLexemeAction(createLexicalAnalyzerContext()); }

"NumbersOnDeck"                     { return LanguageFunctionLexemeAction(createLexicalAnalyzerContext()); }
"TypesOfCards"                      { return LanguageFunctionLexemeAction(createLexicalAnalyzerContext()); }
"CardsByPlayer"                     { return LanguageFunctionLexemeAction(createLexicalAnalyzerContext()); }
"Rounds"                            { return LanguageFunctionLexemeAction(createLexicalAnalyzerContext()); }
"RoundsTimer"                       { return LanguageFunctionLexemeAction(createLexicalAnalyzerContext()); }
"StartingScore"                     { return LanguageFunctionLexemeAction(createLexicalAnalyzerContext()); }
"WinRoundCondition"                 { return LanguageFunctionLexemeAction(createLexicalAnalyzerContext()); }
"WinGameCondition"                  { return LanguageFunctionLexemeAction(createLexicalAnalyzerContext()); }
"CardsDesign"                       { return LanguageFunctionLexemeAction(createLexicalAnalyzerContext()); }
"BackgroundDesign"                  { return LanguageFunctionLexemeAction(createLexicalAnalyzerContext()); }

"MoveCards"                         { return GameFunctionLexemeAction(createLexicalAnalyzerContext()); }
"LookAt"                            { return GameFunctionLexemeAction(createLexicalAnalyzerContext()); }
"RestockDeck"                       { return GameFunctionLexemeAction(createLexicalAnalyzerContext()); }
"WinGame"                           { return GameFunctionLexemeAction(createLexicalAnalyzerContext()); }
"WinnerType"                        { return GameFunctionLexemeAction(createLexicalAnalyzerContext()); }
"SpecialCardsOnPlay"                { return GameFunctionLexemeAction(createLexicalAnalyzerContext()); }

"RoundBorders"                      { return DesignFunctionLexemeAction(createLexicalAnalyzerContext()); }
"ColorBorders"                      { return DesignFunctionLexemeAction(createLexicalAnalyzerContext()); }
"BackgroundColor"                   { return DesignFunctionLexemeAction(createLexicalAnalyzerContext()); }


"("									{ return ParenthesisLexemeAction(createLexicalAnalyzerContext()); }
")"									{ return ParenthesisLexemeAction(createLexicalAnalyzerContext()); }

[[:digit:]]+						{ return IntegerLexemeAction(createLexicalAnalyzerContext()); }

[[:space:]]+						{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }

//VARIABLE
{alphanumeric}+                     { return VariablePatternAction(yytext, yyleng); }

.									{ return UnknownLexemeAction(createLexicalAnalyzerContext()); }

%%

#include "FlexExport.h"
