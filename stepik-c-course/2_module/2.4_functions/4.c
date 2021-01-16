#include <inttypes.h>
#include <malloc.h>
#include <stdio.h>

enum move_dir { MD_UP, MD_RIGHT, MD_DOWN, MD_LEFT, MD_NONE };

// Определите тип обработчика событий move_callback с помощью typedef
typedef void (move_callback)(enum move_dir dir);

struct list {
    void (*callback) (enum move_dir dir);
    struct list* next;
};

// Робот и его callback'и
// callback'ов может быть неограниченное количество
struct robot {
    const char* name;
    struct list* callback_list;
};

struct list *node_create(move_callback callback) {
    struct list *const list = malloc(sizeof(list));
    *list = (struct list) {.callback = callback, .next = NULL};
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
void list_add_back(struct list **old, move_callback value) {
    struct list *last_node = list_last(*old);
    struct list *new_node = node_create(value);
    if (last_node) {
        last_node->next = new_node;
    } else {
        *old = new_node;
    }
}

// Добавить callback к роботу, чтобы он вызывался при движении
// В callback будет передаваться направление движения
void register_callback(struct robot* robot, move_callback new_cb) {
    list_add_back(&robot->callback_list, new_cb);
}

// Отменить все подписки на события.
// Это нужно чтобы освободить зарезервированные ресурсы
// например, выделенную в куче память
void unregister_all_callbacks(struct robot* robot) {
    list_destroy(robot->callback_list);
}

// Вызывается когда робот движется
// Эта функция должна вызвать все обработчики событий
void move(struct robot* robot, enum move_dir dir) {
    struct list* callback_list = robot->callback_list;
    while (callback_list) {
        callback_list->callback(dir);
        callback_list = callback_list->next;
    }
}

void print_up(enum move_dir dir) { printf("UP"); }
void print_down(enum move_dir dir) { printf("DOWN"); }

int main() {
    struct robot robot = {.name = "Kek", .callback_list = NULL};

    register_callback(&robot, print_up);
    register_callback(&robot, print_down);

    return 0;
}