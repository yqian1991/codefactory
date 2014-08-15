#include <stdio.h>
#include <stdlib.h>

char *strcpy(char *dest, char *src)
{
    while( *dest++ = * src++)
    ;

    return dest;
}

char *itoa1(int a)
{
    char buf[43];
    sprintf(buf, "%d", a);
    return buf;

}
int main()
{
    char *src="qianyua";
    char *dest;
    strcpy(dest, src);
    printf("%s\n", dest);

    char *str;
    str=itoa1(12);
    printf("%s\n", str);
    return 0;
}
