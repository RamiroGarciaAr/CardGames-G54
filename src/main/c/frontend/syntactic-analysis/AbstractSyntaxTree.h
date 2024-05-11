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
typedef enum AritmethicType AritmethicType;
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
typedef struct Aritmethic Aritmethic;
typedef struct Asignation Asignation;
typedef struct CardTypes CardTypes;
typedef struct Structures Structures;
typedef struct HandRef HandRef;
typedef struct InBrakets InBrakets;
typedef struct Deck Deck;
typedef struct If If;
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
	ARITMETHIC,
	NUMBERS,
	ATOMIC,
	CONSTANT
};

enum BlockType {
	VALUE,
	TYPE,
	GAME,
	DESIGN
};

enum CardTypesType{
	ONE,
	MULTIPLE
};

enum RuleType {
	STRUCTURES,
	MOVE_CARDS,
	LOOK_AT,
	WINNER_TYPE,
	USER_RULES,
	TIED
};

enum BoolType  {
	TRUE,
	FALSE
};

enum NumbersType {
	CONSTANT,
	USER_SCORE
};

enum PmOneType{
	INCREASE,
	DECREASE
};

enum AritmethicType {
	ADD,	
	DIV,
	MUL,
	SUB,
	MODULE
};

enum AsignationsType {
	EQUAL,
	ADD_EQUAL,
	SUB_EQUAL
};

enum UserRulesType{
	CONSTANT_ASSIG,
	NUMBER_ASSIG,
	ARITMETHIC_ASSIG,
	PMO_ASSIG	
};

enum StructuresType {
	IF,
	FOREACH,
	ELIF,
	ELSE
};

enum InBraketsType{
	ONE,
	MULTIPLE	
};

enum HandRefType {
	USER,
	DECK
};

enum IfType {
	INIF, 
	AND,
	OR,
	TIED
};

enum InIfType {
	VALUE,
	TYPE,
	ACTIVATE_SPECIAL_CARDS,
	USER_SCORE,
	EXPRESSION
};

enum ComparisonType{
	GREATER,
	LOWER,
	EQUAL_EQUAL,
	GREATER_OR_EQUAL,
	LOWER_OR_EQUAL,
	DIFERENT
};

enum AtomicType{
	VALUE,
	TYPE
};

enum DesignType {
	ROUND_BORDERS,
	COLOR_BORDERS,
	BACKGROUND_COLOR
};

enum UserType{
	PLAYER,
	IDENTIFIER
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

struct Aritmethic {
	AritmethicType type;
};

struct Asignation {
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
			Variable * variable;
			CardTypes * cardTypes;
			Rules * rules;
		};
		struct {
			Variable * variable;
			GameFunction * gameFunctions;
		};
		struct {
			Variable * variable;
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
			Variable * variable;
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
            HandRef * rightandRef;
            Constant * constant;
        };
        struct {
            HandRef * handRef;
            Constant * constant;
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
			Aritmethic * aritmetic;
			Expression * rightExpression;
		};
		Numbers * numbers;
		struct {
			UserCard * userCard;
			Atomic * atomic;
		};
		Constant * constant;
	};
	ExpressionType type;
};

struct UserRules{
	union{
		struct{
			UserScore * userScore;
			Asignation * asignation;
			Constant * constant;
		};
		struct{
			UserScore * userScore;
			Asignation * asignation;
			Numbers * numbers;
		};
		struct{
			UserScore * userScore;
			Asignation * asignation;
			Numbers * leftNumber;
			Aritmethic * arithmetic;
			Numbers * rightNumber;
		};
		struct{
			UserScore * userScore;
			PmOne * pmOne;
		};		
	};
	UserRulesType type
};


struct Structures {
	union {
		struct {
			If * conditional;
			InBrakets * inBrakets;
		};
		struct {
			Atomic *  atomic;
			InBrakets * inBrakets;
		};
		InBrakets * inBrakets;
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

struct If {
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
			Comparison * comparison;
			Variable * variable;
		};
		struct {
			UserScore * userScore;
			Comparison * comparison;
			Constant * constant;
		};
		struct {
			Expression * leftExpression;
			Comparison * comparison;
			Expression * rightExpression;
		};
	};
	InIfType type;
};


struct Design {
	union{
		Variable * roundBorders;
		Variable * colorBorders;
		Variable * backGroundColor;
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
