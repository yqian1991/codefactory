/*
 * function.h
 *
 *  Created on: 2012-10-22
 *      Author: hongye
 */

#ifndef FUNCTION_H_
#define FUNCTION_H_

int creatFile();
int readCount(char* fileName , uint32_t totalArray[], uint32_t mapArray[]) ;
uint32_t popCount(uint32_t u);
int bitSet(unsigned char bitSetTable[]) ;
uint32_t bitCount3_1(uint32_t n, unsigned char bitSetTable[]);

#endif /* FUNCTION_H_ */
