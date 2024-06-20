#ifndef GENERATOR_HEADER
#define GENERATOR_HEADER

#include "../../frontend/syntactic-analysis/AbstractSyntaxTree.h"
#include "../../shared/CompilerState.h"
#include "../../shared/Logger.h"
#include "../../shared/String.h"
#include <stdarg.h>
#include <stdio.h>

/** Initialize module's internal state. */
void initializeGeneratorModule();

/** Shutdown module's internal state. */
void shutdownGeneratorModule();

/**
 * Generates the final output using the current compiler state.
 */
void generate(CompilerState * compilerState);

static void _generateProgram(Program * program);
static void _generateEpilogue(void);
static void _generatePrologue(void);
static void _generateProgram(Program * program);
static void _generateBlock(Block * block);
static void _generateRules(Rules * rules);
static void _generateUserScore(UserScore * userScore);
static void _generateGameFunction(GameFunction * gameFunction);
static void _generateCardTypes(CardTypes * cardTypes);
static void _generateUserCard(UserCard * userCard);
static void _generateNumbers(Numbers * numbers);
static void _generateUserRules(UserRules * userRules);
static void _generateGetters(Getters * getters);
static void _generateArithmetic(Arithmetic * arithmetic);
static void _generateAsignations(Asignations * asignations);
static void _generatePmOne(PmOne * pmOne);
static void _generateStructures(Structures * structures);
static void _generateInBrakets(InBrakets * inBrakets);
static void _generateHandRef(HandRef * handRef);
static void _generateDeck(Deck * deck);
static void _generateUser(User * user);
static void _generateIfs(Ifs * ifs);
static void _generateInIf(InIf * inIf);
static void _generateComparison(Comparison * comparison);
static void _generateAtomic(Atomic * atomic);
static void _generateBoolean(bool boolean);
static void _generateVariable(char * variable);
static void _generateInteger(int constant);

#endif
