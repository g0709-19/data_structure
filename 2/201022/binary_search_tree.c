/*
	���α׷���: ���� Ž�� Ʈ��
	�ۼ���: 2020�� 10�� 22��(��)
	�й�: 20184014
	�̸�: �̽���
*/

#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct TreeNode {
	element key;
	struct TreeNode *left, *right;
} TreeNode;

// ��ȯ���� Ž�� �Լ�
TreeNode * search(TreeNode * node, int key)
{
	if (node == NULL) return NULL;
	if (key == node->key) return node;
	else if (key < node->key)
		return search(node->left, key);
	else
		return search(node->right, key);
}

TreeNode * new_node(int item)
{
	TreeNode * temp = (TreeNode *)malloc(sizeof(TreeNode));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}

//TreeNode * insert_node(TreeNode * node, int key)
//{
//	// Ʈ���� �����̸� ���ο� ��带 ��ȯ�Ѵ�.
//	if (node == NULL) return new_node(key);
//
//	// �׷��� ������ ��ȯ������ Ʈ���� ��������.
//	if (key < node->key)
//		node->left = insert_node(node->left, key);
//	else if (key > node->key)
//		node->right = insert_node(node->right, key);
//	
//	// ����� ��Ʈ �����͸� ��ȯ�Ѵ�.
//	return node;
//}

// key�� ���� Ž�� Ʈ�� root�� ����, �̹� root�ȿ� ������ ���Ե��� ����
void insert_node(TreeNode **root, int key)
{
	TreeNode *p, *t;	// p�� �θ���, t�� ������
	TreeNode *n;		// n�� ���ο� ���

	t = *root;
	p = NULL;
	// Ž���� ���� ����
	while (t != NULL) {
		if (key == t->key) return;
		p = t;
		if (key < t->key) t = t->left;
		else t = t->right;
	}
	// key�� Ʈ�� �ȿ� �����Ƿ� ���� ����
	n = (TreeNode *)malloc(sizeof(TreeNode));
	if (n == NULL) return;
	// ������ ����
	n->key = key;
	n->left = n->right = NULL;
	// �θ� ���� ��ũ ����
	if (p != NULL)
		if (key < p->key) p->left = n;
		else p->right = n;
	else *root = n;
}

TreeNode * min_value_node(TreeNode * node)
{
	TreeNode * current = node;

	// �� ���� �ܸ� ��带 ã���� ������
	while (current->left != NULL)
		current = current->left;

	return current;
}

// ���� Ž�� Ʈ���� Ű�� �־����� Ű�� ����� ��带 �����ϰ�
// ���ο� ��Ʈ ��带 ��ȯ�Ѵ�.
//TreeNode * delete_node(TreeNode * root, int key)
//{
//	if (root == NULL) return root;
//
//	// ���� Ű�� ��Ʈ���� ������ ���� ���� Ʈ���� �ִ� ����
//	if (key < root->key)
//		root->left = delete_node(root->left, key);
//	// ���� Ű�� ��Ʈ���� ũ�� ������ ���� Ʈ���� �ִ� ����
//	else if (key > root->key)
//		root->right = delete_node(root->right, key);
//	// Ű�� ��Ʈ�� ������ �� ��带 �����ϸ� ��
//	else {
//		// ù ���糪 �� ���� ���
//		if (root->left == NULL) {
//			TreeNode * temp = root->right;
//			free(root);
//			return temp;
//		}
//		else if (root->right == NULL) {
//			TreeNode * temp = root->left;
//			free(root);
//			return temp;
//		}
//		// �� ��° ���
//		TreeNode * temp = min_value_node(root->right);
//
//		// ���� ��ȸ�� �İ� ��带 �����Ѵ�.
//		root->key = temp->key;
//		// ���� ��ȸ�� �İ� ��带 �����Ѵ�.
//		root->right = delete_node(root->right, temp->key);
//	}
//	return root;
//}

void delete_node(TreeNode **root, int key)
{
	TreeNode *p, *child, *succ, *succ_p, *t;

	// key�� ���� ��� t�� Ž��, p�� t�� �θ���
	p = NULL;
	t = *root;

	// key�� ���� ��� t�� Ž���Ѵ�.
	while (t != NULL && t->key != key) {
		p = t;
		t = (key < t->key) ? t->left : t->right;
	}

	// Ž���� ����� ������ t�� NULL�̸� Ʈ���ȿ� key�� ����
	if (t == NULL) {	// Ž��Ʈ���� ���� Ű
		printf("key is not in the tree");
		return;
	}
	// ù��° ���: �ܸ������ ���
	if ((t->left == NULL) && (t->right == NULL)) {
		if (p != NULL) {
				// �θ����� �ڽ��ʵ带 NULL�� �����.
			if (p->left == t)
				p->left = NULL;
			else p->right = NULL;
		}
		else	// ���� �θ��尡 NULL�̸� �����Ǵ� ��尡 ��Ʈ
			*root = NULL;
	}
	// �ι�° ���: �ϳ��� �ڽĸ� ������ ���
	else if ((t->left == NULL) || (t->right == NULL)) {
		child = (t->left != NULL) ? t->left : t->right;
		if (p != NULL) {
			if (p->left == t)	// �θ� �ڽİ� ����
				p->left = child;
			else p->right = child;
		}
		else	// ���� �θ��尡 NULL�̸� �����Ǵ� ��尡 ��Ʈ
			*root = child;
	}
	// ����° ���: �ΰ��� �ڽ��� ������ ���
	else {
		// ������ ����Ʈ������ �İ��ڸ� ã�´�.
		succ_p = t;
		succ = t->right;
		// �İ��ڸ� ã�Ƽ� ��� �������� �̵��Ѵ�.
		while (succ->left != NULL) {
			succ_p = succ;
			succ = succ->left;
		}
		// �ļ����� �θ�� �ڽ��� ����
		if (succ_p->left == succ)
			succ_p->left = succ->right;
		else
			succ_p->right = succ->right;
		// �ļ��ڰ� ���� Ű���� ���� ��忡 ����
		t->key = succ->key;
		// ������ �ļ��� ����
		t = succ;
	}
	free(t);
}

// ���� ��ȸ
void inorder(TreeNode * root) {
	if (root) {
		inorder(root->left);		// ���ʼ���Ʈ�� ��ȸ
		printf("[%d] ", root->key);	// ��� �湮
		inorder(root->right);		// �����ʼ���Ʈ�� ��ȸ
	}
}

int main()
{
	TreeNode * root = NULL;
	TreeNode * temp = NULL;

	//root = insert_node(root, 30);
	//root = insert_node(root, 20);
	//root = insert_node(root, 10);
	//root = insert_node(root, 40);
	//root = insert_node(root, 50);
	//root = insert_node(root, 60);

	insert_node(&root, 30);
	insert_node(&root, 20);
	insert_node(&root, 10);
	insert_node(&root, 40);
	insert_node(&root, 50);
	insert_node(&root, 60);

	printf("���� Ž�� Ʈ�� ���� ��ȸ ���\n");
	inorder(root);
	printf("\n\n");
	if (search(root, 30) != NULL)
		printf("���� Ž�� Ʈ������ 30�� �߰���\n");
	else
		printf("���� Ž�� Ʈ������ 30�� �߰߸���\n");

	delete_node(&root, 30);
	inorder(root);
	printf("\n\n");
	return 0;
}