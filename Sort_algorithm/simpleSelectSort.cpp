// 简单选择排序 O(N^2)
void  simpleSelect_sort(vector<int>& nums)
{
	if (nums.empty())
		return;

	int len(nums.size()), m(0);

	for (int i = 0; i < len - 1; i++)
	{
		m = i;
		// 循环选择最小数值的下标
		for (int j = i + 1; j < len; j++)
		{
			m = (nums[m] < nums[j] ? m : j);
		}
		// 将当前位置与最小数值进行交换
		if (m != i)
		{
			int temp = nums[i];
			nums[i] = nums[m];
			nums[m] = temp;
		}
	}
}
