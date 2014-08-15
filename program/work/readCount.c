/*
 * readCount.c
 *
 *  Created on: 2012-10-22
 *      Author: hongye
 */

#include "std.h"
#include "constValue.h"

#include "function.h"
/*函数功能：对每个染色体的mapping read进行计数
 * 参数：*fileName 01文件名 ；
 * totalArray[] 每个染色体总碱基的终止位置 对于第i条染色体，碱基范围为totalArray[i-1]+1 ~ totalArray[i];
 * mapArray[] 每条染色体上映射的read数量（01串中1的个数）
 *输出： FAILED --失败   SUCCESS  -- 成功
 *
 */
int readCount(char* fileName , uint32_t totalArray[], uint32_t mapArray[]) {


	FILE *fout;
	int i;
	uint32_t j, k;
	uint32_t upperLimit;
	uint32_t number;
	unsigned char bitSetTable[256] = { 0 };

	fout = fopen(fileName, "rb");

	for (i = 0; i < CHROMNUM; i++) {

		if(fread(&totalArray[i], sizeof(uint32_t), 1, fout) < 1){
			printf("in readCount.c , the file: %s fread() error!\n ", fileName);
			return FAILED;
		}
        /*
		printf("totalArray[%d] : %u\n", i, totalArray[i]);
		printf("mapArray[%d]: %u \n", i, mapArray[i]);
		*/
	}

	j = 0;
	if (bitSet(bitSetTable) == FAILED) {
		printf("in readCount.c ,bitSet() error!\n");
		return FAILED;
	}
	for (i = 0; i < CHROMNUM; i++) {
		upperLimit =  totalArray[i]/(sizeof(uint32_t) *8) * (sizeof(uint32_t)*8);
		printf("i: %d ; j: %u ; upperLimit : %u totalArray: %u \n", i, j , upperLimit, totalArray[i]);
		while (j < totalArray[i]) {
			if((fread(&number, sizeof(uint32_t), 1, fout) )!= 1){
				if(ferror(fout)){               //如果遇到文件结束，返回值为非0
					printf("in readCount.c , ferror() error ! \n");

				}else if(feof(fout)) {
			    printf("in readCount.c , the file: %s feof() error!\n ", fileName);
				}
				return FAILED;
			}
			/////////////////////
			if(j >= upperLimit){
				mapArray[i] += bitCount3_1( number>>( sizeof(uint32_t)*8 - totalArray[i] + upperLimit ), bitSetTable );
				if(i<CHROMNUM-1)
					mapArray[i+1] += bitCount3_1(number<<(totalArray[i] - upperLimit) , bitSetTable);
				/*
				printf("%u \n",number>>(sizeof(uint32_t)*8 - totalArray[i] + upperLimit));
				printf("%u \n",number<<(totalArray[i] - upperLimit));
				printf("%u \n",number);
				printf("right yi: %d , left yi: %d \n",(sizeof(uint32_t)*8 - totalArray[i] + upperLimit),(totalArray[i]-upperLimit));
				*/
			}
			else mapArray[i] += bitCount3_1(number,bitSetTable);
			/////////////////////
			j += sizeof(uint32_t)*8;
		}
	}
	printf("the number : %u \n", number);
	if(feof(fout) != 0){
		printf("in readCount.c , the file: %s feof() error!\n ", fileName);
		return FAILED;
	}

	if(fclose(fout) != 0){
		printf("in readCount.c , the file: %s fclose() error!\n ", fileName);
		return FAILED;
	}
/*
	for(i=0; i<CHROMNUM ; i++){
		printf("mapArray[%d] : %u\n", i, mapArray[i]);
	}
	*/
	return 0;

}



