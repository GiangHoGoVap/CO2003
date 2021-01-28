#include <iostream>
#include <cstring>
#include <math.h>
using namespace std;
#define ARRAY_SIZE 5
#define INC_SORT 0
#define DEC_SORT 1
#define MAX_HEAP 0
#define MIN_HEAP 1

class Heap
{
public:
	int *arr;
	int count;
	int capacity;
	int heap_type;

public:
	int getCount()
	{
		return count;
	}
	void CopyData(int *data, int size)
	{
		memcpy(this->arr, data, sizeof(int) * size);
		this->count = size;
	}
	void createHeap(int capacity, int heap_type)
	{
		this->heap_type = heap_type;
		this->count = 0;
		this->capacity = capacity;
		this->arr = new int[this->capacity];
		if (this->arr == NULL)
		{
			cout << "Not enough memory";
		}
	}
	~Heap()
	{
		delete[] this->arr;
	}
	void reheapUp(long position)
	{
		if (position > 0)
		{
			long parent = (position - 1) / 2;
			//For max heap
			if (this->heap_type == MAX_HEAP && this->arr[position] > this->arr[parent])
			{
				int temp = this->arr[position];
				this->arr[position] = this->arr[parent];
				this->arr[parent] = temp;
				reheapUp(parent);
			}
			//For min heap
			if (this->heap_type == MIN_HEAP && this->arr[position] < this->arr[parent])
			{
				int temp = this->arr[position];
				this->arr[position] = this->arr[parent];
				reheapUp(parent);
			}
		}
	}
	void reheapDown(int position, int lastPosition)
	{
		long leftChild = 2 * position + 1;
		long rightChild = 2 * position + 2;
		long largeChild;
		//For max heap
		if (this->heap_type == MAX_HEAP)
		{
			if (leftChild <= lastPosition)
			{
				if (rightChild <= lastPosition && this->arr[rightChild] > this->arr[leftChild])
				{
					largeChild = rightChild;
				}
				else
				{
					largeChild = leftChild;
				}
			}
			if (this->arr[largeChild] > this->arr[position])
			{
				int temp = this->arr[largeChild];
				this->arr[largeChild] = this->arr[position];
				this->arr[position] = temp;
				reheapDown(largeChild, lastPosition);
			}
		}
		//For min heap
		if (this->heap_type == MIN_HEAP)
		{
			if (leftChild <= lastPosition)
			{
				if (rightChild <= lastPosition && this->arr[rightChild] < this->arr[leftChild])
				{
					largeChild = rightChild;
				}
				else
					largeChild = leftChild;
			}
			if (this->arr[largeChild] < this->arr[position])
			{
				int temp = this->arr[largeChild];
				this->arr[largeChild] = this->arr[position];
				this->arr[position] = temp;
				reheapDown(largeChild, lastPosition);
			}
		}
	}
	bool insertHeap(int DataIn)
	{
		if (this->count == this->capacity)
			return false;
		else
		{
			this->arr[this->count] = DataIn;
			reheapUp(this->count);
			this->count++;
			return true;
		}
	}
	bool deleteHeap(int &DataOut)
	{
		if (this->count == 0)
			return false;
		else
		{
			DataOut = this->arr[0];
			this->arr[0] = this->arr[count - 1];
			count = count - 1;
			reheapDown(0, count - 1);
			return true;
		}
	}
	void buildHeap()
	{
		long position = this->count / 2 - 1;
		while (position >= 0)
		{
			reheapDown(position, count - 1);
			position--;
		}
	}
	bool isHeap()
	{
		long position = this->count / 2 - 1;
		long lastPosition = this->count - 1;
		while (position >= 0)
		{
			long leftChild = position * 2 + 1;
			long rightChild = position * 2 + 2;
			long child;
			//For max heap
			if (this->heap_type == MAX_HEAP)
			{
				if (leftChild <= lastPosition)
				{
					if (rightChild <= lastPosition && this->arr[rightChild] > this->arr[leftChild])
					{
						child = rightChild;
					}
					else
						child = leftChild;
					if (this->arr[child] > this->arr[position])
					{
						return false;
					}
				}
			}
			//For min heap
			if (this->heap_type == MIN_HEAP)
			{
				if (leftChild <= lastPosition)
				{
					if (rightChild <= lastPosition && this->arr[rightChild] < this->arr[leftChild])
					{
						child = rightChild;
					}
					else
						child = leftChild;
					if (this->arr[child] < this->arr[position])
					{
						return false;
					}
				}
			}
			position--;
		}
		return true;
	}
	void printHeap()
	{
		for (long i = 0; i < this->count; i++)
		{
			cout << this->arr[i] << " ";
		}
		cout << endl;
	}
};

int *arr1 = NULL;
Heap heap;

void InsertionSort(int *arr)
{
	long count = ARRAY_SIZE, current;
	current = 1;
	while (current < count)
	{
		long temp = arr[current];
		long walker = current - 1;
		while (walker >= 0 && temp < arr[walker])
		{
			arr[walker + 1] = arr[walker];
			walker--;
		}
		arr[walker + 1] = temp;
		current++;
	}
}

void Sorting(void (*SortFunc)(int *))
{
	(*SortFunc)(arr1);
	cout << "After sorting:" << endl;
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		cout << arr1[i] << " ";
	}
}

int main()
{
	arr1 = new int[ARRAY_SIZE];
	for (long i = 0; i < ARRAY_SIZE; i++)
	{
		cout << "Enter the [" << i << "]: " << endl;
		cin >> arr1[i];
	}
	heap.createHeap(ARRAY_SIZE, MIN_HEAP);
	heap.CopyData(arr1, ARRAY_SIZE);
	heap.buildHeap();
	heap.printHeap();
	cout << "\n----------------------\n";
	cout << "INSERTION SORT" << endl;
	Sorting(InsertionSort);
	delete[] arr1;
	return 0;
}
