//USER KHOA LUONG
//USERNAME KLUON7`
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void inssort (void* base, size_t nelem, size_t size,
int (*compar) (const void*, const void*)){
   void* copy = (void*)malloc(size);
   for(size_t sorted = 1; sorted < nelem; sorted++) {
      size_t slot = sorted;
      memcpy(copy, base + sorted * size, size);
      for(; slot > 0; --slot) {
         int cmp = compar(copy, base + (slot - 1)*size);
         if (cmp > 0)break;
         memcpy(base + slot * size, base + (slot - 1)*size, size);
      }
      memcpy(base + slot * size, copy, size);
   }
   free(copy);
}
