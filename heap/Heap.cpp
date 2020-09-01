// 模拟实现heap堆

#pragma once

#include<iostream>
#include<assert.h>
#include<vector>
#include<list>
#include<stack>
#include<queue>
using namespace std;

// 仿函数
// 进行大小的比较，来构建对应的大小堆

// 小堆
template<class T>
struct Less
{
	bool operator()(T& left, T& right)
	{
		return left < right; 
	}
};

// 大堆
template<class T>
struct Greater
{
	bool operator()(T& left, T& right)
	{
		return left > right;
	}
};

template<class T, class Compare=Greater<T>>
class Heap
{
public:
	// 此空构造函数不可删
	// 当是空堆时，会在初始化列表里调用vector的缺省构造函数进行初始化
	Heap()
	{}

	// 构造函数
	Heap(T* a, size_t n)
	{
		// 提前开辟空间，避免不断地增容，降低效率
		_array.reserve(n);

		for (size_t i = 0; i < n; i++)
		{
			_array.push_back(a[i]);
		}

		// 建堆
		// 从最后一个非叶节点开始进行调整，此处即为i
		for (int i = ((int)_array.size() - 2) >> 1; i >= 0; i--)
		{
			AdjustDown(i);
		}
	}

	void Push(const T& x)
	{
		// 插入数据到vector
		_array.push_back(x);
		// 进行向上调整
		AdjustUp(_array.size() - 1);
	}

	void Pop()
	{
		// 将首尾结点进行交换
		swap(_array[_array.size() - 1], _array[0]);
		// 删掉尾节点
		_array.pop_back();
		// 通过向下调整重复建堆
		AdjustDown(0);
	}

	size_t Size()
	{
		return _array.size();
	}

	T& Top()
	{
		return _array[0];
	}

	bool Empty()
	{
		return _array.empty();
	}

	void PrintfHeap()
	{
		if (!Empty())
		{
			for (int i = 0; i < _array.size(); i++)
			{
				cout << _array[i] << " ";
			}
			cout << endl;
		}
	}

protected:
	// 向上调整法
	void AdjustUp(size_t child)
	{
		Compare com;
		size_t parent = (child - 1) / 2;
		while (child > 0)
		{
			// 比较父亲与孩子结点，并进行向上调整
			if (com(_array[child], _array[parent]))
			{
				swap(_array[parent], _array[child]);
				// 向上进行调整
				child = parent;
				parent = (child - 1) / 2;
			}
			else
			{
				break;
			}
		}
	}

	// 向下调整法
	void AdjustDown(size_t root)
	{
		Compare com;
		int parent = root;
		int child = parent * 2 + 1; //默认为左孩子
		while (child < _array.size())
		{
			// 选左右孩子里面最大的
			if (child + 1 < _array.size() && com(_array[child+1],_array[child]))
			{
				child++;
			}

			// 孩子与父亲进行比较和调整
			if (com(_array[child], _array[parent]))
			{
				//父节点与孩子进行交换
				swap(_array[parent], _array[child]);
				// 继续向下进行调整
				parent = child;
				child = parent * 2 + 1;
			}
			else
			{
				break;
			}
		}
	}

	// 用来处理topK问题
	void AdjustDown(int* heap, int k, int root)
	{
		assert(heap);

		int parent = root;
		int child = parent * 2 + 1;
		
		// 建立前K个的堆
		while (child < k)
		{
			if (heap[child + 1]>heap[child])
			{
				child++;
			}

			if (heap[parent] > heap[child])
			{
				swap(heap[parent], heap[child]);
				parent = child;
				child = parent * 2 + 1;
			}
			else
			{
				break;
			}
		}
	}

protected:
	vector<T> _array;
};


void heaptest()
{
	int a[] = { 12, 10, 6, 9, 14, 17, 20, 13 };
	// 建大堆
	Heap<int, Greater<int>> h1(a, sizeof(a) / sizeof(int));
	h1.PrintfHeap();

	// 建小堆	
	Heap<int, Less<int>> h2(a, sizeof(a) / sizeof(int));
	h2.PrintfHeap();

	// Push 测试
	h1.Push(30);
	h1.PrintfHeap();
	h2.Push(5);
	h2.PrintfHeap();

	// Pop 测试
	h1.Pop();
	h1.PrintfHeap();
	h2.Pop();
	h2.PrintfHeap();

	// Size() 测试
	int len = h1.Size();
	cout << "h1 size = " << len << endl;

	// Top 测试
	int top1 = h1.Top();
	cout << "h1 top = " << top1 << endl;
}
