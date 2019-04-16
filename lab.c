#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <stdbool.h>

#define ERROR -1
#define NUMBER_OF_BLOCKS(memorySize, blockSize)(memorySize/blockSize)

struct CacheStatus
{
	int numBlock;
	int dirtyBit;
	int validBit;
	char *tag;
	char *data;
};


struct MemoryReferncesStatus
{
	int mainMemoryAddress;
	int numMMBlock;
	int numCMSet;
	int numCMBlock;
	bool HitOrMissStatus;
};


int numberOfBits(int n) 
{  int bits=ERROR;
   if(ceil(log2(n)) == floor(log2(n)))
	   bits=ceil(log2(n));
   return bits;
} 

int calCacheSize(int size, int block, int tagBits)
{
	int memory;
	memory= (block/8) + ((tagBits*block)/8) + size *block;
	return memory;
}

void validate(int *input, int min, int max, int *numBits, char *str)
{
	int error=ERROR; char ch;
	do
	{
		printf("Enter the size of %s in bytes: ", str);
		scanf("%d",input);
		if(*input>=min && *input<=max)
		{
			*numBits=numberOfBits(*input);
			if(*numBits!=ERROR)
				error=0;
			else
				printf("Error>>>> input should be in power of 2.\n");
		}
		else
		{
			printf("Error>>>>  enter number bewteen %d-%d.\n", min, max);
			error=ERROR;
		}
	}while(error==ERROR);
}
int main()
{
	int sizeMM, sizeCM, sizeBlock, setDegree, numOffBits, numAddrLines, numMMBlocks, numCMBlocks, numIndexBits, numTagBits, totalCacheSize;
	validate(&sizeMM,4,32768, &numAddrLines,"main memory");
	
	validate(&sizeBlock,2,32768, &numOffBits,"cache block/line");
	//validate(&sizeCM, 2, 32768, &e)
	printf("Enter the size of cache in bytes : ");
	scanf("%d",&sizeCM);
	
	printf("Enter the degree of set-associativity(input n for n-way set-associative mapping) : ");
	scanf("%d",&setDegree);
	numOffBits=numberOfBits(sizeBlock);
	 numMMBlocks=NUMBER_OF_BLOCKS(sizeMM,sizeBlock);
	numCMBlocks=NUMBER_OF_BLOCKS(sizeCM,sizeBlock);
	numIndexBits=numberOfBits(numCMBlocks/setDegree);
	numTagBits=numAddrLines-(numOffBits+numIndexBits);
	totalCacheSize=calCacheSize(sizeBlock,numCMBlocks, numTagBits);
	printf("%d %d %d %d %d %d\n", numAddrLines, numOffBits, numMMBlocks, numIndexBits,numTagBits, totalCacheSize);
	return 0;
}

