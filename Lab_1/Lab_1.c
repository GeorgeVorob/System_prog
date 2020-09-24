#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/io.h>
#include <unistd.h>

void arrpush(int *arr, int index, int value, int *size, int *capacity) //Функция добавления элемента в массив с его расширения при необходимости(чтобы не прогонять текст 2 раза)
{
    if (*size > *capacity)
    { //Если массив заполнен, то перевыделяет память, увеличивая выделенный блок в 2 раза
        realloc(arr, sizeof(arr) * 2);
        *capacity = sizeof(arr) * 2;
    }
    arr[index] = value;
    *size = *size + 1;
}

int main(int argc, char *argv[])
{
    int arrSize = 0;
    int arrCap = 2;
    int *arr = malloc(arrCap * sizeof(int));

    char ch;
    int strCount = 0;
    int enterCount = 0;
    int strNumToPrint;
    off_t offsetToPrint;
    ssize_t ret;
    printf("Путь к файлу указывается как аргумент при запуске \nПопытка открыть файл %s \n", argv[1]);
    int filedesc = open(argv[1], 00);
    if (filedesc < 0)
    {
        perror("Ошибка открытия файла:");
        return 1;
    }
    while ((ret = read(filedesc, &ch, 1)) > 0) //Считывание файла, счёт кол-ва и длины строк
    {
        strCount++;
        if (ch == '\n')
        {
            arrpush(arr, enterCount++, strCount, &arrSize, &arrCap);
            printf("Строка %d , символов %d \n", enterCount, strCount);
            strCount = 0;
        }
    }
    if (ret == -1)
    {
        perror("Ошибка чтения файла: ");
        return 1;
    }
    printf("Всего строк: %d\n Введите номер требуемой для вывода строки(0 для выхода):", enterCount);
    scanf("%d", &strNumToPrint);

    if (strNumToPrint == 0)
    {
        printf("Завершение программы \n");
        return 0;
    }
    strNumToPrint--;

    for (int i = 0; i < strNumToPrint; i++) //Суммирование всех символов до указанной строки для нахождения начала указанной строки
    {
        offsetToPrint += arr[i];
    }
    //printf("Offset: %ld \n", offsetToPrint);

    lseek(filedesc, offsetToPrint, SEEK_SET); //Сдвиг дескриптора на нужное место

    for (int i = 0; i < arr[strNumToPrint]; i++)
    {
        ret = read(filedesc, &ch, 1);
        if (ret == -1)
        {
            perror("Ошибка чтения файла: ");
            return 1;
        }
        printf("%c", ch);
    }
    close(filedesc);
    return 0;
}