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
#pragma region Typedefs
#pragma region EnumsDefinitions
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
typedef enum InBraketsType InBraketsType;
typedef enum HandRefType HandRefType;
typedef enum IfType IfType;
typedef enum InIfType InIfType;
typedef enum ComparisonType ComparisonType;
typedef enum AtomicType AtomicType;
typedef enum DesignType DesignType;
typedef enum UserType UserType;
#pragma endregion EnumsDefinitions

#pragma region ExpresionDefinitions
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
typedef struct Design Design;
typedef struct Program Program;

#pragma endregion ExpresionDefinitions


#pragma endregion typedefs
/**
 * Node types for the Abstract Syntax Tree (AST).
 */
 
/* ------------------------------------------------- ENUMS ------------------------------------------------- */
#pragma region Enums

enum ExpressionType {
	ARITHMETIC,
	NUMBERS,
	ATOMIC
};

enum BlockType {
	VALUE_BLOCK,
	TYPE_BLOCK,
	GAME_BLOCK,
	DESIGN_BLOCK
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
	TIED_RULE
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
	ARITHMETIC_ASSIG,
	PMO_ASSIG	
};

enum StructuresType {
	IF_STRUCTURE,
	FOREACH_STRUCTURE,
	ELIF_STRUCTURE,
	ELSE_STRUCTURE
};

enum InBraketsType{
	ONE_IF,
	MULTIPLE_IF
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
	VALUE_IF,
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
	BACKGROUND_COLOR_DESIGN
};

enum UserType{
	USER_PLAYER,
	USER_IDENTIFIER
};

#pragma endregion 
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
			Design * design;
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
	Block * block1; 
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
			Rules * rule ; 
        };
        struct {
            HandRef * handRef;
            int constant1;
        };
		char * variable;
		UserRules * userRules;
		bool tied;
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
			Arithmetic * arithmetic;
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
		};
		struct{
			UserScore * userScore1;
			Asignations * asignations1;
			Numbers * leftNumber;
			Arithmetic * arithmetic;
			Numbers * rightNumber;
		};
		struct{
			UserScore * userScore2;
			PmOne * pmOne;
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
		Rules * rules;
		struct {
			Rules * leftRules;
			Rules * rightRules;	
		};
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
			Comparison * comparison;
			int constant;
		};
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
		char * roundBorders;
		char * colorBorders;
		char * backgroundColor;
	};
	DesignType type;
};

struct Boolean{
	bool value;
};
	

/**
 * Node recursive destructors.
 */
void releaseProgram(Program * program);

#endif
