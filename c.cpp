#include<stdio.h>
#include<iostream>
#include<vector>

using namespace std;
class TrackBlock
{
	int bb;
	int cacheBlockNum;
	vector<TrackBlock>TrackBlockVector;
	public:
	void set(int cache,int bNum)
	{
		bb=bNum;
		cacheBlockNum=cache;
	}
	int getBB()
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
				//cout<<"Blck to compare "<<TrackBlockVector[i].getBB()<<endl;
				if(TrackBlockVector[i].getBB()==blockNum)
					return i;
			}
		}
		return -1;
	}
	int getBlockNum(int b,int cSet, int degree, char p)
	{
		int none=empty();
		int exist;
		int allocNum;
		string stat;
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
		cout<<"Exist "<<exist<<endl;
		if(exist!=-1)
		{
			stat="HIT";
			if(TrackBlockVector.size()<=degree)
			{
				this->cacheBlockNum=TrackBlockVector[0].getBB();
				//cout<<"Here "<<" "<<this->cacheBlockNum;
				if(p=='L')
					updateTracker(exist);
			}
			/*else
			{
				this->cacheBlockNum=TrackBlockVector[0].getBB();
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
			this->cacheBlockNum=TrackBlockVector[exist].getBB();
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
				this->cacheBlockNum=TrackBlockVector[0].getBB();
				TrackBlockVector.erase(TrackBlockVector.begin()+0);
				add.set(this->cacheBlockNum, b);
				TrackBlockVector.push_back(add);
				
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

class Cache
{
	char dirtyBit;
	int validBit;
	int cacheBlockNum;
	string tag;
	string data;
	public:
	Cache(string te)
	{
		dirtyBit='X';
		validBit=0;
		tag=te;
		data="X";
	}
	void get()
	{
		cout<<dirtyBit<<" "<<validBit<<" "<<tag<<" "<<data<<" "<<cacheBlockNum<<endl;
	}

};

int main()
{
	Cache **cref;
	string st;
	char policy='F';
	int set[]={0,0,2,3,4,0};
	int deg=2;
	int total=8;
	int numCacheSets=4;
	int cb;
	cref=new Cache*[total];
	TrackBlock *bref;
	bref=new TrackBlock[numCacheSets];
	//initialized cache
	for(int i=0;i<total;i++)
	{
		cref[i]=new Cache("YYY");
	}
	
	//checking cache status
	for(int i=0;i<total;i++)
	{
		cref[i]->get();
	}
	
	int found=bref[0].found(0);
	if(found!=-1)
		st="HIT";
	else
		st="MISS";
	
	//printing status
	cout<<st <<endl;
	//cout<<"Cache block "<<cb<<endl;	
	cb=bref[0].getBlockNum(0,0,deg,policy);
	
	cout<<"Cacche block "<<cb<<endl;
	found=bref[0].found(9);
		if(found!=-1)
			st="HIT";
	    else
			st="MISS";
		
	cout<<st <<endl;
	cb=bref[0].getBlockNum(9,0,deg,policy);
	
	cout<<"Cacche block "<<cb<<endl;
	
	
	found=bref[0].found(0);
		if(found!=-1)
			st="HIT";
	    else
			st="MISS";
		
	cout<<st <<endl;
	cb=bref[0].getBlockNum(0,0,deg,policy);
	
	cout<<"Cacche block "<<cb<<endl;
	
	found=bref[0].found(17);
		if(found!=-1)
			st="HIT";
	    else
			st="MISS";
		
	cout<<st <<endl;
	cb=bref[0].getBlockNum(17,0,deg,policy);
	
	cout<<"Cacche block "<<cb<<endl;
	
	//See block vector details
	bref[0].getVectorDetails();
	
}