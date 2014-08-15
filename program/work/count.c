/*
 * count.c
 *
 *  Created on: 2012-10-24
 *      Author: hongye
 */

#include "std.h"
#include "constValue.h"


/*

 int count1(char *fileName)
 {
 FILE *fout;
 uint32_t number;
 uint32_t i = 0;
 fout = fopen(fileName, "rb");

 while(fread(&number, sizeof(uint32_t), 1, fout) == 1){
 bitCount(number);
 i++;
 }
 if(feof(fout)!=0 && i == total){
 fclose(fout);
 return SUCCESS;
 } else{
 fclose(fout);
 return FAILED;
 }

 }
 */

/*
 * 普通法--- 慢
 */
uint32_t bitCount1(uint32_t number) {
	uint32_t c = 0;
	while (number > 0) {
		if ((number & 1) == 1)
			c++;
		number = number >> 1;
	}
	return c;
}

/*
 * 快速法
 */
uint32_t bitCount2(uint32_t n) {
	uint32_t c = 0;
	while (n != 0) {
		n = n & (n - 1);
		c++;
	}
	return c;
}
/*
 * 静态表——8bit
 */
int bitSet(unsigned char bitSetTable[])
{
	int i;
	for (i = 0; i < 256; i++) {
		bitSetTable[i] = (i & 1) + bitSetTable[i / 2];
	}
	if (i == 256)
		return SUCCESS;
	else
		return FAILED;
}
uint32_t bitCount3(uint32_t n, unsigned char bitSetTable[])
{
	uint32_t c;
	unsigned char *p = (unsigned char*) &n;
	c = (uint32_t) (bitSetTable[p[0]] + bitSetTable[p[1]] + bitSetTable[p[2]]
			+ bitSetTable[p[3]]);
	return c;
}

uint32_t bitCount3_1(uint32_t n, unsigned char bitSetTable[])
{
	uint32_t c;
	//unsigned char *p = (unsigned char*) &n;
	c = (uint32_t) (bitSetTable[n & 0xFF] + bitSetTable[(n >> 8) & 0xFF]
			+ bitSetTable[(n >> 16) & 0xFF] + bitSetTable[(n >> 24) & 0xFF]);
	return c;
}

/*
 * 平行算法---慢
 */
uint32_t bitCount4(uint32_t u) {
	u = (u & 0x55555555) + ((u >> 1) & 0x55555555);
	u = (u & 0x33333333) + ((u >> 2) & 0x33333333);
	u = (u & 0x0F0F0F0F) + ((u >> 4) & 0x0F0F0F0F);
	u = (u & 0x00FF00FF) + ((u >> 8) & 0x00FF00FF);
	u = (u & 0x0000FFFF) + ((u >> 16) & 0x0000FFFF);
	return u;
}
/*
 * 完美法
 */
uint32_t bitCount5(uint32_t n) {

	unsigned int tmp = n - ((n >> 1) & 033333333333)
			- ((n >> 2) & 011111111111);
	return ((tmp + (tmp >> 3)) & 030707070707) % 63;
}


/*
 * 测试移位操作
 */

int main2()
{
	unsigned char bitSetTable[256] = {0};
	uint32_t number;
	number = (uint32_t)3078395992;
	if (bitSet(bitSetTable) == FAILED) {
			printf("bitSet() error!\n");
			return FAILED;
		}
	printf("%d \n",bitCount3_1(number>>1,bitSetTable));
					printf("%d \n",bitCount3_1(number<<31,bitSetTable));
					printf("%d \n",bitCount3_1(number,bitSetTable));
					return 0;
}
/*
 * 测试本源文件中的函数的主程序
 */
