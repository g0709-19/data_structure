/*
	프로그램명: Prim 최소 비용 신장 트리
	작성일: 2020년 11월 6일(금)
	학번: 20184014
	이름: 이승준
*/
#include <stdio.h>
#include <stdlib.h>

#define	TRUE	1
#define	FALSE	0

#define MAX_VERTICES	100
#define INF				1000

int weight[MAX_VERTICES][MAX_VERTICES];
int selected[MAX_VERTICES];
int distance[MAX_VERTICES];

int get_min_vertex(int n)
{
	int v, i;

	for (i=0; i<n; ++i)
		if (!selected[i]) {
			v = i;
			break;
		}

	for (i=0; i<n; ++i)
		if (!selected[i] && (distance[i] < distance[v]))
			v = i;

	return v;
}

void prim(int s, int n)
{
	int i, u, v;

	for (u = 0; u<n; ++u)
		distance[u] = INF;
	distance[s] = 0;
	for (i=0; i<n; ++i) {
		u = get_min_vertex(n);
		selected[u] = TRUE;
		if (distance[u] == INF) return;
		printf("%d ", u);
		for (v=0; v<n; ++v)
			if (weight[u][v] != INF)
				if (!selected[v] && (weight[u][v] < distance[v])) {
					distance[v] = weight[u][v];
				}
	}
}

int main()
{
	int i, j;
	int temp1, temp2, temp3;	// from vertex, to vertex, weight
	int max = 0;				// 노드가 얼마나 있는지 카운트
	FILE *fp;
	fp = fopen("data3.txt", "r");
	if (fp == NULL) {
		printf("File not found\n");
		return 0;
	}

	// count number of nodes in the file
	while (!feof(fp)) {
		fscanf(fp, "%d %d %d", &temp1, &temp2, &temp3);
		if (temp2 > max)
			max = temp2;
	}

	max += 1;
	rewind(fp);

	for (i=0; i<max; ++i) {
		for (j=0; j<max; ++j) {
			if (i == j)
				weight[i][j] = 0;
			else
				weight[i][j] = INF;
		}
	}

	while (!feof(fp)) {
		fscanf(fp, "%d %d %d", &temp1, &temp2, &temp3);
		weight[temp1][temp2] = temp3;
		weight[temp2][temp1] = temp3;
	}

	prim(0, max);
	printf("\n");

	fclose(fp);
	return 0;
}