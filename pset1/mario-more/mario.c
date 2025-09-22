#include <cs50.h>
#include <stdio.h>

void print_rows(int spaces, int heights);

int main(void)
{
    // as user for height of pyramid
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1);

    // printing the pyramid
    for (int i = 0; i < n; i++)
    {
        print_rows(n - i, i + 1);
    }
}

void print_rows(int spaces, int heights)
{
    // print first spaces
    for (int m = 1; m < spaces; m++)
    {
        printf(" ");
    }

    // print first lines of #
    for (int n = 0; n < heights; n++)
    {
        printf("#");
    }

    // print common space
    printf("  ");

    // print lines of last #
    for (int i = 0; i < heights; i++)
    {
        printf("#");
    }
    printf("\n");
}
