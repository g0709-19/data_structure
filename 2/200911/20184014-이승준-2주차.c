/*
	프로그램명: MP3 재생 프로그램
	작성자: 이승준
	학번: 20184014
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char element[100]; // 곡명을 저장하기 위한 공간

typedef struct DListNode {
	element data;
	// Self referencial pointer
	struct DListNode *llink;	// 이전 곡
	struct DListNode *rlink;	// 다음 곡
} DListNode;

DListNode *current;				// 현재 곡

void init(DListNode *head)
{
	head->llink = head;
	head->rlink = head;
}

void printDList(DListNode *head)
{
	DListNode *p;
	// Head 는 무조건 앞에 있으면서 값을 가지지 않는
	// 기준점 역할을 하기 때문에 rlink 부터 참조
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
	new_node->rlink = before->rlink; // 기존에 있던 노드를 밀어냄
	before->rlink->llink = new_node; // 기존에 있던 노드의 왼쪽 노드를 새로운 노드로 변경
	before->rlink = new_node;
}

void dDelete(DListNode *head, DListNode *removed)
{
	// Head 는 계속 유지해야 함
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
		printf("\n명령어를 입력하세요( <, >, q ) : ");
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