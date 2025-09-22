#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // take word from user
    string word = get_string(" what is your word: ");

    // check if the word is alphabatical or not
    for ( int i = 1, n = strlen(word); i < n; i++)
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
