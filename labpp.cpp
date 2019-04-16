#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<math.h>
#include <stdbool.h>
#include<fstream>
#include<vector>
#include<algorithm>
#include<iomanip>

using namespace std;

#define ERROR -1
#define NUMBER_OF_BLOCKS(memorySize, blockSize)(memorySize/blockSize)


class TrackBlock
{
	int cacheBlockNum;
	int bb;
	vector<TrackBlock>TrackBlockVector;
	public:
	void set(int cache, int bNum)
	{
		cacheBlockNum=cache;
		bb=bNum;
	}
	int getCacheBlockNum()
	{
		return cacheBlockNum;
	}
	int getBlockNum()
	{
		return bb;
	}
	int empty()
	{
		if(TrackBlockVector.empty())
			return 1;
		else
			return 0;
	}
	int found(int blockNum)
	{
		//cout<<"In found "<<blockNum<<endl;
		//cout<<"Size "<<TrackBlockVector.size()<<endl;
		if(!empty())
		{
			for(int i=0;i<TrackBlockVector.size();i++)
			{
				//cout<<"Blck to compare "<<TrackBlockVector[i].getCacheBlockNum()<<endl;
				if(TrackBlockVector[i].getBlockNum()==blockNum)
				{
					//cout<< "Inside found"<<i<<endl;
					return i;
				}
			}
		}
		return -1;
	}
	int getBlockNum(int b,int cSet, int degree, char p, int *replaced)
	{
		int none=empty();
		int exist;
		int allocNum;
		string stat;
		*replaced=0;
		//printf("%d\n", none);
		TrackBlock add;
		if(none)
		{
			this->cacheBlockNum=cSet*degree+0;
			add.set(this->cacheBlockNum, b);
			TrackBlockVector.push_back(add);
			stat="MISS";
			allocNum=this->cacheBlockNum;
			return allocNum;
		}
		exist=found(b);
		//cout<<"Exist "<<exist<<endl;
		if(exist!=-1)
		{
			stat="HIT";
			if(TrackBlockVector.size()<=degree)
			{
				this->cacheBlockNum=TrackBlockVector[0].getCacheBlockNum();
				//cout<<"Here "<<" "<<this->cacheBlockNum;
				if(p=='L')
					updateTracker(exist);
			}
			/*else
			{
				this->cacheBlockNum=TrackBlockVector[0].getCacheBlockNum();
				TrackBlockVector.erase(TrackBlockVector.begin()+0);
				add.set(this->cacheBlockNum, bb);
				stat="MISS";
			}*/
			allocNum=this->cacheBlockNum;
		}
		else
		{
			/*if(p=='L')
				updateTracker(exist);
			this->cacheBlockNum=TrackBlockVector[exist].getCacheBlockNum();
			allocNum=this->cacheBlockNum;*/
				
			 if(TrackBlockVector.size()<degree)
			{
				this->cacheBlockNum=(cSet*degree)+TrackBlockVector.size();
				add.set(this->cacheBlockNum, b);
				TrackBlockVector.push_back(add);
				
			}
			else
			{
				//cout<<"Here";
				this->cacheBlockNum=TrackBlockVector[0].getCacheBlockNum();
				TrackBlockVector.erase(TrackBlockVector.begin()+0);
				add.set(this->cacheBlockNum, b);
				TrackBlockVector.push_back(add);
				*replaced=1;
				
			}
		}
		allocNum=this->cacheBlockNum;
		return allocNum;
	}
	void updateTracker(int exist)
	{
		TrackBlock add=TrackBlockVector[exist];
		TrackBlockVector.erase(TrackBlockVector.begin()+exist);
		TrackBlockVector.push_back(add);
	}
	void get()
	{
		cout<<bb<<" "<<cacheBlockNum<<endl;
	}
	void getVectorDetails()
	{
		for(int i=0;i<TrackBlockVector.size();i++)
		{
			cout << "Vector"<<i<<" ";
			TrackBlockVector[i].get();
		}
	}
	
};

//int totalNumOfMemRef;
string tagInString(int tagBits, string tag)
{
	string add="";
	if(tag.length()<tagBits)
	{
		int diff=tagBits-tag.length();
		for(int i=0;i<diff;i++)
		{
			add=add+"0";
		}
		add=add+tag;
	}
	else
		add=tag;
	//printf("Tag %s\n", add.c_str());
	return add;
}

