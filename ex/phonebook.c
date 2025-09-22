#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *file = fopen("phonebook.csv", "a");
    if (file == NULL)
    {
        return 1;
    }
    char *name = malloc(20);
    printf("name: ");
    scanf("%s", name);

    char *number = malloc(20);
    printf("number: ");
    scanf("%s", number);
    printf("\n");

    fprintf(file, "%s, %s\n", name, number);
    fclose(file);
    free(name);
    free(number);
}
