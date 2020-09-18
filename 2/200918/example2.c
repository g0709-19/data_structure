/*
	이진 트리 순회 방법
	6개의 노드로 구성된 이진트리 구현 및 전위순회, 중위순회, 후위순회 결과 출력
	작성일: 2020년 9월 18일(금)
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

	printf("중위순회=");
	inorder(n6);
	printf("\n");

	printf("전위순회=");
	preorder(n6);
	printf("\n");

	printf("후위순회=");
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