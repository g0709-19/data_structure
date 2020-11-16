/*
	Floyd 의 최단 경로 알고리즘
	작성일: 2020년 11월 13일(금)
	학번: 20184014
	이름: 이승준
*/

#include <stdio.h>
#include <stdlib.h>

#define INF				1000
#define MAX_VERTICES	7

int A[MAX_VERTICES][MAX_VERTICES];
int weight[MAX_VERTICES][MAX_VERTICES];

void error(char *msg)
{
	fprintf(stdout, msg);
	exit(1);
}

void printNode(int weight)
{
	if (weight == INF)
		printf("|INF ");
	else
		printf("| %-3d", weight);
}

void floyd(int n)
{
	int i, j, k;
	
	// weight -> A 로 복사
	for (i=0; i<n; ++i)
		for (j=0; j<n; ++j)
			A[i][j] = weight[i][j];

	printf("-1 상태 초기상태\n");

	for (i=0; i<n; ++i) {
		for (j=0; j<n; ++j) {
			printNode(A[i][j]);
		}
		printf("|\n");
	}

	printf("\n\n");

	for (k=0; k<n; ++k) {	// 거쳐가는 노드 0, 1, ...
		printf("0부터 %d까지의 모든 정점을 이용한 최단 거리\n\n", k);
		for (i=0; i<n; ++i) { // 시작노드 0, 1, ...
			for (j=0; j<n; ++j) { // 도착노드 0, 1, ...
				if (A[i][k] + A[k][j] < A[i][j])
					A[i][j] = A[i][k] + A[k][j];

				printNode(A[i][j]);
			}
			printf("|\n");
		}
		printf("\n\n");
	}
}

int main()
{
	int i, j;	// two dimensional array
	int x, y, w;
	FILE *fp;
	fp = fopen("data1.txt", "r");
	if (fp == NULL) error("File not found!\n");
	
	// 가중치 테이블 초기화
	for (i=0; i<MAX_VERTICES; ++i) {
		for (j=0; j<MAX_VERTICES; ++j) {
			if (i == j) // 0-0, 1-1, ...
				weight[i][j] = 0;
			else
				weight[i][j] = INF;
		}
	}

	// 가중치 할당
	while (!feof(fp)) {
		fscanf(fp, "%d %d %d", &x, &y, &w);
		weight[x][y] = w;
		weight[y][x] = w;
	}

	floyd(MAX_VERTICES); // node 0-MAX_VERTICES 경로 탐색

	fclose(fp);
	return 0;
}