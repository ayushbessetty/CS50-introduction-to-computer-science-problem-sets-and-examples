#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// point for each letter
int p[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int score1(string w);
int score2(string w);

int main(void)
{
    // ask players for input
    string w1 = get_string("Player 1 : ");
    string w2 = get_string("Player 2 : ");

    // score of both the players
    int s1 = score1(w1);
    int s2 = score2(w2);

    // which player wins
    if (s1 > s2)
    {
        printf("player 1 wins!\n");
    }
    else if (s1 < s2)
    {
        printf("player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

// score1
int score1(string w)
{
    int score = 0;
    for (int i = 0, n = strlen(w); i < n; i++)
    {
        if (islower(w[i]))
        {
            score += p[w[i] - 'a'];
        }
        else if (isupper(w[i]))
        {
            score += p[w[i] - 'A'];
        }
    }
    return score;
}

// score2
int score2(string w)
{
    int score = 0;
    for (int i = 0, n = strlen(w); i < n; i++)
    {
        if (islower(w[i]))
        {
            score += p[w[i] - 'a'];
        }
        else if (isupper(w[i]))
        {
            score += p[w[i] - 'A'];
        }
    }
    return score;
}
