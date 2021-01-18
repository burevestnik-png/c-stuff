#include "map.h"

static struct list** map_find_bucket(struct map m, key k) {
    const size_t sz = strlen(k);
    const hash hash = hash_compute(k, sz);
    return m.buckets + hash % MAP_SIZE;
}

struct map map_create() {
    return (struct map) {
        .buckets = calloc(MAP_SIZE, sizeof(struct list*))
    };
}

void map_destroy(struct map map) {
    free(map.buckets);
}

void map_add(struct map m, key k, value v) {
    list_add_front(
            map_find_bucket(m, k),
            (struct entry) {.key = k, .value = v});
}

void map_foreach_kvp(struct map m, kvp_action action) {
    for (size_t i = 0; i < MAP_SIZE; i++) {
        if (m.buckets[i]) {
            list_foreach(m.buckets[i], action);
        }
    }
}

const value map_get(struct map m, const key k) {
    struct list** bucket = map_find_bucket(m, k);
    const struct entry* entry = list_find_key(*bucket, k);
    return entry->value;
}