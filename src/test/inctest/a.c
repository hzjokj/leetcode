#include <stdio.h>
#include "a.h"
#include "b.h"

/* gcc a.c b.c c.c -I ./ -o main */
void funca(void)
{
    printf("funca test\n");
}

int main(void)
{
    printf("MAIN ENTRY\n");
    funca();
    funcb();
    funcc();
    return 0;
}
