//归并排序（循环写法）
void Merge(vector<int>& nums, int start, int mid, int end);
void MergeSort(vector<int>& nums) 
{
	int length = nums.size();
	//i每次乘2，是因为每次合并以后小组元素也变成两倍个了
	for (int i = 1; i < length; i *= 2) 
	{
		//对拥有2的幂次方个数值的小组进行两两合并
		int index = 0;
		while (2 * i + index <= length) 
		{
			index += 2 * i;
			Merge(nums, index - 2 * i, index - i, index);
		}

		//index+i<length 说明剩余两个小组，但其中一个小组数据的数量不满足2的幂次个，对两个小组进行合并
		if (index + i < length) 
		{
			Merge(nums, index, index + i, length);
		}
	}
}

void Merge(vector<int>& nums, int start, int mid, int end) {
	//需要一个临时数组来存放排序好的数据
	vector<int> temp(end - start, 0);

	// 对分割数列进行归并
	int i = start, j = mid, index = 0;

	while (index + start < end) 
	{
		//从两个子序列中取出数据放入临时数组
		if (i < mid && (j == end || nums[i] < nums[j])) 
		{
			temp[index++] = nums[i++];
		}
		else 
		{
			temp[index++] = nums[j++];
		}
	}

	//将临时数组的值重现赋给数组
	for (int i = start; i < end; i++) 
	{
		nums[i] = temp[i - start];
	}
}
