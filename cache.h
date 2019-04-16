#include<vector>
#include<stdio>
#include<iostream>
#include<string>

using namespace std;

class Cache
{
	char dirtyBit;
	int validBit;
	int cacheBlockNum;
	string tag;
	string data;
	vector<Cache>CacheVector;
	Cache(Cache &c)
	{
		this->dirtyBit='X';
		this->validBit=0;
		this->tag="XXXX";
		this->data="X";
		CacheVector.push_back(*c);
	}
}

int main()
{
	Cache cref=new **
}