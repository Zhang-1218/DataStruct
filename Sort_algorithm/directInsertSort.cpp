// 直接插入排序 O(N^2)
void  directInsert_sort(vector<int>& nums)
{
	if (nums.empty())
		return;

	int len(nums.size()), tmp(0), i(0), j(0);

	for (i = 1; i < len; i++)
	{
		// 如果要插入的数据比当前排序好的序列最后一位大，不做操作
		if (nums[i-1] < nums[i])
			continue;

		// 保存要插入的数据
		tmp = nums[i];
			
		// 在前面已经排好序的序列中寻找要插入的位置，注意边界问题
		for (j = i - 1; j >= 0 && nums[j] > tmp; j--)
		{
			nums[j + 1] = nums[j];
		}
		nums[j + 1] = tmp;
	}
}
