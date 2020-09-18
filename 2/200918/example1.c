/*
	이진 트리 연습
	3개의 노드로 구성된 이진트리 구현
	작성일: 2020년 9월 18일(금)
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