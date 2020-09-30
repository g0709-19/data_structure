/*
	���� data.txt(���Ϸ� ������)�� ���������� 2���� ����Ǿ� �ִ�.
	��ȯ�� �ݺ����� �̷���� ���� Ž�� Ʈ���� �����ϰ�
	��� �����͸� �����ϴµ� �ɸ��� �ð��� �� �Ͻÿ�.
	���� ������ Ʈ���� ��ü ��� ������ �� ��������
	���ϴ� �ڵ带 �����Ͽ� ��� �Ͻÿ�.
	���� ������ Ʈ���� ���̸� ���ϴ� �ڵ带 �����Ͽ�
	��� �Ͻÿ�.
	���� ������ Ʈ���� �ܸ� ��尡 �� �������� ���ϴ�
	�ڵ带 �����Ͽ� ��� �Ͻÿ�.

	�ۼ���: 2020�� 9�� 30��(��)
	�й�: 20184014
	�̸�: �̽���
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
	// root �� NULL �̶�� ���� ���� ���� root
	if (root == NULL)
		return createNode(data);
	// root �� NULL �� �ƴ϶�� ���� ��ġ Ž��
	else
	{
		// root �� ������ �����Ϸ��� ���� �۴ٸ� ���� ����, ũ�ٸ� ������ ���� ��ȯ
		if (root->data > data)
			root->left = insertByRecursive(root->left, data);
		else
			root->right = insertByRecursive(root->right, data);
	}
	// ����� root ��ȯ
	return root;
}

void insertByLoop(TreeNode **root, int data)
{
	TreeNode *p, *t;	// �θ�, ���� ���
	TreeNode *newnode;		// ���ο� ���
	
	t = *root;
	p = NULL;

	while (t != NULL)
	{
		// Ʈ���� �̹� ���� �ִٸ� ����
		if (t->data == data)
			return;
		p = t;
		// ���� ����� ������ �����ϴ� ���� �۴ٸ� ���� ���, ũ�ٸ� ������ ���� Ž��
		if (t->data > data)
			t = t->left;
		else
			t = t->right;
	}

	newnode = createNode(data);
	// Ʈ���� ���� �����ٸ� t�� ��������Ƿ� �� �ڸ��� ���ο� ��� ����
	if (p != NULL)
	{
		if (p->data > data)
			p->left = newnode;
		else
			p->right = newnode;
	}
	// p �� NULL �̶�� Ʈ���� �ƹ� ���� ���� ���̹Ƿ� ���ο� ��尡 root
	else
		*root = newnode;
}

int countNode(TreeNode *root)
{
	int count = 0;
	// ��� ����� ������ ��
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
	// root �������� ���� ����Ʈ��, ������ ����Ʈ���� ���̸� ���Ͽ� ū ������ ��ȯ
	if (root != NULL)
		return 1 + getMax(getHeight(root->left), getHeight(root->right));
	return height;
}

int countLeaf(TreeNode *root)
{
	int count = 0;
	if (root != NULL)
	{
		// �ܸ� ����� ��쿡�� ������ ��
		if (root->left == NULL && root->right == NULL)
			return 1;
		// �ܸ� ��尡 �ƴ϶�� ���� ���, ������ ���� �ܸ� ��带 Ž��
		else
			count = countLeaf(root->left) + countLeaf(root->right);
	}
	return count;
}

int main()
{
	int temp;							// ���Ϸκ��� ���� �Է¹ޱ� ���� �ӽ� ����
	int start, end; float runtime;		// ����ð� ������ ���� ����

	TreeNode *root_for_recursive = NULL;
	TreeNode *root_for_loop = NULL;

	FILE *fp = fopen("data.txt", "r");
	if (fp == NULL)
		error("File not found!\n");
	
	// ����ð� ���� ����
	start = clock();

	// ������ ������ ������ �о�鿩 Ʈ���� ��ȯ ��� ����� ����
	while (!feof(fp))
	{
		fscanf(fp, "%d", &temp);
		root_for_recursive = insertByRecursive(root_for_recursive, temp);
	}

	// ����ð� ���� ����
	end = clock();

	// ����ð� ���
	runtime = (float)(end-start)/CLOCKS_PER_SEC;
	printf("��ȯ��� - �ɸ� �ð��� %f�Դϴ�\n", runtime);

	rewind(fp);

	// ����ð� ���� ����
	start = clock();

	// ������ ������ ������ �о�鿩 Ʈ���� �ݺ� ��� ����� ����
	while (!feof(fp))
	{
		fscanf(fp, "%d", &temp);
		insertByLoop(&root_for_loop, temp);
	}

	// ����ð� ���� ����
	end = clock();

	// ����ð� ���
	runtime = (float)(end-start)/CLOCKS_PER_SEC;
	printf("�ݺ���� - �ɸ� �ð��� %f�Դϴ�\n", runtime);

	printf("\n");

	// ��� ����, ����, �ܸ���� ���� ���
	printf("��ü ����� ������ %d���Դϴ�\n", countNode(root_for_recursive));
	printf("��ü ���̴� %d�Դϴ�\n", getHeight(root_for_recursive));
	printf("��ü �ܸ������ ������ %d���Դϴ�\n", countLeaf(root_for_recursive));

	fclose(fp);
	return 0;
}