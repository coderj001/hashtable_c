// hash_table.c
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "hash_table.h"


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
