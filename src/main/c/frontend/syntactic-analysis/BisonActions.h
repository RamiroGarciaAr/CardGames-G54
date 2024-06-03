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
Block * BlockDesignSemanticAction(char * variable, Design * design);
GameFunction * GameFunctionSemanticAction(int cteNumbersOnDeck, CardTypes * cardTypes, int cteCardsByPlayers, int cteRounds, int cteRoundTimer, int cteUserStartingScore, int cteMachineStartingScore, char * varWinRoundCondition, char * varWinGameCondition, char * varCardDesign, char * varBackDesign);
CardTypes * CardTypeRuleSemanticAction(char * type );
CardTypes * MultipleCardTypesRuleSemanticAction(char * A, CardTypes *  B);
Rules * RuleStrcuturesSemanticAction(Structures * structures);
Rules * RuleMoveCardsSemanticAction(HandRef * leftHandRef, HandRef * rightHandRef, int constant);
Rules * RuleLookAtSemanticAction(HandRef * handRef, int constant);
Rules * RuleRestockDeckSemanticAction();
Rules * RuleWinGameSemanticAction();
Rules * RuleWinnerTypeSemanticAction(char * variable);
Rules * RuleActivateSpecialCardsSemanticAction();
Rules * RuleUserSemanticAction(UserRules * userRules);
Rules * RuleTiedSemanticAction(bool boolean);
UserScore * UserScoreSemanticAction(User * user );
UserCard * UserCardSemanticAction(User * user);
Numbers * NumberConstSemanticAction(int constant);
Numbers * NumberUserSemanticAction(UserScore * userScore);
Expression * ExpressionArithmeticSemanticAction(Expression * expression1 ,Arithmetic * arithmetic ,Expression * expression2 );
Expression * ExpressionNumberSemanticAction(Numbers * numbers);
Expression * ExpressionAtomicSemanticAction(UserCard * usercard , Atomic * atomic);
UserRules * UserRuleNumberSemanticAction(UserScore * userScore, Asignations * asignations,Numbers * numbers);
UserRules * UserRuleArithmeticSemanticAction(UserScore * userScore, Asignations * asignations, Numbers * leftNum, Arithmetic * arithmetic, Numbers * rightNum);
UserRules * UserRulePMOneSemanticAction(UserScore * userScore,PmOne * pmOne);
Structures * StructureIfSemanticAction(Ifs * conditional, InBrakets * inBrakets);
Structures * StructureForeachSemanticAction(Atomic * atomic, InBrakets * inBrakets);
Structures * StructureElseSemanticAction(InBrakets * inBrakets);
InBrakets * BraketsSemanticAction(Rules * rules);
InBrakets * MultipleBraketsSemanticAction(Rules * leftRules, Rules * rightRules);
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
InIf * InIfConstantSemanticAction(Comparison * comparison, int constant);
InIf * InIfVariableSemanticAction(Comparison * comparison, char * variable);
InIf * InIfSpecialCardsSemanticAction();
InIf * InIfComparisonExpressionSemanticAction(Expression * leftExpression, Comparison * comparison, Expression * rightExpression);
Comparison * ComparisonSemanticAction();
Atomic * AtomicSemanticAction();
Design * RoundBordersDesignSemanticAction(char * variable);
Design * ColorBordersDesignSemanticAction(char * variable);
Design * BackColorDesignSemanticAction(char * variable);

#endif
