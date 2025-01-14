#ifndef ABSTRACT_SYNTAX_TREE_HEADER
#define ABSTRACT_SYNTAX_TREE_HEADER

#include "../../shared/Logger.h"
#include <stdlib.h>
#include <stdbool.h>

/** Initialize module's internal state. */
void initializeAbstractSyntaxTreeModule();

/** Shutdown module's internal state. */
void shutdownAbstractSyntaxTreeModule();

/**
 * This typedefs allows self-referencing types.
 */
/* ------------------------------------------------- TYPEDEF ------------------------------------------------- */
typedef enum ExpressionType ExpressionType;
typedef enum BlockType BlockType;
typedef enum CardTypesType CardTypesType;
typedef enum RuleType RuleType;
typedef enum NumbersType NumbersType;
typedef enum PmOneType PmOneType;
typedef enum ArithmeticType ArithmeticType;
typedef enum AsignationsType AsignationsType;
typedef enum UserRulesType UserRulesType;
typedef enum StructuresType StructuresType;
typedef enum HandRefType HandRefType;
typedef enum IfType IfType;
typedef enum InIfType InIfType;
typedef enum ComparisonType ComparisonType;
typedef enum AtomicType AtomicType;
typedef enum UserType UserType;
typedef enum WithType WithType;

typedef struct Block Block;
typedef struct GameFunction GameFunction;
typedef struct Rules Rules;
typedef struct UserScore UserScore;
typedef struct UserCard UserCard;
typedef struct Numbers Numbers;
typedef struct Expression Expression;
typedef struct User User;
typedef struct UserRules UserRules;
typedef struct PmOne PmOne;
typedef struct Arithmetic Arithmetic;
typedef struct Asignations Asignations;
typedef struct CardTypes CardTypes;
typedef struct Structures Structures;
typedef struct HandRef HandRef;
typedef struct InBrakets InBrakets;
typedef struct Deck Deck;
typedef struct Ifs Ifs;
typedef struct InIf InIf;
typedef struct Comparison Comparison;
typedef struct Atomic Atomic;
typedef struct Program Program;
typedef struct With With;

/**
 * Node types for the Abstract Syntax Tree (AST).
 */
 
/* ------------------------------------------------- ENUMS ------------------------------------------------- */

enum ExpressionType {
	EXPR_ADD,
	EXPR_DIV,
	EXPR_MUL,
	EXPR_SUB,
	EXPR_MODULE,
	NUMBERS,
	ATOMIC,
	EXPR_VALUE
};

enum BlockType {
	VALUE_BLOCK,
	TYPE_BLOCK,
	GAME_BLOCK,
	DESIGN_BLOCK,
	RULE_BLOCK
};

enum CardTypesType{
	ONE_TYPE,
	MULTIPLE_TYPE
};

enum RuleType {
    STRUCTURES,
    RULE_MOVE_CARDS,
    RULE_LOOK_AT,
    RULE_RESTOCK_DECK,
    RULE_WIN_GAME,
    RULE_WINNER_TYPE,
    RULE_ACTIVATE_SPECIAL_CARDS,
	COLOR_BORDERS_DESIGN,
	BACKGROUND_COLOR_DESIGN,
    USER_RULES,
    FINISH_RULE
};

enum NumbersType {
	CONSTANT,
	USER_SCORE
};

enum PmOneType{
	INCREASE,
	DECREASE
};

enum ArithmeticType {
	ARIT_ADD,	
	ARIT_DIV,
	ARIT_MUL,
	ARIT_SUB,
	ARIT_MODULE
};

enum AsignationsType {
	ASIG_EQUAL,
	ASIG_ADD_EQUAL,
	SUB_EQUAL
};

enum UserRulesType{
	NUMBER_ASSIG,
	CARD_ASSIG,
	ARITHMETIC_ASSIG,
	PMO_ASSIG	
};

enum StructuresType {
	IF_STRUCTURE,
	ELIF_STRUCTURE,
	ELSE_STRUCTURE,
	WITH_STRUCTURE
};

enum HandRefType {
	USER,
	HAND_DECK
};

enum IfType {
	INIF, 
	AND_IF,
	OR_IF
};

enum InIfType {
	TYPE_IF,
	ACTIVATE_SPECIAL_CARDS_IF,
	EXPRESSION_IF
};

enum ComparisonType{
	COMP_GREATER,
	COMP_LOWER,
	COMP_EQUAL_EQUAL,
	COMP_GREATER_OR_EQUAL,
	COMP_LOWER_OR_EQUAL,
	COMP_DIFERENT
};

