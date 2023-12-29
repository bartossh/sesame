#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "sesame.h"
#include "../vendor/ht/src/ht.h"

unsigned long 
SE_shannon(unsigned char *str) {
    if (!str) {
        return 0;
    }

    size_t len = strlen((const char *)str);
    HT ht = HT_new(len *100, HT_HashDJB2);

    for (size_t i = 0; i < len; i++) {
        char key[2];
        key[0] = str[i];
        key[1] = '\0';

        size_t *value = (size_t*)HT_read(&ht, (unsigned char*)key);
        if (!value) {
            value = malloc(sizeof(size_t));
            size_t v = 0;
            memcpy(value, &v, sizeof(size_t));
        }
        size_t update = *value + 1;
        memcpy(value, &update, sizeof(size_t));
        HT_insert(&ht, (unsigned char*)key, value);
    } 

    double sum = 0.0;
    double divider = (double)(len); 

    Iterator it = HT_newIterator();
    while (true) {
        Entity *en = HT_next(&ht, &it);
        if (!en) {
            break;
        }
        size_t *value = (size_t*)(en->value);
        if (!value) {
            printf("FATAL: cannot dereferance value of NULL\n");
            return 0;
        }
        double freq = (double)(*value) / divider;
        sum += freq * log2(freq);
        free(value);
    }
    HT_free(&ht);

    sum *= -1.0;

    return (unsigned long)ceil(sum) * len;
}
