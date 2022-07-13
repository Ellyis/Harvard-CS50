#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Check if argument count is 2
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open input file for reading
    FILE *input = fopen(argv[1], "r");

    if (input == NULL)
    {
        printf("Failed to open file\n");
        return 1;
    }

    // JPEGs are in blocks of 512 bytes
    unsigned char buffer[512];
    int count = 0;

    // Pointer for output file
    FILE *output = NULL;

    // char filename[8] e.g. "000.jpg\0"
    char *filename = malloc(8 * sizeof(char));

    // Read through blocks of 512 bytes
    while (fread(buffer, sizeof(char), 512, input))
    {
        // Check if matches JPEG header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Create JPEG filename
            sprintf(filename, "%03i.jpg", count);

            // Open output file for writing
            output = fopen(filename, "w");
            count++;
        }

        // If output file can be accessed successfully
        if (output != NULL)
        {
            fwrite(buffer, sizeof(char), 512, output);
        }
    }
    free(filename);
    fclose(input);
    fclose(output);
}