#include <stdio.h>
#include <cs50.h>

const int num = 3;

typedef struct
{
    string name;
    int votes;
} candidate;

int main(void)
{
    // define number of candidates
    candidate candidates[num];

    // input candidate details
    for (int i = 0; i < num; i++)
    {
        candidates[i].name = get_string("NAME: ");
        candidates[i].votes = get_int("VOTES: ");
    }

    //get the highest votes
    int highest_votes = 0;
    for (int i = 0; i < num; i++)
    {
        if (candidates[i].votes > highest_votes)
        {
            highest_votes = candidates[i].votes;
        }
    }

    // printing the name of winner
    for(int i = 0; i < num; i++)
    {
        if (highest_votes == candidates[i].votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
}
