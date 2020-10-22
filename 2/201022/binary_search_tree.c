/*
	프로그램명: 이진 탐색 트리
	작성일: 2020년 10월 22일(목)
	학번: 20184014
	이름: 이승준
*/

#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct TreeNode {
	element key;
	struct TreeNode *left, *right;
} TreeNode;

// 순환적인 탐색 함수
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
//	// 트리가 공백이면 새로운 노드를 반환한다.
//	if (node == NULL) return new_node(key);
//
//	// 그렇지 않으면 순환적으로 트리를 내려간다.
//	if (key < node->key)
//		node->left = insert_node(node->left, key);
//	else if (key > node->key)
//		node->right = insert_node(node->right, key);
//	
//	// 변경된 루트 포인터를 반환한다.
//	return node;
//}

// key를 이진 탐색 트리 root에 삽입, 이미 root안에 있으면 삽입되지 않음
void insert_node(TreeNode **root, int key)
{
	TreeNode *p, *t;	// p는 부모노드, t는 현재노드
	TreeNode *n;		// n은 새로운 노드

	t = *root;
	p = NULL;
	// 탐색을 먼저 수행
	while (t != NULL) {
		if (key == t->key) return;
		p = t;
		if (key < t->key) t = t->left;
		else t = t->right;
	}
	// key가 트리 안에 없으므로 삽입 가능
	n = (TreeNode *)malloc(sizeof(TreeNode));
	if (n == NULL) return;
	// 데이터 복사
	n->key = key;
	n->left = n->right = NULL;
	// 부모 노드와 링크 연결
	if (p != NULL)
		if (key < p->key) p->left = n;
		else p->right = n;
	else *root = n;
}

TreeNode * min_value_node(TreeNode * node)
{
	TreeNode * current = node;

	// 맨 왼쪽 단말 노드를 찾으러 내려감
	while (current->left != NULL)
		current = current->left;

	return current;
}

// 이진 탐색 트리와 키가 주어지면 키가 저장된 노드를 삭제하고
// 새로운 루트 노드를 반환한다.
//TreeNode * delete_node(TreeNode * root, int key)
//{
//	if (root == NULL) return root;
//
//	// 만약 키가 루트보다 작으면 왼쪽 서브 트리에 있는 것임
//	if (key < root->key)
//		root->left = delete_node(root->left, key);
//	// 만약 키가 루트보다 크면 오른쪽 서브 트리에 있는 것임
//	else if (key > root->key)
//		root->right = delete_node(root->right, key);
//	// 키가 루트와 같으면 이 노드를 삭제하면 됨
//	else {
//		// 첫 번재나 두 번재 경우
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
//		// 세 번째 경우
//		TreeNode * temp = min_value_node(root->right);
//
//		// 중위 순회시 후계 노드를 복사한다.
//		root->key = temp->key;
//		// 중위 순회시 후계 노드를 삭제한다.
//		root->right = delete_node(root->right, temp->key);
//	}
//	return root;
//}

void delete_node(TreeNode **root, int key)
{
	TreeNode *p, *child, *succ, *succ_p, *t;

	// key를 갖는 노드 t를 탐색, p는 t의 부모노드
	p = NULL;
	t = *root;

	// key를 갖는 노드 t를 탐색한다.
	while (t != NULL && t->key != key) {
		p = t;
		t = (key < t->key) ? t->left : t->right;
	}

	// 탐색이 종료된 시점에 t가 NULL이면 트리안에 key가 없음
	if (t == NULL) {	// 탐색트리에 없는 키
		printf("key is not in the tree");
		return;
	}
	// 첫번째 경우: 단말노드인 경우
	if ((t->left == NULL) && (t->right == NULL)) {
		if (p != NULL) {
				// 부모노드의 자식필드를 NULL로 만든다.
			if (p->left == t)
				p->left = NULL;
			else p->right = NULL;
		}
		else	// 만약 부모노드가 NULL이면 삭제되는 노드가 루트
			*root = NULL;
	}
	// 두번째 경우: 하나의 자식만 가지는 경우
	else if ((t->left == NULL) || (t->right == NULL)) {
		child = (t->left != NULL) ? t->left : t->right;
		if (p != NULL) {
			if (p->left == t)	// 부모를 자식과 연결
				p->left = child;
			else p->right = child;
		}
		else	// 만약 부모노드가 NULL이면 삭제되는 노드가 루트
			*root = child;
	}
	// 세번째 경우: 두개의 자식을 가지는 경우
	else {
		// 오른쪽 서브트리에서 후계자를 찾는다.
		succ_p = t;
		succ = t->right;
		// 후계자를 찾아서 계속 왼쪽으로 이동한다.
		while (succ->left != NULL) {
			succ_p = succ;
			succ = succ->left;
		}
		// 후속자의 부모와 자식을 연결
		if (succ_p->left == succ)
			succ_p->left = succ->right;
		else
			succ_p->right = succ->right;
		// 후속자가 가진 키값을 현재 노드에 복사
		t->key = succ->key;
		// 원래의 후속자 삭제
		t = succ;
	}
	free(t);
}

// 중위 순회
void inorder(TreeNode * root) {
	if (root) {
		inorder(root->left);		// 왼쪽서브트리 순회
		printf("[%d] ", root->key);	// 노드 방문
		inorder(root->right);		// 오른쪽서브트리 순회
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

	printf("이진 탐색 트리 중위 순회 결과\n");
	inorder(root);
	printf("\n\n");
	if (search(root, 30) != NULL)
		printf("이진 탐색 트리에서 30을 발견함\n");
	else
		printf("이진 탐색 트리에서 30을 발견못함\n");

	delete_node(&root, 30);
	inorder(root);
	printf("\n\n");
	return 0;
}