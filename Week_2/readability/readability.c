#include "cs50.h"
#include <stdio.h>
#include <string.h>
int count_words(string text);
int count_letters(string text);
int count_sentences(string text);

char text[10];
int main()
{
    /* char text[100000000];
    printf("Text: ");
    fgets(text, sizeof(text), stdin); */
    printf("Text: ");
    scanf("%[^\n]", text);
    // printf("%s\n", text);

    int words = count_words(text);
    int letters = count_letters(text);
    int sentences = count_sentences(text);
    //printf("words: %d letters: %d sentences: %d\n", words, letters, sentences);

    int index = ((0.0588 * ((letters / (float)words) * 100)) - (0.296 * ((sentences / (float)words) * 100)) - 15.8) + 0.5;
    // printf("%d",index);
    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 0)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %d\n", index);
    }

    return 0;
}

int count_words(string text)
{
    int count = 1;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ')
        {
            count++;
        }
    }
    return count;
}
// Congratulations !Today is your day.You 're off to Great Places! You' re off and away !

int count_letters(string text)
{
    int count = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if ((122 >= text[i] && text[i] >= 97) || (90 >= text[i] && text[i] >= 65))
        {
            count++;
        }
    }
    return count;
}

int count_sentences(string text)
{
    int count = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
        if (text[i + 1] == ' ')
        {
            i++;
        }
    }
    return count;
}