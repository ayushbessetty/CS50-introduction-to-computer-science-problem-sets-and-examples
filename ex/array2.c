#include <stdio.h>

void set_a(int x);
void set_b(int array[]);

int main(void)
{
    int a = 10;
    int b[] = {0, 1, 8, 8};
    set_a(a);
    set_b(b);
    printf(" %d %d\n", a, b[0]);
}

void set_a(int x)
{
    x = 22;
    printf("x is %d\n", x);
}

void set_b(int array[])
{
    array[0] = 22;
}
