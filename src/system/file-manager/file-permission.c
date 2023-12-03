#include <stdio.h>
#include <sys/stat.h>

int main()
{
    int ret = 0;

    ret = chmod("../../temp/file", 0755);
    if(ret<0)
    {
        printf("Faol to chmod()\n");
    }

    return 1;
}