#include <stdio.h>
#include "my_str/lib_string.h"
#include "ctype.h"

int main(int argc, char* argv[]){
    if (argc > 2){
        printf("Hi!");
//        FILE *in_file = fopen(argv[1], 'r');
//        FILE *out_file = fopen(argv[2], 'a');
        FILE *in_file;
        FILE *out_file;
        in_file = fopen(argv[1], 'r');
        out_file = fopen(argv[2], 'a');
        if (!in_file){
            return -1;
        }
        if (!out_file){
            return -1;
        }


        fclose(in_file);
        fclose(out_file);
    }
    return 0;
}