#include <stdio.h>
#include <sys/time.h>


int main(void)
{
    struct timeval  time;

    gettimeofday(&time, NULL);
    printf("%ld\n", time.tv_sec);
    return (0);
}