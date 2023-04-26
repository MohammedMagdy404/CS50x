#include "cs50.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
string key;
string cap = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
string low = "abcdefghijklmnopqrstuvwxyz";
char plaintext[1000];

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        // printf("args: %s\n", argv[1]);
        // bool flag = false;

        int count = 0;
        for (int i = 0; argv[1][i] != '\0'; i++)
        {
            count++;
            if (!isalpha(argv[1][i]))
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }

            for (int j = i + 1; j < argv[1][j] != '\0'; j++)
            {
                if (argv[1][i] == argv[1][j])
                {
                    printf("Usage: ./caesar key\n");
                    return 1;
                }
            }
        }

        if (count == 26)
        {
            key = argv[1];
        }
        else
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    printf("plaintext: ");
    scanf("%[^\n]", plaintext);

    for (int i = 0; plaintext[i] != '\0'; i++)
    {
        if ((122 >= plaintext[i] && plaintext[i] >= 97))
        {
            plaintext[i] = (key[plaintext[i] - 97] < 97) ? key[plaintext[i] - 97] - 65 + 97 : key[plaintext[i] - 97];
        }
        else if ((90 >= plaintext[i] && plaintext[i] >= 65))
        {
            plaintext[i] = (key[plaintext[i] - 65] > 90) ? key[plaintext[i] - 65] - 97 + 65 : key[plaintext[i] - 65];
        }
    }
    printf("ciphertext: %s\n", plaintext);

    return 0;
}