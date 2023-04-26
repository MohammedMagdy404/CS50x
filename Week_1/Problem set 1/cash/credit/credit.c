#include "cs50.h"
#include <stdio.h>
#include <math.h>

int main(void)
{
    long arr[20] = {0};
    long num = 0, temp = 0;
    do
    {
        /* code */
        printf("Number: ");
        scanf("%ld", &num);
    }
    while (num <= 0);
    temp = num;
    int n = 0;
    for (int i = 0; temp > 0; i++)
    {
        /* code */
        arr[i] = temp % 10;
        temp = temp / 10;
        n++;
    }

    if (n != 15 && n != 13 && n != 16)
    {
        printf("INVALID\n");
        return 0;
    }
    else
    {
    }

    int sum = 0;
    for (int i = 1; i < n; i += 2)
    {
        /* code */
        arr[i] = arr[i] * 2;
    }
    for (int i = 0; i < n; i++)
    {
        /* code */
        if (arr[i] >= 10)
        {
            sum += (arr[i] % 10) + 1;
        }
        else
        {
            sum += arr[i];
        }
    }

    if (sum % 10 == 0)
    {
        /* code */
        if (n == 13)
        {

            (num / (long)pow(10, 12) == 4) ? printf("VISA\n") : printf("INVALID\n");
        }
        else if (n == 15)
        {
            // printf("%ld\n", num / (long)pow(10, 13));
            (num / (long)pow(10, 13) == 34 || num / (long)pow(10, 13) == 37) ? printf("AMEX\n") : printf("INVALID\n");
        }
        else if (n == 16)
        {
            if (num / (long)pow(10, 14) == 51 || num / (long)pow(10, 14) == 52 || num / (long)pow(10, 14) == 53 || num / (long)pow(10, 14) == 54 || num / (long)pow(10, 14) == 55)
            {
                printf("MASTERCARD\n");
            }
            else if (num / (long)pow(10, 15) == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
