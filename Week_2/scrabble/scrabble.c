#include <ctype.h>
#include "cs50.h"
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    char word1[26];
    printf("Player 1: ");
    scanf("%s", word1);
    char word2[26];
    printf("Player 2: ");
    scanf("%s", word2);

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 == score2)
    {
        printf("Tie!");
    }
    else
    {

        (score1 > score2) ? printf("Player 1 wins!") : printf("Player 2 wins!");
    }
    return 0;
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    int sum = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (122 >= word[i] && word[i] >= 97)
        {
            sum += POINTS[word[i] - 97];
        }
        else if (90 >= word[i] && word[i] >= 65)
        {
            sum += POINTS[word[i] - 65];
        }
        else
        {
            continue;
        }
    }
    return sum;
}
