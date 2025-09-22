#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    string phrase;
    struct node *next;
} node;

bool unload(node *list);

int main(void)
{
    // asking user for how many inputs
    int l = get_int("NUMBER: ");

    // initializing first pointer
    node *list = NULL;

    // adding the data
    for (int i = 0; i < l; i++)
    {
        string p = get_string("phrase: ");
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return 1;
        }
        n->phrase = p;
        n->next = list;
        list = n;
    }
    // printing the data
    for (node *ptr = list; ptr != NULL; ptr = ptr->next)
    {
        printf("%s\n", ptr->phrase);
    }

    // freeing the nodes
    if (!unload(list))
    {
        printf("not freed");
        return 1;
    }

    printf("freed\n");
    return 0;
}

// free the memory
bool unload(node *list)
{
    node *buffer = NULL;
    for (node *ptr = list; ptr != NULL; ptr = buffer)
    {
        buffer = ptr->next;
        free(ptr);
        if (buffer == NULL)
        {
            return true;
        }
    }
    return false;
}
