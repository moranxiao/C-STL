#include <iostream>
#include <cassert>
#include "BinarySearchTree.hpp"

using namespace moran;
using namespace std;


int main()
{
	//BSTree<int> bst;
	//bst.Insert(42);
	//bst.Insert(17);
	//bst.Insert(93);
	//bst.Insert(58);
	//bst.Insert(26);
	//bst.Insert(74);
	//bst.Insert(11);
	//bst.Insert(88);
	//bst.Insert(39);
	//bst.Insert(65);
	//bst.Erase(42); // 删除根节点
	//assert(!bst.Find(42));
	//bst.Erase(11); // 删除叶子节点
	//assert(!bst.Find(11));


	BSTree<int> bst;

	// 插入测试
	assert(bst.InsertR(42) == true);
	assert(bst.InsertR(17) == true);
	assert(bst.InsertR(93) == true);
	assert(bst.InsertR(58) == true);

	// 查找测试
	assert(bst.FindR(42) == true);
	assert(bst.FindR(99) == false);

	// 删除测试
	assert(bst.EraseR(42) == true); // 删除成功
	assert(bst.FindR(42) == false);  // 查找返回 false
	assert(bst.EraseR(99) == false);  // 删除不存在的元素

	// 继续测试其他元素
	assert(bst.EraseR(11) == false);  // 尝试删除不存在的元素

	bst.InOrder();
	
	BSTree<int> bst1(bst);
	bst1.InOrder();
	BSTree<int> bst2;
	bst2 = bst1;
	bst2.InOrder();

	return 0;
}