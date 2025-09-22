#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool positive(string k);
void cipher(string p, int k);

int main(int argc, string argv[])
{
    // CLA is 1
    if (argc != 2)
    {
        printf("Usage: ./caeser key\n");
        return 1;
    }

    // CLA is a positive integer
    if (!(positive(argv[1])))
    {
        printf("Usage: ./caeser key\n");
        return 1;
    }

    // CLA string to integer
    int key = atoi(argv[1]);

    // taking plaintext from user
    string plain = get_string("plaintext:  ");

    // to cipher
    cipher(plain, key);
    return 0;
}

// positive integer key
bool positive(string k)
{
    for (int i = 0, n = strlen(k); i < n; i++)
    {
        if (!(isdigit(k[i])))
        {
            return false;
        }
    }
    return true;
}

// to cipher
void cipher(string p, int k)
{
    printf("ciphertext: ");
    for (int i = 0, l = strlen(p); i < l; i++)
    {
        if (isupper(p[i]))
        {
            int m = 0;
            m = ((int) p[i]) - ((int) 'A');
            m = (m + k) % 26;
            printf("%c", ('A' + m));
        }
        else if (islower(p[i]))
        {
            int n = 0;
            n = ((int) p[i]) - ((int) 'a');
            n = (n + k) % 26;
            printf("%c", ('a' + n));
        }
        else
        {
            printf("%c", p[i]);
        }
    }
    printf("\n");
}
