#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
int main(int argc, char *argv[])
{
printf("Запускаемая программа\n");
printf("Аргументы:\n");
          int i=0;
          while(argv[i]!=NULL)
          {
                  printf("%s \n",argv[i]);
                  i++;
          }
          exit(0);
}