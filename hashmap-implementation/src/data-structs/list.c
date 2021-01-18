#include "list.h"
#include <string.h>

static struct list* node_create(entry value) {
    struct list* new_node = malloc(sizeof(struct list));
    *new_node = (struct list) {.value = value, .next = NULL};
    return new_node;
}

static struct list *list_last(struct list *list) {
    while (list) {
        if (list->next != NULL) {
            list = list->next;
        } else {
            return list;
        }
    }
    return NULL;
}

void list_add_front(struct list **list, entry value) {
    if (*list) {
        struct list* new_node = node_create(value);
        new_node->next = *list;
        *list = new_node;
    } else {
        *list = node_create(value);
    }
}

void list_add_back(struct list **list, entry value) {
    if (*list) {
        struct list* last_node = list_last(*list);
        last_node->next = node_create(value);
    } else {
        *list = node_create(value);
    }
}

void list_destroy(struct list* list) {
    struct list *tmp;

    while (list) {
        tmp = list;
        list = list->next;
        free(tmp);
    }
}

void list_foreach(const struct list* list, entry_action action) {
    if (!list) return;

    while (list) {
        action(list->value);
        list = list->next;
    }
}

void entry_print(entry e) {
    printf("%s -> %s\n", e.key, e.value);
}

struct list* c(entry e, struct list* next) {
    struct list* list = node_create(e);
    list->next = next;
    return list;
}

const struct entry* list_find_key(struct list* list, const char * key) {
    for (const struct list *cur = list; cur; cur = cur->next) {
        if (strcmp(key, cur->value.key) == 0) {
            return &(cur->value);
        }
    }
    return NULL;
}