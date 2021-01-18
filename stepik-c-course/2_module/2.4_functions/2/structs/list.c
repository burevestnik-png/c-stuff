#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "maybe_int.h"
#include "../io/io.h"
#include <inttypes.h>

//#error Вставьте часть решения https://stepik.org/lesson/408350/step/8 содержащую нужные функции и исключая read_int64, maybe_int64_print и определение struct list.



struct list *node_create(int64_t value) {
    struct list *const list = malloc(sizeof(struct list));
    *list = (struct list) {.value = value, .next = NULL};
    return list;
}


void list_destroy(struct list *list) {
    struct list *tmp;

    while (list) {
        tmp = list;
        list = list->next;
        free(tmp);
    }
}

void list_add_front(struct list **old, int64_t value) {
    struct list *new_node = node_create(value);
    new_node->next = *old;
    *old = new_node;
}

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

void list_add_back(struct list **old, int64_t value) {
    struct list *last_node = list_last(*old);
    struct list *new_node = node_create(value);
    last_node->next = new_node;
}

size_t list_length(struct list const *list) {
    size_t length = 0;
    while (list) {
        length++;
        list = list->next;
    }
    return length;
}

struct list *list_node_at(struct list *list, size_t idx) {
    if (idx < 0 || idx > list_length(list) - 1)
        return NULL;

    for (size_t i = 0; i < idx; i++) {
        list = list->next;
    }

    return list;
}

struct maybe_int64 list_at(struct list *list, size_t idx) {
    list = list_node_at(list, idx);

    if (list) {
        return some_int64(list->value);
    }
    return none_int64;
}

struct list *list_reverse(const struct list *list) {
    struct list *reversed_list = node_create(list_last(list)->value);

    size_t length = list_length(list);
    for (size_t i = 0; i < length - 1; i++) {
        struct list *last_primordial = list_node_at(list, length - (2 + i));
        list_last(reversed_list)->next = node_create(last_primordial->value);
    }

    return reversed_list;
}

void list_print(const struct list *l) {
    while (l) {
        printf("%" PRId64 " ", l->value);
        l = l->next;
    }
}

