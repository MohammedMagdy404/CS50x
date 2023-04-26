#include <stdio.h>
#include "cs50.h"

int main(void)
{
    // TODO: Prompt for start size
    int st = 0;
    while (st < 9)
    {
        printf("Start size: ");
        scanf("%d", &st);
    }

    // TODO: Prompt for end size
    int en = 0;
    while (en < st)
    {
        printf("End size: ");
        scanf("%d", &en);
    }

    // TODO: Calculate number of years until we reach threshold
    int c = 0;
    while (st < en)
    {
        st = st + (st / 3) - (st / 4);
        c++;
    }

    // TODO: Print number of years
    printf("Years: %d", c);
}