int convert(int dec)
{
    if (dec == 0)
    {
        return 0;
    }
    else
    {
        return (dec % 2 + 10 * convert(dec / 2));
    }
}

class MemoryReferenceTable
{
	char operation;
	int memoryRef;
	int MMBlockNum;
	int cacheSetNum;
	int tagNum;
	string cacheBlockNum;
	string status=" ";
	public:
	void setTageNum(int blockSize, int cacheSets)
	{
		tagNum=memoryRef/(blockSize*cacheSets);
	}
	void set(char op,int ref, int mmNum, int cacheSet, string cacheBlock,  string stat)
	{
		operation=op;
		memoryRef=ref;
		MMBlockNum=mmNum;
		cacheSetNum=cacheSet;
		cacheBlockNum=cacheBlock;
		status=stat;
	}
	void setStatus(string stat)
	{
		status=stat;
	}
	
	void setOperation(char op)
	{
		operation=op;
	}
	
	void setMemoryRef(int ref)
	{
		memoryRef=ref;
	}
	
	char getOperation()
	{
		return operation;
	}
	int getBlockNum()
	{
		return MMBlockNum;
	}
	int getCacheSetNum()
	{
		return  cacheSetNum;
	}
	int getTagNum()
	{
		return tagNum;
	}
	int getmemoryRef()
	{
		return memoryRef;
	}
	string getStatus()
	{
		return status;
	}
	void get()
	{
		cout<<operation<<" "<<memoryRef<<" "<<MMBlockNum<<" "<<cacheSetNum<<" "<<tagNum<<" "<<cacheBlockNum<<" "<<status<<endl;
	}
	void update(int blocksize, int totalCacheSets, int degree)
	{
		MMBlockNum=NUMBER_OF_BLOCKS(memoryRef,blocksize);
		cacheSetNum=MMBlockNum%totalCacheSets;
		if(degree==1)
			cacheBlockNum=to_string(cacheSetNum);
		else
		{
			int minBlockNum=cacheSetNum*degree;
			int maxBlockNum=minBlockNum+degree-1;
			cacheBlockNum=to_string(minBlockNum)+"-"+ to_string(maxBlockNum);
		}
	}
	void updateStatus(string stat)
	{
		status=stat;
	}
	void printMemoryReferenceTableContent()
	{
		cout << left << setw(25) << setfill(' ') <<memoryRef;
		cout << left << setw(25) << setfill(' ') << MMBlockNum;
		cout << left << setw(25) << setfill(' ') << cacheSetNum;
		cout << left << setw(25) << setfill(' ') << cacheBlockNum;
		cout << left << setw(25) << setfill(' ') << status;
		cout<<endl;
		//cout<<left<<setw(130)<<setfill('_')<<" ";
		//cout<<endl;
	}
};


class CacheStatus
{   
	int numCacheBlock;
	char dirtyBit;
	int validBit;
    string tagNumber;
    string data;
	public:
	CacheStatus(string tag, int index)
	{
		numCacheBlock=index;
		dirtyBit='X';
		validBit=0;
		tagNumber=tag;
		data="X";	
	}
	void getStatus()
	{
		cout<<numCacheBlock<<" "<<dirtyBit<<" "<<validBit<<" "<<tagNumber<<" "<< " "<<data<<endl;
	}
	void setTagNumber(string tag)
	{
		tagNumber=tag;
	}
	
	void setDirtyBit(char op)
	{
		if(op=='W')
			dirtyBit='1';
		if(op=='R')
			dirtyBit='0';
	}
	
	void update(char dirty, int valid, string tag, int mBlock, int replaced)
	{
		if(replaced)
			setDirtyBit(dirty);
		else
		{
			if(dirtyBit!='1')
				setDirtyBit(dirty);
		}
		validBit=valid;
		tagNumber=tag;
		data="Main Memory Block #"+to_string(mBlock);
	}
	
	void printCacheContent()
	{
		cout << left << setw(25) << setfill(' ') <<numCacheBlock;
		cout << left << setw(25) << setfill(' ') << dirtyBit;
		cout << left << setw(25) << setfill(' ') << validBit;
		cout << left << setw(25) << setfill(' ') << tagNumber;
		cout << left << setw(25) << setfill(' ') << data;
		cout<<endl;
		//cout<<left<<setw(130)<<setfill('_')<<" ";
		//cout<<endl;
	}

};



