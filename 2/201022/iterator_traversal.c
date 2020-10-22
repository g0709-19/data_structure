/*
	���α׷���: �ݺ��� ��ȸ
	�ۼ���: 2020�� 10�� 22��(��)
	�й�: 20184014
	�̸�: �̽���
*/

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct TreeNode {
	int data;
	struct TreeNode *left, *right;
} TreeNode;

#define SIZE	100
int top = -1;
TreeNode *stack[SIZE];

// Stack push �Լ�
void push(TreeNode *p)
{
	if (top < SIZE - 1)
		stack[++top] = p;
}

// Stack pop �Լ� (LIFO)
TreeNode *pop()
{
	TreeNode *p = NULL;
	if (top >= 0)
		p = stack[top--];
	return p;
}

// ������ �̿��� ���� Ʈ�� �ݺ��� ���� ��ȸ
void inorder_iter(TreeNode *root)
{
	while (1) {
		// ���� ��带 Ÿ�� �������鼭 ���� ���ÿ� ����
		for (; root; root = root->left)
			push(root);
		// ���� ���� ������ ���� ���
		root = pop();
		// ���� ���� NULL �̶�� break
		if (!root) break;
		printf("[%d] ", root->data);
		root = root->right;
	}
}

TreeNode n1 = { 1, NULL, NULL };
TreeNode n2 = { 4, &n1, NULL };
TreeNode n3 = { 16, NULL, NULL };
TreeNode n4 = { 25, NULL, NULL };
TreeNode n5 = { 20, &n3, &n4 };
TreeNode n6 = { 15, &n2, &n5 };
TreeNode *root = &n6;

int main()
{
	printf("���� ��ȸ=");
	inorder_iter(root);
	printf("\n");
	return 0;
}