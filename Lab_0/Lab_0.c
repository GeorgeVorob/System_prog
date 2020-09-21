#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
int main(int argc, char *argv[])
{
  pid_t pid;
  int rv;
  int i;
  char *newargs[argc-1];
  switch(pid=fork()) {
  case -1:
          perror("fork"); /* произошла ошибка */
          exit(1); /*выход из родительского процесса*/
  case 0:
          printf("CHILD: Это процесс-потомок!\n");
          printf("CHILD: Мой PID -- %d\n", getpid());
          
          i=0;
          while(argv[i]!=NULL)
          {
                  printf("CHILD: Аргумент: %s \n",argv[i]);
                  i++;
          }
          for(i=2;i<=argc-1;i++)
          {
                  newargs[i]=argv[i];
          }
          execv(argv[1],argv);

  default: 
          printf("PARENT: Это процесс-родитель!\n");
          printf("PARENT: Мой PID -- %d\n", getpid());
          printf("PARENT: PID моего потомка %d\n",pid);
          printf("PARENT: Жду, пока потомок не вызовет exit()...\n");
          printf("PARENT: Код возврата потомка:%d\n", WEXITSTATUS(rv));
          printf("PARENT: Выход!\n");
          exit(0);
  }
  return 100;
}