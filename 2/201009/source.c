/*
	���α׷���: ��������
	�ۼ���: 2020�� 10�� 9��(��)
	�й�: 20184014
	�̸�: �̽���
*/

#include <stdio.h>

#define MAX_ELEMENT	100
// priority animal_name = 15 tiger

typedef struct {
	int key;					// priority
	char animal[MAX_ELEMENT];	// animal name
} element;

typedef struct {
	element heap[MAX_ELEMENT];	// array based heap tree
	int heap_size;				// number of nodes
} HeapType;

void init(HeapType *heap)
{
	heap->heap_size = 0;
}

void insertMaxHeap(HeapType *heap, element item)
{
	int i, j;

	i = ++(heap->heap_size);	// ���� ����� 1�� ����, ���ο� ��� �߰��� array �ε��� ����

	while ((i != 1)				// ��Ʈ ��尡 �ƴϰ�
		&& (item.key > heap->heap[i/2].key))
	{
		heap->heap[i] = heap->heap[i/2];	// ���� �߰��� ��带 �θ� ��ġ�� ����
		i /= 2;
	}

	heap->heap[i] = item;		// �ǵ����͸� �ش� ��ġ�� �Է�
}

void display(HeapType *heap)
{
	int i;

	for (i=1; i<heap->heap_size+1; ++i)
		printf("%d:%s>", heap->heap[i].key, heap->heap[i].animal);
	printf("\n");
}

int main()
{
	int i;
	element temp;
	HeapType heap;
	FILE *fp;

	init(&heap);

	fp = fopen("data.txt", "r");
	if (fp == NULL)
	{
		printf("File Not Found!\n");
		return 1;
	}
	while (!feof(fp))
	{
		// read in the data and insert into heap tree
		fscanf(fp, "%d %s", &temp.key, temp.animal);
		printf(">>%d %s\n", temp.key, temp.animal);

		insertMaxHeap(&heap, temp);
		display(&heap);
	}

	printf("\nPlease enter the priority and animal name : \n");
	
	while (1)
	{
		printf(">");
		scanf("%d", &temp.key);
		if (temp.key != 0)
		{
			scanf("%s", temp.animal);
			insertMaxHeap(&heap, temp);
			display(&heap);
		}
		else
			break;
	}

	fclose(fp);
	return 0;
}