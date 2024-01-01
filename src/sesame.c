/// Copyright (c) 2024 Bartosz Lenart

#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <curl/curl.h>
#include <openssl/sha.h>
#include "sesame.h"
#include "../vendor/ht/src/ht.h"
#include "../vendor/log.c/src/log.h"

#define DAYS_IN_YEAR 365
#define OPERATIONS_PER_DAY  (60*60*24*1000)
#define PWND_BUFF_SIZE (5*1000*1000)

const char url[38] = "https://api.pwnedpasswords.com/range/\0";

unsigned long 
se_shannon(const unsigned char *str) {
    if (!str) {
        return 0;
    }

    size_t len = strlen((const char *)str);
    HT ht = ht_new(len *100, ht_HashDJB2);

    for (size_t i = 0; i < len; i++) {
        char key[2];
        key[0] = str[i];
        key[1] = '\0';

        size_t *value = (size_t*)ht_read(&ht, (unsigned char*)key);
        if (!value) {
            value = malloc(sizeof(size_t));
            size_t v = 0;
            memcpy(value, &v, sizeof(size_t));
        }
        size_t update = *value + 1;
        memcpy(value, &update, sizeof(size_t));
        ht_insert(&ht, (unsigned char*)key, value);
    } 

    double sum = 0.0;
    double divider = (double)(len); 

    Iterator it = ht_newIterator();
    while (true) {
        Entity *en = ht_next(&ht, &it);
        if (!en) {
            break;
        }
        size_t *value = (size_t*)(en->value);
        if (!value) {
            log_fatal("cannot dereferance value of NULL");
            return 0;
        }
        double freq = (double)(*value) / divider;
        sum += freq * log2(freq);
        free(value);
    }
    ht_free(&ht);

    sum *= -1.0;

    return (unsigned long)ceil(sum) * len;
}

unsigned long long 
se_bruteForceDays(unsigned long bits) { 
    return ((unsigned long long)pow(2.0, (double)bits)) / OPERATIONS_PER_DAY ;
}

char *
se_yearsAndDays(unsigned long long days) {
    unsigned long long d = days % DAYS_IN_YEAR;
    unsigned long long y = days / DAYS_IN_YEAR;
    size_t len = (d / 10 + 1)  + (y / 10 + 1) + 17; 
    char *buf = malloc(sizeof(char)*len);
    snprintf(buf, len*sizeof(char), "%llu years and %llu days", y, d);
    buf[len-1] = '\0';
    return buf;
}

struct string {
    char *ptr;
    size_t len;
};

static void 
init_string(struct string *s) {
    s->len = 0;
    s->ptr = malloc(s->len+1);
    if (s->ptr == NULL) {
        fprintf(stderr, "Unexpected failure\n");
        exit(EXIT_FAILURE);
    }
    s->ptr[0] = '\0';
}

static size_t 
writefunc(void *ptr, size_t size, size_t nmemb, struct string *s) {
    size_t new_len = s->len + size*nmemb;
    s->ptr = realloc(s->ptr, new_len+1);
    if (s->ptr == NULL) {
      fprintf(stderr, "Unexpected failure\n");
      exit(EXIT_FAILURE);
    }
    memcpy(s->ptr+s->len, ptr, size*nmemb);
    s->ptr[new_len] = '\0';
    s->len = new_len;
    return size*nmemb;
}

static void
free_string(struct string *s) {
    free(s->ptr);
    s->ptr = NULL;
    s->len = 0;
}

static unsigned char * 
sha1sum(const unsigned char *str) {
    size_t len = strlen((const char*)str);
    unsigned char * s = malloc(sizeof(char)*SHA_DIGEST_LENGTH);
    SHA1(str, len, s);
    unsigned char *hash = malloc(sizeof(char)*((SHA_DIGEST_LENGTH*2)+1));

    for(int i = 0; i<SHA_DIGEST_LENGTH; ++i) {
        snprintf((char *)(&hash[i*2]), sizeof(char)*5, "%02X", s[i]);
    }
    hash[40]='\0';
    free(s);
    return hash;
}

static unsigned long long 
findMatching(const unsigned char *buff, unsigned char *hash) {
    char * line = strtok(strdup((const char*)buff), "\n");
    while(line) {
        if (strncmp(line, (const char *)(&hash[5]), 35) == 0) {
            unsigned long long value = strtoull((char *)(&line[36]), NULL, 10);
            return value;
        }
        line  = strtok(NULL, "\n");
    }
    return 0;
}

unsigned long long 
se_getPwned(const unsigned char *str) {
    if (!str) {
        return 0;
    }

    CURL *curl;
    if ((curl = curl_easy_init()) == NULL) {
        fprintf(stderr, "%s\n", "Cannot create curl request.\n"); 
        exit(EXIT_FAILURE);
    }
    unsigned char *hash = sha1sum(str); 
    char url_request[43] = "";
    int written = snprintf(url_request, 43,"%s%s", url, hash);
    if (written == 0) {
        fprintf(stderr, "Cannot create url request.\n"); 
        exit(EXIT_FAILURE);
    }

    struct string s;
    init_string(&s);
    
    curl_easy_setopt(curl, CURLOPT_URL, url_request);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
    
    if (curl_easy_perform(curl) == CURLE_OK) {
        unsigned char *buffer = malloc(sizeof(unsigned char)*s.len+1);
        memcpy((void *)buffer, (void *)s.ptr, s.len);
        buffer[s.len]= '\0';
        free_string(&s);

        int result = findMatching(buffer, hash); 

        free(buffer);
        buffer = NULL;
        free(hash);
        hash = NULL; 
        curl_easy_cleanup(curl);
        
        return result;
    } else {
        fprintf(stderr, "Failed to download password hashes from %s.\n", url_request); 
        
        free_string(&s);
        free(hash);
        hash = NULL;
        curl_easy_cleanup(curl);
        
        exit(EXIT_FAILURE);
    }
}
