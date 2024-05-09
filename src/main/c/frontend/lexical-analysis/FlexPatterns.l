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

"++"                                { return DummyLexemeAction(); }
"--"                                { return DummyLexemeAction(); }
"+="                                { return DummyLexemeAction(); }
"-="                                { return DummyLexemeAction(); }

"<"                                 { return DummyLexemeAction(); }
">"                                 { return DummyLexemeAction(); }
"=="                                { return DummyLexemeAction(); }
"<="                                { return DummyLexemeAction(); }
">="                                { return DummyLexemeAction(); }
"!="                                { return DummyLexemeAction(); }

","                                 { return DummyLexemeAction(); }
"."                                 { return DummyLexemeAction(); }

"{"                                 { return DummyLexemeAction(); }
"}"                                 { return DummyLexemeAction(); }

"%"                                 { return DummyLexemeAction(); }
"&&"                                { return DummyLexemeAction(); }
"||"                                { return DummyLexemeAction(); }

"game"                              { return DummyLexemeAction(); }
"design"                            { return DummyLexemeAction(); }
"has"                               { return DummyLexemeAction(); }
"for"                               { return DummyLexemeAction(); }
"type"                              { return DummyLexemeAction(); }
"value"                             { return DummyLexemeAction(); }
":"                                 { return DummyLexemeAction(); }

"score"                             { return DummyLexemeAction(); }

"Playing"                           { return DummyLexemeAction(); }
"Waiting"                           { return DummyLexemeAction(); }
"Deck"                              { return DummyLexemeAction(); }
"User"                              { return DummyLexemeAction(); }
"Machine"                           { return DummyLexemeAction(); }

"Hand"                              { return DummyLexemeAction(); }

"foreach"                           { return DummyLexemeAction(); }
"if"                                { return DummyLexemeAction(); }
"else"                              { return DummyLexemeAction(); }
"elif"                              { return DummyLexemeAction(); }

"NumbersOnDeck"                     { return DummyLexemeAction(); }
"TypesOfCards"                      { return DummyLexemeAction(); }
"CardsByPlayer"                     { return DummyLexemeAction(); }
"Rounds"                            { return DummyLexemeAction(); }
"RoundsTimer"                       { return DummyLexemeAction(); }
"StartingScore"                     { return DummyLexemeAction(); }
"WinRoundCondition"                 { return DummyLexemeAction(); }
"WinGameCondition"                  { return DummyLexemeAction(); }
"CardsDesign"                       { return DummyLexemeAction(); }
"BackgroundDesign"                  { return DummyLexemeAction(); }

"MoveCards"                         { return DummyLexemeAction(); }
"LookAt"                            { return DummyLexemeAction(); }
"RestockDeck"                       { return DummyLexemeAction(); }
"WinGame"                           { return DummyLexemeAction(); }
"WinnerType"                        { return DummyLexemeAction(); }
"SpecialCardsOnPlay"                { return DummyLexemeAction(); }

"RoundBorders"                      { return DummyLexemeAction(); }
"ColorBorders"                      { return DummyLexemeAction(); }
"BackgroundColor"                   { return DummyLexemeAction(); }

/*
"++"                                { return IncrementPatternAction(createLexicalAnalyzerContext()); }
"--"                                { return DecrementPatternAction(createLexicalAnalyzerContext()); }
"+="                                { return PlusEqualsPatternAction(createLexicalAnalyzerContext()); }
"-="                                { return IncrementPatternAction(createLexicalAnalyzerContext()); }

"<"                                 { return ComparationLexemeAction(createLexicalAnalyzerContext()); }
">"                                 { return ComparationLexemeAction(createLexicalAnalyzerContext()); }
"=="                                { return ComparationLexemeAction(createLexicalAnalyzerContext()); }
"<="                                { return ComparationLexemeAction(createLexicalAnalyzerContext()); }
">="                                { return ComparationLexemeAction(createLexicalAnalyzerContext()); }
"!="                                { return ComparationLexemeAction(createLexicalAnalyzerContext()); }

","                                 { return CommaLexemeAction(createLexicalAnalyzerContext()); }
"."                                 { return DotLexemeAction(createLexicalAnalyzerContext()); }

"{"                                 { return BraketsLexemeAction(createLexicalAnalyzerContext()); }
"}"                                 { return BraketsLexemeAction(createLexicalAnalyzerContext()); }

"%"                                 { return ModuleLexemeAction(createLexicalAnalyzerContext()); }
"&&"                                { return LogicLexemeAction(createLexicalAnalyzerContext()); }
"||"                                { return LogicLexemeAction(createLexicalAnalyzerContext()); }

"game"                              { return TypeLexemeAction(createLexicalAnalyzerContext()); }
"design"                            { return TypeLexemeAction(createLexicalAnalyzerContext()); }  
"has"                               { return TypeLexemeAction(createLexicalAnalyzerContext()); }                
"for"                               { return TypeLexemeAction(createLexicalAnalyzerContext()); }
"type"                              { return TypeLexemeAction(createLexicalAnalyzerContext()); }
"value"                             { return TypeLexemeAction(createLexicalAnalyzerContext()); }
":"                                 { return TypeLexemeAction(createLexicalAnalyzerContext()); }

"score"                             { return ScoreLexemeAction(createLexicalAnalyzerContext()); }
"SelectedCard"                      { return SelectedCardLexemeAction(createLexicalAnalyzerContext()); }

"Playing"                           { return PlayerLexemeAction(createLexicalAnalyzerContext()); }
"Waiting"                           { return PlayerLexemeAction(createLexicalAnalyzerContext()); }
"Deck"                              { return DeckLexemeAction(createLexicalAnalyzerContext()); }
"User"                              { return IdentifierLexemeAction(createLexicalAnalyzerContext()); }
"Machine"                           { return IdentifierLexemeAction(createLexicalAnalyzerContext()); }

"Hand"                              { return HandLexemeAction(createLexicalAnalyzerContext()); }

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
*/

"("									{ return ParenthesisLexemeAction(createLexicalAnalyzerContext()); }
")"									{ return ParenthesisLexemeAction(createLexicalAnalyzerContext()); }

[[:digit:]]+						{ return IntegerLexemeAction(createLexicalAnalyzerContext()); }

[[:space:]]+						{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }

/*
//VARIABLE
[[:alnum:]]+                        { return VariablePatternAction(createLexicalAnalyzerContext()); }
*/

[[:alnum:]]+                        { return DummyLexemeAction(); }

.									{ return UnknownLexemeAction(createLexicalAnalyzerContext()); }

%%

#include "FlexExport.h"
