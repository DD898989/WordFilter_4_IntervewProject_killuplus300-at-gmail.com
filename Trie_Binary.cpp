//#include "stdafx.h"
#include <iostream>
#include <string>
#include <bitset>
#include <fstream>
#include <codecvt>
#include <windows.h>
#include <regex>
using namespace std;

#define MAXN 2 //binary tree

typedef struct Trie
{
	bool IsEnd;
	Trie *next[MAXN];
} Trie;

Trie *root, *q, *p; 
int length;
bitset<16> bitAry;

void createTrie(wstring str)
{
	length = str.length();
	q = root;
	p = root;

	for(int i = 0; i < length; i++)
	{
		bitAry = bitset<16>(str[i]);
		for(int k=0;k<16;k++)
		{
			int idBit = bitAry[k];
			if(p->next[idBit] == NULL)
			{
				q = new Trie;
				for(int j = 0; j < MAXN; j++)
				{
					q->next[j] = NULL;
					q->IsEnd=false;
				}
				p->next[idBit] = q;
				p = p->next[idBit];
			}
			else
			{
				p = p->next[idBit];
			}
		}
	}
	p->IsEnd=true;
}

bool findTrie(wstring str)
{
	length = str.length();
	p = root;

	for(int i = 0; i < length; i++)
	{
		bitAry = bitset<16>(str[i]);
		for(int k=0;k<16;k++)//wstring = 16 bits
		{
			p = p->next[(int)bitAry[k]];
			if(p == NULL) 
				return false;
		}

	}
	if(p->IsEnd)
		return true;
	else
		return false;
}

int main()
{
	locale::global(locale(""));
	int minLen =9999;
	int maxLen =-1;

	root = new Trie;
	for(int i = 0; i < MAXN; i++) 
		root->next[i] = NULL;

	typedef codecvt_utf8<wchar_t> converter_type;	
	const converter_type* converter = new converter_type;

	string dicPath = "D:\\Dictionary.txt";
	cout<<"Please check dictionary path: "<<dicPath<<endl;  system("pause");
	wifstream stream(dicPath);

	stream.imbue(locale(locale::empty(), converter));
	wstring line;

	while (getline(stream, line))
	{
		int len = line.length();

		if(len<1)
			continue;

		if(len>maxLen)
			maxLen = len;

		if(len<minLen)
			minLen = len;

		for(int i=0;i<len;i++) 
			line[i]= towlower(line[i]);

		createTrie(line);
	}


	while(true)
	{
		cout<<endl<<"請輸入搜尋詞囊:"<<endl;
		wstring newWrod;
		getline(wcin, newWrod);
		if(newWrod.length()>0)
		{
			if(!findTrie(newWrod))
			{
				cout<<endl<<"沒找到!  輸入Y來新增"<<endl;
				wstring Input;   getline(wcin,Input);
				if(Input==L"Y")
					createTrie(newWrod);
			}
			else
			{
				cout<<endl<<"找到!"<<endl;
			}
		}

		wstring seq;
		cout<<endl<<"請輸入過濾句子:"<<endl;
		getline(wcin, seq);
		wstring seq_ = seq;

		LARGE_INTEGER nFreq,nBeginTime,nEndTime;
		QueryPerformanceFrequency(&nFreq);
		QueryPerformanceCounter(&nBeginTime);

		for(int i=0;i<seq_.length();i++) 
			seq_[i]= towlower(seq_[i]);

		wregex rgx(L"\\w+");
		for( wsregex_iterator it(seq_.begin(), seq_.end(), rgx), it_end; it != it_end; ++it )
		{
			wstring line = (*it)[0];
			if(line.length()<minLen)
				continue;


			for(int wordLen=minLen;wordLen<=maxLen;wordLen++)
			{
				if(line.length()<wordLen)
					break;

				for(int i=0;i<line.length()+1-wordLen;i++)
				{
					wstring line0=line.substr(i,wordLen);
					if(line0.find(L"*") != string::npos)
						continue;
					if(findTrie(line0))
					{
						wstring ws(line0.length(), L'*');
						line.replace(i, wordLen, ws);
						seq.replace(it->position()+i, wordLen, ws);
					}
				}
			}
		}

		cout<<endl<<"過濾後:"<<endl;
		wcout<<seq<<endl;

		QueryPerformanceCounter(&nEndTime);
		double timeT = (double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;
		printf("\n耗時:%f\n",timeT);
	}
	return 0;
}

