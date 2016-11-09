#include <stdio.h> 
#include <string.h>
#include <assert.h>

#include "libarith.h"

int main(int argc, char *argv[])
{
    ArithCode *output;
    char *str;
    output = encode(argv[1]);
    str = decode(output);
    printf("Decode : %s\n", str);
    assert(strcmp(str, argv[1]) == 0 && "Decode Error");
    return 0;
}
