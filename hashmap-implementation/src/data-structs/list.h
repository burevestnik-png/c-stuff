#ifndef LIST_H
#define LIST_H

#include <stdint.h>
#include <malloc.h>
#include <stdio.h>
#include <inttypes.h>
#include "../common/common.h"

typedef struct entry {
    const char *key;
    const char *value;
} entry;

struct list {
    entry value;
    struct list *next;
};

typedef void entry_action(entry);

void list_add_front(struct list **list, entry value);

void list_add_back(struct list **list, entry value);

void list_destroy(struct list *list);

void list_print(const struct list *l);

void list_foreach(const struct list *list, entry_action action);

void entry_print(entry e);

struct list* c(entry e, struct list* next);

const struct entry* list_find_key(struct list*, const char *);

#endif