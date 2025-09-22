#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int alpha(string k);
int repeat(string k);
void cipher(string p, string k);

int main(int argc, string argv[])
{
    // CLA is only one
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // key has 26 characters
    if (strlen(argv[1]) != 26)
    {
        printf("Key must have 26 characters.\n");
        return 1;
    }

    // all characters of key is a alphabet
    int a = alpha(argv[1]);
    if (a == 1)
    {
        printf("key must have only alphabets.\n");
        return 1;
    }

    // alphabets in key does not repeat
    int r = repeat(argv[1]);
    if (r == 1)
    {
        printf("Key must have each character exactly once.\n");
        return 1;
    }

    // taking plaintext from user
    string p = get_string("plaintext:  ");

    // plaintext to ciphertext
    cipher(p, argv[1]);
    return 0;
}

int alpha(string k)
{
    for (int i = 0, n = strlen(k); i < n; i++)
    {
        if (!(isalpha(k[i])))
        {
            return 1;
        }
    }
    return 0;
}

// to convert plaintext to ciphertext
void cipher(string p, string k)
{
    printf("ciphertext: ");
    for (int i = 0, n = strlen(p); i < n; i++)
    {
        int m = 0; // initializing m to index the cipher

        // for upper character in plain text
        if (isupper(p[i]))
        {
            m = p[i] - 'A';
            if (isupper(k[m]))
            {
                printf("%c", k[m]);
            }
            else
            {
                printf("%c", toupper(k[m]));
            }
        }

        // for lower character in plaintext
        else if (islower(p[i]))
        {
            m = p[i] - 'a';
            if (islower(k[m]))
            {
                printf("%c", k[m]);
            }
            else
            {
                printf("%c", tolower(k[m]));
            }
        }

        // for non- alphabatical characters in plaintext
        else
        {
            printf("%c", p[i]);
        }
    }
    printf("\n");
}

// to check no characters are repeated in key
int repeat(string k)
{
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (((k[i] == k[j]) || (k[i] == toupper(k[j])) || (k[i] == tolower(k[j]))) && (i != j))
            {
                return 1;
            }
        }
    }
    return 0;
}
