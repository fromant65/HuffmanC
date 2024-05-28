#include "comprimir.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#define BYTE_SIZE 8
#define CHAR_SIZE 256

// Function to get the binary representation length of a number
int get_binary_length(unsigned int n) {
    int length = 0;
    while (n > 0) {
        n >>= 1;
        length++;
    }
    return length;
}

// Function to write binary data to a file
void write_binary_file(CodigoList codeList, const char* input_filename, const char* output_filename, char* tree) {
    FILE *input_file = fopen(input_filename, "r");
    if (!input_file) {
        perror("Error opening input file");
        return;
    }

    FILE *output_file = fopen(output_filename, "wb");
    if (!output_file) {
        perror("Error opening output file");
        fclose(input_file);
        return;
    }
    //printf("TREE %s\n",tree);
    fprintf(output_file, "%sET", tree);

    unsigned char buffer = 0;
    int bit_count = 0;
    int char_count = 0, comp_buff_size=2048;
    int ch;
    char* compressed_buffer = malloc(sizeof(char)*comp_buff_size);
    printf("reading the file..\n");
    while ((ch = fgetc(input_file)) != EOF) {
        unsigned int code=codeList[(int)ch];
        //printf("code %u ", code);
        int code_length = get_binary_length(code)-1; //Ignoramos el bit significativo mas grande
        //printf("length %d\n", code_length);
        for (int i = code_length - 1; i >= 0; i--) {
            buffer = (buffer << 1) | ((code >> i) & 1);
            bit_count++;
            
            if (bit_count == BYTE_SIZE) {
                if(comp_buff_size<=char_count){
                    comp_buff_size*=2;
                    compressed_buffer= realloc(compressed_buffer,comp_buff_size);
                }
                compressed_buffer[char_count++]=buffer;
                buffer = 0;
                bit_count = 0;
            }
        }
    }
    if (bit_count > 0) {
        buffer <<= (BYTE_SIZE - bit_count); // Pad the remaining bits with zeros
        if(comp_buff_size<=char_count){
            comp_buff_size*=2;
            compressed_buffer= realloc(compressed_buffer,comp_buff_size);
        }
        compressed_buffer[char_count++]=buffer;
    }
    fprintf(output_file, "%d\n%s", char_count, compressed_buffer);
    fclose(input_file);
    fclose(output_file);
}