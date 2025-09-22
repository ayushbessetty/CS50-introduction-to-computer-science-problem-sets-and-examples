#include <cs50.h>
#include <stdio.h>

int card_digits(long card);
int checksum_card(long card);
int start_digit(long card);
int Two_start_digit(long card);
int AMEX(int t, int d);
int MASTERCARD(int t, int d);
int VISA(int s, int d);

int main(void)
{
    // as user for credit card no.
    long card;
    do
    {
        card = get_long("Number: ");
    }
    while (card < 1);

    // count number of digits
    int digits = card_digits(card);

    // checksum
    int checksum = checksum_card(card);

    // starting digit of card
    int start = start_digit(card);

    // starting two digits of card;
    int two = Two_start_digit(card);

    // type of card
    if (checksum == 0)
    {
        int a = AMEX(two, digits);
        int m = MASTERCARD(two, digits);
        int v = VISA(start, digits);
        if ((a == 1) && (m == 1) && (v == 1))
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

// check the card numbers and checksum
int card_digits(long card)
{
    int c = 0;
    do
    {
        card = (card - card % 10) / 10;
        c++;
    }
    while (card != 0);
    return c;
}

// checksum
int checksum_card(long card)
{
    int c = 0;
    int a = 0;
    int b = 0;
    do
    {
        int r = 0;
        r = card % 10;
        // sum of all multiplied by 1
        if (c % 2 == 0)
        {
            a = a + r;
        }
        // sum of all multiplied by 2
        else
        {
            // for 2 digit numbers
            if ((2 * r) >= 10)
            {
                int m = 0;
                m = (2 * r) % 10;
                b = b + m + ((2 * r) - (m)) / 10;
            }
            else
            {
                b = b + (2 * r);
            }
        }
        card = (card - r) / 10;
        c++;
    }
    while (card != 0);
    // total sum required
    int checksum = (a + b) % 10;
    return checksum;
}

// to know the starting digit of cards
int start_digit(long card)
{
    do
    {
        card = (card - card % 10) / 10;
    }
    while (card >= 10);
    return card;
}

// to know starting two digits of cards
int Two_start_digit(long card)
{
    do
    {
        card = (card - card % 10) / 10;
    }
    while (card >= 100);
    return card;
}

// validating AMEX card
int AMEX(int t, int d)
{
    if ((t == 34 || t == 37) && (d == 15))
    {
        printf("AMEX\n");
        return 0;
    }
    else
    {
        return 1;
    }
}

// validating MASTERCARD
int MASTERCARD(int t, int d)
{
    if ((t == 51 || t == 52 || t == 53 || t == 54 || t == 55) && (d == 16))
    {
        printf("MASTERCARD\n");
        return 0;
    }
    else
    {
        return 1;
    }
}

// validating VISA
int VISA(int s, int d)
{
    if ((s == 4) && (d == 13 || d == 16))
    {
        printf("VISA\n");
        return 0;
    }
    else
    {
        return 1;
    }
}
