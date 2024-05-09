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

%x ONELINE_COMMENT

/**
 * Reusable patterns.
 *
 * @see https://westes.github.io/flex/manual/Matching.html
 * @see https://westes.github.io/flex/manual/Patterns.html
 */

%%

"/*"								{ BEGIN(MULTILINE_COMMENT); BeginMultilineCommentLexemeAction(createLexicalAnalyzerContext()); }/*listo*/
<MULTILINE_COMMENT>"*/"				{ EndMultilineCommentLexemeAction(createLexicalAnalyzerContext()); BEGIN(INITIAL); }
<MULTILINE_COMMENT>[[:space:]]+		{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>[^*]+			{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>.				{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }

"//"								{ BEGIN(ONELINE_COMMENT); BeginOnelineCommentLexemeAction(createLexicalAnalyzerContext()); }/*listo*/
<ONELINE_COMMENT>"\n"				{ EndOnelineCommentLexemeAction(createLexicalAnalyzerContext()); BEGIN(INITIAL); }
<ONELINE_COMMENT>[[:space:]]+		{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<ONELINE_COMMENT>.					{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }

"-"									{ return ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext()); }/*listo*/
"*"									{ return ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext()); }
"/"									{ return ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext()); }
"+"									{ return ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext()); }

"++"                                { return IncrementPatternAction(createLexicalAnalyzerContext()); }
"--"                                { return DecrementPatternAction(createLexicalAnalyzerContext()); }
"+="                                { return PlusEqualsPatternAction(createLexicalAnalyzerContext()); }
"-="                                { return MinusEqualsPatternAction(createLexicalAnalyzerContext()); }

"<"                                 { return ComparationLexemeAction(createLexicalAnalyzerContext()); }
">"                                 { return ComparationLexemeAction(createLexicalAnalyzerContext()); }
"=="                                { return ComparationLexemeAction(createLexicalAnalyzerContext()); }
"<="                                { return ComparationLexemeAction(createLexicalAnalyzerContext()); }
">="                                { return ComparationLexemeAction(createLexicalAnalyzerContext()); }
"!="                                { return ComparationLexemeAction(createLexicalAnalyzerContext()); }

"{"                                 { return BraketsLexemeAction(createLexicalAnalyzerContext()); }/*listo*/
"}"                                 { return BraketsLexemeAction(createLexicalAnalyzerContext()); }

"%"                                 { return LogicLexemeAction(createLexicalAnalyzerContext()); }
"&&"                                { return LogicLexemeAction(createLexicalAnalyzerContext()); }
"||"                                { return LogicLexemeAction(createLexicalAnalyzerContext()); }

"game"                              { return TypeLexemeAction(createLexicalAnalyzerContext()); }/*listo*/
"design"                            { return TypeLexemeAction(createLexicalAnalyzerContext()); }  
"has"                               { return TypeLexemeAction(createLexicalAnalyzerContext()); }                
"for"                               { return TypeLexemeAction(createLexicalAnalyzerContext()); }
"type"                              { return TypeLexemeAction(createLexicalAnalyzerContext()); }
"value"                             { return TypeLexemeAction(createLexicalAnalyzerContext()); }

":"                                 { return PunctuationLexemeAction(createLexicalAnalyzerContext()); }/*listo*/
","                                 { return PunctuationLexemeAction(createLexicalAnalyzerContext()); }
"."                                 { return PunctuationLexemeAction(createLexicalAnalyzerContext()); }

"score"                             { return ScoreLexemeAction(createLexicalAnalyzerContext()); }

"Playing"                           { return PlayerLexemeAction(createLexicalAnalyzerContext()); }
"Waiting"                           { return PlayerLexemeAction(createLexicalAnalyzerContext()); }
"Deck"                              { return DeckLexemeAction(createLexicalAnalyzerContext()); }
"User"                              { return IdentifierLexemeAction(createLexicalAnalyzerContext()); }
"Machine"                           { return IdentifierLexemeAction(createLexicalAnalyzerContext()); }

"Hand"                              { return HandLexemeAction(createLexicalAnalyzerContext()); }
"SelectedCard"                      { return SelectedCardLexemeAction(createLexicalAnalyzerContext()); }

"foreach"                           { return ForEachLexemeAction(createLexicalAnalyzerContext()); }
"if"                                { return IfLexemeAction(createLexicalAnalyzerContext()); }
"else"                              { return ElseisLexemeAction(createLexicalAnalyzerContext()); }
"elif"                              { return ElifLexemeAction(createLexicalAnalyzerContext()); }

"NumbersOnDeck"                     { return LanguageFunctionLexemeAction(createLexicalAnalyzerContext()); }/*listo*/
"TypesOfCards"                      { return LanguageFunctionLexemeAction(createLexicalAnalyzerContext()); }
"CardsByPlayer"                     { return LanguageFunctionLexemeAction(createLexicalAnalyzerContext()); }
"Rounds"                            { return LanguageFunctionLexemeAction(createLexicalAnalyzerContext()); }
"RoundsTimer"                       { return LanguageFunctionLexemeAction(createLexicalAnalyzerContext()); }
"StartingScore"                     { return LanguageFunctionLexemeAction(createLexicalAnalyzerContext()); }
"WinRoundCondition"                 { return LanguageFunctionLexemeAction(createLexicalAnalyzerContext()); }
"WinGameCondition"                  { return LanguageFunctionLexemeAction(createLexicalAnalyzerContext()); }
"CardsDesign"                       { return LanguageFunctionLexemeAction(createLexicalAnalyzerContext()); }
"BackgroundDesign"                  { return LanguageFunctionLexemeAction(createLexicalAnalyzerContext()); }

"MoveCards"                         { return GameFunctionLexemeAction(createLexicalAnalyzerContext()); }/*listo*/
"LookAt"                            { return GameFunctionLexemeAction(createLexicalAnalyzerContext()); }
"RestockDeck"                       { return GameFunctionLexemeAction(createLexicalAnalyzerContext()); }
"WinGame"                           { return GameFunctionLexemeAction(createLexicalAnalyzerContext()); }
"WinnerType"                        { return GameFunctionLexemeAction(createLexicalAnalyzerContext()); }
"SpecialCardsOnPlay"                { return GameFunctionLexemeAction(createLexicalAnalyzerContext()); }

"RoundBorders"                      { return DesignFunctionLexemeAction(createLexicalAnalyzerContext()); }/*listo*/
"ColorBorders"                      { return DesignFunctionLexemeAction(createLexicalAnalyzerContext()); }
"BackgroundColor"                   { return DesignFunctionLexemeAction(createLexicalAnalyzerContext()); }

"("									{ return ParenthesisLexemeAction(createLexicalAnalyzerContext()); }/*listo*/
")"									{ return ParenthesisLexemeAction(createLexicalAnalyzerContext()); }

[[:digit:]]+						{ return IntegerLexemeAction(createLexicalAnalyzerContext()); }/*listo*/

[[:space:]]+						{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }/*listo*/

//VARIABLE
[[:alnum:]]+                        { return VariablePatternAction(createLexicalAnalyzerContext()); }

.									{ return UnknownLexemeAction(createLexicalAnalyzerContext()); }

%%

#include "FlexExport.h"
