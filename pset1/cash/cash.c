#include <cs50.h>
#include <stdio.h>

int cal_quarters(int c);
int cal_dimes(int c);
int cal_nickels(int c);
int cal_pennies(int c);

int main(void)
{
    // as user for positive cents
    int cents;
    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 1);

    // count the change
    int q = cal_quarters(cents);
    cents = cents - (q * 25);
    int d = cal_dimes(cents);
    cents = cents - (d * 10);
    int n = cal_nickels(cents);
    cents = cents - (n * 5);
    int p = cal_pennies(cents);
    cents = cents - p;

    // sum the total no. of coins
    printf("%i\n", q + d + n + p);
}

// calculate quarters
int cal_quarters(int c)
{
    int q = 0;
    while (c >= 25)
    {
        q++;
        c = c - 25;
    }
    return q;
}

// calculate dimes
int cal_dimes(int c)
{
    int d = 0;
    while (c >= 10)
    {
        d++;
        c = c - 10;
    }
    return d;
}

// calculate nickels
int cal_nickels(int c)
{
    int n = 0;
    while (c >= 5)
    {
        n++;
        c = c - 5;
    }
    return n;
}

// calculate pennies
int cal_pennies(int c)
{
    int p = 0;
    while (c >= 1)
    {
        p++;
        c = c - 1;
    }
    return p;
}
