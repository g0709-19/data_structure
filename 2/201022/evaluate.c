/*
	프로그램명: 수식 트리 계산
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

TreeNode n1 = { 1, NULL, NULL };
TreeNode n2 = { 4, NULL, NULL };
TreeNode n3 = { '*', &n1, &n2 };
TreeNode n4 = { 16, NULL, NULL };
TreeNode n5 = { 25, NULL, NULL };
TreeNode n6 = { '+', &n4, &n5 };
TreeNode n7 = { '+', &n3, &n6 };
TreeNode *exp = &n7;

// 수식 계산 함수
int evaluate(TreeNode *root)
{
	if (root == NULL)	return 0;
	// 단말 노드라면 피연산자
	if (root->left == NULL && root->right == NULL)	return root->data;
	else {
		int op1 = evaluate(root->left);
		int op2 = evaluate(root->right);
		printf("%d %c %d을 계산합니다.\n", op1, root->data, op2);
		switch (root->data) {
		case '+':	return op1 + op2;
		case '-':	return op1 - op2;
		case '*':	return op1 * op2;
		case '/':	return op1 / op2;
		}
	}
	return 0;
}

int main()
{
	printf("수식의 값은 %d입니다.\n", evaluate(exp));
	return 0;
}