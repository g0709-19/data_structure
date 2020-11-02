/*
	프로그램명: 그래프 깊이 우선 탐색
	작성일: 2020년 10월 30일(금)
	학번: 20184014
	이름: 이승준
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

// 깊이 우선 탐색
void dfs_mat(GraphType *g, int v)
{
	int w;	// v가 행, w가 열(인접하고 있는 노드를 찾기 위한 변수)
	visited[v] = 1;
	printf("vertex %d ->", v);

	for (w=0; w<g->n; ++w)
		// 인접 노드를 다 하기 전에 처음을 계속 실행
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