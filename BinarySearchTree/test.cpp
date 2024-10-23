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
	//bst.Erase(42); // ɾ�����ڵ�
	//assert(!bst.Find(42));
	//bst.Erase(11); // ɾ��Ҷ�ӽڵ�
	//assert(!bst.Find(11));


	BSTree<int> bst;

	// �������
	assert(bst.InsertR(42) == true);
	assert(bst.InsertR(17) == true);
	assert(bst.InsertR(93) == true);
	assert(bst.InsertR(58) == true);

	// ���Ҳ���
	assert(bst.FindR(42) == true);
	assert(bst.FindR(99) == false);

	// ɾ������
	assert(bst.EraseR(42) == true); // ɾ���ɹ�
	assert(bst.FindR(42) == false);  // ���ҷ��� false
	assert(bst.EraseR(99) == false);  // ɾ�������ڵ�Ԫ��

	// ������������Ԫ��
	assert(bst.EraseR(11) == false);  // ����ɾ�������ڵ�Ԫ��

	bst.InOrder();
	
	BSTree<int> bst1(bst);
	bst1.InOrder();
	BSTree<int> bst2;
	bst2 = bst1;
	bst2.InOrder();

	return 0;
}