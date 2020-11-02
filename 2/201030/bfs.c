/*
	프로그램명: 그래프 너비 우선 탐색
	작성일: 2020년 10월 30일(금)
	학번: 20184014
	이름: 이승준
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES	50

int visited[MAX_VERTICES];

typedef struct GraphType {
	int n;
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

// Queue 구현
typedef int element;typedef struct QueueNode {	element item;	struct QueueNode *link;}QueueNode;typedef struct{	QueueNode *front, *rear;	struct QueueNode *link;}QueueType;void init(QueueType *q){	q->front = q->rear = NULL;}int is_empty(QueueType *q){	return q->front == NULL;}void enqueue(QueueType *q, element item){	QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode));	if (temp == NULL)		printf("할당 오류\n");	else	{		temp->item = item;		temp->link = NULL;		if (is_empty(q))		{			q->front = temp;			q->rear = temp;		}		else		{			q->rear->link = temp;			q->rear = temp;		}	}}element dequeue(QueueType *q){	QueueNode *temp = q->front;	element item;	if (is_empty(q))		printf("큐 공백 에러\n");	else	{		item = temp->item;		q->front = q->front->link;		if (q->front == NULL)			q->rear = NULL;		free(temp);		return item;	}}
/////////////////////////////////////////////


void graph_init(GraphType *g)
{
	int row, column;
	g->n = 0;
	
	// 2차원 배열 0으로 초기화
	for (row = 0; row < MAX_VERTICES; ++row)
		for (column = 0; column < MAX_VERTICES; ++column)
			g->adj_mat[row][column] = 0;
}

void insert_vertex(GraphType *g, int v)
{
	if ((g->n) + 1 > MAX_VERTICES) {
		printf("최대정점수 초과\n");
		return;
	}

	g->n++;
}

void insert_edge(GraphType *g, int start, int end)
{
	if (start >= g->n || end >= g->n)
	{
		printf("최대정점수 초과\n");
		return;
	}

	// 양방향이기 때문에 양쪽에 1로 설정
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}

// 너비 우선 탐색
void bfs_mat(GraphType *g, int v)
{
	int w;	// v가 행, w가 열(인접하고 있는 노드를 찾기 위한 변수)
	QueueType q;

	init(&q);

	visited[v] = 1;
	printf("Vectex %d ", v);
	enqueue(&q, v);

	while (!is_empty(&q))
	{
		v = dequeue(&q);

		for (w=0; w<g->n; ++w)
			if ((g->adj_mat[v][w] == 1) && !visited[w])
			{
				visited[w] = 1;
				printf("%d ", w);
				enqueue(&q, w);
			}
	}
}

int main()
{
	int i;
	GraphType g;
	char command;
	int temp1, temp2;
	FILE *fp;
	fp = fopen("data1.txt", "r");
	if (fp == NULL) {
		printf("File not found\n");
		return 0;
	}

	graph_init(&g);

	while (!feof(fp)) {
		fscanf(fp, "%c", &command); 
		switch(command) {
		case 'v':
			fscanf(fp, "%d", &temp1);
			insert_vertex(&g, temp1);
			break;
		case 'e':
			fscanf(fp, "%d %d", &temp1, &temp2);
			insert_edge(&g, temp1, temp2);
			break;
		}
	}

	printf("bfs started\n");
	bfs_mat(&g, 0);
	printf("\n\n");
	return 0;
}