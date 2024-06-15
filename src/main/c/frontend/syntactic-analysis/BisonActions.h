#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include "../../shared/CompilerState.h"
#include "../../shared/Logger.h"
#include "../../shared/Type.h"
#include "AbstractSyntaxTree.h"
#include "SyntacticAnalyzer.h"
#include <stdlib.h>
#include <stdbool.h>

/** Initialize module's internal state. */
void initializeBisonActionsModule();

/** Shutdown module's internal state. */
void shutdownBisonActionsModule();

/**
 * Bison semantic actions.
 */

Program * BlockSemanticAction(CompilerState * compilerState, Block * block);
Block * BlockValueSemanticAction(char * variable, int constant, Rules * rules);
Block * BlockTypeSemanticAction(char * variable, CardTypes * cardTypes, Rules * rules);
Block * BlockGameSemanticAction(char * variable, GameFunction * gameFunction);
Block * BlockDesignSemanticAction(char * variable, Design * design1);
Block * BlockRuleSemanticAction(char * variable, Rules * rules);
GameFunction * GameFunctionSemanticAction(int cteNumbersOnDeck, CardTypes * cardTypes, int cteCardsByPlayers, int cteRounds, int cteRoundTimer, int cteUserStartingScore, int cteMachineStartingScore, char * varWinRoundCondition, char * varWinGameCondition, char * varCardDesign, char * varBackDesign, Block * block);
CardTypes * CardTypeRuleSemanticAction(char * type );
CardTypes * MultipleCardTypesRuleSemanticAction(char * A, CardTypes *  B);
Rules * RuleStrcuturesSemanticAction(Structures * structures);
Rules * RuleMoveCardsSemanticAction(HandRef * leftHandRef, HandRef * rightHandRef, int constant, Rules * rule);
Rules * RuleLookAtSemanticAction(HandRef * handRef, int constant, Rules * rule);
Rules * RuleRestockDeckSemanticAction(Rules * rule);
Rules * RuleWinGameSemanticAction(Rules * rule);
Rules * RuleWinnerTypeSemanticAction(char * variable, Rules * rule);
Rules * RuleActivateSpecialCardsSemanticAction(Rules * rule);
Rules * RuleUserSemanticAction(UserRules * userRules);
Rules * RuleTiedSemanticAction(bool boolean, Rules * rule);
Rules * RuleFinishedSemanticAction(Block * block);
UserScore * UserScoreSemanticAction(User * user );
UserCard * UserCardSemanticAction(User * user);
Numbers * NumberConstSemanticAction(int constant);
Numbers * NumberUserSemanticAction(UserScore * userScore);
Expression * ExpressionArithmeticSemanticAction(Expression * expression1, Expression * expression2 );
Expression * ExpressionNumberSemanticAction(Numbers * numbers);
Expression * ExpressionAtomicSemanticAction(UserCard * usercard , Atomic * atomic);
Expression * ExpressionValueSemanticAction();
UserRules * UserRuleNumberSemanticAction(UserScore * userScore, Asignations * asignations,Numbers * numbers, Rules * rule);
UserRules * UserRuleCardSemanticAction(UserScore * userScore, Asignations * asignation, UserCard * userCard, Rules * rule);
UserRules * UserRuleArithmeticSemanticAction(UserScore * userScore, Asignations * asignations, Numbers * leftNum, Arithmetic * arithmetic, Numbers * rightNum, Rules * rule);
UserRules * UserRulePMOneSemanticAction(UserScore * userScore,PmOne * pmOne, Rules * rule);
UserRules * UserRuleGetterSemanticAction(Getters * leftGetter, Asignations * asignation, Getters * rightGetter, Rules * rule);
Getters * GettersSemanticAction(char * variable);
Structures * StructureIfSemanticAction(Ifs * conditional, InBrakets * inBrakets);
Structures * StructureForeachSemanticAction(Atomic * atomic, InBrakets * inBrakets);
Structures * StructureElseSemanticAction(InBrakets * inBrakets);
InBrakets * MultipleBraketsSemanticAction(Rules * leftRules, Rules * rightRules);
InBrakets * MultipleBraketsDesignSemanticAction(Design * leftDesign, Design * rightDesign);
Arithmetic * ArithmeticSemanticAction();
Asignations * AsignationsSemanticAction();
PmOne * PMOneSemanticAction();
HandRef * UserHandRefSemanticAction(User * user);
HandRef * DeckRefSemanticAction(Deck * deck);
Deck * DeckSemanticAction();
User * UserSemanticAction();
Ifs * IfSemanticAction(InIf * inIf);
Ifs * IfChainSemanticAction(InIf * leftInIf, InIf * rightInIf);
Ifs * IfTiedAction(bool tied);
InIf * InIfVariableSemanticAction(Comparison * comparison, char * variable);
InIf * InIfSpecialCardsSemanticAction();
InIf * InIfComparisonExpressionSemanticAction(Expression * leftExpression, Comparison * comparison, Expression * rightExpression);
Comparison * ComparisonSemanticAction();
Atomic * AtomicSemanticAction();
Design * RoundBordersDesignSemanticAction(int constant, Design * design2);
Design * ColorBordersDesignSemanticAction(char * variable, Design * design1);
Design * BackColorDesignSemanticAction(char * variable, Design * design1);
Design * DesignFinishedSemanticAction(Block * block);
Design * DesignStructuresSemanticAction(Structures * structures);

#endif
