/*
* 岛问题：
* 思路：使用并查集时（多任务，并行计算）
* 将一个大矩阵化成多个小矩阵，然后不同的CPU处理不同的矩阵，最后将不同的矩阵合并。
* 边界问题，将边界上连成一片的1合并
* 在小矩阵中，第一个1作为头结点，后面1连成一片的1都挂在头结点下
* 然后在解决边界时，若两个1碰到一起了，就检查两个1的头结点是不是一样的，
* 不一样的话，就合并两个集合，同时岛的个数-1；
* 一样的话，证明之前已经合并过了，岛的个数不变
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include<list>
#include<string>
#include<stack>
#include<unordered_map>

using namespace std;

// 封装样本的节点类
template<class T>
struct Element
{
private:
	T value;
public:
	Element()
	{}

	Element(const T& val)
		:value(val)
	{}

	T getValue()  const
	{
		return value;
	}

	// 重载等于运算符，哈希时应用
	bool operator==(const Element<T>& a) const
	{
		return (value == a.getValue());
	}

	bool operator!=(const Element<T>& a) const
	{
		return (value != a.getValue());
	}
};


// 针对Element类型，自定义哈希函数
template<class T>
struct hashkey
{
	// 针对整型数据进行哈希
	size_t operator()(const Element<int>& s) const
	{
		size_t seed = 131;
		size_t hash = 0;
		size_t i = 0;
		hash = (hash * seed) + s.getValue();
		return hash;
	}

	// 针对string类型进行哈希
	size_t operator()(const Element<string>& s) const
	{
		size_t seed = 131;
		size_t hash = 0;
		size_t i = 0;
		for (i = 0; i < s.getValue().size(); ++i)
		{
			hash = (hash * seed) + s.getValue()[i];
		}
		return hash;
	}
};

// 并查集
template<class T>
class UnionFindSet
{
private:
	unordered_map<T, Element<T>> elementMap;						// 样本与节点一一对应的表：key为原始样本，value为对应的节点
	unordered_map<Element<T>, Element<T>, hashkey<T>> fatherMap;	// 节点关系表：key为某节点，value为其父节点。将此关系存在map中
	unordered_map<Element<T>, int, hashkey<T>> sizeMap;				// 节点规模表：key为某节点（key一定是集合的头节点，代表整个集合），value为对应集合大小

public:
	UnionFindSet()
	{}

	// 初始化
	UnionFindSet(list<T>& list)
	{
		for (T val : list)
		{
			Element<T> element(val);
			elementMap.insert(pair<T, Element<T>>(val, element));				// 每个样本与节点对应
			fatherMap.insert(pair<Element<T>, Element<T>>(element, element));	// 起始时，每个节点的父节点是自己
			sizeMap.insert(pair<Element<T>, int>(element, 1));					// 起始时，每个节点都作为头节点，其集合大小均为1
		}
	}

	// 从输入参数element出发，往上一直找，找到不能再往上的头节点时返回（沿途链扁平化）
	Element<T> findHead(Element<T>& element)
	{
		stack<Element<T>> path{};					// 在往上查找的过程中，沿途的点全部记录在path中

		while (element != fatherMap[element])
		{
			path.push(element);						// 向上寻找时，讲沿途节点全部入栈
			element = fatherMap[element];			// 更新element为其父节点，循环寻找头节点
		}

		// 沿途链扁平化，保证后期查找成本为 O(1)
		while (!path.empty())
		{
			Element<T> pathElement = path.top();
			fatherMap[pathElement] = element;		// 将路径上所有节点的父亲都更新为集合头节点
			path.pop();
		}

		return element;
	}

	// 判断两个样本是否是同一个集合
	bool isSameSet(T a, T b)
	{
		if (elementMap.count(a) && elementMap.count(b))					// 判断两个样本是否在集合中
		{
			return findHead(elementMap[a]) == findHead(elementMap[b]);
		}

		return false;
	}

	// 将两个集合合并
	void Union(T a, T b)
	{
		if (elementMap.count(a) && elementMap.count(b))					// 判断两个样本是否在集合中
		{
			Element<T> af = findHead(elementMap[a]);					// 寻找a节点所在集合的头节点
			Element<T> bf = findHead(elementMap[b]);					// 寻找b节点所在集合的头节点

			if (af != bf)												// 比对两个头节点是否相同，即两个节点是否在同一个集合中
			{
				Element<T> big = sizeMap[af] >= sizeMap[bf] ? af : bf;	// 寻找af、bf两个集合中较大的集合的头节点
				Element<T> small = big == af ? bf : af;					// 较小集合头节点
				fatherMap[small] = big;									// 集合合并：更改较小集合small头节点的父亲为大集合的头节点
				sizeMap[big] = sizeMap[af] + sizeMap[bf];				// 更改较大集合的容量
				sizeMap.erase(small);									// 从头节点集合中删除较小集合的头节点
			}
		}
	}

	// 返回并查集中集合数量
	int getSetSize()
	{
		return sizeMap.size();
	}

};


int countIsLand(vector<vector<int>>& nums)
{
	list<string> l;

	// 遍历数组，将所有等于1的样本点转换为字符串，再加入链表中
	for (int i = 0; i < nums.size(); i++)
	{
		for (int j = 0; j < nums[0].size(); j++)
		{
			// 当为1时，将其行列整合为字符串，加入链表中
			if (nums[i][j] == 1)
			{
				string str = to_string(i) + '_' + to_string(j);
				l.push_back(str);
			}
		}
	}

	// 构建并查集，将所有样本点加入
	UnionFindSet<string> ufs(l);

	for (int i = 0; i < nums.size(); i++)
	{
		for (int j = 0; j < nums[0].size(); j++)
		{
			// 当前样本满足条件为1，则对并查集操作
			if (nums[i][j] == 1)
			{
				// 当前样本转换为字符串（并查集中节点的表示）
				string cur = to_string(i) + '_' + to_string(j);

				// 判断样本上面的节点是否满足条件，满足则将其转为字符串，再与当前节点进行合并
				if (i - 1 >= 0 && nums[i - 1][j] == 1)
				{
					string up = to_string(i - 1) + '_' + to_string(j);
					ufs.Union(cur, up);
				}
				// 判断样本左边的节点是否满足条件，满足则将其转为字符串，再与当前节点进行合并
				if (j - 1 >= 0 && nums[i][j - 1] == 1)
				{
					string left = to_string(i) + '_' + to_string(j - 1);
					ufs.Union(cur, left);
				}
			}
		}
	}

	// 返回并查集中集合的数量（岛的个数即是并查集中集合的个数）
	return ufs.getSetSize();
}

void countIsLand_Test()
{
	int arr[][6] = {
		{ 0, 0, 1, 0, 1, 0 },
		{ 1, 1, 1, 0, 1, 0 },
		{ 1, 0, 0, 1, 0, 0 },
		{ 0, 0, 0, 0, 0, 0 },
	};
	vector<vector<int> > nums(4, vector<int>(6));
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 6; j++){
			nums[i][j] = arr[i][j];
		}
	}
	cout << countIsLand(nums) << endl;;
	cout << "success" << endl;
}
