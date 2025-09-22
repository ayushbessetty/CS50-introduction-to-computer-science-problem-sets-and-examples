#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node* next;
}
node;

int main(void)
{
    // making NULL block
    node* list = NULL;

    // puttiing in the values
    for(int i = 0; i < 3; i++)
    {
        // making a block n
        node* n = malloc(sizeof(node));
        if (n == NULL)
        {
            return 1;
        }

        // getting the values
        printf("Number %i:", i + 1);
        scanf("%i",&n->number);
        printf("\n");

        //seeting the location(address)
        n->next = NULL;
        if (list == NULL)
        {
            // assigning check
            list = n;
        }
        else if (n->number < list->number)
        {
            // initial input check
            n->next = list;
            list = n;
        }
        else
        {
            for(node* ptr = list; ptr != NULL;ptr = ptr->next)
            {
                // end check
                if (ptr->next == NULL)
                {
                    ptr->next = n;
                    break;
                }

                // middle check
                if (n->number < ptr->next->number)
                {
                    n->next = ptr->next;
                    ptr->next = n;
                    break;
                }
            }
        }
    }

    // printing numbers
    for (node* ptr = list; ptr != NULL;ptr = ptr->next)
    {
        printf("%i\n", ptr->number);
    }

    node* buffer = NULL;
    for (node* ptr = list; ptr != NULL; ptr = buffer)
    {
        buffer = ptr->next;
        free(ptr);
    }
}
