#include<iostream>
#include<string>
#include<vector>

using namespace std;

// 堆
namespace heap_sort
{
	// 仿函数
	// 大顶堆
	template<class T>
	struct Greater
	{
		bool isequal(const T& n1, const T& n2)
		{
			return n1 > n2;
		}
	};

	// 小顶堆
	template<class T>
	struct Less
	{
		bool isequal(const T& n1, const T& n2)
		{
			return n1 < n2;
		}
	};

	// 模板参数传参
	template<class T, class Compare = Greater<T>>
	class myHeap
	{
	public:
		myHeap()
		{}

		myHeap(vector<T>& addr)
			:nums(addr)
		{
			// 建堆
			// 从最后节点开始进行调整，此处即为i
			for (int i = nums.size() - 1; i >= 0; i--)
			{
				AdjustDown(i, nums.size());
			}
		}

		// 插入元素
		void Push(const T& num)
		{
			nums.push_back(num);  // 将新元素插入数组末尾，即在堆底最后一个位置
			// 向上调整		
			AdjustUp();		      // 判断堆是否成立，即新的元素是否需要需要向上调整
		}

		/* 
		  弹出堆顶元素：
		  1、将数组中头元素（即堆顶元素）和尾元素（堆底元素）进行交换
		  2、将原本的堆顶元素（数组尾元素）弹出
		  3、从堆顶元素开始对整个堆进行向下调整，使其变成堆
		*/
		void Pop()
		{
			swap(nums[0], nums[nums.size() - 1]);
			nums.pop_back();
			AdjustDown(0, nums.size());
		}

		// 堆排序
		void Sort()
		{
			for (int len = nums.size(); len > 0;)
			{
				// 输出堆顶元素（将堆顶最大或最小元素与堆底元素交换）
				swap(nums[0], nums[len - 1]);
				//cout << nums[0] << "," << nums[len - 1] << endl;;
				// 从头节点开始整理，对剩余的len-1个元素进行向下调整，重新成为大顶或小顶堆
				AdjustDown(0, --len);
			}
		}

		void Print()
		{
			for (auto i : nums)
			{
				cout << i << " ";
			}
			cout << endl;
		}

	protected:
		/*
		 向上调整算法思路：
		 判断插入是否满足堆成立条件，因为插入新的节点时只会影响其祖先所在的路径上的节点
		 若不满足则沿着当前节点index，向上一路（祖先路径）进行更新
		 直至满足条件或者已到达根节点
		*/
		void AdjustUp()
		{
			Compare con;					// 定义比较对象
			int index = nums.size() - 1;	// 堆底元素下标
			int parent = (index - 1) / 2;	// 堆底元素父节点下标

			//判断下标是否越界，以及子节点与父节点之间是否满足大小堆的条件
			while (index > 0 && con.isequal(nums[index], nums[parent]))
			{
				swap(nums[parent], nums[index]);	// 交换父子节点数据，使其满足堆条件
				// 向上更新
				index = parent;						// 更新index为原来的父节点
				parent = (index - 1) / 2;			// 更新parent为原来父节点的父节点
			}
		}

		/*
		  向下调整算法思路：
		  由于堆顶元素的调整，导致堆不符合条件。所以从堆顶元素开始向下进行调整。
		  不满足条件时，父节点与其两个孩子中的较大或较小者（根据大顶堆、小顶堆判断）进行交换
		  循环此过程，直到满足堆条件或是已到堆底

		  参数：
		  root	向下调整的起始节点（一般为堆顶节点）
		  size	向下调整的范围
		*/	
		void AdjustDown(size_t root, int size)
		{
			Compare con;								// 定义比较对象
			int parent(root);							// 定义父节点为总根节点
			int child(parent * 2 + 1);					// 定义子孩子节点为左孩子节点
			
			while (child < size)
			{
				// 判断左右孩子中哪一个需要与父节点进行数据交换，默认为左孩子
				if ((child + 1 < size) && (con.isequal(nums[child + 1], nums[child])))
					child++;
				
				// 比较父节点与孩子节点是否满足堆要求
				if (con.isequal(nums[child], nums[parent]))
				{
					swap(nums[child], nums[parent]);	// 交换父子节点数据，使其满足堆条件
					parent = child;						// 更新父节点为原本的子节点
					child = parent * 2 + 1;				// 更新子节点为原本的子节点的左孩子
				}
				else
					break;
			}

		}

	public:
		vector<T> nums;
	};

	void heapTest()
	{
		// 默认实现大顶堆
		//myHeap<int> m;
		// 通过仿函数实现小堆
		//myHeap<int, Less<int>> m;
		// 通过仿函数实现大堆
		myHeap<int, Greater<int>> m;
		m.Push(3);
		m.Push(1);
		m.Push(0);
		m.Push(5);
		m.Push(4);
		m.Print();
		m.Pop();
		m.Print();

		int arr[] = { 3, 1, 0, 5, 4 };
		vector<int> num(arr, arr + 5);

		myHeap<int, Greater<int>> n(num);
		n.Print();
		n.Sort();
		n.Print();
	}
}

int main()
{
	heap_sort::heapTest();
	return 0;
}

