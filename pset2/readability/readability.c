#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>

float average_w(string t);
float average_s(string t);

int main(void)
{
    // taking text from user
    string t = get_string("Text: ");

    // getting L average of letters per 100 words
    float L = average_w(t);
    float S = average_s(t);

    // using coleman liau formulae
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int i = (int) round(index);

    // printing the grade
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", i);
    }
}

// average of letters in text per 100 words
float average_w(string t)
{
    int w = 1; // initializing words
    int l = 0; // initializing letters
    for (int i = 0; t[i] != '\0'; i++)
    {
        if (isalpha(t[i]))
        {
            l++;
        }
        if (isspace(t[i]) && (i > 1))
        {
            w++;
        }
    }
    return ((float) l / w) * 100;
}

// average of sentences in text per 100 words
float average_s(string t)
{
    int w = 1; // initializing words
    int s = 0; // initializing sentences
    for (int i = 0; t[i] != '\0'; i++)
    {
        if (((t[i] == '.') || (t[i] == '?') || (t[i] == '!') ||
             ((t[i] == ' ') && (t[i + 1] == ' '))) &&
            (i > 1))
        {
            s++;
        }
        if (isspace(t[i]) && (i > 1))
        {
            w++;
        }
    }
    return ((float) s / w) * 100;
}