enum AtomicType{
	ATOMIC_VALUE,
	ATOMIC_TYPE
};

enum UserType{
	USER_PLAYER,
	USER_IDENTIFIER
};

enum WithType{
	VALUE_WITH,
	TYPE_WITH
};

/* ------------------------------------------------- EXPRESSIONS ------------------------------------------------- */

struct User{
	UserType type; 
};

struct UserScore {
	User * user;
};

struct UserCard {
	User * user;
};

struct Deck {
	Deck * deck;
};

struct Program {
	Block * block;
};

struct PmOne{
	PmOneType type;
};

struct Arithmetic {
	ArithmeticType type;
};

struct Asignations {
	AsignationsType type;
};

struct Comparison {
	ComparisonType type;
};

struct Atomic {
	AtomicType type;
};

struct Block {
	union {
		struct {
			char * variable;
			int constant;
			Rules * rules;
		};
		struct {
			char * variable1;
			CardTypes * cardTypes;
			Rules * rules1;
		};
		struct {
			char * variable2;
			GameFunction * gameFunction;
		};
		struct {
			char * variable3;
			Rules * rules3;
		};
		struct {
			char * variable4;
			Rules * rules2;
		};
	};
	BlockType type;
};

struct GameFunction { 
	int cteNumbersOnDeck;
	CardTypes * cardTypes;
	int cteCardsByPlayers;
	int cteRounds;
	int cteRoundTimer;		
	int cteUserStartingScore;	
	int cteMachineStartingScore;	
	char * varWinRoundCondition;	
	char * varWinGameCondition;	
	char * varCardDesign;	
	char * varBackDesign;	
	Block * block; 
};

struct CardTypes {
	union {
		char * variable;
		struct {
			char * variable1;
			CardTypes * cardType;
		};
	};
	CardTypesType type;
};

struct Rules {
    union {
        Structures * structures;
        struct {
            HandRef * leftHandRef;
            HandRef * rightHandRef;
            int constant;
            Rules * rule;
        };
        struct {
            HandRef * handRef;
            int constant1;
            Rules * rule1;
        };
        Rules * rule2;
        struct {
            char * variable;
            Rules * rule3;
        };
		struct {
			User * user;
			Rules * rule4;
		};
		struct {
            char * variable2;
			char * variable3;
            Rules * rule6;
        };
        UserRules * userRules;
		Block * block;
    };
    RuleType type;
};

struct Numbers{
	union {
		int constant;
		UserScore * userScore;
	};
	NumbersType type;
};

struct Expression {
	union {
		struct {
			Expression * leftExpression;
			Expression * rightExpression;
		};
		Numbers * numbers;
		struct {
			UserCard * userCard;
			Atomic * atomic;
		};
	};
	ExpressionType type;
};

struct UserRules{
	union{
		struct{
			UserScore * userScore;
			Asignations * asignations;
			Numbers * numbers;
			Rules * rule;
		};
		struct {
			UserScore * userScore3;
			Asignations * asignations3;
			UserCard * userCard;
			Rules * rule4;
		};
		struct{
			UserScore * userScore1;
			Asignations * asignations1;
			Numbers * leftNumber;
			Arithmetic * arithmetic;
			Numbers * rightNumber;
			Rules * rule1;
		};
		struct{
			UserScore * userScore2;
			PmOne * pmOne;
			Rules * rule2;
		};
	};
	UserRulesType type;
};

struct Structures {
	union {
		struct {
			Ifs * conditional;
			InBrakets * inBrakets;
		};
		struct{
			With * with;
			InBrakets * inBrakets3;
		};
		InBrakets * inBrakets2;
	};
	StructuresType type;
};

struct With{
	union{
		int constant;
		char * variable;
	};
	WithType type;
};

struct InBrakets {
    Rules * leftRules;
    Rules * rightRules;
};

struct HandRef{
	union{
		User * user;
		Deck * deck;
	};
	HandRefType type;
};

struct Ifs {
	union {
		InIf * inIf;
		struct {
			InIf * leftInIf;
			InIf * rightInIf;
		};
	};
	IfType type;
};

struct InIf {
	union {
		struct {
			Comparison * comparison1;
			char * variable;
		};
		struct {
			Expression * leftExpression;
			Comparison * comparison2;
			Expression * rightExpression;
		};
	};
	InIfType type;
};

/**
 * Node recursive destructors.
 */
void releaseProgram(Program * program);

#endif
