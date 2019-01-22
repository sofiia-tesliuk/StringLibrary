/*
 * lib_string.c
 */
#include <ctype.h>
#include "lib_string.h"


// my_str constructor
int my_str_create(my_str_t* str, size_t buf_size){
    if (!str){                                                                               // check str pointer
        return -1;
    }
    str->data = malloc(buf_size + 1);
    if (str->data != NULL){                                                                  // check if malloc worked
        str->capacity_m = buf_size;
        str->size_m = 0;
        str->data[0] = '\0';
        return 0;
    }
    return -1;
}


// my_str destructor
void my_str_free(my_str_t* str){
    str->data = NULL;
    str->size_m = 0;
    str->capacity_m = 0;
}


// get size of c string
size_t cstr_get_len(const char *cstr){
    size_t length = 0;
    while (cstr[length] != '\0'){
        length++;
    }
    return length;
}


// cstr --> my_str |  return -- 0 if OK -- (-1) if buf_size too small-- (-2) if malloc error
int my_str_from_cstr(my_str_t* str, const char* cstr, size_t buf_size){
    size_t capacity;
    if (buf_size == 0){
        capacity = cstr_get_len(cstr);
    } else if (buf_size < cstr_get_len(cstr)){
        return -1;
    } else { capacity = buf_size; }

    int error = my_str_create(str, capacity);
    if (!error){
        for (int i = 0; i < cstr_get_len(cstr); i++){
            my_str_pushback(str, cstr[i]);
        }
        return  0;
    } else { return -2; }
}





// get size
size_t my_str_size(const my_str_t *str){
    return str->size_m;
}


// get capacity
size_t my_str_capacity(const my_str_t* str){
    return str->capacity_m;
}


// check if my_str is empty
int my_str_empty(const my_str_t* str){
    return str->size_m == 0;
}

// get char by index | return char if OK else -1
int my_str_getc(const my_str_t* str, size_t index){
    if (index < str->size_m){
        return str->data[index];
    }
    return -1;
}


// set char by index | return 0 if OK else -1
int my_str_putc(my_str_t* str, size_t index, char c){
    if (index < str->size_m){
        str->data[index] = c;
        return 0;
    } else { return -1; }
}


// append char | return 0 if OK else -1
int my_str_pushback(my_str_t* str, char c){
    if (str->size_m < str->capacity_m) {
        str->data[str->size_m] = c;
        str->size_m++;
        str->data[str->size_m] = '\0';
        return 0;
    } else { return -1; }
}


// pop char | return 0 if OK else -1
int my_str_popback(my_str_t* str){
    if (str->size_m > 0){
        char c = str->data[str->size_m - 1];
        str->size_m--;
        str->data[str->size_m] = '\0';
        return c;
    } else { return -1; }
}

// copy my_str | if reserve == true and 'from' fits into 'to', to-capacity is kept -- else adjusted.
int my_str_copy(const my_str_t* from,  my_str_t* to, int reserve){
    if ((!reserve) || (from->size_m > to->capacity_m)) {
        to->capacity_m = my_str_size(from) + 1;
    }
    if (to->data){
        my_str_clear(to);
    }
    for (int i = 0; i < from->size_m; i++){
        my_str_pushback(to, from->data[i]);
    }
    return 0;
}



// free content of my_str
void my_str_clear(my_str_t* str){
    str->data[0] = '\0';
    str->size_m = 0;
}


// shift-insert char by index | return 0 if OK else (-1) if capacity overflow
int my_str_insert_c(my_str_t* str, char c, size_t pos){
    if (str->size_m < str->capacity_m){
        char shift_c;
        for (size_t i = pos; i < str->size_m; i++){
            shift_c = str->data[i];
            str->data[i] = c;
            c = shift_c;
        }
        my_str_pushback(str, c);
        return 0;
    } else { return -1; }
}


// shift-insert another my_str by index | return 0 if OK else (-1) for capacity overflow
int my_str_insert(my_str_t* str, const my_str_t* from, size_t pos){
    if (str->capacity_m >= str->size_m + from->size_m){
        my_str_insert_cstr(str, from->data, pos);
        return 0;
    } else { return -1; }
}


// shift-insert cstr by index | return 0 if OK else (-1) if capacity overflow
int my_str_insert_cstr(my_str_t* str, const char* from, size_t pos){
    size_t len_from = cstr_get_len(from);
    if (str->capacity_m >= str->size_m + len_from){
        str->size_m += cstr_get_len(from);
        str->data[str->size_m] = '\0';
        char c;
        for (size_t i = str->size_m - 1; i >= pos + len_from; i--){
            c = str->data[i - len_from];
            my_str_putc(str, i, c);
        }
        for (size_t i = pos; i < pos + len_from; i++){
            my_str_putc(str, i, from[i - pos]);
        }
        return 0;
    }
    return -1;
}


// append my_str | return 0 if OK else (-1) for capacity overflow
int my_str_append(my_str_t* str, const my_str_t* from){
    if (str->capacity_m >= str->size_m + from->size_m){
        my_str_append_cstr(str, from->data);
        return 0;
    } else { return -1; }
}


