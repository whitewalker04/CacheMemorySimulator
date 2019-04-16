#include<vector>
#include<stdio.h>
#include<iostream>
#include<string>

using namespace std;

class Tracker
{
	int cnum;
	int bb;
	public:
	void set(int a, int b)
	{
		cnum=a;
		bb=b;
	}
	int getCNum()
	{
		return cnum;
	}
	int getBB()
	{
		return bb;
	}
};

class Cache
{
	char dirtyBit;
	int validBit;
	int cacheBlockNum;
	string tag;
	string data;
	vector<Cache>CacheVector;
	vector<Tracker>TrackerVector;
	public:
	Cache(string tag)
	{
		this->dirtyBit='X';
		this->validBit=0;
		this->tag=tag;
		this->data="X";
		CacheVector.push_back(*this);
	}
	void showCacheVector()
	{
		for(int i=0;i<CacheVector.size();i++)
		{
			CacheVector[i].get();
			cout<<endl;
		}
	}
	void get()
	{
		cout<<dirtyBit<<" "<<validBit<<" "<<tag<<" "<<data<<" "<<cacheBlockNum;
	}
	int empty()
	{
		if(TrackerVector.empty())
			return 1;
		else
			return 0;
	}
	
	int found(int blockNum)
	{
		if(!empty())
		{
			for(int i=0;i<TrackerVector.size();i++)
			{
				if(TrackerVector[i].getBB()==blockNum)
					return i;
			}
		}
		return -1;
		
		
	}
	
	string pushOperations(int bb, int cSet,int degree, char p)
	{
		int none=empty();
		int exist;
		string stat;
		printf("%d\n", none);
		Tracker add;
		if(none)
		{
			this->cacheBlockNum=cSet*degree+0;
			this->validBit=1;
			add.set(this->cacheBlockNum, bb);
			TrackerVector.push_back(add);
			CacheVector[0]=*this;
			stat="MISS";
			return stat;
		}
		exist=found(bb);
		if(exist!=-1)
		{
			stat="HIT";
			if(TrackerVector.size()<degree)
			{
				this->cacheBlockNum=TrackerVector[exist].getBB();
				this->validBit=1;
				if(p=='L')
					updateTracker(exist);
			}
			else
			{
				this->cacheBlockNum=TrackerVector[0].getBB();
				TrackerVector.erase(TrackerVector.begin()+0);
				add.set(this->cacheBlockNum, bb);
				this->validBit=1;
				CacheVector[this->cacheBlockNum]=*this;
				stat="MISS";
			}
		}
		return stat;
	}
	void updateTracker(int exist)
	{
		Tracker add=TrackerVector[exist];
		TrackerVector.erase(TrackerVector.begin()+exist);
		TrackerVector.push_back(add);
	}
	
};

int main()
{
	Cache **cref;
	cref=new Cache*[2];
	string st;
	char policy='F';
	int set[]={0,0,2,3,4,0};
	int deg=2;
	for(int i=0;i<2;i++)
	{
		cref[i]=new Cache("YYY");
	}
	st=cref[0]->pushOperations(0,0,2,'F');
	cout<<st<<endl;
	st=cref[2]->pushOperations(24,2,2,'F');
	cout<<st<<endl;
	st=cref[0]->pushOperations(9,0,2,'F');
	cout<<st<<endl;
	st=cref[1]->pushOperations(24,3,2,'F');
	cout<<st<<endl;
	for(int i=0;i<6;i++)
	{
		cref[i]->showCacheVector();
	}
}