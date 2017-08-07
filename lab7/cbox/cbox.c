// $Id: cbox.c,v 1.1 2014-02-13 18:38:23-08 - - $

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cbox.h"

struct cbox {
   int value;
};

cbox *new_cbox (void) {
   return new_int_cbox (0);
}

cbox *new_int_cbox (int value) {
   cbox *this = malloc (sizeof (struct cbox));
   assert (this != NULL);
   this->value = value;
   return this;
}

void free_cbox (cbox *this) {
   free (this);
}

int get_cbox (cbox *this) {
   return this->value;
}

void put_cbox (cbox *this, int newvalue) {
   this->value = newvalue;
}

// 
// Notes that would normally not be put in the file:
// 
// A '.c' file always includes its own header.
// 
// The 'struct' definition itself is specified in the
// implementation file.  Everything declared in the implementation
// file is 'private'.  Never put field definitions in a header
// file.
// 

