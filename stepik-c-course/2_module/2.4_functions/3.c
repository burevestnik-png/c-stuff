#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Мы хотим, чтобы в структуре user хранились ссылки только на строчки из кучи.
typedef struct {
    char *addr;
} string_heap;

/*  Тип для идентификаторов пользователей
    и его спецификаторы ввода и вывода для printf */
typedef uint64_t uid;
#define PRI_uid PRIu64
#define SCN_uid SCNu64

enum city {
    C_SARATOV, C_MOSCOW, C_PARIS, C_LOS_ANGELES, C_OTHER
};

/*  Массив, где элементам перечисления сопоставляются их текстовые представления */
const char *city_string[] = {
        [C_SARATOV] = "Saratov",
        [C_MOSCOW] = "Moscow",
        [C_PARIS] = "Paris",
        [C_LOS_ANGELES] = "Los Angeles",
        [C_OTHER] = "Other"
};


struct user {
    const uid id;
    const string_heap name;
    enum city city;
};

int int64_comparer(const uint64_t x, const uint64_t y) {
    if (x > y) return 1;
    if (x < y) return -1;
    return 0;
}

int int64_void_comparer(const void *_x, const void *_y) {
    return int64_comparer(((struct user*) _x)->id, ((struct user*) _y)->id);
}

/* Сортировать массив пользователей по полю uid по возрастанию */
void users_sort_uid(struct user users[], size_t sz) {
    qsort(users, sz, sizeof(struct user), int64_void_comparer);
}

int string_comparer(const char* x, const char* y ) {
    return strcmp(x, y);
}

int string_void_comparer(const void *_x, const void *_y) {
    return string_comparer(((struct user*) _x)->name.addr, ((struct user*) _y)->name.addr);
}

/* Сортировать массив пользователей по полю name */
/* Порядок строк лексикографический; можно использовать компаратор
   строк -- стандартную функцию strcmp */
void users_sort_name(struct user users[], size_t sz) {
    qsort(users, sz, sizeof(struct user), string_void_comparer);
}

int city_comparer(const enum city x, const enum city y) {
    return strcmp(city_string[x], city_string[y]);
}

int city_void_comparer(const void* _x, const void* _y) {
    return city_comparer(((struct user*) _x)->city, ((struct user*) _y)->city);
}

/* Сортировать массив по _текстовому представлению_ города */
void users_sort_city(struct user users[], size_t sz) {
    qsort(users, sz, sizeof(struct user), city_void_comparer);
}