#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<string.h>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;

class ABC
{
	char op;
	int addr;
	int mm=50;
	int block;
public:
	ABC()
	{
		op='T';
		addr=123;
	}
    void setOp(char p)
	{
		op=p;
	}
	void setAddr(int a)
	{
		addr=a;
	}
     void get()
	{
		printf("Op %c: ",op);
		printf("Addr %d: ",addr);
	}
	int getMM()
	{
		return mm;
	}
};




class D
{
	int cache;
	int block;
	vector<ABC>cacheVector;
	vector<int>stat;
	string st;
	public:
	void setCache(ABC a, int numberOfSets)
	{
		cache=a.getMM()%numberOfSets;
	}
	void updateSet(int numberOfSets, ABC a )
	{
		int mm=a.getMM();
		bool found;
		stat.push_back(0);
		stat.push_back(50);
		stat.push_back(100);
		
		for(int i=0;i<stat.size();i++)
		{
			printf("stat :%d ", stat[i]);
		}
		vector<int>::iterator it = find(stat.begin(), stat.end(), mm);
		if(it!= stat.end())
		{
			st="HIT";
			found=1;
		}
		else
		{
			stat.push_back((mm));
			st="MISS";
			found=0;
		}
		if(found)
		{
			stat.erase(it);
			stat.push_back(mm);
		}
		if(found==0)
		{	
			if(cacheVector.size()<numberOfSets)
			{
				cacheVector.push_back(a);
				block=cache*0+cacheVector.size()-1;
			}
			else
			{
				stat.erase(stat.begin());
			}
		}
	}
	
	void get()
	{
		printf("cache :%d ", cache);
		printf("block :%d ", block);
		for(int i=0;i<cacheVector.size();i++)
		{
			cacheVector.at(i).get();
		}
		printf(" %s\n",st.c_str());
		printf("Block %d\n:",block);
		for(int i=0;i<stat.size();i++)
		{
			printf("stat :%d ", stat[i]);
		}
	}
};

int main()
{
	int time=0, i=0;
	int num;
	char filename[100];
	char line[50];
	int mm=128,cm=32,bm=4,degree=2;
	ABC *ob;
	D *o;
	char *token;
	ifstream fp;
	scanf("%s",filename);
	printf("%s\n",filename);
	fp.open(filename);
	if(!fp)
	{
		printf("Not found file\n");
		exit(0);
	}
	while(fp.getline(line,50))
	{   
		if(time==0)
		{
			num=atoi(line);
			if(num>0)
			{
				printf("NUM =%d \n", num);
				ob = new ABC[num] ;
				/*for(int i=0;i<num;i++)
				{
					ob[i].get();
					printf(" %d \n ", i);
				}*/
			}
		}
		else
		{	
			token=strtok(line, " ");
			printf("Token %s\n", token);
			if(strlen(token)==1 && strcmp(token,"R")==0 || strcmp(token,"W")==0)
			{
				char op=token[0];
					printf("Char %c\n", op);
					ob[i].setOp(op);
			}
			else
				{
					printf("Error>>>> In file does not contain valid opaeration R/W\n");
				}
			while(token!=NULL)
			{ 	
				token=strtok(NULL," ");
				if(token==NULL)
					break;
				printf(" %s\n", token);
				int n=atoi(token); 
				ob[i].setAddr(n);	
			}
			i++;
			
		}
		time++;
	}
	for(int i=0;i<num;i++)
	{
		ob[i].get();
		printf("%d\n",i);
	}
	int sets=(cm/(bm*degree));
	printf("%d\n", sets);
	o=new D[sets];
		o[0].setCache(ob[i], sets);
	    o[0].updateSet(sets, ob[i]);
	    o[0].get();
	
	return 0;
}