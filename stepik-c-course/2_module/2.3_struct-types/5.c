#include <stdio.h>
#include <inttypes.h>
#include <malloc.h>
#include <stdbool.h>

struct maybe_int64 {
    int64_t value;
    bool valid;
};

struct maybe_int64 some_int64(int64_t i);

const struct maybe_int64 none_int64 = {0, false};

void maybe_int64_print(struct maybe_int64 i) {
    if (i.valid) printf("Some %" PRId64, i.value);
    else printf("None");
}

void print_int64(int64_t i) { printf("%"PRId64, i); }


struct array_int {
    int64_t *data;
    size_t size;
};

struct array_int array_int_create(size_t sz) {
    return (struct array_int) {.size = sz, .data = malloc(sz * sizeof(int64_t))};
}

int64_t *array_int_last(struct array_int a);

struct maybe_int64 array_int_get(struct array_int a, size_t i) {
    if (i < 0 || i > a.size || a.size == 0) return none_int64;
    return (struct maybe_int64) {.valid = true, .value = a.data[i]};
}

bool array_int_set(struct array_int a, size_t i, int64_t value) {
    if (i < 0 || i > a.size || a.size == 0) return false;
    a.data[i] = value;
    return true;
}

void array_int_print(struct array_int array);

void array_int_free(struct array_int *a) {
    if ( a->size > 0 ) {
        free(a->data);
        a->size = 0;
    }
}

struct stack {
    size_t count;
    struct array_int data;
};

// Количество элементов в стеке
size_t stack_count(const struct stack *s) {
    return s->count;
}

// Создаем и деинициализируем стек
struct stack stack_create(size_t size) {
    return (struct stack) {.count = 0, .data = array_int_create(size)};
}

void stack_destroy(struct stack *s) {
    array_int_free(&(s->data));
}

// Стек полный
bool stack_is_full(const struct stack *s) {
    return s->count == s->data.size;
}

// Стек пустой
bool stack_is_empty(const struct stack *s) {
    return s->count == 0;
}

// Поместить значение в стек
bool stack_push(struct stack *s, int64_t value) {
    bool result = false;
    if (!stack_is_full(s)) {
        result = array_int_set(s->data, s->count, value);
        s->count++;
    }
    return result;
}

// Вынуть значение с вершины стека. Может вернуть none_int64
struct maybe_int64 stack_pop(struct stack *s) {
    if (stack_is_empty(s)) {
        return none_int64;
    }

    s->count--;
    return array_int_get(s->data, s->count);
}

void stack_print(const struct stack *s) {
    for (size_t i = 0; i < stack_count(s); i = i + 1) {
        print_int64(array_int_get(s->data, i).value);
        printf(" ");
    }
}

int main() {
    struct maybe_int64 none = none_int64;
    maybe_int64_print(none);
    return 0;
}