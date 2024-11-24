// hash_table.c
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "hash_table.h"


#define HT_PRIME_1 151
#define HT_PRIME_2 167

static ht_item* ht_new_item(const char* k, const char* v){
    // Allocate memory for ht_item
    ht_item* i = malloc(sizeof(ht_item)); 
    if (i == NULL) {
        return NULL; // Handle malloc failure
    }

    i -> key = strdup(k);
    if (i->key == NULL) {
        // Free allocated memory if strdup fails        
        free(i); 
        return NULL;     
    }


    i -> value = strdup(v);
    if (i->value == NULL) {
        free(i->key);
        free(i); 
        return NULL;     
    }
    return i;
}

ht_hash_table* ht_new(){
    ht_hash_table* ht = malloc(sizeof(ht_hash_table));

    ht->size = 53;
    ht->count = 0;

    ht->items = calloc((size_t)ht->size, sizeof(ht_item));
    if (ht->items == NULL) {
        free(ht); // Clean up if calloc fails
        return NULL;     
    }
    return ht;
}

static void ht_del_item(ht_item* i){
    printf("Deleted Hash Item, Key: %s, Value: %s \n",
            i->key,
            i->value);
    free(i->key);
    free(i->value);
    free(i);
}

void ht_del_hash_table(ht_hash_table* ht){
    for (int i = 0; i < ht->size; i++) {
        ht_item* item = ht->items[i];
        if (item != NULL) {
            ht_del_item(item);
        }
    }
    free(ht->items);
    free(ht);
    printf("<----Deleted Hash Table---->\n");
}

static int ht_hash(const char* s, const int a, const int m){
    long hash = 0;
    const int len_S = strlen(s);
    for (int i = 0; i < len_S; i++) {
        hash += (long)pow(a, len_S - (i + 1)) * s[i];
        hash = hash % m;
    }
    return (int)hash;
}

static int ht_get_hash(const char* s, const int num_buckets, const int attempt){
    const int hash_a = ht_hash(s, HT_PRIME_1, num_buckets);
    const int hash_b = ht_hash(s, HT_PRIME_2, num_buckets);
    return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}


void ht_insert(ht_hash_table* ht, const char* key, const char* value){
    ht_item* item = ht_new_item(key, value);
    int index = ht_get_hash(item->key, ht->size, 0);

    ht_item* cur_item = ht->items[index];
    int i=1;
    while(cur_item != NULL){
        index = ht_get_hash(item->key, ht->size, i);
        cur_item = ht->items[index];
        i++;
    }
    ht->items[index] = item;
    ht->count++;
}

void ht_print(ht_hash_table* ht){
        printf("Index\tKey\tValue\n");
    for (int i = 0; i < ht -> size; i++) {
        ht_item* item = ht->items[i]; 
        if (item != NULL) {
            printf("%d\t%s\t%s\n", i, item->key, item->value);
        } else {
            printf("%d\t---\t----  -\n", i);
        }
    }
}

char* ht_search(ht_hash_table* ht, const char* key) {
    int index = ht_get_hash(key, ht->size, 0);
    ht_item* item = ht->items[index];
    int i = 1;
    while(item != NULL){
        if (strcmp(item->key, key) == 0) {
            return item->value ;
        }
        index = ht_get_hash(key, ht->size, i);
        item = ht->items[index];
        i++;
    }
    return NULL;
}
