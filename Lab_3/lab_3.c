#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int main(int argc, char *argv[])
{
    DIR *d;
    struct dirent *dir;
    struct stat fileInfo;
    d = opendir(".");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if (stat(dir->d_name,&fileInfo) == -1)
            {
                perror("stat failue");
                return -1;
            }
            printf( (S_ISDIR(fileInfo.st_mode)) ? "d" : (S_ISREG(fileInfo.st_mode)) ? "-" : "?");
            printf(" ");
            printf( (fileInfo.st_mode & S_IRUSR) ? "r" : "-");
            printf( (fileInfo.st_mode & S_IWUSR) ? "w" : "-");
            printf( (fileInfo.st_mode & S_IXUSR) ? "x" : "-");
            printf(" ");
            printf( (fileInfo.st_mode & S_IRGRP) ? "r" : "-");
            printf( (fileInfo.st_mode & S_IWGRP) ? "w" : "-");
            printf( (fileInfo.st_mode & S_IXGRP) ? "x" : "-");
            printf(" ");
            printf( (fileInfo.st_mode & S_IROTH) ? "r" : "-");
            printf( (fileInfo.st_mode & S_IWOTH) ? "w" : "-");
            printf( (fileInfo.st_mode & S_IXOTH) ? "x" : "-");

            printf(" %s",getpwuid(fileInfo.st_uid)->pw_name);
            printf(" %s",getgrgid(fileInfo.st_gid)->gr_name);

            if(S_ISREG(fileInfo.st_mode)) printf(" %-9jd",fileInfo.st_size);
            else
            {
                printf("          ");
            }
            

            char* a = ctime(&fileInfo.st_mtim.tv_sec);
            strtok(a,"\n");
            printf(" %s",a);

            printf(" %s",dir->d_name);
            printf("\n\n");
        }
    }
    return 0;
}