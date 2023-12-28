
//placeholder
#include <stdio.h>
#include "set.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//typedef struct Set set_t;
/*typedef struct Set
{
char *key;
void *item;
set_t *next;
} set_t;
*/
//Function prototype declaration
void *set_find(set_t *, const char *);
bool set_insert(set_t *, const char *, void *);
void set_print(set_t *, FILE *, void (*itemprint)(FILE *fp, const char *key, void *item) );
void set_iterate(set_t *set, void *arg,void (*itemfunc)(void *arg, const char *key, void *item) );
void set_delete(set_t *set, void (*itemdelete)(void *item) );

set_t* set_new(void)/* Create a new (empty) set; return NULL if error. */
{
	set_t *new_set =(set_t *) malloc(sizeof(set_t));
	new_set->key = NULL;
	new_set->item = NULL;
	new_set->next = NULL;
	return new_set;
}
/* Insert item, identified by a key (string), into the given set.
 * The key string is copied for use by the set.
 * Return false if key exists, any parameter is NULL, or error;
 * return true iff new item was inserted.
 */
bool set_insert(set_t *set, const char *key, void *item)
{
	if( key == NULL || item == NULL || set == NULL)return false;
	//Check if key exists
	set_t *temp = set;
		//if(set_find(set,key) != NULL)return false;
	while(temp != NULL){
		if(temp->key != NULL && strcmp(temp->key,key) == 0){
			return false;
		}
		temp = temp->next;
	}
	if(set->key == NULL){//First node is empty
		set->key = strdup(key);
		set->item = item;
		set->next = NULL;
		return true;
	}else if(set->next == NULL){
		set->next = set_new();
		set = set->next;
		set->key = strdup(key);
		set->item = item;
		set->next = NULL;
		return true;
	}else{
		while(set->next != NULL){
			if(strcmp(set->key,key) == 0){
				return false;
			}
			set = set->next;
		}
		set->next = set_new();
		set = set->next;
		set->key = strdup(key);
		set->item = item;
		set->next = NULL;
		return true;
	}
}
/* Return the item associated with the given key;
 * return NULL if set is NULL, key is NULL, or key is not found.
 */
void *set_find(set_t *set, const char *key){
	if(set == NULL || key == NULL){
		return NULL;
	}else{
		if(set->next == NULL){
			if(strcmp(set->key,key) == 0)
				{return set->item;}
			else{return false;}
		}else{
			while(set->next != NULL){
				if(strcmp(set->key,key) == 0){
					return set->item;
				}
				set = set->next;
			}
			return NULL;//Key not found
		}
	}
}
/* Print the whole set; provide the output file and func to print each item.
 * Ignore if NULL fp. Print (null) if NULL set.
 * Print a set with no items if NULL itemprint.
*/
void set_print(set_t *set, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item) ){
	if(fp == NULL || itemprint == NULL)return;
	else{
		if(set == NULL ){
			fprintf(fp,"null");
       		}else{
                	while(set != NULL){
                        	itemprint(fp,set->key,set->item);
                        	set = set->next;
                	}
        	}
	}
}
/* Iterate over all items in the set, in undefined order.
 * Call the given function on each item, with (arg, key, item).
 * If set==NULL or itemfunc==NULL, do nothing.
 */
void set_iterate(set_t *set, void *arg,
                 void (*itemfunc)(void *arg, const char *key, void *item) ){
	if(set != NULL && itemfunc != NULL){
		while(set != NULL){
			itemfunc(arg, set->key, set->item);
			set = set->next;
		}
	}
	return;
}

/* Delete the whole set; ignore NULL set.
 * Provide a function that will delete each item (may be NULL).
 */
void set_delete(set_t *set, void (*itemdelete)(void *item) ){
	if(itemdelete == NULL || set == NULL)return;
	if(set != NULL){
		set_t *next_node,*temp;
		next_node = set;
//fprintf(stderr,"Test within code 1");

		while(next_node != NULL){
//		fprintf(stderr,"Test within code 2");

			if(next_node->item != NULL){
//fprintf(stderr, "Deleting item: %s\n", (char*)next_node->item); // Adjust the format based on your item type
                		itemdelete(next_node->item);
			}
			free(next_node->key);
			temp = next_node->next;
			free(next_node);
			next_node = temp;
		}
	}
}
