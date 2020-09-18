/*
	���� Ʈ�� ��ȸ ���
	6���� ���� ������ ����Ʈ�� ���� �� ������ȸ, ������ȸ, ������ȸ ��� ���
	�ۼ���: 2020�� 9�� 18��(��)
*/

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define MAX_NODE	6

typedef struct TreeNode {
	int data;
	struct TreeNode *left;
	struct TreeNode *right;
} TreeNode;

void preorder(TreeNode *node)
{
	if (node == NULL)
		return;
	printf("[%d] ", node->data);
	preorder(node->left);
	preorder(node->right);
}

void inorder(TreeNode *node)
{
	if (node == NULL)
		return;
	inorder(node->left);
	printf("[%d] ", node->data);
	inorder(node->right);
}

void postorder(TreeNode *node)
{
	if (node == NULL)
		return;
	postorder(node->left);
	postorder(node->right);
	printf("[%d] ", node->data);
}

void init(TreeNode **node, int data, TreeNode *left, TreeNode *right)
{
	*node = (TreeNode*)malloc(sizeof(TreeNode));
	(*node)->data = data;
	(*node)->left = left;
	(*node)->right = right;
}

int main()
{
	int i;
	TreeNode *n1, *n2, *n3, *n4, *n5, *n6;

	init(&n1, 1, NULL, NULL);
	init(&n2, 4, n1, NULL);
	init(&n3, 16, NULL, NULL);
	init(&n4, 25, NULL, NULL);
	init(&n5, 20, n3, n4);
	init(&n6, 15, n2, n5);

	printf("������ȸ=");
	inorder(n6);
	printf("\n");

	printf("������ȸ=");
	preorder(n6);
	printf("\n");

	printf("������ȸ=");
	postorder(n6);
	printf("\n");

	free(n1);
	free(n2);
	free(n3);
	free(n4);
	free(n5);
	free(n6);
	return 0;
}