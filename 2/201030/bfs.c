/*
	���α׷���: �׷��� �ʺ� �켱 Ž��
	�ۼ���: 2020�� 10�� 30��(��)
	�й�: 20184014
	�̸�: �̽���
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

// Queue ����
typedef int element;typedef struct QueueNode {	element item;	struct QueueNode *link;}QueueNode;typedef struct{	QueueNode *front, *rear;	struct QueueNode *link;}QueueType;void init(QueueType *q){	q->front = q->rear = NULL;}int is_empty(QueueType *q){	return q->front == NULL;}void enqueue(QueueType *q, element item){	QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode));	if (temp == NULL)		printf("�Ҵ� ����\n");	else	{		temp->item = item;		temp->link = NULL;		if (is_empty(q))		{			q->front = temp;			q->rear = temp;		}		else		{			q->rear->link = temp;			q->rear = temp;		}	}}element dequeue(QueueType *q){	QueueNode *temp = q->front;	element item;	if (is_empty(q))		printf("ť ���� ����\n");	else	{		item = temp->item;		q->front = q->front->link;		if (q->front == NULL)			q->rear = NULL;		free(temp);		return item;	}}
/////////////////////////////////////////////


void graph_init(GraphType *g)
{
	int row, column;
	g->n = 0;
	
	// 2���� �迭 0���� �ʱ�ȭ
	for (row = 0; row < MAX_VERTICES; ++row)
		for (column = 0; column < MAX_VERTICES; ++column)
			g->adj_mat[row][column] = 0;
}

void insert_vertex(GraphType *g, int v)
{
	if ((g->n) + 1 > MAX_VERTICES) {
		printf("�ִ������� �ʰ�\n");
		return;
	}

	g->n++;
}

void insert_edge(GraphType *g, int start, int end)
{
	if (start >= g->n || end >= g->n)
	{
		printf("�ִ������� �ʰ�\n");
		return;
	}

	// ������̱� ������ ���ʿ� 1�� ����
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}

// �ʺ� �켱 Ž��
void bfs_mat(GraphType *g, int v)
{
	int w;	// v�� ��, w�� ��(�����ϰ� �ִ� ��带 ã�� ���� ����)
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