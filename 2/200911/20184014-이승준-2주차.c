/*
	���α׷���: MP3 ��� ���α׷�
	�ۼ���: �̽���
	�й�: 20184014
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char element[100]; // ����� �����ϱ� ���� ����

typedef struct DListNode {
	element data;
	// Self referencial pointer
	struct DListNode *llink;	// ���� ��
	struct DListNode *rlink;	// ���� ��
} DListNode;

DListNode *current;				// ���� ��

void init(DListNode *head)
{
	head->llink = head;
	head->rlink = head;
}

void printDList(DListNode *head)
{
	DListNode *p;
	// Head �� ������ �տ� �����鼭 ���� ������ �ʴ�
	// ������ ������ �ϱ� ������ rlink ���� ����
	for (p=head->rlink; p!=head; p=p->rlink)
	{
		if (p == current)
			printf("<-| #%s# |->", p->data);
		else
			printf("<-| %s |->", p->data);
	}
	printf("\n");
}

void dInsert(DListNode *before, element data)
{
	DListNode *new_node = (DListNode*)malloc(sizeof(DListNode));
	if (new_node == NULL)
	{
		printf("Memory allocation failure\n");
		exit(0);
	}

	strcpy(new_node->data, data);
	new_node->llink = before;
	new_node->rlink = before->rlink; // ������ �ִ� ��带 �о
	before->rlink->llink = new_node; // ������ �ִ� ����� ���� ��带 ���ο� ���� ����
	before->rlink = new_node;
}

void dDelete(DListNode *head, DListNode *removed)
{
	// Head �� ��� �����ؾ� ��
	if (removed == head)
		return;
	else
	{
		removed->rlink->llink = removed->llink;
		removed->llink->rlink = removed->rlink;
		
		free(removed);
	}
}

int main()
{
	char ch;
	DListNode *head = (DListNode*)malloc(sizeof(DListNode));
	init(head);

	dInsert(head, "Mamamia");
	dInsert(head, "Dancing Queen");
	dInsert(head, "Fernando");
	
	current = head->rlink;
	printDList(head);

	do
	{
		printf("\n��ɾ �Է��ϼ���( <, >, q ) : ");
		ch = getchar();

		switch (ch)
		{
		case '<':
			current = current->llink;
			if (current == head)
				current = current->llink;
			break;
		case '>':
			current = current->rlink;
			if (current == head)
				current = current->rlink;
			break;
		}

		printDList(head);
		getchar();
	} while(ch != 'q');

	return 0;
}