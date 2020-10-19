/*
	배열 기반 히프
	작성일: 2020년 10월 16일(금)
	학번: 20184014
	이름: 이승준
*/

#include <stdio.h>

#define MAX_ELEMENT 100

typedef struct {
	int priority;	// 1, 2, 3, ...
	char data;		// A, B, C, ...
} element;

typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

void init(HeapType *h)
{
	h->heap_size = 0;
}

// 부모에서 자식으로, 자식에서 부모로
// 높이, 개수
// 중간 고사!!
void insert_min_heap(HeapType *h, element item)
{
	int i, j;
	i = ++(h->heap_size);

	while ( (i != 1) && item.priority <   h->heap[i/2].priority ) {
		h->heap[i] = h->heap[i/2];
		i /= 2;
	}

	h->heap[i] = item;
}

void display(HeapType *h)
{
	int i;
	for (i=1; i<h->heap_size+1; ++i) {
		printf("%c\n", h->heap[i].data);
	}

	printf("\n\n");
}

int main()
{
	element temp;
	HeapType heap;
	
	init(&heap);

	// insert data
	// A, 1
	// B, 2
	 
	// C, 3
	// ...
	temp.data = 'A';
	temp.priority = 1;
	insert_min_heap(&heap, temp);

	temp.data = 'B';
	temp.priority = 2;
	insert_min_heap(&heap, temp);

	temp.data = 'C';
	temp.priority = 3;
	insert_min_heap(&heap, temp);

	temp.data = 'D';
	temp.priority = 4;
	insert_min_heap(&heap, temp);

	temp.data = 'C';
	temp.priority = 3;
	insert_min_heap(&heap, temp);

	temp.data = 'B';
	temp.priority = 2;
	insert_min_heap(&heap, temp);

	display(&heap);
	return 0;
}