#include "my_str/lib_string.h"
#include <stdio.h>


int main(int argc, char* argv[]){
    char example_str[] = {'a', 'b', 'c', 'd', 'e', 'f', '\0'};
    my_str_t* str_1;
    my_str_create(str_1, example_str);
    printf("%zu %zu %s", str_1->size_m, str_1->capacity_m, str_1->data);
    return 0;
}