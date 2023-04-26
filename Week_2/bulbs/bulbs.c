#include "cs50.h"
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

char text[10];

int main(void)
{
    // TODO
    printf("Message: ");
    scanf("%[^\n]", text);

    for (int i = 0; text[i] != '\0'; i++)
    {
        int temp = text[i];
        // printf("%d\n", temp);
        int arr[8];
        for (int i = 0; i < 8; i++)
        {
            arr[i] = temp % 2;
            temp = temp / 2;
        }
        for (int i = 7; i >= 0; i--)
        {
            print_bulb(arr[i]);
        }
        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
