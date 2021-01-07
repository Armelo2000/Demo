#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main()
{
    /* The second parameter :
        - rb for read process
        - wb for write process
    */
    FILE * streamIn = fopen("images/cameraman.bmp", "rb");
    FILE * streamOut = fopen("images/cameraman_copy.bmp", "wb");

    uint8_t header[54];
    uint8_t ColorTable[1024];
    if(streamIn == (FILE *)0)
    {
        printf("Unable to open file\n");
    }
    else
    {
        // file exist
        int i;
        for(i=0; i<54; i++)
        {
            header[i] = getc(streamIn);
        }
        int width = *(int *)&header[18];
        int height = *(int *)&header[22];
        int bitDepth = *(int *)&header[28];

        printf("The file cameraman.bmp has following Informations:\n");
        printf("Width : %d\n", width);
        printf("Height : %d\n", height);
        printf("Bit depth : %d\n\n", bitDepth);

        if(bitDepth <= 8)
        {
            fread(ColorTable, sizeof(uint8_t), 1024, streamIn);
        }
        // write the header into the output stream.
        fwrite(header, sizeof(uint8_t), 54, streamOut);
        uint8_t buf[height * width];
        //read pixel data and store into buf
        fread(buf, sizeof(uint8_t), height*width, streamIn);
        if(bitDepth <= 8)
        {
            fwrite(ColorTable, sizeof(uint8_t), 1024, streamOut);
        }
        fwrite(buf, sizeof(uint8_t), height*width, streamOut);
        fclose(streamIn);
        fclose(streamOut);
        printf("successful!\n");
    }

    return 0;
}
