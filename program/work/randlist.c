/*
 * randlist.c
 *
 *  Created on: 2012-10-22
 *      Author: hongye
 */

#include "std.h"
#include "constValue.h"

int creatFile(char *fileName, uint32_t refArray[]) {
	uint32_t number;
	int i;
	int pos;
	uint32_t upperLimit;
	uint32_t count;

	uint32_t totalArray[CHROMNUM];

	FILE *fin;
	fin = fopen(fileName, "wb");
	if (fin == NULL) {
		printf("in randlist.c , the file %s  fopen() failed!\n", fileName);
		return FAILED;
	}

	srand((unsigned) time(NULL));

	i = 0;
	while (i < CHROMNUM) {
		totalArray[i] = rand() % 100000000;
		printf("the %d chrom : %u \n", i, totalArray[i]);
		i++;

	}

	upperLimit = 0;
	for (i = 0; i < CHROMNUM; i++) {
		upperLimit += totalArray[i];
		printf("the %d chrom : %u \n", i, upperLimit);
		if (fwrite(&upperLimit, sizeof(uint32_t), 1, fin) < 1) {
			printf("in randlist.c , the file %s  fwrite() failed!\n", fileName);
			return FAILED;
		}
	}

	count = 0;
	upperLimit = totalArray[0];
	i = 0;

	while (1) {
		number = 0;
		for (pos = 0; pos < 32; pos++) {
			if (rand() % 2 == 0) {
				number = (number << 1) + 1; //位置靠前的碱基占高位

				if (count < upperLimit)
					refArray[i]++;
				else {
					i++;

					if (i >= CHROMNUM) {
						number = number >> 1;
						break;
					} else {
						refArray[i]++;
						upperLimit = upperLimit + totalArray[i];
					}

				}
			} else {
				number = (number << 1);
			}

			count++;

		}

		if (i >= CHROMNUM) {

			while (pos < 32){
				number = number << 1;
				pos++;
			}
			if (fwrite(&number, sizeof(uint32_t), 1, fin) < 1) {
				printf("in randlist.c , the file %s  fwrite() failed!\n",
						fileName);
				return FAILED;
			}
			printf("upperLimit: %u \n", upperLimit);
			break;

		}
		if ( fwrite(&number, sizeof(uint32_t), 1, fin) < 1) {
			printf("in randlist.c , the file %s  fwrite() failed!\n", fileName);
			return FAILED;
		}

	}

	printf("the number : %u \n", number);
	/*
	 for (i = 0; i < CHROMNUM; i++) {
	 printf("refArray[%d] : %u\n", i, refArray[i]);
	 printf(" percent: %d\n", refArray[i] * 100 / totalArray[i]);
	 }
	 */
	if (fclose(fin) != 0) {
		printf("in randlist.c , the file %s  fclose() failed!\n", fileName);
		return FAILED;
	}
	return SUCCESS;

}