int main1() {

// int main(){
	char *fileName = "test.txt";

	FILE *fout;
	uint32_t number;
	uint32_t total = 0;
	clock_t start, finish;
	unsigned char bitSetTable[256] = { 0 };
	int i;
/*
	//////////////////////----------------1
	printf("the bitCount1()\n");

	start = clock();
	fout = fopen(fileName, "rb");
	if (fout == NULL) {
		printf("open the file failed!\n");
		return FAILED;
	}
	while (fread(&number, sizeof(uint32_t), 1, fout) == 1) {
		total = total + bitCount1(number);
	}
	//printf("the total 1: %u \n", total);
	if (feof(fout) == 0) {
		printf("file not read to end!\n");
		return FAILED;
	}

	fclose(fout);
	finish = clock();

	printf("the total 1: %u \n", total);
	printf("the creatFile process using time:%f seconds\n", difftime(finish,
			start) / 1000);
	//////////////////////////

	//////////////////////------------------------2
	total = 0;
	printf("the bitCount2()\n");
	start = clock();
	fout = fopen(fileName, "rb");
	if (fout == NULL) {
		printf("open the file failed!\n");
		return FAILED;
	}
	while (fread(&number, sizeof(uint32_t), 1, fout) == 1) {
		total = total + bitCount2(number);
	}
	//printf("the total 2: %u \n", total);
	if (feof(fout) == 0) {
		printf("file not read to end!\n");
		return FAILED;
	}

	fclose(fout);
	finish = clock();

	printf("the total 2: %u \n", total);
	printf("the creatFile process using time:%f seconds\n", difftime(finish,
			start) / 1000);
	//////////////////////////

	//////////////////////------------------------3
	total = 0;
	printf("the bitCount3()\n");
	start = clock();
	if (bitSet(bitSetTable) == FAILED) {
		printf("bitSet() error!\n");
		return FAILED;
	}
	fout = fopen(fileName, "rb");
	if (fout == NULL) {
		printf("open the file failed!\n");
		return FAILED;
	}
	while (fread(&number, sizeof(uint32_t), 1, fout) == 1) {
		total = total + bitCount3(number, bitSetTable);
	}
	//printf("the total 3: %u \n", total);
	if (feof(fout) == 0) {
		printf("file not read to end!\n");
		return FAILED;
	}

	fclose(fout);
	finish = clock();

	printf("the total 3: %u \n", total);
	printf("the creatFile process using time:%f seconds\n", difftime(finish,
			start) / 1000);
	//////////////////////////

	 */
	//////////////////////------------------------3_1
	total = 0;
	printf("the bitCount3_1()\n");
	start = clock();
	if (bitSet(bitSetTable) == FAILED) {
		printf("bitSet() error!\n");
		return FAILED;
	}
	fout = fopen(fileName, "rb");
	if (fout == NULL) {
		printf("open the file failed!\n");
		return FAILED;
	}
	for(i=0; i<CHROMNUM; i++){
		if(fread(&number, sizeof(uint32_t), 1, fout) != 1){
			printf("preprocess error!");
			return FAILED;
		}

	}
	while (fread(&number, sizeof(uint32_t), 1, fout) == 1) {
		total = total + bitCount3_1(number, bitSetTable);
	}
	if (feof(fout) == 0) {
		printf("file not read to end!\n");
		return FAILED;
	}

	fclose(fout);
	finish = clock();

	printf("the total 1: %u \n", total);
	printf("the creatFile process using time:%f seconds\n", difftime(finish,
			start) / 1000);
	printf("the number: %u\n", number);
	//////////////////////////
	/*
	//////////////////////------------------------4
	total = 0;
	printf("the bitCount4()\n");
	start = clock();
	fout = fopen(fileName, "rb");
	if (fout == NULL) {
		printf("open the file failed!\n");
		return FAILED;
	}
	while (fread(&number, sizeof(uint32_t), 1, fout) == 1) {
		total = total + bitCount4(number);
	}
	if (feof(fout) == 0) {
		printf("file not read to end!\n");
		return FAILED;
	}

	fclose(fout);
	finish = clock();

	printf("the total 1: %u \n", total);
	printf("the creatFile process using time:%f seconds\n", difftime(finish,
			start) / 1000);
	//////////////////////////
	//////////////////////------------------------5
	total = 0;
	printf("the bitCount5()\n");
	start = clock();
	fout = fopen(fileName, "rb");
	if (fout == NULL) {
		printf("open the file failed!\n");
		return FAILED;
	}
	while (fread(&number, sizeof(uint32_t), 1, fout) == 1) {
		total = total + bitCount5(number);
	}
	if (feof(fout) == 0) {
		printf("file not read to end!\n");
		return FAILED;
	}

	fclose(fout);
	finish = clock();

	printf("the total 1: %u \n", total);
	printf("the creatFile process using time:%f seconds\n", difftime(finish,
			start) / 1000);
	//////////////////////////
	/*
	 //////////////////////------------------------6
	 printf("the bitCount6()\n");
	 start = clock();
	 fout = fopen(fileName, "rb");
	 if(fout == NULL){
	 printf("open the file failed!\n");
	 return FAILED;
	 }
	 while(fread(&number, sizeof(uint32_t), 1, fout) == 1)
	 {
	 total = total + _mm_popcnt_u32(number);
	 }
	 if(feof(fout) == 0){
	 printf("file not read to end!\n");
	 return FAILED;
	 }

	 fclose(fout);
	 finish = clock();

	 printf("the total 1: %u \n",total);
	 printf("the creatFile process using time:%f seconds\n", difftime(finish,
	 start)/1000);
	 //////////////////////////

	// */
	return 0;
}


