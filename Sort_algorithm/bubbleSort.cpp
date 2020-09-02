//冒泡排序 O(N^2)
void bubble_sort(vector<int>& nums)
{
	if (nums.empty())
		return ;

	int len(nums.size());
	bool flag = true;

	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len - i - 1; j++)
		{
			if (nums[j] > nums[j+1])
			{
				int tmp = nums[j];
				nums[j] = nums[j+1];
				nums[j + 1] = tmp;

				// 标志符，如果没有交换说明数组有序
				flag = false;
			}
		}

		if (flag)
			break;
	}
}
