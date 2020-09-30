/*
	파일 data.txt(파일로 제공됨)에 정수값들이 2만개 저장되어 있다.
	순환과 반복으로 이루어진 이진 탐색 트리를 구현하고
	모든 데이터를 삽입하는데 걸리는 시간을 비교 하시오.
	현재 구성된 트리의 전체 노드 개수가 몇 개인지를
	구하는 코드를 구현하여 출력 하시오.
	현재 구성된 트리의 높이를 구하는 코드를 구현하여
	출력 하시오.
	현재 구성된 트리의 단말 노드가 몇 개인지를 구하는
	코드를 구현하여 출력 하시오.

	작성일: 2020년 9월 30일(수)
	학번: 20184014
	이름: 이승준
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void error(char *message)
{
	fprintf(stderr, message);
	exit(1);
}

typedef struct TreeNode {
	int data;
	struct TreeNode *left, *right;
} TreeNode;

TreeNode* createNode(int data)
{
	TreeNode *newnode = (TreeNode*)malloc(sizeof(TreeNode));
	if (newnode == NULL)
		error("Memory allocation error!\n");
	newnode->data = data;
	newnode->left = newnode->right = NULL;
	return newnode;
}

TreeNode* insertByRecursive(TreeNode *root, int data)
{
	// root 가 NULL 이라면 새로 만든 값이 root
	if (root == NULL)
		return createNode(data);
	// root 가 NULL 이 아니라면 삽입 위치 탐색
	else
	{
		// root 의 값보다 삽입하려는 값이 작다면 왼쪽 노드로, 크다면 오른쪽 노드로 순환
		if (root->data > data)
			root->left = insertByRecursive(root->left, data);
		else
			root->right = insertByRecursive(root->right, data);
	}
	// 변경된 root 반환
	return root;
}

void insertByLoop(TreeNode **root, int data)
{
	TreeNode *p, *t;	// 부모, 현재 노드
	TreeNode *newnode;		// 새로운 노드
	
	t = *root;
	p = NULL;

	while (t != NULL)
	{
		// 트리에 이미 값이 있다면 종료
		if (t->data == data)
			return;
		p = t;
		// 현재 노드의 값보다 삽입하는 값이 작다면 왼쪽 노드, 크다면 오른쪽 노드로 탐색
		if (t->data > data)
			t = t->left;
		else
			t = t->right;
	}

	newnode = createNode(data);
	// 트리에 값이 없었다면 t가 비어있으므로 그 자리에 새로운 노드 삽입
	if (p != NULL)
	{
		if (p->data > data)
			p->left = newnode;
		else
			p->right = newnode;
	}
	// p 가 NULL 이라면 트리에 아무 값도 없던 것이므로 새로운 노드가 root
	else
		*root = newnode;
}

int countNode(TreeNode *root)
{
	int count = 0;
	// 모든 노드의 개수를 셈
	if (root != NULL)
		count = 1 + countNode(root->left) + countNode(root->right);
	return count;
}

int getMax(int num1, int num2)
{
	return num1 > num2 ? num1 : num2;
}

int getHeight(TreeNode *root)
{
	int height = 0;
	// root 기준으로 왼쪽 서브트리, 오른쪽 서브트리의 높이를 구하여 큰 쪽으로 반환
	if (root != NULL)
		return 1 + getMax(getHeight(root->left), getHeight(root->right));
	return height;
}

int countLeaf(TreeNode *root)
{
	int count = 0;
	if (root != NULL)
	{
		// 단말 노드일 경우에만 개수를 셈
		if (root->left == NULL && root->right == NULL)
			return 1;
		// 단말 노드가 아니라면 왼쪽 노드, 오른쪽 노드로 단말 노드를 탐색
		else
			count = countLeaf(root->left) + countLeaf(root->right);
	}
	return count;
}

int main()
{
	int temp;							// 파일로부터 값을 입력받기 위한 임시 변수
	int start, end; float runtime;		// 실행시간 측정을 위한 변수

	TreeNode *root_for_recursive = NULL;
	TreeNode *root_for_loop = NULL;

	FILE *fp = fopen("data.txt", "r");
	if (fp == NULL)
		error("File not found!\n");
	
	// 실행시간 측정 시작
	start = clock();

	// 파일의 끝까지 정수를 읽어들여 트리에 순환 방법 사용한 삽입
	while (!feof(fp))
	{
		fscanf(fp, "%d", &temp);
		root_for_recursive = insertByRecursive(root_for_recursive, temp);
	}

	// 실행시간 측정 종료
	end = clock();

	// 실행시간 출력
	runtime = (float)(end-start)/CLOCKS_PER_SEC;
	printf("순환방법 - 걸린 시간은 %f입니다\n", runtime);

	rewind(fp);

	// 실행시간 측정 시작
	start = clock();

	// 파일의 끝까지 정수를 읽어들여 트리에 반복 방법 사용한 삽입
	while (!feof(fp))
	{
		fscanf(fp, "%d", &temp);
		insertByLoop(&root_for_loop, temp);
	}

	// 실행시간 측정 종료
	end = clock();

	// 실행시간 출력
	runtime = (float)(end-start)/CLOCKS_PER_SEC;
	printf("반복방법 - 걸린 시간은 %f입니다\n", runtime);

	printf("\n");

	// 노드 개수, 높이, 단말노드 개수 출력
	printf("전체 노드의 개수는 %d개입니다\n", countNode(root_for_recursive));
	printf("전체 높이는 %d입니다\n", getHeight(root_for_recursive));
	printf("전체 단말노드의 개수는 %d개입니다\n", countLeaf(root_for_recursive));

	fclose(fp);
	return 0;
}