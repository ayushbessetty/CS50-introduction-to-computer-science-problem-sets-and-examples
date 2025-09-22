#include <cs50.h>
#include <stdio.h>

int collatz(int n);

int main(void)
{
    // get the number
    int number;
    do
    {
        number = get_int("Number: ");
    } while (number < 0);

    // collatz
    int steps = collatz(number);

    // print number of steps
    printf("%i\n", steps);
}

// collatz function
int collatz(int n)
{
    if (n == 1)
    {
        return 0;
    }

    // collatz condition
    else if ((n % 2) == 0)
    {
        return 1 + collatz(n/2);
    }
    else
    {
        int l = n * 3;
        return 1 + collatz(l + 2);
    }
    return 0;
}
