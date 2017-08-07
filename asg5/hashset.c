// $Id: hashset.c,v 1.9 2014-05-15 20:01:08-07 - - $

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"
#include "hashset.h"
#include "strhash.h"

#define HASH_NEW_SIZE 15
int clusters[1000];

typedef struct hashnode hashnode;
struct hashnode {
   char *word;
   hashnode *link;
};

struct hashset {
   size_t size;
   size_t load;
   hashnode **chains;
};

hashset *new_hashset (void) {
   hashset *this = malloc (sizeof (struct hashset));
   assert (this != NULL);
   this->size = HASH_NEW_SIZE;
   this->load = 0;
   size_t sizeof_chains = this->size * sizeof (hashnode *);
   this->chains = malloc (sizeof_chains);
   assert (this->chains != NULL);
   memset (this->chains, 0, sizeof_chains);
   DEBUGF ('h', "%p -> struct hashset {size = %zd, chains=%p}\n",
                this, this->size, this->chains);
   return this;
}

void double_hashset (hashset *this){
   hashnode **old = this->chains;
   size_t old_size = this->size;
   size_t new_size = old_size * 2 + 1;
   this->chains = malloc (new_size*sizeof(char*));
   this->size = new_size;
   this->load = 0;
   for (size_t i = 0; i < this->size; ++i){
      this->chains[i] = NULL;
   }
   for (size_t i = 0; i < old_size; ++i){
      char *item = old[i];
      if (item != NULL) put_hashset (this, item);
   }
   free (old);
}

void free_hashset (hashset *this) {
   DEBUGF ('h', "free (%p)\n", this);
   memset (this->chains, 0, this->size * sizeof (char*));
   for (size_t i = 0; i < this->size; i++){
      free (this->chains[i]);
   }
   free (this->chains);
   memset (this, 0, sizeof (struct hashset));
   free (this);
}

void put_hashset (hashset *this, const char *item) {
   assert (item != NULL);
   if (this->load * 2 > this->size) double_hashset (this);
   if (this->chains != NULL){
      if (has_hashset(this, item)) return;
   }
   hashnode *new_node = malloc (sizeof (struct hashnode));
   new_node->word = strdup (item);
   new_node->link = NULL;
   size_t hash_index = strhash (item) % this->size;
   if (has_hashset (this, item)) return;
   for (size_t i = hash_index; i < this->size; i++){
      if (this->chains[i] == NULL){
         if (i == hash_index){
            this->chains[i] = new_node;
            this->load++;
            return;
         }
         else{
            this->chains[i - 1]->link = new_node;
            this->load++;
            return;
         }
      }
   }
}

bool has_hashset (hashset *this, const char *item) {
   //STUBPRINTF ("hashset=%p, item=%s\n", this, item);
   size_t hash_index = strhash (item) % this->size;
   for (hashnode *curr = this->chains[hash_index]; curr != NULL;
        curr = curr->link){
           if (strcmp (curr->word, item) == 0) return true;
   }
   return false;
}

void print_hashtable (hashset *this){
   int counts = 0;
   int words = 0;
   for (size_t i = 0; i < this->size; i++){
      if (this->chains[i] != NULL){
         counts++;
         words++; 
      }
      else{
         clusters[counts]++;
         counts = 0;
      }
   }
   printf ("%10d words in the hash set\n",words);
   printf ("%10zd length of the hash array\n",this->size);
   for (int i = 1; i < 1000; i++){
      if(clusters[i] != 0){
         printf("%10d chains of size %d\n", clusters[i], i);
      }
   }
}
/*
void hashset_dump (hashset *this){
   for (size_t i = 0; i < this->size; i++){
      if (this->chains[i] != NULL){
         printf("array[%10zd] = %12zu \"%s\"\n", i,
               (strhash(this->chains[i]->word)%this->size),
               this->chains[i]->word);
      }
   }
}
*/
void print_hashset_clusters (hashset *this){
   printf("%10d words in the hashset\n", (int)this->load);
}










