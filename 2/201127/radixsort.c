/*
	기수 정렬
	작성일: 2020년 11월 27일(금)
	학번: 20184014
	이름: 이승준
*/

#include <stdio.h>

#define BUCKETS	10
#define DIGITS	3

#define MAX_QUEUE_SIZE	100

typedef int element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;

void init(QueueType *q){	q->front = q->rear = 0;}int is_empty(QueueType *q){	return (q->front == q->rear);}int is_full(QueueType *q){	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);}void enqueue(QueueType *q, element item){	if (is_full(q))		printf("큐가 포화상태입니다.");	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;	q->queue[q->rear] = item;}element dequeue(QueueType *q){	if (is_empty(q))		printf("");	q->front = (q->front + 1) % MAX_QUEUE_SIZE;	return q->queue[q->front];}

void print(int list[], int size)
{
	int i;
	for (i=0; i<size; ++i)
		printf("%d > ", list[i]);
}

void radix_sort(int list[], int size)
{
	int i, d, b;
	int factor = 1;
	QueueType queues[BUCKETS];

	for (i=0; i<BUCKETS; ++i)
		init(&queues[i]);

	printf("\n\n<정렬 과정>\n");

	for (d=0; d<DIGITS; ++d) {
		printf("\nDigit : %d\n", d+1);
		
		for (i=0; i<size; ++i)
			// 자리수가 많아지면 %10 만으로는 안 되지 않나?
			// 그래서 factor 로 나눠줌
			enqueue(&queues[(list[i] / factor) % 10], list[i]);

		for (b=i=0; b<BUCKETS; ++b) {
			printf("Bucket[%d] : ", b);
			if (is_empty(&queues[b]))
				printf("Empty");

			while (!is_empty(&queues[b])) {
				list[i] = dequeue(&queues[b]);
				printf("%d ", list[i++]);
			}
			printf("\n");
		}

		factor *= 10;
	}
}

int main()
{
	int list[MAX_QUEUE_SIZE] = { 0 };
	int size = 0, i;
	FILE *fp;

	fp = fopen("data1.txt", "r");

	if (fp == NULL) {
		printf("File not found\n");
		return 0;
	}

	while (!feof(fp)) {
		fscanf(fp, "%d", &list[size]);
		++size;
	}

	printf("<정렬전 데이터>\n");
	print(list, size);

	radix_sort(list, size);

	printf("\n<정렬후 데이터>\n");
	print(list, size);

	printf("\n\n");

	fclose(fp);
	return 0;
}