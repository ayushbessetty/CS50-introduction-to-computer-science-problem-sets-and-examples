#include<cs50.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(void)
{
    char *s = get_string("s: ");
    char *t = malloc(strlen(s));
    if (t == NULL)
    {
        return 1;
    }
    for (int i = 0, n = strlen(s); i <= n; i++)
    {
        t[i] = s[i];
        t[i] = toupper(t[i]);
    }

    printf("s: %s\n", s);
    printf("t: %s\n", t);
    printf("%p\n %p\n", s, t);
    free(t);
}
