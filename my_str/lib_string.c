/*
 * lib_string.c
 */

#include "lib_string.h"


int my_str_pushback(my_str_t* str, char c);

// void my_str_clear(my_str_t* str);

// length of c string
size_t len_cstr(const char* cstr){
    size_t length = 0;
    while (cstr[length] != '\0'){
        length++;
    }
    return length;
}

//! Створити стрічку із буфером вказаного розміру. Пам'ять виділяється динамічно.
//! Варто виділяти buf_size+1 для спрощення роботи my_str_get_cstr().
//! УВАГА! Ця функція -- аналог конструктора інших мов.
//! Всі решта функцій можуть вважати, що їм не буде передано жодної змінної,
//! до якої не застосували рівно один раз цю функцію.
//! Тобто, до того, як викликати будь-яку іншу функцію, до змінної типу
//! my_str_t слід рівно один раз за час її існування викликати  my_str_create().
//! (З біллю в серці згадуються закони Мерфі -- кожне твердження
//! обов'язково зрозуміють неправильно. Розказавши 20-30 раз, вирішив
//! записати. Тепер очікую збільшення кількості скарг на довжину опису...)
int my_str_create(my_str_t* str, size_t buf_size){
    // check str pointer
    if (!str){      
        return -1;
    }
    str->data = malloc(buf_size + 1);
    if (str->data != NULL){
        str->capacity_m = buf_size;
        str->size_m = 0;
        str->data[0] = '\0';
        return 0;
    }
    return -1;
}

//! Створити стрічку із буфером вказаного розміру із переданої С-стрічки.
//! Якщо розмір -- 0, виділяє блок, рівний розміру С-стрічки, якщо
//! менший за її розмір -- вважати помилкою.
//! Пам'ять виділяється динамічно.
//! 0 -- якщо все ОК, -1 -- недостатній розмір буфера, -2 -- не вдалося виділити пам'ять
int my_str_from_cstr(my_str_t* str, const char* cstr, size_t buf_size){
    size_t capacity;
    if (buf_size == 0){
        capacity = len_cstr(cstr);
    } else if (buf_size < len_cstr(cstr)){
        return -1;
    } else {
        capacity = buf_size;
    }
    int success = my_str_create(str, capacity);
    if (success == 0){
        for (int i = 0; i < len_cstr(cstr); i++){
            my_str_pushback(str, cstr[i]);
        }
    }
    return -2;
}

//! Звільняє пам'ять, знищуючи стрічку.
//! Аналог деструктора інших мов.
void my_str_free(my_str_t* str){
    free(str->data);
    str->size_m = 0;
    str->capacity_m = 0;
}

//! Повертає розмір стрічки:
size_t my_str_size(const my_str_t* str){
    return str->size_m;
}

//! Повертає розмір буфера:
size_t my_str_capacity(const my_str_t* str){
    return str->capacity_m;
}

//! Повертає булеве значення, чи стрічка порожня:
int my_str_empty(const my_str_t* str){
    return str->size_m == 0;
}

//! Повертає символ у вказаній позиції, або -1, якщо вихід за межі стрічки
//! Тому, власне, int а не char
int my_str_getc(const my_str_t* str, size_t index){
    if (index < str->size_m){
        return str->data[index];
    }
    return -1;
}

//! Записує символ у вказану позиції (заміняючи той, що там був),
//! Повертає 0, якщо позиція в межах стрічки,
//! Поветає -1, не змінюючи її вмісту, якщо ні.
int my_str_putc(my_str_t* str, size_t index, char c){
    if (index < str->size_m){
        str->data[index] = c;
        return 0;
    }
    return -1;
}

//! Додає символ в кінець.
//! Повертає 0, якщо успішно, -1, якщо буфер закінчився.
int my_str_pushback(my_str_t* str, char c){
    if (str->size_m < str->capacity_m){
        str->data[str->size_m] = c;
        str->size_m++;
        str->data[str->size_m] = '\0';
        return 0;
    }
    return -1;
}

