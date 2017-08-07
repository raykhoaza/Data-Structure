//USER KHOA LUONG
//USERNAME KLUON7
#include <assert.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inssort.h"

int compare(const void *a, const void *b){
   const char *aa = *(char **)a;
   const char *bb = *(char **)b;
   return strcmp(aa,bb);
}
         
int main (int argc, char **argv) {
   (void) argc;
   (void) argv;
   char err_buffer [256];
   char err_buf_fmt[16];
   char buffer[1000];
   char *array[1000];
   size_t count = 0;
   sprintf (err_buf_fmt, "%%%lds", sizeof err_buffer - 1);
   for (int linenr = 0 ;; linenr++) {
      char *gotline = fgets(buffer, sizeof buffer, stdin);
      if (gotline == NULL) break;
      char *nlpos = strchr (buffer, '\n');
      if(nlpos != NULL){
         *nlpos = '\0';
      }
      char *temp = strdup(gotline);
      array[linenr] = temp;
      count++;
   }
   inssort(array, count, sizeof(char *), compare);
   for (size_t i = 0; i < count; i++){
      printf("%s\n", array[i]);
   }
   
   return EXIT_SUCCESS;
}
