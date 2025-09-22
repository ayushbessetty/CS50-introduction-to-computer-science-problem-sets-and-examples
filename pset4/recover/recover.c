#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("usage: ./recover file\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("could not open the file\n");
        return 1;
    }

    uint8_t b[512];
    char *filename = malloc(8);
    if (filename == NULL)
    {
        return 3;
    }
    int i = 0, check = 0;
    FILE *out = NULL;

    while (fread(b, 1, 512, file))
    {
        if ((b[0] == 0xff) && (b[1] == 0xd8) && (b[2] == 0xff) &&
            ((b[3] & 0xf0) == 0xe0)) // start of images
        {
            check = 1;
        }

        if (check == 1)
        {
            if (i > 0)
            {
                fclose(out);
            }

            sprintf(filename, "%03i.jpg", i);
            out = fopen(filename, "w");
            fwrite(b, 1, 512, out);
            i++;
            check = 0;
        }
        else if (i > 0)
        {
            fwrite(b, 1, 512, out);
        }
    }
    fclose(file);
    fclose(out);
    free(filename);
}
