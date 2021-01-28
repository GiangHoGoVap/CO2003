#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Interval
{
public:
	int start;
	int end;
	Interval(int start = 0, int end = 0)
	{
		this->start = start;
		this->end = end;
	}
};

int minPark(vector<Interval> lInterval)
{
	int size = lInterval.size();
	int *_start = new int[size];
	int *_end = new int[size];
	for (int i=0; i<size; i++){
		_start[i] = lInterval[i].start;
		_end[i] = lInterval[i].end;
	}
	sort(_start, _start + size);
	sort(_end, _end + size);
	int park_needed = 1, result = 1;
	unsigned int i = 1, j = 0;
	while (i < lInterval.size() && j < lInterval.size())
	{
		if (_start[i] < _end[j]){
			park_needed++;
			i++;
		}
		else if (_start[i] >= _end[j]){
			park_needed--;
			j++;
		}
		if (park_needed > result) result = park_needed;
	}
	return result;
}

int main()
{
	vector<Interval> intervals;
	intervals.push_back(Interval(1,4));
	intervals.push_back(Interval(2,4));
	intervals.push_back(Interval(3,6));
	intervals.push_back(Interval(4,5));
	//intervals.push_back(Interval(3,9));
	
	cout << minPark(intervals) << endl; //Ans = 3
	//print(intervals);
}
