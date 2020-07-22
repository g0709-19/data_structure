/*
	설명: 연결 리스트를 이용하여 2개의 다항식을 곱하는 곱셈 연산을 구현하는 프로그램
	이름: 이승준
*/

#include <stdio.h>
#include <stdlib.h>

// 연결 리스트 노드
typedef struct ListNode
{
	int coef;	// 계수
	int ex;		// 지수
	struct ListNode *link; // 다음 노드
} ListNode;

// 연결 리스트 헤더
typedef struct ListType
{
	int size;
	ListNode *head;
	ListNode *tail;
} ListType;

void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// 리스트 헤더 생성 
ListType* create()
{
	ListType *plist = (ListType*)malloc(sizeof(ListType));
	plist->size = 0;
	plist->head = plist->tail = NULL;
	return plist;
}

// 리스트에 계수, 지수 삽입하되 높은 차수를 맨 앞으로 정렬하고 같은 차수가 있으면 더해줘야 함
void insert(ListType *plist, int coef, int ex)
{
	ListNode* p = plist->head;
	ListNode* ptemp;
	ListNode* temp = (ListNode*)malloc(sizeof(ListNode));
	if (temp == NULL)
		error("메모리 할당 에러");
	temp->coef = coef;
	temp->ex = ex;
	temp->link = NULL;
	
	// 노드가 하나도 없을 경우 삽입
	if (plist->head == NULL)
	{
		plist->head = plist->tail = temp;
	}
	// 노드가 하나밖에 없는 경우 p와 temp 비교
	else if (p->link == NULL)
	{
		// 지수가 같으면 계수를 더해줌
		if (p->ex == ex)
		{
			p->coef += coef;
			free(temp);
		}
		// 지수가 크면 앞에 삽입
		else if (p->ex < ex)
		{
			plist->head = temp;
			plist->tail = p;
			temp->link = p;
		}
		// 지수가 작으면 뒤로 이동
		else if (p->ex > ex)
		{
			p->link = temp;
			plist->tail = temp;
		}
	}
	// 노드가 2개 이상인 경우 p의 다음 노드와 비교해야 temp->ex 가 클 때 그 노드의 앞에 temp 를 넣을 수 있음
	else
	{
		//요소를 앞에서부터 모두 봤을때 link 의 ex 가 같으면 거기 더하고 할당해제
		//link 의 ex 가 크면 p->link->link = temp , 작으면 앞에 삽입
		while(p)
		{
			// 지수가 같으면 계수를 더해줌
			if (p->link->ex == ex)
			{
				p->link->coef += coef;
				free(temp);
				break;
			}
			// 지수가 크면 앞에 삽입
			else if (p->link->ex < ex)
			{
				// A -> B -> C 여기서 C를 B앞으로 보내려면 A -> C -> B 니까 A link와 C link 를 바꿔야함
				ptemp = p->link;
				p->link = temp;
				temp->link = ptemp;
				break;
			}
			// 지수가 작으면 뒤로 이동
			else if (p->link->ex > ex)
			{
				// 다음 값이 없다면 바로 삽입
				if (p->link->link == NULL)
				{
					if (p->link == plist->tail)
						plist->tail = temp;
					p->link->link = temp;
					break;
				}
				p = p->link;
			}
		}
	}
}

// 다항식 * 다항식2
void poly_mul(ListType* plist1, ListType* plist2, ListType* plist3)
{
	ListNode* a = plist1->head;
	ListNode* b = plist2->head;
	int prod, sum; // 계수곱, 지수합

	while (a)
	{
		while (b)
		{
			prod = a->coef * b->coef;
			sum = a->ex + b->ex;
			if (prod != 0 && sum != 0)
				insert(plist3, prod, sum);
			b = b->link;
		}
		a = a->link;
		b = plist2->head;
	}
}

// 다항식 출력
void poly_print(ListType* plist)
{
	ListNode* p = plist->head;

	printf("polynomial = ");
	for (; p; p = p->link)
	{
		printf("%d^%d", p->coef, p->ex);
		// 다항식 끝 + 출력하지 않기 위한 조건문
		if (p->link != NULL)
			printf(" + ");
	}
	printf("\n");
}

// 다항식 입력
void poly_insert(FILE *fp, ListType* list)
{
	int coef_temp, ex_temp; // 계수, 지수 받을 변수
	char temp[10]; // 다항식 이름 받을 변수

	fscanf(fp, "%s", temp);
	while (!feof(fp))
	{
		// fscanf 가 0이면 입력을 받지 못한 것, 즉 다항식 한 개 입력 완료
		if (!fscanf(fp, "%d %d", &coef_temp, &ex_temp))
			break;
		insert(list, coef_temp, ex_temp);
	}
}

int main()
{
	int i;
	ListType *list[2];	// 다항식 1, 다항식 2
	ListType *result;	// 연산 결과
	FILE *fp;

	// 연결 리스트 헤더 생성
	list[0] = create();
	list[1] = create();
	result = create();

	fp = fopen("data.txt", "r");
	if (fp == NULL)
		error("파일 찾을 수 없음");

	// 다항식 입력
	for (i=0; i<2; ++i)
		poly_insert(fp, list[i]);

	// 다항식 출력
	for (i=0; i<2; ++i)
		poly_print(list[i]);

	// 다항식 연산, 출력
	poly_mul(list[0], list[1], result);
	poly_print(result);

	for (i=0; i<2; ++i)
		free(list[i]);
	free(result);
	return 0;
}