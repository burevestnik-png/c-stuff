#include <string.h>
#include <malloc.h>

struct heap_string {
    char *addr;
};

// скопировать в кучу
struct heap_string halloc(const char *s) {
    size_t string_length = 0;

    while (s[string_length] != 0) {
        string_length++;
    }

    char *copied_string = malloc((string_length + 1) * sizeof(char));
    for (size_t i = 0; i < string_length; i++) {
        copied_string[i] = s[i];
    }
    copied_string[string_length] = 0;

    return (struct heap_string) {
        .addr = copied_string
    };
}

// освободить память
void heap_string_free(struct heap_string h) {
    free(h.addr);
}