int numberOfBits(int n) 
{  
	int bits=ERROR;
	if(ceil(log2(n)) == floor(log2(n)))
	   bits=ceil(log2(n));
	return bits;
} 

int calCacheSize(int size, int block, int tagBits)
{
	int memory;
	memory= 2*(block/8) + ((tagBits*block)/8) + size *block;
	return memory;
}
void checkCharacters(int *error, char *token)
{
	int len=strlen(token);
	printf("%s", token);
	printf("Here\n");
	int i=0;
	while(len)
	{
		if(token[i]>=48 && token[i]==57)
		{
			*error=0;
		}
		else
		{
			 *error=ERROR;
			 break;
		}
		len--;
		i++;
	}
}

MemoryReferenceTable * validateFile(int  *totalNumOfMemRef, int range)
{   
	MemoryReferenceTable *mref;
    int error=ERROR;
	int ok=0;
	int numEntry, time=0, i=0;
    char filename[100];
	ifstream fp;
	char line[100];
	char *token;
	char op;
	do
	{
		printf("Enter the file name :");
        scanf("%s", filename);
		//printf("%s", filename);
		if(strlen(filename)==1 && (strcmp(filename,"q")==0))
			exit(0);
		fp.open(filename);
		if(!fp)
		{
			error=ERROR;
			printf("Error>>>> Cannot open file.\n");
		}
		else
		{    
			error=0;
			//parseFile(&fp);
			while (fp.getline(line,50))
			{  
				time++;
				if(time==2)
					continue;
				//printf("%s\n", line);
				if(time==1)
				{
					*totalNumOfMemRef=atoi(line);
					if(*totalNumOfMemRef>0)
					{
						//printf("NUM =%d \n", totalNumOfMemRef);
						mref = new MemoryReferenceTable[*totalNumOfMemRef] ;
					}
					else
					{
						error=ERROR;
						printf("Error>>>> File does not contain valid number for total entries \n");
						break;
					}
				}
				else
				{
					token=strtok(line, " ");
					//printf("Token %s\n", token);
					if(strlen(token)==1 && strcmp(token,"R")==0 || strcmp(token,"W")==0)
					{
						char op=token[0];
						//printf("Char %c\n", op);
						mref[i].setOperation(op);
					}
					else
					{
						printf("Error>>>> In file does not contain valid opaeration R/W\n");
						error=ERROR;
						break;
					}
					while(token!=NULL)
					{ 	
						token=strtok(NULL," ");
						if(token==NULL)
							break;
						//printf("%s\n", token);
						//checkCharacters(&error,token);
						//printf("%d", strlen(token));
						if(token[0]=='0' && strlen(token)==2)
							ok=1;
						int n=atoi(token);
						if((n>0 || ok==1) && n<range)
						{
							mref[i].setMemoryRef(n);
							ok=0;
						}
					    else
						{
							error=ERROR;
							printf("Error>>>> In file memory references are invalid values\n");
						}
					}
					i++;
					if(error==ERROR)
						break;
				}
				//time++;
			}
				//fputs (str, stdout);
		}
				fp.close();
    }while(error==ERROR);
	return mref;
}

void validate(int *input, int min, int max, int *numBits, string str, int range)
{
	int error=ERROR; 
	char *ch;
	do
	{
		printf("Enter the  %s : ", str.c_str());
		scanf("%s",ch);
		if(strlen(ch)==1 and (strcmp(ch,"q")==0))
			exit(0);
		*input=atoi(ch);
		if(*input>=min && *input<=max && *input<=range)
		{
			*numBits=numberOfBits(*input);
			if(*numBits!=ERROR)
				error=0;
			else
				printf("Error>>>> input should be in power of 2.\n");
		}
		else
		{
			printf("Error>>>>  Out of range exception. Enter number between %d-%d. Also MM <= CM<= BlockSize.\n ", min, max);
			error=ERROR;
		}
	}while(error==ERROR);
}


