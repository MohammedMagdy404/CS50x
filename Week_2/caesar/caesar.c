#include "cs50.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

char plaintext[1000];

int main(int argc, char *argv[])
{
    // handling running the main function with no. of arguments and only digits input
    int key;
    if (argc == 2)
    {
        printf("args: %s\n", argv[1]);
        bool flag = false;
        for (int i = 0; argv[1][i] != '\0'; i++)
        {
            if (!isdigit(argv[1][i]))
            {
                flag = true;
            }
        }

        if (flag)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
        else
        {
            key = atoi(argv[1]);
        }
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    printf("plaintext: ");
    scanf("%[^\n]", plaintext);

    // encrypting the message with ascii code

    for (int i = 0; plaintext[i] != '\0'; i++)
    {
        if ((122 >= plaintext[i] && plaintext[i] >= 97))
        {
            plaintext[i] = (((plaintext[i] - 96 + key) % 26) + 96);
            // printf("cipher: %d\n", plaintext[i]);
            // printf("cipher: %d\n", plaintext[i]);
        }
        else if ((90 >= plaintext[i] && plaintext[i] >= 65))
        {
            plaintext[i] = ((plaintext[i] - 64 + key) % 26) + 64;

            printf("cipher: %d\n", 'b');
        }
    }
    printf("ciphertext: %s\n", plaintext);
    // printf("key: %d\n", key);
}
