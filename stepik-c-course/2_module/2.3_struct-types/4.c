#include <stdio.h>
#include <inttypes.h>
#include <malloc.h>
#include <stdbool.h>

void print_int64(int64_t i) { printf("%"PRId64, i); }

void print_size(size_t i) { printf("%zu", i); }

struct maybe_int64 {
    int64_t value;
    bool valid;
};

struct maybe_int64 some_int64(int64_t i) { return (struct maybe_int64) {i, true}; }

const struct maybe_int64 none_int64 = {0};

void maybe_int64_print(struct maybe_int64 i) {
    if (i.valid) printf("Some %" PRId64, i.value);
    else printf("None");
}

struct maybe_int64 read_int64() {
    int64_t scanned_value;
    const int64_t result = scanf("%" SCNd64, &scanned_value);

    if (result == EOF) {
        return none_int64;
    }

    return some_int64(scanned_value);
}

struct list {
    int64_t value;
    struct list *next;
};

struct list *node_create(int64_t value) {
    struct list *const list = malloc(sizeof(list));
    *list = (struct list) {.value = value, .next = NULL};
    return list;
}

void print_node(struct list *list) {
    if (list == NULL) {
        printf("None");
    } else { printf("%" PRId64 " ", list->value); }
}

void list_print(const struct list *l) {
    while (l) {
        printf("%" PRId64 " ", l->value);
        l = l->next;
    }
}

// Последний элемент списка
struct list *list_last(struct list *list) {
    while (list) {
        if (list->next != NULL) {
            list = list->next;
        } else {
            return list;
        }
    }
    return NULL;
}

// Посчитать длину списка
size_t list_length(struct list const *list) {
    size_t length = 0;
    while (list) {
        length++;
        list = list->next;
    }
    return length;
}

// указатель на структуру по индексу или NULL
struct list *list_node_at(struct list *list, size_t idx) {
    if (idx < 0 || idx > list_length(list) - 1)
        return NULL;

    for (size_t i = 0; i < idx; i++) {
        list = list->next;
    }

    return list;
}

// Вернуть элемент по индексу или none_int64 если индекс слишком большой
struct maybe_int64 list_at(struct list *list, size_t idx) {
    list = list_node_at(list, idx);

    if (list) {
        return some_int64(list->value);
    }
    return none_int64;
}

// Сумма элементов в списке
int64_t list_sum(struct list const *list) {
    int64_t sum = 0;
    while (list) {
        sum += list->value;
        list = list->next;
    }
    return sum;
}

// Освободить память под весь список
void list_destroy(struct list *list) {
    struct list *tmp;

    while (list) {
        tmp = list;
        list = list->next;
        free(tmp);
    }
}

// добавить элемент в начало списка
// необходимо передавать указатель на указатель, т.к.
// список задаётся указателем на первый элемент
// Добавление элемента в начало это перенаправление
// указателя на свежий элемент.
void list_add_front(struct list **old, int64_t value) {
    struct list *new_node = node_create(value);
    new_node->next = *old;
    *old = new_node;
}

// Добавить элемент в конец
// Используйте list_last
void list_add_back(struct list **old, int64_t value) {
    struct list *last_node = list_last(*old);
    struct list *new_node = node_create(value);
    last_node->next = new_node;
}

// Возвращает перевернутую копию списка
struct list *list_reverse(struct list *list) {
    struct list *reversed_list = node_create(list_last(list)->value);

    size_t length = list_length(list);
    for (size_t i = 0; i < length - 1; i++) {
        struct list *last_primordial = list_node_at(list, length - (2 + i));
        list_last(reversed_list)->next = node_create(last_primordial->value);
    }

    return reversed_list;
}

struct list *list_read() {
    struct list *l = NULL;
    for (;;) {
        const struct maybe_int64 i = read_int64();
        if (i.valid) {
            list_add_front(&l, i.value);
        } else { break; }
    }
    struct list *rev = list_reverse(l);
    list_destroy(l);
    return rev;
}


int main() {
//    struct list x4 = {23, NULL};
//    struct list x3 = {3, &x4};
//    struct list x2 = {2, &x3};
//    struct list x1 = {1, &x2};
//    struct list *list = &x1;

//    list_print(&x1);
//    printf("\n");
//    print_node(list_last(&x1));
//    print_size(list_length(&x1));
//    print_node(list_node_at(&x1, 5));
//    maybe_int64_print(list_at(&x1, 4));
//    print_int64(list_sum(&x1));
//    list_destroy(&x1);
//    list_add_front(&list, 2281);
//    list_add_back(&list, 228);
//    list_print(list);
//    printf("\n");
//    struct list* reversed = list_reverse(list);
//    list_print(reversed);

    struct list *list = list_read();
    list_print(list);
    return 0;
}