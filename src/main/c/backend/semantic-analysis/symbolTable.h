#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#include "hashmap.h"

struct key {
    char * varname;
};

typedef enum VarType {
    VAR_DECK,
    VAR_PLAYING,
    VAR_WAITING,
    VAR_USER,
    VAR_MACHINE
} VarType;

struct metadata {
    bool hasValue;
};

struct value {
    VarType type;
    struct metadata metadata;
};

void symbolTableInit();

bool symbolTableFind(struct key * key, struct value * value);

void symbolTableInsert(struct key * key, struct value * value);

void symbolTableDestroy();
#endif