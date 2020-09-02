// 归并排序
void merge_sort(vector<int>& nums);								// 归并排序主函数
void process(vector<int>& nums, int left, int right);			// 递归函数
void merge(vector<int>& nums, int left, int mid, int right);	// 合并函数

void merge_sort(vector<int>& nums)
{
	if (nums.empty() || nums.size() < 2) // 异常判断
		return;

	process(nums, 0, nums.size() - 1);
}

void process(vector<int>& nums, int left, int right)
{
	if (left == right)
		return;

	int mid = left + ((right - left) >> 1);	// 寻找中位数
	process(nums, left, mid);				// 递归左子数组
	process(nums, mid + 1, right);			// 递归右子数组
	merge(nums, left, mid, right);			// 将左右子数组合并
}

void merge(vector<int>& nums, int left, int mid, int right)
{
	vector<int> tmp(right - left + 1, 0);	// 创建临时数组保存合并数值
	int i(0), l(left), r(mid + 1);

	while (l <= mid && r <= right)			// 左右子数组有序合并
	{
		tmp[i++] = (nums[l] <= nums[r] ? nums[l++] : nums[r++]);
	}

	while (l <= mid)						// 左子数组有剩余数据
	{
		tmp[i++] = nums[l++];
	}
	while (r <= right)						// 右子数组有剩余数据
	{
		tmp[i++] = nums[r++];
	}

	for (int j = 0; j < tmp.size(); j++)	// 从临时数组中拷贝有序数据至原始数组中
	{
		nums[left + j] = tmp[j];
	}
}
