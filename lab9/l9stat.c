//USER KHOA LUONG
//USERNAME KLUON7
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <assert.h>

char *progname = NULL;
int exit_status = EXIT_SUCCESS;

void l9stat(char *filename) {
   struct stat buffer;
   int status = lstat(filename, &buffer);
   if (status != 0) {
      printf("stat fail\n");
      fflush (NULL);
      fprintf (stderr, "%s: %s: %s\n", progname,
               filename, strerror (errno));
      fflush (NULL);
      exit_status = EXIT_FAILURE;
   } else {
      printf("stat success\n");
      int size = (int)buffer.st_size;
      int mode = (int)buffer.st_mode;
      
      printf("%06o\t%d ", mode, size);
      
      struct tm *tm = localtime(&buffer.st_mtime);
      time_t currtime;
      time(&currtime);
      double diff = difftime(buffer.st_mtime, currtime);
      char *format = NULL;
      if (diff < 0) diff = -diff;
      if (diff > 15552000) {
         format = "%b %d %y";
      } else {
         format = "%b %d %X";
      }
      char tbuffer[1024];
      strftime(tbuffer, sizeof(tbuffer), format, tm);
      printf("%s %s", tbuffer, filename);
      
      char *name = NULL;
      name = malloc(buffer.st_size + 1);
      assert(name != NULL);
      int flag = readlink(filename, name, buffer.st_size + 1);

      if (flag != -1) {
         name[buffer.st_size] = '\0';
         printf(" --> %s", name);
      }
      printf("\n");
      free(name);
   }
}

int main(int argc, char **argv) {

   exit_status = EXIT_SUCCESS;
   progname = basename (argv[0]);

   if (argc == 1) {
      l9stat(".");
   } else {
      for (int i = 1; i < argc; i++) {
         char *filename = argv[i];
         l9stat(filename);
      }
   }   
}


