#include <stdio.h>

const int N = 5;

int main(void)
{
    int array[N];
    array[0] = 1;
    // giving valus to array
    for (int i = 0; i < N; i++)
    {
        array[i + 1] = array[i] * 2;
        // print digits in array
        printf("%i\n", array[i]);
    }
}
