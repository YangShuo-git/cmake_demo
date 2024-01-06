#include <stdio.h>

extern int sharedVariable;

void function2() {
    printf("sharedVariable = %d\n", sharedVariable);
}