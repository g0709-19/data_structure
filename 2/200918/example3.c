/*
	���� Ʈ�� ����
	���� Ž�� Ʈ���� �̿��� ������� ���α׷�
	�ۼ���: 2020�� 9�� 18��(��)
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

// root ���� ���� ������ ���ĺ� ����
void insertNode(TreeNode **root, element key)
{
	TreeNode *p, *t;
	TreeNode *n;

	t = *root;
	p = NULL;

	// NULL�� �ǹ�! ������ ������
	while (t != NULL)
	{
		if (compare(key, t->key) == 0)
			return;
		p = t; // p �� �ٲ� t�� �θ�
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
	n->left = n->right = NULL; // ������ ���� ����

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
		printf("Ʈ�����(%s: %s)", p->key.word, p->key.meaning);
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
			printf("%s : %s �Է¿Ϸ�!\n", e.word, e.meaning);
			break;
		case 'd':
			fscanf(fp, "%s", e.word);
			strcpy(e.meaning, ""); // meaning = "";
			//delete_node(&root, e);
			printf("%s �����Ϸ�!\n", e.word);
			// ���� �ð� ����
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
				printf("�ܾ� %s�� �ǹ�: %s\n", temp->key.word, temp->key.meaning);
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