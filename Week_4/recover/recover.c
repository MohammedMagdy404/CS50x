#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#define BLOCK_SIZE 512
int main(int argc, char *argv[])
{
    typedef uint8_t BYTE;
    uint8_t Buffer[BLOCK_SIZE];
    char filename[8];

    FILE *f = fopen(argv[1], "r");
    FILE *img = NULL;

    int JPEG_NO = 0;
    int read;

    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    if (f == NULL)
    {
        printf("./recover card.raw\n");
        return 1;
    }

    while (1)
    {
        read = fread(Buffer, sizeof(uint8_t), BLOCK_SIZE, f);
        if (Buffer[0] == 0xff && Buffer[1] == 0xd8 && Buffer[2] == 0xff && (Buffer[3] & 0xf0) == 0xe0)
        {
            if (JPEG_NO == 0)
            {
                sprintf(filename, "%03i.jpg", JPEG_NO);
                JPEG_NO++;
                img = fopen(filename, "w");
                fwrite(Buffer, sizeof(uint8_t), read, img);
            }
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", JPEG_NO);
                JPEG_NO++;
                img = fopen(filename, "w");
                fwrite(Buffer, sizeof(uint8_t), read, img);
            }
        }
        else if (JPEG_NO != 0)
        {
            fwrite(Buffer, sizeof(uint8_t), read, img);
            if (read == 0)
            {
                fclose(img);
                fclose(f);
                break;
            }
        }
    }
    // carefull u fclose the files twice ### !!!!!!!!!!!!!!!!
    /* fclose(img);
    fclose(f); */
}