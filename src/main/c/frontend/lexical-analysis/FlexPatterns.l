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

"/*"								{ BEGIN(MULTILINE_COMMENT); BeginMultilineCommentLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>"*/"				{ EndMultilineCommentLexemeAction(createLexicalAnalyzerContext()); BEGIN(INITIAL); }
<MULTILINE_COMMENT>[[:space:]]+		{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>[^*]+			{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>.				{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }

"//"								{ BEGIN(ONELINE_COMMENT); BeginOnelineCommentLexemeAction(createLexicalAnalyzerContext()); }
<ONELINE_COMMENT>"\n"				{ EndOnelineCommentLexemeAction(createLexicalAnalyzerContext()); BEGIN(INITIAL); }
<ONELINE_COMMENT>[[:space:]]+		{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<ONELINE_COMMENT>.					{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }

"-"									{ return ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext()); }
"*"									{ return ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext()); }
"/"									{ return ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext()); }
"+"									{ return ArithmeticOperatorLexemeAction(createLexicalAnalyzerContext()); }

"++"                                { return OperatorPatternAction(createLexicalAnalyzerContext()); }
"--"                                { return OperatorPatternAction(createLexicalAnalyzerContext()); }
"+="                                { return OperatorPatternAction(createLexicalAnalyzerContext()); }
"-="                                { return OperatorPatternAction(createLexicalAnalyzerContext()); }

"<"                                 { return ComparationLexemeAction(createLexicalAnalyzerContext()); }
">"                                 { return ComparationLexemeAction(createLexicalAnalyzerContext()); }
"=="                                { return ComparationLexemeAction(createLexicalAnalyzerContext()); }
"<="                                { return ComparationLexemeAction(createLexicalAnalyzerContext()); }
">="                                { return ComparationLexemeAction(createLexicalAnalyzerContext()); }
"!="                                { return ComparationLexemeAction(createLexicalAnalyzerContext()); }
"="                                 { return ComparationLexemeAction(createLexicalAnalyzerContext()); }

"{"                                 { return BraketsLexemeAction(createLexicalAnalyzerContext()); }
"}"                                 { return BraketsLexemeAction(createLexicalAnalyzerContext()); }

"%"                                 { return LogicLexemeAction(createLexicalAnalyzerContext()); }
"&&"                                { return LogicLexemeAction(createLexicalAnalyzerContext()); }
"||"                                { return LogicLexemeAction(createLexicalAnalyzerContext()); }

"game"                              { return TypeLexemeAction(createLexicalAnalyzerContext()); }
"design"                            { return TypeLexemeAction(createLexicalAnalyzerContext()); }  
"has"                               { return TypeLexemeAction(createLexicalAnalyzerContext()); }                
"for"                               { return TypeLexemeAction(createLexicalAnalyzerContext()); }
"type"                              { return TypeLexemeAction(createLexicalAnalyzerContext()); }
"value"                             { return TypeLexemeAction(createLexicalAnalyzerContext()); }

":"                                 { return PunctuationLexemeAction(createLexicalAnalyzerContext()); }
","                                 { return PunctuationLexemeAction(createLexicalAnalyzerContext()); }
"."                                 { return PunctuationLexemeAction(createLexicalAnalyzerContext()); }

"Playing"                           { return GamingLexemeAction(createLexicalAnalyzerContext()); }
"Waiting"                           { return GamingLexemeAction(createLexicalAnalyzerContext()); }
"Deck"                              { return GamingLexemeAction(createLexicalAnalyzerContext()); }
"User"                              { return GamingLexemeAction(createLexicalAnalyzerContext()); }
"Machine"                           { return GamingLexemeAction(createLexicalAnalyzerContext()); }

"Hand"                              { return PlayerReferenceLexemeAction(createLexicalAnalyzerContext()); }
"SelectedCard"                      { return PlayerReferenceLexemeAction(createLexicalAnalyzerContext()); }
"score"                             { return PlayerReferenceLexemeAction(createLexicalAnalyzerContext()); }
"tied"                              { return PlayerReferenceLexemeAction(createLexicalAnalyzerContext()); }

"foreach"                           { return ControlStructureLexemeAction(createLexicalAnalyzerContext()); }
"if"                                { return ControlStructureLexemeAction(createLexicalAnalyzerContext()); }
"else"                              { return ControlStructureLexemeAction(createLexicalAnalyzerContext()); }
"elif"                              { return ControlStructureLexemeAction(createLexicalAnalyzerContext()); }

"true"                              { return BooleanLexemeAction(createLexicalAnalyzerContext()); }
"false"                             { return BooleanLexemeAction(createLexicalAnalyzerContext()); }

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
"ActivateSpecialCards"              { return GameFunctionLexemeAction(createLexicalAnalyzerContext()); }
"GetLoser"                          { return GameFunctionLexemeAction(createLexicalAnalyzerContext()); }
"GetWinner"                         { return GameFunctionLexemeAction(createLexicalAnalyzerContext()); }

"RoundBorders"                      { return DesignFunctionLexemeAction(createLexicalAnalyzerContext()); }
"ColorBorders"                      { return DesignFunctionLexemeAction(createLexicalAnalyzerContext()); }
"BackgroundColor"                   { return DesignFunctionLexemeAction(createLexicalAnalyzerContext()); }

"("									{ return ParenthesisLexemeAction(createLexicalAnalyzerContext()); }
")"									{ return ParenthesisLexemeAction(createLexicalAnalyzerContext()); }

[[:digit:]]+						{ return IntegerLexemeAction(createLexicalAnalyzerContext()); }

[[:space:]]+						{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }

[[:alnum:]]+                        { return VariablePatternAction(createLexicalAnalyzerContext()); }

.									{ return UnknownLexemeAction(createLexicalAnalyzerContext()); }

%%

#include "FlexExport.h"
