//KHOA LUONG KLUON7@UCSC.EDU
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

extern char **environ;
int main (int argc, char **argv){
   for (int i=0;environ[1]!=NULL;i++){
      printf("%s\n",environ[i]);
   }
}