void validate(char *policy)
{
	char input[20];
	int error=ERROR;
	do
	{
		printf("Enter replacement policy(Least recently Used[LRU=L], First In First Out[FIFO=F]) : ");
		fflush(NULL);
		scanf("%s",input);
		if(strlen(input)==1 and (strcmp(input,"q")==0))
			exit(0);
		if(strlen(input)==1 && (strcmp(input,"L")==0) || (strcmp(input,"F")==0))
		{
			error=0;
			*policy=input[0];
		}
		else
		{
			cout<<"Enter valid character (L/F)"<<endl;
		}
		
	}while(error==ERROR);	
}
void validateAssociativeDegree(int *degree, int range)
{
	int error=ERROR;
	char input[20];
	int deg;
	do
	{
		printf("Enter degree of set-associativity(input n for an n-way set-associative mapping) : ");
		scanf("%s",input);
		if(strlen(input)==1 and (strcmp(input,"q")==0))
			exit(0);
		deg=atoi(input);
		if(deg>0 && deg<=range)
		{
			if(numberOfBits(deg)!=ERROR)
			{
				error=0;
		   		*degree=deg;
			}
			else
			{
				error=ERROR;
				cout<<"Error>>>> Associativity not in power in 2."<<endl;
			}
			
		}
		else
		{
			cout<<"Error>>>> Associativity range error. It must be in range of [1-numberofCacheBlocks] i.e. [1-"<<range<<"]."<<endl;
			error=ERROR;
		}
	}while(error==ERROR);
}

char *initializeTag(int tagBits)
{
	char *s;
	int i;
	s=(char *)malloc((tagBits)*sizeof(char));
	for(i=0;i<tagBits;i++)
	{
		s[i]='X';
	}
	s[i]='\0';
	return s;
}

void printMemoryReferenceTableHeader()
{
	cout << left << setw(25) << setfill(' ') << "Main Meory Address";
	cout << left << setw(25) << setfill(' ') << "MM Block #";
	cout << left << setw(25) << setfill(' ') << "CM Set #";
	cout << left << setw(25) << setfill(' ') << "CM Block #";
	cout << left << setw(25) << setfill(' ') << "HIT/MISS";
	cout<<endl;
	cout<<left<<setw(130)<<setfill('_')<<" ";
	cout<<endl;
}

void printCacheStatusHeader()
{
	cout << left << setw(25) << setfill(' ') << "Cache Block #";
	cout << left << setw(25) << setfill(' ') << "Dirty Bit";
	cout << left << setw(25) << setfill(' ') << "Valid Bit";
	cout << left << setw(25) << setfill(' ') << "Tag";
	cout << left << setw(25) << setfill(' ') << "Data";
	cout<<endl;
	cout<<left<<setw(130)<<setfill('_')<<" ";
	cout<<endl;
}
string computeMissOrHit(int found)
{
	string stat;
	if(found!=-1)
		stat="HIT";
	else
		stat="MISS";
	return stat;
}
int computeNumberOfRepeats(MemoryReferenceTable *mref, int len)
{
	int count=0;
	int blocks[len];
	for(int i=0;i<len;i++)
	{
		blocks[i]=mref[i].getBlockNum();
	}
	for (int i = 0; i < len; i++)            
	{
		for (int j = i+1; j < len; j++)           
		{
			if (blocks[j] > blocks[i])            
			{
				int tmp = blocks[i];         
				blocks[i] = blocks[j];            
				blocks[j] = tmp;            
			}  
		}
	}
	/*for(int i=0;i<len;i++)
	{
		cout<<blocks[i]<<" ";
	}
	cout<<endl;*/
	int a=0;
	while(len)
	{
		if(blocks[a]==blocks[a+1])
			count++;
		a++;
		len--;
	}
	return count;
}
int computeNumberOfHits(MemoryReferenceTable *mref, int len)
{
	int count=0;
	for(int i=0;i<len;i++)
	{
		if(mref[i].getStatus()=="HIT")
			count++;
	}
	return count;
}

