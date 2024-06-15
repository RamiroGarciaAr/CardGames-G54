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
typedef enum GettersType GettersType;
typedef enum StructuresType StructuresType;
typedef enum InBraketsType InBraketsType;
typedef enum HandRefType HandRefType;
typedef enum IfType IfType;
typedef enum InIfType InIfType;
typedef enum ComparisonType ComparisonType;
typedef enum AtomicType AtomicType;
typedef enum DesignType DesignType;
typedef enum UserType UserType;

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
typedef struct Getters Getters;
typedef struct Structures Structures;
typedef struct HandRef HandRef;
typedef struct InBrakets InBrakets;
typedef struct Deck Deck;
typedef struct Ifs Ifs;
typedef struct InIf InIf;
typedef struct Comparison Comparison;
typedef struct Atomic Atomic;
typedef struct Design Design;
typedef struct Program Program;

/**
 * Node types for the Abstract Syntax Tree (AST).
 */
 
/* ------------------------------------------------- ENUMS ------------------------------------------------- */

enum ExpressionType {
	ARIT_ADD,
	ARIT_DIV,
	ARIT_MUL,
	ARIT_SUB,
	ARIT_MODULE,
	NUMBERS,
	ATOMIC
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
	RULE_WINNER_TYPE,
	USER_RULES,
	TIED_RULE,
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
	PMO_ASSIG,
	GETTER_ASSIG	
};

enum GettersType{
	GETTER_LOSER,
	GETTER_WINNER
};

enum StructuresType {
	IF_STRUCTURE,
	FOREACH_STRUCTURE,
	ELIF_STRUCTURE,
	ELSE_STRUCTURE
};

enum InBraketsType{
	MULTIPLE_RULES,
	MULTIPLE_DESIGNS
};

enum HandRefType {
	USER,
	HAND_DECK
};

enum IfType {
	INIF, 
	AND_IF,
	OR_IF,
	TIED_IF
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

enum DesignType {
	ROUND_BORDERS_DESIGN,
	COLOR_BORDERS_DESIGN,
	BACKGROUND_COLOR_DESIGN,
	FINISHED_DESIGN,
	STRUCTURES_DESIGN
};

enum UserType{
	USER_PLAYER,
	USER_IDENTIFIER
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
			Design * design1;
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
        UserRules * userRules;
        struct {
            bool tied;
            Rules * rule4;
        };
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
		struct {
			Getters * leftGetter;
			Asignations * asignations2;
			Getters * rightGetter;
			Rules * rule3;
		};
	};
	UserRulesType type;
};

struct Getters{
	char * variable;
	GettersType type;
};

struct Structures {
	union {
		struct {
			Ifs * conditional;
			InBrakets * inBrakets;
		};
		struct {
			Atomic *  atomic;
			InBrakets * inBrakets1;
		};
		InBrakets * inBrakets2;
	};
	StructuresType type;
};

struct InBrakets {
	union {
		Rules * leftRules;
		Rules * rightRules;	
	};
	union {
		Design * leftDesign;
		Design * rightDesign;
	};
	InBraketsType type;
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
		bool tied;
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


struct Design {
	union{
		struct {
			int constant;
			Design * design2;
		};
		struct {
			char * variable;
			Design * design1;
		};
		Block * block;
		Structures * structures;
	};
	DesignType type;
};

/**
 * Node recursive destructors.
 */
void releaseProgram(Program * program);

#endif
