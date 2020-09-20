#include <iostream>
#include <algorithm>
#include <vector>
#include<list>
#include<string>
#include<stack>
#include<unordered_map>

using namespace std;


// 关闭罪犯
struct node{
	int x, y, num;
};

vector<node> arr(100001);
vector<int> prison(20001, 0);
vector<int> enemy(20001, 0);

bool equal(const node& a, const node& b)
{
	return a.num > b.num;
}

// 初始化监狱集合，每个自成单元素集合
// 数组中下标i为真实元素样本，而下标对应数据prison[i]为其父元素
void initSet(const int n)
{
	for (int i = 1; i <= n; i++)
	{
		prison[i] = i;
	}
}

/*
 * 寻找数据x所在集合的代表元素操作：
 * 如果x=prison[x]，说明x自成单元素集合，返回即可
 * 否则从其父元素开始，继续递归进行寻找，直到找到代表元素
 * 同时寻找途中，进行路径压缩，将x所在路径元素的父元素均更新为集合代表元素
 */
int findHead(const int n)
{
	if (n != prison[n])
	{
		prison[n] = findHead(prison[n]);
	}

	return prison[n];
}

/*
 * 集合合并操作：
 * 判断x与y是否在同一集合，如果不在，则递归查找其各自所在集合代表元素
 * 再将y所在集合的代表元素其父更新为x所在集合代表元素
*/
void Union(const int x, const int y)
{
	if (prison[x] != prison[y])
	{
		prison[findHead(x)] = prison[findHead(y)];
	}
}

/*
 * 判断两个元素是否在同一集合操作：
 * 递归查找其各自集合所在代表元素，如果一样，说明为同一集合
*/
bool isSameSet(const int x, const int y){
	if (findHead(prison[x]) == findHead(prison[y]))
	{
		return true;
	}
	else
	{
		return false;
	}
}

// 罪犯分离函数
void separateCriminal()
{
	int crmNum(0), lines(0), i(1);
	cin >> crmNum >> lines;

	for (i = 0; i < lines; i++)
	{
		cin >> arr[i].x >> arr[i].y >> arr[i].num;
	}

	// 根据怨气将所有的罪犯对进行降序排序
	sort(arr.begin(), arr.end(), equal);

	// 初始化监狱集合
	initSet(crmNum);

	for (i = 0; i < lines; i++)
	{
		// 如果冲突的罪犯已经处在同一集合，则说明无法再分开，输出结果
		if (isSameSet(arr[i].x, arr[i].y)){
			cout << arr[i].x << " " << arr[i].y << endl;
			cout << arr[i].num;
			break;
		}

		/* 判断敌人集合中是否已经有当前元素 x:
		 * 若x不存在，说明还未存储其敌人，则将以x为下标的数据位上数据更新为x的敌人 y
		 * 若x存在，说明数组以x为下标的数据位上存在的是x的敌人
		 * 那么敌人的敌人就是朋友，所以将 x 所对应的敌人 y 与其在敌人集合中的敌人enemy[x]进行聚合
		*/
		if (enemy[arr[i].x] != 0)
		{
			Union(arr[i].y, enemy[arr[i].x]);
		}
		else
		{
			enemy[arr[i].x] = arr[i].y;
		}

		// 对y进行与x相同的操作
		if (enemy[arr[i].y] != 0)
		{
			Union(arr[i].x, enemy[arr[i].y]);
		}
		else
		{
			enemy[arr[i].y] = arr[i].x;
		}
	}

}

int main()
{
	separateCriminal();
	return 0;
}