//! Викидає символ з кінця.
//! Повертає його, якщо успішно, -1, якщо буфер закінчився.
int my_str_popback(my_str_t* str){
    if (str->size_m > 0){
        char c = str->data[str->size_m - 1];
        str->size_m--;
        str->data[str->size_m] = '\0';
        return c;
    }
    return -1;
}

//! Копіює стрічку. Якщо reserve == true,
//! то із тим же розміром буферу, що й вихідна,
//! інакше -- із буфером мінімального достатнього розміру.
//! Старий вміст стрічки перед тим звільняє, за потреби.
int my_str_copy(const my_str_t* from,  my_str_t* to, int reserve){
    if (!reserve){
        my_str_create(to, from->size_m);
    }
    if(from->size_m > to->capacity_m){
        return -1;
    }
    my_str_clear(to);
    char c;
    for (int i = 0; i < from->size_m; i++){
        c = my_str_getc(from, i);
        my_str_pushback(to, c);
    }
    return 0;
}

//! Очищає стрічку -- робить її порожньою. Складність має бути О(1).
//! Уточнення (чомусь ця ф-ція викликала багато непорозумінь):
//! стрічка продовжує існувати, буфер той самий, того ж розміру, що був,
//! лише містить 0 символів -- size_m = 0.
void my_str_clear(my_str_t* str){
    str->data[0] = '\0';
    str->size_m = 0;
}

//! Вставити символ у стрічку в заданій позиції, змістивши решту символів праворуч.
//! Якщо це неможливо, повертає -1, інакше 0.
int my_str_insert_c(my_str_t* str, char c, size_t pos){
    if (str->size_m < str->capacity_m){
        char shift_c;
        for (int i = pos; i < str->size_m; i++){
            shift_c = my_str_getc(str, i);
            my_str_putc(str, i, c);
            c = shift_c;
        }
        my_str_pushback(str, c);
        return 0;
    }
    return -1;
}

//! Вставити стрічку в заданій позиції, змістивши решту символів праворуч.
//! Якщо це неможливо, повертає -1, інакше 0.
int my_str_insert(my_str_t* str, const my_str_t* from, size_t pos){
    if (str->capacity_m >= str->size_m + from->size_m){
        my_str_insert_cstr(str, from->data, pos);
        return 0;
    }
    return -1;
}

//! Вставити C-стрічку в заданій позиції, змістивши решту символів праворуч.
//! Якщо це неможливо, повертає -1, інакше 0.
int my_str_insert_cstr(my_str_t* str, const char* from, size_t pos){
    size_t len_from = len_cstr(from);
    if (str->capacity_m >= str->size_m + len_from){
        str->size_m += len_cstr(from);
        str->data[str->size_m] = '\0';
        char c;
        for (size_t i = str->size_m - 1; i >= pos + len_from; i--){
            c = my_str_getc(str, i - len_from);
            my_str_putc(str, i, c);
        }
        for (size_t i = pos; i < pos + len_from; i++){
            my_str_putc(str, i, from[i - pos]);
        }
        return 0;
    }
    return -1;
}

//! Додати стрічку в кінець.
//! Якщо це неможливо, повертає -1, інакше 0.
int my_str_append(my_str_t* str, const my_str_t* from){
    if (str->capacity_m >= str->size_m + from->size_m){
        my_str_append(str, from->data);
        return 0;
    }
    return -1;
}

//! Додати С-стрічку в кінець.
//! Якщо це неможливо, повертає -1, інакше 0.
int my_str_append_cstr(my_str_t* str, const char* from){
    my_str_t* from_str;
    size_t len_from = len_cstr(from);
    if (str->capacity_m >= str->size_m + len_from){
        for (int i = 0; i < len_from; i++){
            my_str_pushback(str, from[i]);
        }
        return 0;
    }
    return -1;
}

