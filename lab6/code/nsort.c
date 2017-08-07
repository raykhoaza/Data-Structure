// $Id: nsort.c,v 1.1 2011-04-29 19:46:42-07 - - $
// KHOA LUONG KLUON7
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <libgen.h>

char *program_name = NULL;
int exit_status = EXIT_SUCCESS;

typedef struct node *node;
struct node {
   double item;
   node link;
};

struct options {
   bool debug;
};

int printlist(node head,struct options *opts) {
   while (head != NULL){
      if (opts->debug == true){
         printf ("&list= %p\n", (void*) &head);
         printf ("list= %p\n", (void*) head);
         printf ("%p -> struct node {item= %.15g, link= %p}\n",
         (void*) head, head->item, (void*) head->link);
         printf ("NULL= %p\n", (void*) NULL);
      }
      else {
      printf("%24.15g\n", head->item);
      }
      head = head->link;
   }
   return exit_status = EXIT_SUCCESS;
}

void scan_options (int argc, char **argv, struct options *opts) {
   opts->debug = false;
   for (;;) {
      int opt = getopt (argc, argv, "d");
      if (opt == EOF) break;
      switch (opt) {
         case 'd':
            opts->debug = true;
            break;
         default:
            exit_status = EXIT_FAILURE;
            fflush (NULL);
            fprintf (stderr, "%s: -%c: invalid option\n",
                     program_name, optopt);
            break;
      }
   }
}

int clearlist(node head){
   while(head != NULL){
   node old = head;
   head = head->link;
   free(old);
   }
   return EXIT_SUCCESS;
}

int main (int argc, char **argv) {
   program_name = basename (argv[0]);
   node head = NULL;
   struct options opts;
   scan_options (argc, argv, &opts);
   
   for (;;) {
      double number;
      int scancount = scanf ("%lg", &number);

      if (scancount == EOF) {
         printlist(head, &opts);
         break;
      }
      else if (scancount == 1){ 
         node new = malloc (sizeof (struct node));
         assert (new != NULL);
         node prev = NULL;
         node curr = head;
         new->item = number;
         //find location
         while (curr != NULL) {
            if (curr->item > number) break;
            prev = curr;
            curr = curr->link;
         }
         //insertion
         new->link = curr;

         if (prev == NULL) head = new;
         else {
           prev->link = new;
         }
      }
      else {
         fprintf (stderr, "%s: bad number\n", program_name);
         exit_status = EXIT_FAILURE;
         return exit_status;
      }
   }
   clearlist(head);
   return exit_status;

}






