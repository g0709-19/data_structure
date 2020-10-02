/*
	프로그램명: 완전 이진 트리 검증 프로그램
	작성일: 2020년 10월 2일(금)
	학번: 20184014
	이름: 이승준
*/

#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct TreeNode {
	element data;
	struct TreeNode *left, *right;
} TreeNode;

void error(char *message)
{
	fprintf(stderr, "%s", message);
	exit(1);
}

int max(int num1, int num2)
{
	return num1 > num2 ? num1 : num2;
}

void insertNode(TreeNode **root, int key)
{
	TreeNode *p, *t; // parent, traverse
	TreeNode *newnode;

	t = *root;
	p = NULL;

	while (t != NULL)
	{
		if (t->data == key) return;
		p = t;
		if (t->data > key) t = t->left;
		else t = t->right;
	}

	newnode = (TreeNode*)malloc(sizeof(TreeNode));
	if (newnode == NULL)
		error("Memory Allocation Error!\n");
	newnode->data = key;
	newnode->left = newnode->right = NULL;

	if (p != NULL)
	{
		if (p->data > key)
			p->left = newnode;
		else
			p->right = newnode;
	}
	else
		*root = newnode;
}

void preorder(TreeNode *root)
{
	if (root != NULL)
	{
		printf("%d ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

int power(int x)
{
	int i, result = 1;

	for (i=0; i<x; ++i)
		result *= 2;
	
	return result;
}

int countLeaf(TreeNode *root)
{
	if (root->left == NULL && root->right == NULL)
		return 1;
	else
		return countLeaf(root->left) + countLeaf(root->right);
}

int getHeight(TreeNode *root)
{
	if (root == NULL)
		return 0;
	else
		return 1 + max(getHeight(root->left), getHeight(root->right));
}

int main()
{
	element e;
	TreeNode *root = NULL;
	TreeNode *temp;

	FILE *fp;
	fp = fopen("data2.txt", "r");
	if (fp == NULL)
		error("File Not Found!\n");

	while (!feof(fp))
	{
		fscanf(fp, "%d", &e);

		insertNode(&root, e);
		printf("inserted %d\n", e);
	}

	printf("preorder >> ");
	preorder(root);

	// 완전 이진 트리 검증 루틴 추가
	if (power(getHeight(root) - 1) == countLeaf(root))
		printf("\n\n완전 이진 트리입니다.\n\n");
	else
		printf("\n\n완전 이진 트리가 아닙니다.\n\n");


	fclose(fp);
	return 0;
}