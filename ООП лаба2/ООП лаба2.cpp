#include <iostream>
#include <ctime>
#include <map>
#include <string>
#include <fstream>
using namespace std;

class SBase
{
public:
	virtual int Get() = 0;
};

class SFile : public SBase
{
	ifstream File;
public:
	virtual int Get() override
	{
		int val;
		if (File >> val) {
			return val;
		}
		else {
			return -1;
		}
		//if (File.eof()) return -1;
		return val;
	}
	SFile(string name)
	{
		File.open(name);
	}
	~SFile()
	{
		File.close();
	}
};

class SQueue : public SBase
{
	int* queue;
	int len;
	int count;

public:
	SQueue(int len)
	{
		srand(time(NULL));
		this->len = len;
		queue = new int[len];
		for (int i = 0; i < len; i++)
		{
			queue[i] = rand() % 100;
		}
		count = 0;
	}
	~SQueue()
	{
		delete[] queue;
	}
	virtual int Get() override
	{
		if (count == len) return -1;
		return queue[count++];
	}
};

class SKbrd : public SBase
{
public:
	virtual int Get() override
	{

		int val;
		cin >> val;
		if (cin.eof()) return -1;
		return val;
	}
};

class Freq
{
	map<int, int>counter;
public:
	virtual void Calc(SBase& sb)
	{
		int num = sb.Get();
		while (num != -1)
		{
			if (num > 0)
			{
				counter[num]++;
				num = sb.Get();
			}
			else
			{
				num = sb.Get();
			}
		}
		for (auto c : counter)
		{
			cout << c.first << ":" << c.second << endl;
		}
	}
};


class Diap : public Freq
{
public:
	virtual void Calc(SBase& sb) override
	{
		int num = sb.Get();
		int sum;
		int max;
		int min = max = sum = num;
		while (num != -1)
		{
			num = sb.Get();
			if (num > 0)
			{
				if (max < num)
				{
					max = num;
				}
				else
				{
					min = num;
				}
				sum += num;
			}
		}
		cout << "Max = " << max << endl << "Min = " << min << endl << "Summ of numbers = " << sum;
	}
};

int main()
{
	SFile file("File.txt");
	Freq freq;
	freq.Calc(file);

}


