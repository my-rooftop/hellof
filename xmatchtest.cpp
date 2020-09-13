#include <fstream>
#include <sstream>
#include <stdio.h>
#include <typeinfo>
#include <vector>
#include <iostream>
#include <memory>
#include <typeinfo>
#include <string>
#include <bitset>
#include <map>
#include <stdlib.h>
#include <sys/time.h>
extern "C" {
	#include "xmatchPro.h"
}

using namespace std;

int main()
{
    FILE* input_file = fopen("web", "rb");
    for(int i = 3; i < 10; i++){
        unsigned char* input = (unsigned char*)malloc(5000);
    
        // fread(hello1, 1, 4096, input);
        fseek(input_file, 4096*i, SEEK_SET);
        fread(input, 4096, 1, input_file);

        unsigned char* output = (unsigned char*)malloc(5000);
        int compressedSize = xmatchCompress(input, 4096, output);
        printf("%d\n", compressedSize);
        FILE* f = fopen("output13", "wb");
        fwrite(output, compressedSize, 1, f);

        fclose(f);

        FILE* f2 = fopen("output13", "rb");
        unsigned char* compressed = (unsigned char*)malloc(5000);
        unsigned char* decompressed = (unsigned char*)malloc(5000);
        fread(compressed, compressedSize, 1, f2);
        for (int j = 0; j <  compressedSize; ++j) {
            if (compressed[j] != output[j]) printf("%d\n", j);
        }
        printf("clear\n");
    
        int Decompressed_size = xmatchDecompress(compressed, compressedSize, decompressed);

        free(input);
        free(output);
    }
    return 0;
}


