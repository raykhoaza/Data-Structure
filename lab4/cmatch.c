// Khoa Luong id: kluon7@ucsc.edu
#define _GNU_SOURCE
#include <unistd.h>
#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char *program_name = NULL;
int exit_status = EXIT_SUCCESS;
#define STDIN_NAME "-"

typedef struct options {
   bool ignore_case;
   bool filenames_only;
   bool number_lines;
} options;

void catbyline (FILE *input, char *filename, options *opts,
                char *pattern, int files) {
   char buffer[1024];
   printf ("FILE %s:\n", filename);
   for (int linenr = 1;; ++linenr) {
      char *buf = fgets (buffer, sizeof buffer, input);
      if (buf == NULL) break;
      if (opts->ignore_case){
         if(strcasestr(buf, pattern)){
            if(opts->filenames_only){
               printf("%s\n", filename); 
               break;
            }
            else if(opts->number_lines){
               printf("%d: %s\n", linenr, buf);
            }
            else if(opts->filenames_only && opts->number_lines){
               printf("%s line %d:\n", filename, linenr);
            }
            else if(opts->number_lines && files>1){
               printf("%s: %d: %s\n", filename, linenr, buf);
            }
            else if(files>1){
               printf("%s: %s\n", filename, buf);
            }
            else { printf("%s\n", buf); }
         }
      }
      else {
         if(strstr(buf, pattern)){
            if(opts->filenames_only){
               printf("%s\n", filename);
               break; 
            }
            else if(opts->number_lines){
               printf("%d: %s\n", linenr, buf);
            }
            else if(opts->filenames_only && opts->number_lines){
               printf("%s line %d:\n", filename, linenr);
            }
            else if(opts->number_lines && files>1){
               printf("%s: %d: %s\n", filename, linenr, buf);
            }
            else if(files>1){
               printf("%s: %s\n", filename, buf);
            }
            else { printf("%s\n", buf); }
         }
      }
   }
}

void scan_options (int argc, char **argv, options *opts) {
   opts->ignore_case = false;
   opts->filenames_only = false;
   opts->number_lines = false;
   opterr = false;
   for (;;) {
      int opt = getopt (argc, argv, "iln");
      if (opt == EOF) break;
      switch (opt) {
         case 'i':
            opts->ignore_case = true;
            break;
         case 'l':
            opts->filenames_only = true;
            break;
         case 'n':
            opts->number_lines = true;
            break;
         default:
            exit_status = EXIT_FAILURE;
            fflush (NULL);
            fprintf (stderr, "%s: -%c: invalid options\n",
                            program_name, optopt);
            break;
      }
   }
}

const char *strbool (bool value) {
   return value ? "true" : "false";
}

int main (int argc, char **argv) {
   options opts;
   program_name = basename (argv[0]);
   scan_options (argc, argv, &opts);
   char *pattern = argv[optind];
   int files = argc - optind - 1;
   if (argc == 1) {
      catbyline (stdin, STDIN_NAME, &opts, pattern, files);
   }else {
      for (int argi = optind + 1; argi < argc; ++argi) {
         char *filename = argv[argi];
         if (strcmp (filename, STDIN_NAME) == 0) {
            catbyline (stdin, STDIN_NAME, &opts, pattern, files);
         }else {
            FILE *input = fopen (filename, "r");
            if (input != NULL) {
               catbyline (input, filename, &opts, pattern, files);
               fclose (input);
            }else {
               exit_status = EXIT_FAILURE;
               fflush (NULL);
               fprintf (stderr, "%s: %s: %s\n", program_name,
                        filename, strerror (errno));
               fflush (NULL);
            }
         }
      }
   }
   return exit_status;
}

