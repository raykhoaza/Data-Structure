// $Id: main.c,v 1.12 2014-02-27 17:46:38-08 - - $

//
// Silly main program which just creates an cbox box, puts a
// number in it, gets it back out, and deletes the box.
// Run with bcheck to verify no memory leaks.
//

#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cbox.h"

char *execname = NULL;

int main (int argc, char **argv) {
   (void) argc; // warning: unused parameter 'argc'
   execname = basename (argv[0]);

   // Declare the box and initialize it.
   cbox *box = new_cbox();
   printf ("box = %p\n", box);

   // Perform a couple of operations on it.
   put_cbox (box, 1024);
   printf ("box value is %d\n", get_cbox (box));

   // Free up the box.
   free_cbox (box);

   return EXIT_SUCCESS;
}