// append cstr | return 0 if OK else (-1) for capacity overflow
int my_str_append_cstr(my_str_t* str, const char* from){
    if (str->capacity_m >= str->size_m + cstr_get_len(from)){
        for (int i = 0; i < cstr_get_len(from); i++){
            my_str_pushback(str, from[i]);
        }
        return 0;
    } else { return -1; }
}


// compare my_str and cstr (by content) | return 0 if equal -- else (-1) if 1st < 2nd -- else 1
int my_str_cmp(my_str_t* str, const char* from){
    if (str->size_m < cstr_get_len(from)){
        return -1;
    } else if (str->size_m > cstr_get_len(from)){
        return 1;
    } else{
        for (int i = 0; i < str->size_m; i++){
            if (str->data[i] != from[i]){
                return 2;
            }
        }
        return 0;
    }
}

// copy my_str [beg, end)  |  return 0 if OK -- else (-1) for wrong slice indices -- else (-2) for to-capacity overflow
int my_str_substr(const my_str_t* str, my_str_t* to, size_t beg, size_t end){
    if ((beg > end) || (beg >= str->size_m)){
        return -1;
    }
    if (to->capacity_m < end - beg) {
        return -2;
    }
    if (end > str->size_m){                // if slice's end is beyond --> copy as much as possible
        end = str->size_m;
    }
    my_str_t str_slice;
    my_str_create(&str_slice, end - beg);
    for (size_t i = beg; i < end; i++){
        str_slice.data[i] = str->data[i];
    }
    my_str_clear(to);
    my_str_copy(&str_slice, to, 1);
    to->data[end] = '\0';

    return 0;
}


// copy my_str [beg, end) into cstr | return 0 for OK -- (-1) for wrong slice indices -- (-2) for cstr overflow
int my_str_substr_cstr(const my_str_t* str, char* to, size_t beg, size_t end){
    if ((beg > end) || (beg >= str->size_m)){
        return -1;
    }
    if (cstr_get_len(to) < end - beg) {
        return -2;
    }
    if (end > str->size_m){                // if slice's end is beyond --> copy as much as possible
        end = str->size_m;
    }

    char c;
    for (size_t i = 0; i < end - beg; i++){
        c = str->data[i + beg];
        to[i] = c;
    }
    to[end - beg] = '\0';
    return 0;
}


// return cstr similar to my_str
const char* my_str_get_cstr(my_str_t* str){
    return str->data;
}


// find the 1st occurrence of a substring | return it's index if found -- else return -1u
size_t my_str_find(const my_str_t* str, const my_str_t* tofind, size_t from){
    size_t j = 0;
    for (size_t i = from; i < str->size_m; i++){
        if (my_str_getc(str, i) == my_str_getc(tofind, j)){
            j++;
            if (j >= tofind->size_m){
                return i - tofind->size_m + 1;
            }
        } else{
            j = 0;
        }
    }
    return (size_t) -1u;
}


// find the 1st occurrence of a char | return it's index if found -- else return -1u
size_t my_str_find_c(const my_str_t* str, char tofind, size_t from){
    for (size_t i = from; i < str->size_m; i++){
        if (my_str_getc(str, i) == tofind){
            return i;
        }
    }
    return (size_t) -1u;
}

// find thw 1st occurrence of a char : predicat(char) returns true | return index of the char if found else -1u
size_t my_str_find_if(const my_str_t* str, int (*predicat)(char)){
    char c;
    for (size_t i = 0; i < str->size_m; i++){
        c = str->data[i];
        if (predicat(c)){
            return i;
        }
    }
    return (size_t ) -1u;
}


// read file into my_str | return 0 if OK -- else (-1) if in case of given wrong path to the file
int my_str_read_file(my_str_t* str, FILE* file){
    if (file != NULL) {
        fgets(str->data, str->capacity_m, file);
        fclose(file);

        size_t i = 0;
        while (str->data[i] != '\0'){
            i++;
        }
        str->size_m = i;
        str->data[i] = '\0';
        return 0;
    } else { return -1; }
}


// read stdin into my_str | return 0 if OK
int my_str_read(my_str_t* str){
    fgets(str->data, str->capacity_m, stdin);
    size_t i = 0;
    while (str->data[i] != '\0') {
        printf("%c", str->data[i]);
        i++;
    }
    if (i <= str->capacity_m){
        i--;
    }
    str->data[i] = '\0';
    str->size_m = i;
    return 0;
}


int my_str_all_alpha(my_str_t* str, my_str_t* res_str){
    if (res_str->capacity_m >= str->capacity_m){
        for (size_t i = 0; i < str->size_m; i++){
            if (isalpha(str->data[i]) || str->data[i] == ' '){
                my_str_pushback(res_str, str->data[i]);
            }
        }
        return 0;
    } else return -1;
}


int my_str_fix_spaces(my_str_t* str, my_str_t* res_str){
    if (res_str->capacity_m >= str->capacity_m){
        size_t count = 0;
        for (size_t i = 0; i < str->size_m; i++){
            if (str->data[i] == ' '){
                count++;
            } else{
                count = 0;
            }

            if (count <= 1){
                my_str_pushback(res_str, str->data[i]);
            }
        }
        return 0;
    } else return -1;
}