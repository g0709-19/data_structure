/*
	���α׷���: �׷��� ���� �켱 Ž��
	�ۼ���: 2020�� 10�� 30��(��)
	�й�: 20184014
	�̸�: �̽���
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES	50

int visited[MAX_VERTICES];

typedef struct GraphType {
	int n;
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

void init(GraphType *g)
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

// ���� �켱 Ž��
void dfs_mat(GraphType *g, int v)
{
	int w;	// v�� ��, w�� ��(�����ϰ� �ִ� ��带 ã�� ���� ����)
	visited[v] = 1;
	printf("vertex %d ->", v);

	for (w=0; w<g->n; ++w)
		// ���� ��带 �� �ϱ� ���� ó���� ��� ����
		if (g->adj_mat[v][w] && !visited[w])
			dfs_mat(g, w);
}

int main()
{
	int i;
	GraphType *g;
	g = (GraphType *)malloc(sizeof(GraphType));
	
	init(g);

	for (i=0; i<4; ++i)
		insert_vertex(g, i);

	insert_edge(g, 0, 1);
	insert_edge(g, 0, 2);
	insert_edge(g, 0, 3);
	insert_edge(g, 1, 2);
	insert_edge(g, 2, 3);

	printf("dfs started\n");
	dfs_mat(g, 0);
	printf("\n\n");

	free(g);
	return 0;
}