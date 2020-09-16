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

void unionFindSet_Test()
{
	list<int> l;
	l.push_back(5);
	l.push_back(3);
	l.push_back(4);
	l.push_back(2);
	l.push_back(6);
	l.push_back(0);
	l.push_back(1);

	UnionFindSet<int> ufs(l);

	cout << ufs.getSetSize() << endl;
	ufs.Union(1, 2);
	ufs.Union(3, 4);
	ufs.Union(4, 0);
	ufs.Union(4, 6);
	ufs.Union(2, 0);

	cout << ufs.getSetSize() << endl;
	cout << "success" << endl;
}

