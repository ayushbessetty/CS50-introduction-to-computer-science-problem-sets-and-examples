#include <cs50.h>
#include <stdio.h>

int positive(int a, int b, int c);
int sum_two_sides(int a, int b, int c);

int main(void)
{
    // ask user for lenght of sides triangles
    int a = get_int("side a: ");
    int b = get_int("side b: ");
    int c = get_int("side c: ");

    int p = positive(a, b, c);
    int q = sum_two_sides(a, b, c);

    // printing valid or not
    if (p != 0 || q != 0)
    {
        printf("invalid triangle\n");
        return 11;
    }
    printf("valid triangle\n");
}

// all sides are of positive length
int positive(int a, int b, int c)
{
    if (a < 0 || b < 0 || c < 0)
    {
        return 1;
    }
    return 0;
}

// sum of two sides are greater than third
int sum_two_sides(int a, int b, int c)
{
    if (((a + b) <= c) || ((a + c) <= b) || ((c + b) <= a))
    {
        return 2;
    }
    return 0;
}
