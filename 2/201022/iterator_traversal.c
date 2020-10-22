/*
	프로그램명: 반복적 순회
	작성일: 2020년 10월 22일(목)
	학번: 20184014
	이름: 이승준
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

// Stack push 함수
void push(TreeNode *p)
{
	if (top < SIZE - 1)
		stack[++top] = p;
}

// Stack pop 함수 (LIFO)
TreeNode *pop()
{
	TreeNode *p = NULL;
	if (top >= 0)
		p = stack[top--];
	return p;
}

// 스택을 이용한 이진 트리 반복적 중위 순회
void inorder_iter(TreeNode *root)
{
	while (1) {
		// 왼쪽 노드를 타고 내려가면서 전부 스택에 삽입
		for (; root; root = root->left)
			push(root);
		// 꺼낸 값은 마지막 왼쪽 노드
		root = pop();
		// 꺼낸 값이 NULL 이라면 break
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
	printf("중위 순회=");
	inorder_iter(root);
	printf("\n");
	return 0;
}