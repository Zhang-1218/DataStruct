问题：
一个矩阵中只有0和1两种值，每个位置都可以和自己的上下左右四个位置相连，如果有一片1连在一起，这个部分叫做一个岛，求一个矩阵中有多少个岛？

举例：
{ 0, 0, 1, 0, 1, 0 }
{ 1, 1, 1, 0, 1, 0 }
{ 1, 0, 0, 1, 0, 0 }
{ 0, 0, 0, 0, 0, 0 }
这个矩阵中有三个岛。

进阶
如果设计一个并行算法解决这个问题。

思路：
使用并查集（多任务，并行计算）
	* 将一个大矩阵化成多个小矩阵，然后不同的CPU处理不同的矩阵，最后将不同的矩阵合并。
	* 边界问题，将边界上连成一片的1合并

 在小矩阵中，第一个1作为头结点，后面1连成一片的1都挂在头结点下。然后在解决边界时，若两个1碰到一起了，就检查两个1的头结点是不是一样的，不一样的话，就合并两个集合，同时岛的个数-1；一样的话，证明之前已经合并过了，岛的个数不变
