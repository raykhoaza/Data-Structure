//USER KHOA LUONG
//USERNAME KLUON7
#include <assert.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include "inssort.h"

int compare(const void *a, const void *b){
   const double *aa = a;
   const double *bb = b;
   if(*aa > *bb) return 1;
   if(*bb > *aa) return -1;
   return 0;
}
         
int main (int argc, char **argv) {
   (void) argc;
   (void) argv;
   char err_buffer [256];
   char err_buf_fmt[16];
   double array[1000];
   size_t count = 0;
   sprintf (err_buf_fmt, "%%%lds", sizeof err_buffer - 1);

   for (;;) {
      double number;
      int scancount = scanf ("%lg", &number);
      if (scancount == EOF) {
         break;
      }
      else if(sizeof(array)==1000){
         printf ("full array");
         break;
      }else if (scancount == 1) {
         array[count] = number;
         count++;
      }else {
         scancount = scanf (err_buf_fmt, err_buffer);
         assert (scancount == 1);
         break;
      };
   };
   inssort(array, count, sizeof(double), compare);
   for (size_t i = 0; i < count; i++){
      printf("%20.15g\n", array[i]);
   }
   return EXIT_SUCCESS;
}
