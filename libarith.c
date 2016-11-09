#include "libarith.h"

static RangeTable *cumulative_distribution(double *table)
{
    RangeTable *rangetable = (RangeTable *)malloc(sizeof(RangeTable) * TABLE_SIZE);
    double accumulation = 0;
    for(int i = 0; i < TABLE_SIZE; i++){
        rangetable[i].low = accumulation;
        rangetable[i].high = accumulation + table[i];
        accumulation = rangetable[i].high;
#if defined(DEBUG)
        printf("%c %lf %lf\n", i+'a', rangetable[i].low, rangetable[i].high);
#endif
    }
    return rangetable;
}

static RangeTable *statistic(char *target)
{
    double *table = (double *)malloc(sizeof(double) * TABLE_SIZE);
    int i;
    // calculate the character count
    for(i = 0; target[i] != '\0'; i++){
        if(target[i] == '\n')
            continue;
        table[target[i] - 'a']++;
    }
    // get probability for each character
    for(int index = 0; index < TABLE_SIZE; index++){
        table[index] = table[index] / i;
    }
    // get range distribution
    return cumulative_distribution(table);
}

ArithCode *encode(char *target)
{
    RangeTable *range_table = statistic(target);
    double lbound = 0, ubound = 1;
    double range;
    int i;
    for(i = 0; target[i] != '\0'; i++){
        range = ubound - lbound;
        ubound = lbound + range_table[target[i] - 'a'].high * range; 
        lbound = lbound + range_table[target[i] - 'a'].low * range;
#if defined(DEBUG)
        printf("lower bound: %lf\n", lbound);
        printf("upper bound: %lf\n", ubound);
#endif
    }
    ArithCode *arithcode = (ArithCode *)malloc(sizeof(ArithCode));
    arithcode->code = (lbound + ubound) / 2;
    arithcode->length = i;
    arithcode->range_table = range_table;
    return arithcode;
}

char *decode(ArithCode *arithcode)
{
    double code = arithcode->code;
    RangeTable *range_table = arithcode->range_table;
    char *str = (char *)malloc(sizeof(char) * arithcode->length);
    for(int i = 0; i < arithcode->length; i++){
        for(int j = 0; j < TABLE_SIZE; j++){
            if(code >= range_table[j].low && code < range_table[j].high){
                str[i] = j + 'a';
                code = code - range_table[j].low;
                code = code / (range_table[j].high - range_table[j].low);
                break;
            } 
        }
    }
    return str;
}
