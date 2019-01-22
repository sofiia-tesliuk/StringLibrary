#include <stdio.h>
#include "my_str/lib_string.h"
#include "ctype.h"

int main(int argc, char* argv[]){
    // init
    size_t curr, next;
    my_str_t str_fname, str_0, str_1, str_copy, str_res;
    my_str_create(&str_fname, 100);
    my_str_create(&str_0, 1000000);
    my_str_create(&str_1, 1000000);
    my_str_create(&str_copy, 1000000);
    my_str_create(&str_res, 1000000);

    // get filename
    my_str_read(&str_fname);

    // read from file
    FILE *fp = fopen(my_str_get_cstr(&str_fname), "r");
    my_str_read_file(&str_0, fp);
    my_str_all_alpha(&str_0, &str_1);

    printf("this: %s\n", my_str_get_cstr(&str_0));
    printf("this: %s\n", my_str_get_cstr(&str_1));

    // to one space
    my_str_fix_spaces(&str_1, &str_res);

    printf("res: %s", my_str_get_cstr(&str_res));

    fp = fopen("../out_file.txt", "w");
    fputs(my_str_get_cstr(&str_res), fp);


    return 0;
}