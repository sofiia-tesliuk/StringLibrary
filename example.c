#include "my_str/lib_string.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>

int lambda(char c){
    return c > 'k';
}

int main(int argc, char* argv[]){
    // C-string example
    char example_str[] = {'k', 'i', 't',  't',  'y', '\0'};
    my_str_t str_1, str_3;
    my_str_create(&str_1, 10);
    my_str_from_cstr(&str_1, example_str, 30);
    printf("Example: %s\n\n", str_1.data);
    printf("my_str_size: %zu\n\n", my_str_size(&str_1));
    printf("my_str_capacity: %zu\n\n",my_str_capacity(&str_1));
    printf("my_str_data and my_str_get_cstr: %s\n\n", my_str_get_cstr(&str_1));
    printf("my_str_empty: %d\n\n", my_str_empty(&str_1));
    printf("my_str_getc with index 3: %c \n\n", my_str_getc(&str_1, 3));
    printf("my_str_putc put '1' to index 1: %d, new string: %s\n\n", my_str_putc(&str_1, 1, '1'), str_1.data);
    printf("my_str_pushback 'y' %d: %s\n\n", my_str_pushback(&str_1, 'y'), str_1.data);
    printf("my_str_popback %c: %s\n\n", my_str_popback(&str_1), str_1.data);

    char to_str[] = {'a'};
    my_str_t str_2;
    my_str_from_cstr(&str_2, to_str, 10);

    printf("Before:\n\tfrom: %s, to: %s\n\tmy_str_copy\n", str_1.data, str_2.data);
    my_str_copy(&str_1, &str_2, 1);
    printf("After: to: %s\n\n", str_2.data);

    printf("Before:\n\tstr: %s\n\tmy_str_clear\n", str_2.data);
    my_str_clear(&str_2);
    printf("After: .size: %zu, .capacity: %zu, .data: %s\n\n", str_2.size_m, str_2.capacity_m, str_2.data);

    printf("Before:\n\tstr: %s\n\tmy_str_insert_c insert 'T' at pos = 3\n", str_1.data);
    my_str_insert_c(&str_1, 'T', 3);
    printf("After: %s\n\n", str_1.data);

    char inst_str[] = {'f', 'l', 'u', 'f', 'f', 'y', '\0'};
    my_str_from_cstr(&str_2, inst_str, 10);
    printf("Before:\n\tstr: %s\n\tInsert str: %s\n\tmy_str_insert insert str at pos = 3\n", str_1.data, str_2.data);
    my_str_insert(&str_1, &str_2, 3);
    printf("After: %s\n\n", str_1.data);

    printf("Before:\n\tstr: %s\n\tInsert str: %s\n\tmy_str_insert_cstr insert str at pos = 3\n", str_1.data, inst_str);
    my_str_insert_cstr(&str_1, inst_str, 3);
    printf("After: %s\n\n", str_1.data);

    my_str_from_cstr(&str_1, example_str, 20);
    printf("Before:\n\tstr: %s\n\tAppend str: %s\n\tmy_str_append\n", str_1.data, str_2.data);
    my_str_append(&str_1, &str_2);
    printf("After: %s\n\n", str_1.data);

    printf("Before:\n\tstr: %s\n\tAppend str: %s\n\tmy_str_append_cstr\n", str_1.data, inst_str);
    my_str_append_cstr(&str_1, inst_str);
    printf("After: %s\n\n", str_1.data);

    printf("Compare:\n\tstr_1: %s\n\tstr_2: %s\n\tmy_str_cmp: %d\n\n", str_1.data, example_str, my_str_cmp(&str_1, example_str));
    my_str_from_cstr(&str_1, example_str, 20);
    printf("Compare:\n\tstr_1: %s\n\tstr_2: %s\n\tmy_str_cmp: %d\n\n", str_1.data, example_str, my_str_cmp(&str_1, example_str));
    printf("Compare:\n\tstr_1: %s\n\tstr_2: %s\n\tmy_str_cmp: %d\n\n", str_1.data, inst_str, my_str_cmp(&str_1, inst_str));

    printf("Before:\n\tfrom: %s\n\tto: %s\n\tmy_str_substr\n", str_1.data, str_2.data);
    my_str_substr(&str_1, &str_2, 1, 4);
    printf("After: \n\t to: %s\n\n", str_2.data);

    printf("Before:\n\tfrom: %s\n\tto: %s\n\tmy_str_substr\n", str_1.data, inst_str);
    my_str_substr_cstr(&str_1, inst_str, 1, 4);
    printf("After: \n\t to: %s\n\n", inst_str);

    printf("Find:\n\tstr: %s\n\tsub_str: %s\n\tfrom: %d\n\tmy_str_find: %zu\n\n", str_1.data, str_2.data, 0, my_str_find(&str_1, &str_2, 0));
    printf("Find:\n\tstr: %s\n\tchar: %c\n\tfrom: %d\n\tmy_str_find: %zu\n\n", str_1.data, 't', 0, my_str_find_c(&str_1, 't', 0));

//    printf("Find:\n\tstr: %s\n\tpredicat: if char > 'k'\n\tmy_str_find_if: %c\n\n", str_1.data, my_str_find_if(&str_1, &lambda));

    printf("Before:\n\tstr: %s\n\tstr.size_m: %zu\n\tstr.capacity: %zu\n\tmy_str_free\n", str_2.data, str_2.size_m, str_2.capacity_m);
    my_str_free(&str_2);
    printf("After:\n\tstr: %s\n\tstr.size_m: %zu\n\tstr.capacity: %zu\n\n", str_2.data, str_2.size_m, str_2.capacity_m);

    printf("Before:\n\tstr: %s\n\tstr.size_m: %zu\n\tstr.capacity: %zu\n\tmy_str_free\n", str_2.data, str_2.size_m, str_2.capacity_m);


    my_str_create(&str_3, 75);
    char buff[PATH_MAX];
    char *fname = realpath("../in_file.txt", buff);
    FILE *fp;
    if (fname == NULL){
        perror("Error: ");
    }
    fp = fopen(fname, "r");
    printf("\nRead file: my_str_read_file: %d\n", my_str_read_file(&str_3, fp));
    printf("After:\n\tstr: %s\n\tstr.size_m: %zu\n\tstr.capacity: %zu\n\n", str_3.data, str_3.size_m, str_3.capacity_m);

//    my_str_clear(&str_3);
//    printf("\nRead file: my_str_read stdin: %d\n", my_str_read(&str_3));
//    printf("Result:\n\tstr: %s\n\tstr.size_m: %zu\n\tstr.capacity: %zu\n\n", str_3.data, str_3.size_m, str_3.capacity_m);

    return 0;
}


//        perror("Error: ");
//char cwd[PATH_MAX];
//if (getcwd(cwd, sizeof(cwd)) != NULL) {
//printf("Current working dir: %s\n", cwd);
//}
