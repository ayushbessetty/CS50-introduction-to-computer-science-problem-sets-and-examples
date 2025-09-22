#include <stdio.h>
#include <cs50.h>

int fact(int f);
int main(void)
{
    // take input from user which factorial you want
    int n;
    do
    {
        n = get_int("NUMBER: ");
    } while(n <= 0);

    // finding the factorial
    int f = fact(n);
    printf("%i\n", f);
    return 0;
}

//factorial
int fact(int f)
{
    if (f <= 0)
    {
        return 1;
    }
    int i = fact(f - 1); // recursive function
    f *= i;  // can be written as f *= fact(f-1);
    return f;
}
