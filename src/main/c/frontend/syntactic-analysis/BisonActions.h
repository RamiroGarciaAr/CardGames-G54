#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include "../../shared/CompilerState.h"
#include "../../shared/Logger.h"
#include "../../shared/Type.h"
#include "AbstractSyntaxTree.h"
#include "SyntacticAnalyzer.h"
#include <stdlib.h>

/** Initialize module's internal state. */
void initializeBisonActionsModule();

/** Shutdown module's internal state. */
void shutdownBisonActionsModule();

/**
 * Bison semantic actions.
 */

Program * BlockSemanticAction(CompilerState * compilerState, Block * block);
Block * BlockValueSemanticAction(Variable * variable, Constant * constant, Rules * rules);
Block * BlockTypeSemanticAction(Variable * variable, CardTypes * cardTypes, Rules * rules);
Block * BlockGameSemanticAction(Variable * variable, GameFunction * gameFunction);
Block * BlockDesignSemanticAction(Variable * variable, Design * design);
GameFunction * GameFunctionSemanticAction(Constant * cteNumbersOnDeck, CardTypes * cardTypes,Constant * cteCardsByPlayers,Constant * cteRounds,Constant * cteRoundTimer, Constant * cteUserStartingScore,Constant * cteMachineStartingScore,Variable * varWinRoundCondition,Variable * varWinGameCondition, Variable * varCardDesign,Variable * varBackDesign);
CardTypes * CardTypeRuleSemanticAction(Variable * type );
CardTypes * MultipleCardTypesRuleSemanticAction(Variable * A, CardTypes *  B);
Rules * RuleStrcuturesSemanticAction(Structures * structures);
Rules * RuleMoveCardsSemanticAction(HandRef * leftHandRef, HandRef * rightHandRef, Constant * constant);
Rules * RuleLookAtSemanticAction(HandRef * handRef, Constant * constant);
Rules * RuleRestockDeckSemanticAction();
Rules * RuleWinGameSemanticAction();
Rules * RuleWinnerTypeSemanticAction(Variable * variable);
Rules * RuleActivateSpecialCardsSemanticAction();
Rules * RuleUserSemanticAction(UserRules * userRules);
Rules * RuleTiedSemanticAction(Tied * boolean);
UserScore * UserScoreSemanticAction(User * user );
UserCard * UserCardSemanticAction(User * user);
Numbers * NumberConstSemanticAction(Constant * constant);
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
Ifs * IfTiedAction(Tied * tied);
InIf * InIfConstantSemanticAction(Comparison * comparison, Constant * constant);
InIf * InIfVariableSemanticAction(Comparison * comparison, Variable * variable);
InIf * InIfSpecialCardsSemanticAction();
InIf * InIfComparisonExpressionSemanticAction(Expression * leftExpression, Comparison * comparison, Expression * rightExpression);
Comparison * ComparisonSemanticAction();
Atomic * AtomicSemanticAction();
Tied * TiedSemanticAction();
Design * RoundBordersDesignSemanticAction(Variable * variable);
Design * ColorBordersDesignSemanticAction(Variable * variable);
Design * BackColorDesignSemanticAction(Variable * variable);
Constant * IntegerConstantSemanticAction(const int value);
Variable * VariableSemanticAction(char * name);
Bool * BooleanSemanticAction(const boolean value);

#endif
