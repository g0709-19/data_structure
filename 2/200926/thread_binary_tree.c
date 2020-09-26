/*
	중위 후속자(Inorder successor)를 이용한 스레드 이진 트리(Thread binary tree)
	단말 노드의 오른쪽 자식은 중위 후속자를 가지고 있기 때문에
	find_successor 함수를 이용해 중위 후속자로 가서 출력을 이어나갈 수 있다.
	단말 노드인지 아닌지 검사하기 위해 오른쪽 노드가 NULL인가? 또는 is_thread 가 TRUE 인가? 여부 확인
	E는 단말 노드지만 다음에 출력할 노드가 없기 때문에 특별히 오른쪽 자식을 가지지 않는다.
*/

#include <stdio.h>

#define TRUE	1
#define FALSE	0

typedef struct TreeNode {
	int data;
	struct TreeNode *left, *right;
	int is_thread;	// 스레드이면 TRUE
} TreeNode;

//		G
//	C		F
//A	 B	  D	 E
TreeNode n1 = { 'A', NULL, NULL, 1 };
TreeNode n2 = { 'B', NULL, NULL, 1 };
TreeNode n3 = { 'C', &n1, &n2, 0 };
TreeNode n4 = { 'D', NULL, NULL, 1 };
TreeNode n5 = { 'E', NULL, NULL, 0 };
TreeNode n6 = { 'F', &n4, &n5, 0 };
TreeNode n7 = { 'G', &n3, &n6, 0 };
TreeNode* exp = &n7;

TreeNode* find_successor(TreeNode* p)
{
	// q는 p의 오른쪽 포인터
	TreeNode* q = p->right;
	// 만약 오른쪽 포인터가 NULL이거나 스레드이면 오른쪽 포인터를 반환
	if (q == NULL || p->is_thread == TRUE)
		return q;

	// 만약 오른쪽 자식이면 다시 가장 왼쪽 노드로 이동
	while (q->left != NULL) q = q->left;
	return q;
}

void thread_inorder(TreeNode* t)
{
	TreeNode* q;
	q = t;
	while (q->left) q = q->left;	// 가장 왼쪽 노드로 간다.
	do {
		printf("%c -> ", q->data);	// 데이터 출력
		q = find_successor(q);
	} while (q);
}

int main()
{
	// 스레드 설정
	n1.right = &n3; // A의 중위 후속자는 C
	n2.right = &n7;	// B의 중위 후속자는 G, B 다음에 불러올건 G기 때문에
	n4.right = &n6;	// D의 중위 후속자는 F
	// 중위 순회
	thread_inorder(exp);
	printf("\n");
	return 0;
} 