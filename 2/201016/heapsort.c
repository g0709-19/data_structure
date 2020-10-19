/*
	히프 정렬 알고리즘
	작성일: 2020년 10월 16일(금)
	학번: 20184014
	이름: 이승준
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ELEMENT	100

typedef int element;	// random date (integer, less than 2-digits)

typedef struct {
	element heap[MAX_ELEMENT+1];
	int heap_size;
} HeapType;

void print_array(element data[], int size)
{
	int i = 0;
	for (i=0; i<size; ++i) {
		if (i%10 == 0 && i != 0) printf("\n");
		printf("%2d ", data[i]);
	}
}

void init(HeapType *h)
{
	h->heap_size = 0;
}

void insert_min_heap(HeapType *h, element data)
{
	int i, j;
	i = ++(h->heap_size);

	while ( (i != 1) && data < h->heap[i/2] ) {
		h->heap[i] = h->heap[i/2];
		i /= 2;
	}

	h->heap[i] = data;
}

element delete_min_heap(HeapType *h)
{
	int parent, child, k;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// 작은 자식에게 붙여주기 위한 조건문
		if ((child < h->heap_size) &&
			(h->heap[child]) > h->heap[child + 1])
			++child;
		// 이 경우 temp 가 child 와 같은 레벨에 있음
		if (temp <= h->heap[child])
			break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}

	h->heap[parent] = temp;
	return item;
}

void heap_sort(element data[], int size)
{
	int i;
	HeapType h;
	init(&h);

	for (i=0; i<size; ++i) {
		insert_min_heap(&h, data[i]);
	}

	for (i=0; i<size; ++i) {
		data[i] = delete_min_heap(&h);
	}
}

int main()
{
	int i, j;
	element data[MAX_ELEMENT];

	srand(time(NULL));

	for (i=0; i<MAX_ELEMENT; ++i) {
		data[i] = rand()%MAX_ELEMENT;
		
		// i까지 입력된 상태이기 때문에 MAX_ELEMENT 까지 안 봐도 됨
		for (j=0; j<i; ++j)
			if (data[i] == data[j]) {
				--i;
				break;
			}
	}

	printf("정렬 전 데이터\n");
	print_array(data, MAX_ELEMENT);

	heap_sort(data, MAX_ELEMENT);

	printf("\n\n정렬 후 데이터\n");
	print_array(data, MAX_ELEMENT);

	printf("\n\n");
	return 0;
}