//! Порівняти стрічки, повернути 0, якщо рівні (за вмістом!)
//! -1 (або інше від'ємне значення), якщо перша менша,
//! 1 (або інше додатне значення) -- якщо друга.
//! Поведінка має бути такою ж, як в strcmp.
int my_str_cmp(my_str_t* str, const char* from){
    if (str->size_m < len_cstr(from)){
        return -1;
    } else if(str->size_m > len_cstr(from)){
        return 1;
    } else{
        for (int i = 0; i < str->size_m; i++){
            if (my_str_getc(str, i) != from[i]){
                return 2;
            }
        }
        return 0;
    }
}

//! Скопіювати підстрічку, із beg включно, по end не включно ([beg, end)).
//! Якщо end виходить за межі str -- скопіювати скільки вдасться, не вважати
//! це помилкою. Якщо ж в ціловій стрічці замало місця, або beg більший
//! за розмір str -- це помилка. Повернути відповідний код завершення.
int my_str_substr(const my_str_t* str, my_str_t* to, size_t beg, size_t end){
    if ((to->capacity_m < end - beg) || (beg >= str->size_m )){
        return -1;
    }
    my_str_clear(to);
    char c;
    if (end > str->size_m){
        end = str->size_m;
    }
    for (int i = beg; i < end; i++){
        c = my_str_getc(str, i);
        my_str_pushback(to, c);
    }
    return 0;
}

//! Її C-string варіант. Враховуючи пізні зміни інтерфейсу, прийнятним
//! Буде і попередній варіант.
int my_str_substr_cstr(const my_str_t* str, char* to, size_t beg, size_t end){
    if ((len_cstr(to) < end - beg) || (beg >= str->size_m )){
        return -1;
    }
    char c;
    if (end > str->size_m){
        end = str->size_m;
    }
    for (int i = 0; i < end - beg; i++){
        c = my_str_getc(str, i + beg);
        to[i] = c;
    }
    return 0;
}

//! Повернути вказівник на С-стрічку, еквівалентну str.
//! Вважатимемо, що змінювати цю С-стрічку заборонено.
//! Якщо в буфері було зарезервовано на байт більше за макс. розмір, можна
//! просто додати нульовий символ в кінці та повернути вказівник data.
const char* my_str_get_cstr(my_str_t* str){
    return str->data;
}

//! Знайти першу підстрічку в стрічці, повернути номер її
//! початку або -1u, якщо не знайдено. from -- місце, з якого починати шукати.
//! Якщо більше за розмір -- вважати, що не знайдено.
size_t my_str_find(const my_str_t* str, const my_str_t* tofind, size_t from){
    int j = 0;
    for (size_t i = from; i < str->size_m; i++){
        if (my_str_getc(str, i) == my_str_getc(tofind, j)){
            j++;
            if (j > tofind->size_m){
                return i - tofind->size_m + 1;
            }
        } else{
            j = 0;
        }
    }
    return -1;
}

//! Знайти перший символ в стрічці, повернути його номер
//! або -1u, якщо не знайдено. from -- місце, з якого починати шукати.
//! Якщо більше за розмір -- вважати, що не знайдено.
size_t my_str_find_c(const my_str_t* str, char tofind, size_t from){
    for (size_t i = from; i < str->size_m; i++){
        if (my_str_getc(str, i) == tofind){
            return i;
        }
    }
    return -1;
}

//TODO
//! Знайти символ в стрічці, для якого передана
//! функція повернула true, повернути його номер
//! або -1u, якщо не знайдено:
size_t my_str_find_if(const my_str_t* str, int (*predicat)(char));

//! Прочитати стрічку із файлу. Повернути, 0, якщо успішно, -1,
//! якщо сталися помилки. Кінець вводу -- не помилка, однак,
//! слід не давати читанню вийти за межі буфера!
//! Рекомендую скористатися fgets().
int my_str_read_file(my_str_t* str, FILE* file){
   if (file != NULL){
       fgets(str->data, (int) str->capacity_m, file);
       fclose (file);
       return 0;
   }
    return -1;
}

//! Аналог my_str_read_file, із stdin
int my_str_read(my_str_t* str){
    return my_str_read_file(str, stdin);
}
