// $Id: nsort.c,v 1.1 2011-04-29 19:46:42-07 - - $
// KHOA LUONG KLUON7
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <libgen.h>
#include <string.h>

char *program_name = NULL;
int exit_status = EXIT_SUCCESS;

typedef struct node *node;
struct node {
   char *string;
   node link;
};

struct options {
   bool debug;
};

int printlist(node head,struct options *opts) {
   while (head != NULL){
      if (opts->debug == true){
         printf ("%p -> struct node {item= %1s, link= %p}\n",
                (void*) head, head->string, (void*) head->link);
      }
      else {
      printf("%s\n", head->string);
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
   free(old->string);
   free(old);
   }
   return exit_status = EXIT_SUCCESS;
}

int main (int argc, char **argv) {
   program_name = basename (argv[0]);
   struct options opts;
   scan_options (argc, argv, &opts);
   if (exit_status == EXIT_FAILURE) return exit_status;

   node head = NULL;
   char buffer[72];
   int linenr;
   for (linenr = 1; ; ++linenr) {
      char *gotline = fgets (buffer, sizeof buffer, stdin);

      if (gotline == NULL) {
         break;
      }
      char *nlpos = strchr (buffer, '\n');
      if (nlpos != NULL) {
         *nlpos = '\0';
      }
      else { 
         fprintf (stderr, "%s: bad line\n", program_name);
         exit_status = EXIT_FAILURE;
         return exit_status;
      }
       
         node new = malloc (sizeof (struct node));
         assert (new != NULL);
         new->string = strdup (buffer);
         assert (new->string != NULL);
        
         node prev = NULL;
         node curr = head;
         //find location
         while (curr != NULL) {
            int compare = strcmp (curr->string, new->string);
            if (compare > 0) break;
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
   printlist (head, &opts);
   clearlist(head);
   return exit_status;

}






