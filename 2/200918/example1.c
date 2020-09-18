/*
	���� Ʈ�� ����
	3���� ���� ������ ����Ʈ�� ����
	�ۼ���: 2020�� 9�� 18��(��)
*/

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct TreeNode {
	int data;
	struct TreeNode *left;
	struct TreeNode *right;
} TreeNode;

void init(TreeNode **node, int data, TreeNode *left, TreeNode *right)
{
	*node = (TreeNode*)malloc(sizeof(TreeNode));
	(*node)->data = data;
	(*node)->left = left;
	(*node)->right = right;
}

int main()
{
	TreeNode *n1, *n2, *n3;

	init(&n2, 20, NULL, NULL);
	init(&n3, 30, NULL, NULL);
	init(&n1, 10, n2, n3);
	
	free(n1);
	free(n2);
	free(n3);
	return 0;
}