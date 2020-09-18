/*
	이진 트리 연습
	이진 탐색 트리를 이용한 영어사전 프로그램
	작성일: 2020년 9월 18일(금)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define MAX_WORD_SIZE		100
#define MAX_MEANING_SIZE	100

typedef struct element {
	char word[MAX_WORD_SIZE];
	char meaning[MAX_MEANING_SIZE];
} element;

typedef struct TreeNode {
	element key;
	struct TreeNode *left;
	struct TreeNode *right;
} TreeNode;

int compare(element e1, element e2)
{
	return strcmp(e1.word, e2.word);
}

// root 보다 순서 먼저인 알파벳 왼쪽
void insertNode(TreeNode **root, element key)
{
	TreeNode *p, *t;
	TreeNode *n;

	t = *root;
	p = NULL;

	// NULL의 의미! 마지막 노드까지
	while (t != NULL)
	{
		if (compare(key, t->key) == 0)
			return;
		p = t; // p 는 바뀐 t의 부모
		if (compare(key, t->key) < 0)
			t = t->left;
		else
			t = t->right;
	}

	n = (TreeNode *)malloc(sizeof(TreeNode));
	if (n == NULL)
	{
		printf("Memory allocation fail\n");
		exit(1);
	}

	n->key = key;
	n->left = n->right = NULL; // 마지막 노드로 설정

	if (p != NULL)
		if (compare(key, p->key) < 0)
			p->left = n;
		else
			p->right = n;
	else
		*root = n;
}

void display(TreeNode *p)
{
	if (p != NULL)
	{
		display(p->left);
		printf("트리노드(%s: %s)", p->key.word, p->key.meaning);
		display(p->right);
		printf(" -> ");
	}
}

TreeNode* search(TreeNode *root, element key)
{
	TreeNode *p = root;

	while (p != NULL)
	{
		switch (compare(key, p->key))
		{
		case -1:
			p = p->left;
			break;
		case 0:
			return p;
		case 1:
			p = p->right;
			break;
		}
	}

	return p;
}

int main()
{
	char command; // i, d, s, p, q
	element e;
	TreeNode *root = NULL;
	TreeNode *temp;
	FILE *fp;
	fp = fopen("data.txt", "r");
	
	if (fp == NULL)
	{
		printf("File not found error.\n");
		return 0;
	}

	while(!feof(fp))
	{
		fscanf(fp, "%c", &command);

		switch (command)
		{
		case 'i':
			fscanf(fp, "%s %s", e.word, e.meaning);
			insertNode(&root, e);
			printf("%s : %s 입력완료!\n", e.word, e.meaning);
			break;
		case 'd':
			fscanf(fp, "%s", e.word);
			strcpy(e.meaning, ""); // meaning = "";
			//delete_node(&root, e);
			printf("%s 삭제완료!\n", e.word);
			// 다음 시간 구현
			break;
		case 'p':
			display(root);
			printf("\n");
			break;
		case 's':
			fscanf(fp, "%s", e.word);
			strcpy(e.meaning, ""); // for safe code
			temp = search(root, e);
			if (temp != NULL)
				printf("단어 %s의 의미: %s\n", temp->key.word, temp->key.meaning);
			break;
		case 'q':
			printf("Quit dictionary\n");
			exit(1);
			break;
		}
	}

	fclose(fp);
	return 0;
}