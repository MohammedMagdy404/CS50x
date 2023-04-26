#include "cs50.h"
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    const char *name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(char name[20]);
void print_winner(void);

int main(int argc, const char *argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {

        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count;
    printf("Number of voters: ");
    scanf("%d", &voter_count);

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {

        char name[20];
        printf("Vote: ");
        scanf("%s", name);
        // printf("%s\n", name);

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    /* for (int i = 0; i < candidate_count; i++)
    {
        printf("%d\n", candidates[i].votes);

    } */

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(char name[20])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }

    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    int max = -1;
    int idx = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > max)
        {
            max = candidates[i].votes;
            idx = i;
        }
    }
    printf("%s\n", candidates[idx].name);

    for (int j = 0; j < candidate_count; j++)
    {
        if (max == candidates[j].votes && candidates[j].name != candidates[idx].name)
        {
            printf("%s\n", candidates[j].name);
        }
    }

    return;
}