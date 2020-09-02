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
			nums.push_back(num);
			// 向上调整
			AdjustUp();
		}

		void Sort()
		{
			for (int len = nums.size(); len > 0; len--)
			{
				// 输出堆顶元素（将堆顶最大或最小元素与堆底元素交换）
				swap(nums[0], nums[len - 1]);
				// 从头节点开始整理，对剩余的len-1个元素进行向下调整，重新成为大顶或小顶堆
				AdjustDown(0, len--);
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
		// 向上调整
		void AdjustUp()
		{
			Compare con;
			int index = nums.size() - 1;
			int parent = (index - 1) / 2;

			while (index > 0 && con.isequal(nums[index], nums[parent]))
			{
				swap(nums[parent], nums[index]);
				index = parent;
				parent = (index - 1) / 2;
			}
		}

		// 向下调整
		void AdjustDown(size_t root, int size)
		{
			Compare con;
			int parent(root), child(parent * 2 + 1);
			while (child < size)
			{
				if ((child + 1 < size) && (con.isequal(nums[child + 1], nums[child])))
					child++;
				
				if (con.isequal(nums[child], nums[parent]))
				{
					swap(nums[child], nums[parent]);
					parent = child;
					child = parent * 2 + 1;
				}
				else
					break;
			}

		}

	private:
		vector<T> nums;
	};

	void test()
	{
		// 默认实现大顶堆
		//myHeap<int> m;
		// 通过仿函数实现小堆
		//myHeap<int, Less<int>> m;
		// 通过仿函数实现大堆
		//myHeap<int, Greater<int>> m;
		//m.Push(3);
		//m.Push(1);
		//m.Push(0);
		//m.Push(5);
		//m.Push(4);
		//m.Print();

		int arr[] = { 3, 1, 0, 5, 4 };
		vector<int> num(arr, arr + 5);
		myHeap<int, Greater<int>> n(num);
		n.Print();
		n.Sort();
		n.Print();
	}
}
