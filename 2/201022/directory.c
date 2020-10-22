/*
	프로그램명: 디렉토리 용량 계산
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

// 용량 계산 함수
int calc_dir_size(TreeNode *root)
{
	int left_size, right_size;
	if (root == NULL) return 0;

	left_size = calc_dir_size(root->left);
	right_size = calc_dir_size(root->right);
	return (root->data + left_size + right_size);
}

int main()
{
	TreeNode n4 = { 500, NULL, NULL };
	TreeNode n5 = { 200, NULL, NULL };
	TreeNode n3 = { 100, &n4, &n5 };
	TreeNode n2 = { 50, NULL, NULL };
	TreeNode n1 = { 0, &n2, &n3 };

	printf("디렉토리의 크기=%d\n", calc_dir_size(&n1));
	return 0;
}