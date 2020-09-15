/*
	����: ���� ����Ʈ�� �̿��Ͽ� 2���� ���׽��� ���ϴ� ���� ������ �����ϴ� ���α׷�
	�̸�: �̽���
*/

#include <stdio.h>
#include <stdlib.h>

// ���� ����Ʈ ���
typedef struct ListNode
{
	int coef;	// ���
	int ex;		// ����
	struct ListNode *link; // ���� ���
} ListNode;

// ���� ����Ʈ ���
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

// ����Ʈ ��� ���� 
ListType* create()
{
	ListType *plist = (ListType*)malloc(sizeof(ListType));
	plist->size = 0;
	plist->head = plist->tail = NULL;
	return plist;
}

// ����Ʈ�� ���, ���� �����ϵ� ���� ������ �� ������ �����ϰ� ���� ������ ������ ������� ��
void insert(ListType *plist, int coef, int ex)
{
	ListNode* p = plist->head;
	ListNode* ptemp;
	ListNode* temp = (ListNode*)malloc(sizeof(ListNode));
	if (temp == NULL)
		error("�޸� �Ҵ� ����");
	temp->coef = coef;
	temp->ex = ex;
	temp->link = NULL;
	
	// ��尡 �ϳ��� ���� ��� ����
	if (plist->head == NULL)
	{
		plist->head = plist->tail = temp;
	}
	// ��尡 �ϳ��ۿ� ���� ��� p�� temp ��
	else if (p->link == NULL)
	{
		// ������ ������ ����� ������
		if (p->ex == ex)
		{
			p->coef += coef;
			free(temp);
		}
		// ������ ũ�� �տ� ����
		else if (p->ex < ex)
		{
			plist->head = temp;
			plist->tail = p;
			temp->link = p;
		}
		// ������ ������ �ڷ� �̵�
		else if (p->ex > ex)
		{
			p->link = temp;
			plist->tail = temp;
		}
	}
	// ��尡 2�� �̻��� ��� p�� ���� ���� ���ؾ� temp->ex �� Ŭ �� �� ����� �տ� temp �� ���� �� ����
	else
	{
		//��Ҹ� �տ������� ��� ������ link �� ex �� ������ �ű� ���ϰ� �Ҵ�����
		//link �� ex �� ũ�� p->link->link = temp , ������ �տ� ����
		while(p)
		{
			// ������ ������ ����� ������
			if (p->link->ex == ex)
			{
				p->link->coef += coef;
				free(temp);
				break;
			}
			// ������ ũ�� �տ� ����
			else if (p->link->ex < ex)
			{
				// A -> B -> C ���⼭ C�� B������ �������� A -> C -> B �ϱ� A link�� C link �� �ٲ����
				ptemp = p->link;
				p->link = temp;
				temp->link = ptemp;
				break;
			}
			// ������ ������ �ڷ� �̵�
			else if (p->link->ex > ex)
			{
				// ���� ���� ���ٸ� �ٷ� ����
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

// ���׽� * ���׽�2
void poly_mul(ListType* plist1, ListType* plist2, ListType* plist3)
{
	ListNode* a = plist1->head;
	ListNode* b = plist2->head;
	int prod, sum; // �����, ������

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

// ���׽� ���
void poly_print(ListType* plist)
{
	ListNode* p = plist->head;

	printf("polynomial = ");
	for (; p; p = p->link)
	{
		printf("%d^%d", p->coef, p->ex);
		// ���׽� �� + ������� �ʱ� ���� ���ǹ�
		if (p->link != NULL)
			printf(" + ");
	}
	printf("\n");
}

// ���׽� �Է�
void poly_insert(FILE *fp, ListType* list)
{
	int coef_temp, ex_temp; // ���, ���� ���� ����
	char temp[10]; // ���׽� �̸� ���� ����

	fscanf(fp, "%s", temp);
	while (!feof(fp))
	{
		// fscanf �� 0�̸� �Է��� ���� ���� ��, �� ���׽� �� �� �Է� �Ϸ�
		if (!fscanf(fp, "%d %d", &coef_temp, &ex_temp))
			break;
		insert(list, coef_temp, ex_temp);
	}
}

int main()
{
	int i;
	ListType *list[2];	// ���׽� 1, ���׽� 2
	ListType *result;	// ���� ���
	FILE *fp;

	// ���� ����Ʈ ��� ����
	list[0] = create();
	list[1] = create();
	result = create();

	fp = fopen("data.txt", "r");
	if (fp == NULL)
		error("���� ã�� �� ����");

	// ���׽� �Է�
	for (i=0; i<2; ++i)
		poly_insert(fp, list[i]);

	// ���׽� ���
	for (i=0; i<2; ++i)
		poly_print(list[i]);

	// ���׽� ����, ���
	poly_mul(list[0], list[1], result);
	poly_print(result);

	for (i=0; i<2; ++i)
		free(list[i]);
	free(result);
	return 0;
}