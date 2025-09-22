#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("invalid usage ./pdf file");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        return 2;
    }

    uint8_t b[4];

    uint8_t signature[] = {0x25, 0x50, 0x44, 0x46};

    fread(b, sizeof(uint8_t), 4, file);
    for (int i = 0; i < 4; i++)
    {
        if (b[i] != signature[i])
        {
            printf("no\n");
            return 0;
        }
    }
    printf("yes\n");
    fclose(file);
    return 0;
}
