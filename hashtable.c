#include "hashtable.h"
//#include "set.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
//#include "set.c"

/*
Your hashtable.c should implement a set of (key, item) pairs of 
type (char*, void*), and export exactly the functions in the provided 
hashtable.h file. Your hashtable should make use of the set ADT in its
 implementation, an easy way to do this would be to create an array of
 sets. Whenever a new item is added, it is then sorted into one of the
 sets. You can choose any hashing algorithm you like, since our keys 
will always be strings an easy one is treating the key as an integer 
and using modulus. 

Note that the constructor of hashtable takes one argument, which sets
 the number of bins. This is different to the constructor of set, which takes no arguments.
*/
int SIZE;

typedef struct hastable{
	int num_bins;
	set_t **set_bins;
}hashtable_t;
/* Create a new (empty) hashtable; return NULL if error. */
hashtable_t *hashtable_new(const int num_slots){
	SIZE = num_slots;
	hashtable_t *hashtable = malloc(sizeof(hashtable_t));
	if(hashtable == NULL) return false;
	else{
		hashtable->num_bins = SIZE;
		hashtable->set_bins = malloc(sizeof(set_t) * num_slots);
		for(int i=0;i<hashtable->num_bins;i++){
			set_t *set = set_new();
			hashtable->set_bins[i]=set; 
		}
	}
	return hashtable;
}

/* Insert item, identified by key (string), into the given hashtable.
 * The key string is copied for use by the hashtable.
 * Return false if key exists in ht, any parameter is NULL, or error;
 * return true iff new iem was inserted.
 */
int hashing(const char *key){
	int i=0;
	for(int j=0; key[j] != '\0';j++){
		if(key[j] != 0){
			i += key[j];
		}
	}
	int hash = i % SIZE;
	return hash;
} 
bool hashtable_insert(hashtable_t *ht, const char *key, void *item){
	if(ht == NULL || key == NULL || item == NULL) return false;
	int hash_key = hashing(key);
	if(ht->set_bins[hash_key]->key == NULL){
                ht->set_bins[hash_key]->key = strdup(key);
		ht->set_bins[hash_key]->item = item;
                return true;
	}else{
		return false;
	}
}

/* Return the item associated with the given key;
 * return NULL if hashtable is NULL, key is NULL, key is not found.
 */
void *hashtable_find(hashtable_t *ht, const char *key){
	int hash_key;
	if(key == NULL)return NULL;
	else{
		hash_key = hashing(key);
	}
	if(ht == NULL || ht->set_bins[hash_key] == NULL) return NULL;
	else{
		set_t *set = ht->set_bins[hash_key];
		return set->item;
	}
}

/* Print the whole table; provide the output file and func to print each item.
 * Ignore if NULL fp. Print (null) if NULL ht.
 * Print a table with no items if NULL itemprint.
 */
void hashtable_print(hashtable_t *ht, FILE *fp,
                     void (*itemprint)(FILE *fp, const char *key, void *item)){
	if(fp == NULL || itemprint == NULL)return;
        else{
            if(ht == NULL ){
                fprintf(fp,"null");
            }else{
				for(int i=0; i< ht->num_bins;i++){
					if(ht->set_bins[i]->key != NULL && ht->set_bins[i]->item != NULL){
						itemprint(fp,ht->set_bins[i]->key, ht->set_bins[i]->item);
					}
				}
            }
        }
}

/* Iterate over all items in the table; in undefined order.
 * Call the given function on each item, with (arg, key, item).
 * If ht==NULL or itemfunc==NULL, do nothing.
 */
void hashtable_iterate(hashtable_t *ht, void *arg,
               void (*itemfunc)(void *arg, const char *key, void *item) ){
	if(ht == NULL || itemfunc == NULL) return;
	else{
		for(int i=0;i < ht->num_bins;i++){
			if(ht->set_bins[i]->key != NULL && ht->set_bins[i]->item != NULL){
					itemfunc(arg,ht->set_bins[i]->key, ht->set_bins[i]->item);
				}
			//itemfunc(arg,ht->set_bins[i]->key,ht->set_bins[i]->item);
		}

	}
}
/* Delete the whole hashtable; ignore NULL ht.
 * Provide a function that will delete each item (may be NULL).
 */
void hashtable_delete(hashtable_t *ht, void (*itemdelete)(void *item) ){
	if(ht == NULL || itemdelete == NULL) return;
	for(int i=0;i < ht->num_bins;i++){
		set_t *set= ht->set_bins[i];
		set_delete(set,itemdelete);
		/*while(set != NULL){
			set_t *next = set->next;
			if(set->item != NULL){
				itemdelete(ht->set_bins[i]->item);
			}
			free(set->key);
			free(set);
			set = next;
		}*/
		//free(set);
	}
	free(ht->set_bins);
	//free(ht->num_bins);
	free(ht);
}
