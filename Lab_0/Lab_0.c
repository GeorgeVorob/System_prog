#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
		int childId;
        switch (childId = fork())
        {
        case -1:
                perror("Ошибка создания нового процесса: "); /* произошла ошибка */
                return 1;
        case 0:
        printf("Дочерний процесс: \n");
        if (execvp(argv[1], &argv[2]) == -1)
        {
                perror("Ошибка запуска программы в дочернем процессе: ");
                return 1;
        }
        break;
        default:
		wait(&childId);
        printf("Родительский процесс: \n");
        printf("Код завершения потомка: %d \n",WEXITSTATUS(childId));
                break;
        }
        return 0;
}