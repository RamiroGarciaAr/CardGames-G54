#ifndef ABSTRACT_SYNTAX_TREE_HEADER
#define ABSTRACT_SYNTAX_TREE_HEADER

#include "../../shared/Logger.h"
#include <stdlib.h>

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
typedef enum BoolType BoolType;
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
typedef struct Constant Constant;
typedef struct Variable Variable;
typedef struct Block Block;
typedef struct GameFunction GameFunction;
typedef struct Rules Rules;
typedef struct Bool Bool;
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
typedef struct Tied Tied;
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

enum BoolType  {
	BOOL_TRUE,
	BOOL_FALSE
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

struct Constant {
	int value;
};

struct Variable{
	char * name;
};

struct Bool {
	boolean value;
};

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

struct Tied {
	Bool * tied;
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
			Variable * variable;
			Constant * constant;
			Rules * rules;
		};
		struct {
			Variable * variable1;
			CardTypes * cardTypes;
			Rules * rules1;
		};
		struct {
			Variable * variable2;
			GameFunction * gameFunctions;
		};
		struct {
			Variable * variable3;
			Design * design;
		};
	};
	BlockType type;
};

struct GameFunction { 
	Constant * cteNumbersOnDeck;
	CardTypes * cardTypes;
	Constant * cteCardsByPlayers;
	Constant * cteRounds;
	Constant * cteRoundTimer;		
	Constant * cteUserStartingScore;	
	Constant * cteMachineStartingScore;	
	Variable * varWinRoundCondition;	
	Variable * varWinGameCondition;	
	Variable * varCardDesign;	
	Variable * varBackDesign;	
};

struct CardTypes {
	union {
		Variable * variable;
		struct {
			Variable * variable1;
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
            Constant * constant;
        };
        struct {
            HandRef * handRef;
            Constant * constant1;
        };
		Variable * variable;
		UserRules * userRules;
		Tied * tied;
    };
    RuleType type;
};

struct Numbers{
	union {
		Constant * constant;
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
		Tied * tied;
	};
	IfType type;
};

struct InIf {
	union {
		struct {
			Comparison * comparison;
			Constant * constant;
		};
		struct {
			Comparison * comparison1;
			Variable * variable;
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
		Variable * roundBorders;
		Variable * colorBorders;
		Variable * backgroundColor;
	};
	DesignType type;
};
	

/**
 * Node recursive destructors.
 */
void releaseConstant(Constant * constant);
void releaseExpression(Expression * expression);
void releaseProgram(Program * program);

#endif
