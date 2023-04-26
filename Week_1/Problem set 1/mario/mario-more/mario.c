#include "cs50.h"
#include <stdio.h>

int main(void)
{

    int n = 0;
    while (n > 8 || n < 1)
    {
        printf("Height: ");
        scanf("%d", &n);
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j < n; j++)
        {
            printf(" ");
        }
        for (int k = 1; k <= i; k++)
        {
            printf("#");
        }
        printf("  ");
        for (int k = 1; k <= i; k++)
        {
            printf("#");
        }

        printf("\n");
    }
}