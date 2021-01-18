
#include <stdio.h>
#include <inttypes.h>
#include "../io/io.h"
#include "stack.h"

size_t stack_count( const struct stack* s ) {
    return s->count;
}

struct stack stack_create( size_t size ){
    return (struct stack) {.count = 0, .data = array_int_create(size)};
}

void stack_destroy( struct stack* s ) {
    array_int_free(&(s->data));
}

bool stack_is_full( const struct stack * s) {
    return s->count == s->data.size;
}

bool stack_is_empty( const struct stack * s) {
    return s->count == 0;
}

bool stack_push( struct stack* s, int64_t value ) {
    bool result = false;
    if (!stack_is_full(s)) {
        result = array_int_set(s->data, s->count, value);
        s->count++;
    }
    return result;
}

struct maybe_int64 stack_pop( struct stack* s ) {
    if (stack_is_empty(s)) {
        return none_int64;
    }

    s->count--;
    return array_int_get(s->data, s->count);
}

void stack_print( const struct stack* s ) {
    for (size_t i = 0; i < stack_count( s ); i = i + 1 ) {
        print_int64( array_int_get( s->data, i).value );
        printf(" ");
    }
}