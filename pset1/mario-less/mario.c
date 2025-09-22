#include <cs50.h>
#include <stdio.h>

void print_rows(int bricks, int space);

int main(void)
{
    // ask user for the height of the pyramid
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1);

    // print the pyramid
    for (int i = 0; i < n; i++)
    {
        // print pyramid rows
        print_rows(n - i, i + 1);
    }
}

void print_rows(int bricks, int space)
{
    // print spaces
    for (int m = 1; m < bricks; m++)
    {
        printf(" ");
    }

    // print #
    for (int j = 0; j < space; j++)
    {
        printf("#");
    }
    printf("\n");
}
