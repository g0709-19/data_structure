/*
	Floyd �� �ִ� ��� �˰���
	�ۼ���: 2020�� 11�� 13��(��)
	�й�: 20184014
	�̸�: �̽���
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
	
	// weight -> A �� ����
	for (i=0; i<n; ++i)
		for (j=0; j<n; ++j)
			A[i][j] = weight[i][j];

	printf("-1 ���� �ʱ����\n");

	for (i=0; i<n; ++i) {
		for (j=0; j<n; ++j) {
			printNode(A[i][j]);
		}
		printf("|\n");
	}

	printf("\n\n");

	for (k=0; k<n; ++k) {	// ���İ��� ��� 0, 1, ...
		printf("0���� %d������ ��� ������ �̿��� �ִ� �Ÿ�\n\n", k);
		for (i=0; i<n; ++i) { // ���۳�� 0, 1, ...
			for (j=0; j<n; ++j) { // ������� 0, 1, ...
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
	
	// ����ġ ���̺� �ʱ�ȭ
	for (i=0; i<MAX_VERTICES; ++i) {
		for (j=0; j<MAX_VERTICES; ++j) {
			if (i == j) // 0-0, 1-1, ...
				weight[i][j] = 0;
			else
				weight[i][j] = INF;
		}
	}

	// ����ġ �Ҵ�
	while (!feof(fp)) {
		fscanf(fp, "%d %d %d", &x, &y, &w);
		weight[x][y] = w;
		weight[y][x] = w;
	}

	floyd(MAX_VERTICES); // node 0-MAX_VERTICES ��� Ž��

	fclose(fp);
	return 0;
}