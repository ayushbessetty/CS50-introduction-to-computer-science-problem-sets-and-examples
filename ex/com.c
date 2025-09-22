#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf(" input command line argument\n");
    }
    // take word from user
    string word = argv[1];

    // alphabet or not
    for (int j = 0, n = strlen(word); j < n; j++)
    {
        if (!isalpha(word[j]))
        {
            printf("This is not a word\n");
            return 3;
        }
    }

    // check if the word is alphabatical or not
    for (int i = 1, n = strlen(word); i < n; i++)
    {
        if ( (word[i] < word[i - 1]))
        {
            printf(" word is not in alphabetical orde\n");
            return 1;
        }
        if ((word[i] < 'a') || (word[i] > 'z'))
        {
            printf("word is not in lower case\n");
            return 2;
        }
    }
    printf("word is in lower case and in alphabetical order\n");

}
