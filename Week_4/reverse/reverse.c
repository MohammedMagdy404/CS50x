#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"
#define ll long long
ll check_format(WAVHEADER header);
ll get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Read header into an array
    // TODO #3
    WAVHEADER header;

    fread(&header, sizeof(WAVHEADER), 1, input);

    // Use check_format to ensure WAV format
    // TODO #4
    if (check_format(header) == 0)
    {
        printf("not .wav file\n");
        return 1;
    }

    // Open output file for writing
    // TODO #5

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    // Write header to file
    // TODO #6
    fwrite(&header, sizeof(WAVHEADER), 1, output);

    // Use get_block_size to calculate size of block
    // TODO #7
    ll size = get_block_size(header);

    // Write reversed audio to file
    // TODO #8
    BYTE buffer[size];
    int cur = ftell(input);
    // printf("coco %ld\n", ftell(input));
    // printf("coco %lld\n", size);
    fseek(input, 0, SEEK_END);
    /* printf("coco %ld\n", ftell(input));
    fseek(input, -2, SEEK_CUR);
    printf("coco %ld\n", ftell(input)); */
    while (1)
    {
        // ll momo = 0;
        //  printf("momo %d\n", cur);

        fseek(input, -size , SEEK_CUR);

        //printf("coco %ld\n", ftell(input));

        if (ftell(input) == cur)
        {
            fread(buffer, sizeof(BYTE), size, input);
            fwrite(buffer, sizeof(BYTE), size, output);
            break;
        }
        fread(buffer, sizeof(BYTE), size, input);
        fwrite(buffer, sizeof(BYTE), size, output);
        fseek(input, -size , SEEK_CUR);
        // momo += size;
    }
    fclose(input);
    fclose(output);
    /* BYTE *bufferA;
    BYTE *arr[1000000];
    ll idx = 0;
    ll read;
    ll soso;
    while (1)
    {
        bufferA = (BYTE *)malloc(sizeof(BYTE) * size);
        ll soso = size;
        while (soso--)
        {
            read = fread(&buffer, sizeof(BYTE), 1, input);
            if (read != 1)
            {
                //fclose(input);
                break;
            }
            bufferA[soso] = buffer;
            prllf("momo %i\n", read);
        }
        if (read != 1)
        {
            fclose(input);
            if (soso < size - 1)
            {
                arr[idx] = bufferA;
            }
            break;
        }
        arr[idx] = bufferA;
        prllf("momo %p\n", arr[idx]);
        idx++;
    }
    for (ll i = 0; i < size - soso; i++)
    {
        fwrite(&arr[idx][i], sizeof(BYTE), 1, output);
    }

    for (ll i = idx - 1; i >= 0; i--)
    {
        for (ll j = 0; j < size; j++)
        {
            fwrite(&arr[i][j], sizeof(BYTE), 1, output);
        }
    }

    //free(bufferA);
    fclose(output); */
}

ll check_format(WAVHEADER header)
{

    // TODO #4
    if (header.format[0] == 'W' && header.format[1] == 'A' && header.format[2] == 'V' && header.format[3] == 'E')
    {
        return 1;
    }

    return 0;
}

ll get_block_size(WAVHEADER header)
{
    // TODO #7
    return header.numChannels * (header.bitsPerSample / 8);
}