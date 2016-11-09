#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 26

typedef struct range_table{
    double low;
    double high;
} RangeTable;

typedef struct arithmetic_code{
    double code;
    unsigned int length;
    RangeTable *range_table;
} ArithCode;

ArithCode *encode(char *target);
char *decode(ArithCode *arithcode);
