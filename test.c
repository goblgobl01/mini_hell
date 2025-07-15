#include <stdio.h>
#include <fcntl.h>

void main()
{
    int fd = open("\"./ file txt\"", O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if(fd < 0)
    {
        printf("hh");
    }
    printf("fd : %d\n", fd);
}