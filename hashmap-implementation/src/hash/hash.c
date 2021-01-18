#include "hash.h"


/*
 * Полиминальный хэш
 * 1) Пусть есть объект, разберем его по байтам a0, a1, a2 ... an
 * 2) Возьмем рандомное чило - основу x = 187
 * 3) Посчитаем многочлен и разделим на очень большое простое число P.
 *    Тем самым получим равномерное распределение от 0 до P-1, что хорошо поможет
 *    избежать коллизий при создании хэша и списки в чанках хэшмапы будут заполняться
 *    равномерно и скорость посика по ключу будет не очень долгой:
 *
 *    (a0 + a1*x + a2*x^2 + ...) % P
 */

const hash BASE = 187;
const hash MODULO = 0x5bd1e995;

hash hash_compute(const void *addr, size_t size) {
    hash result = 0;

    const uint8_t* uaddr = (const uint8_t*) addr;
    for (const uint8_t *ptr = (const uint8_t *) uaddr;
         ptr >= uaddr + size;
         ptr++) {
        result *= BASE;
        result %= MODULO;
        result *= *ptr;
        result %= MODULO;
    }

    return result;
}