int main(int argc, char *argv[] )
{
	int sizeMM, sizeCM, sizeBlock, setDegree, numOffBits, numCacheBits, numAddrLines, numMMBlocks, numCMBlocks, numIndexBits, numTagBits, totalCacheSize, totalNumOfMemRef, 
	numTotalCacheSets, countRepeats,countHits,isReplaced;
	char replacementPolicy;
	string filename;
	MemoryReferenceTable *mref;
	TrackBlock *bref;
	string tag;
	char ch;
	CacheStatus **cref;
	//bin=convert(8);
	do
	{
		printf("Press 'q' at any time to quit at any input prompt \n");
		//calling all validation functions and validating inputs
		validate(&sizeMM,4,32768, &numAddrLines,"size of main memory in bytes", 32768);
		validate(&sizeCM,2,32768,&numCacheBits,"size of the cache in bytes",sizeMM);
		validate(&sizeBlock,2,32768,&numOffBits,"cache block/lines size",sizeCM);
		numCMBlocks=NUMBER_OF_BLOCKS(sizeCM,sizeBlock);
		validateAssociativeDegree(&setDegree,numCMBlocks);	
		validate(&replacementPolicy);
		
		mref=validateFile(&totalNumOfMemRef, sizeMM);
		
		numMMBlocks=NUMBER_OF_BLOCKS(sizeMM,sizeBlock);
		numTotalCacheSets=numCMBlocks/setDegree;
		numIndexBits=numberOfBits(numCMBlocks/setDegree);
		numTagBits=numAddrLines-(numOffBits+numIndexBits);
		totalCacheSize=calCacheSize(sizeBlock,numCMBlocks, numTagBits);
		bref=new TrackBlock[numTotalCacheSets];
		for(int i=0;i<totalNumOfMemRef;i++)
		{
			mref[i].update(sizeBlock,numTotalCacheSets,setDegree);
			mref[i].setTageNum(sizeBlock,numTotalCacheSets);
		}
		//printf("%d %d %d %d %d %d %d\n", numAddrLines, numOffBits, numMMBlocks, numTotalCacheSets,numIndexBits,numTagBits, totalCacheSize);
		tag=initializeTag(numTagBits);
		cout<<"Simulator output :"<<endl;
		cout<<"Total number of address lines required = "<<numAddrLines<<endl;
		cout<<"Number of bits for offset = "<<numOffBits<<endl;
		cout<<"Number of bits for index = "<<numIndexBits<<endl;
		cout<<"Number of bits for tag = "<<numTagBits<<endl;
		cout<<"Total cache size required = "<<totalCacheSize<<"bytes"<<endl<<endl;
		//printf("%s\n", tag.c_str());
		cref=new CacheStatus*[numCMBlocks];
		for(int i=0;i<numCMBlocks;i++)
		{
			cref[i]=new CacheStatus(tag,i);
		}
		/*for(int i=0;i<numCMBlocks;i++)
		{
			cref[i]->getStatus();	
		}*/
		for(int i=0;i<totalNumOfMemRef;i++)
		{
			int blockNum=mref[i].getBlockNum();
			//cout<<"Block num"<<blockNum<<endl;
			int cacheSetNum=mref[i].getCacheSetNum();
			int tagNumBinary=convert(mref[i].getTagNum());
			int memoryRef=mref[i].getmemoryRef();
			char op=mref[i].getOperation();
			string tag=to_string(tagNumBinary);
			tag=tagInString(numTagBits,tag);
			int exist=bref[cacheSetNum].found(blockNum);
			string stat=computeMissOrHit(exist);
			mref[i].updateStatus(stat);
			int cacheBlockNumber=bref[cacheSetNum].getBlockNum(blockNum,cacheSetNum,setDegree,replacementPolicy,&isReplaced);
			//cout<<"Replaced :"<<isReplaced<<endl;
			//cout<<"Cblock"<<cacheBlockNumber<<endl;
			cref[cacheBlockNumber]->update(op,1,tag,blockNum,isReplaced);
		}
		printMemoryReferenceTableHeader();
		for(int i=0;i<totalNumOfMemRef;i++)
			mref[i].printMemoryReferenceTableContent();
		cout<<endl;
		countRepeats=computeNumberOfRepeats(mref,totalNumOfMemRef);
		float percentage =((float)(countRepeats*100))/totalNumOfMemRef;
		cout<<fixed<<setprecision(2)<<"Highest Possible Hit Rate= "<<countRepeats<<"/"<<totalNumOfMemRef<<" = "<<percentage<<"%"<<endl;
		cout<<endl;
		countHits=computeNumberOfHits(mref,totalNumOfMemRef);
		percentage =((float)(countHits*100))/totalNumOfMemRef;
		cout<<fixed<<setprecision(2)<<"Actual Hit Rate= "<<countHits<<"/"<<totalNumOfMemRef<<" = "<<percentage<<"%"<<endl;
		cout<<endl;
		printCacheStatusHeader();
		for(int i=0;i<numCMBlocks;i++)
			cref[i]->printCacheContent();
		cout<<"Continue? (y=yes, n=no) :";
		cin>>ch;
	} while (ch!='n');
	
}