/*
 * main.c
 *
 *  Created on: 2012-10-22
 *      Author: hongye
 */
#include <stdio.h>
#include <stdlib.h>

void print ()
{
    int i;
    printf("i=%d\n",i);
    i=777;
}
int main()
{

    print();
    print();
    void print_time(int, int);
	print_time(23, 59);
	return 0;

}
