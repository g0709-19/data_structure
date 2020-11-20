/*
	쉘 정렬
	작성일: 2020년 11월 20일(금)
	학번: 20184014
	이름: 이승준
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Student {
	char name[20];
	int id;
	char phone[20];
} Student;

void print(Student list[], int n)
{
	int i;
	for (i=0; i<n; ++i) {
		printf("%s %d %s\n", list[i].name, list[i].id, list[i].phone);
	}
}

void inc_insertion_sort(Student list[], int first, int last, int gap)
{
	int i, j;
	Student key;

	for (i=first+gap; i<=last; i=i+gap) {
		key = list[i];

		for (j=i-gap; j>=first && list[j].id > key.id; j=j-gap) {
			list[j+gap] = list[j];
		}

		list[j+gap] = key;
	}
}

void shell_sort(Student list[], int n)
{
	int i, gap;

	for (gap=n/2; gap>0; gap/=2) {
		if ((gap%2) == 0) ++gap;

		for (i=0; i<gap; ++i) {
			inc_insertion_sort(list, i, n-1, gap);
		}
	}
}

int main()
{
	int count = 0;
	Student temp, *list;

	FILE *fp;
	fp = fopen("data4.txt", "r");
	if (fp == NULL) {
		printf("File not found\n");
		return 0;
	}

	while (!feof(fp)) {
		fscanf(fp, "%s %d %s", temp.name, &temp.id, temp.phone);
		++count;
	}

	list = (Student*)malloc(sizeof(Student)*count);
	
	rewind(fp);
	count = 0;

	while (!feof(fp)) {
		fscanf(fp, "%s %d %s", list[count].name, &list[count].id, list[count].phone);
		++count;	
	}

	printf("[정렬전]\n");
	print(list, count);

	printf("\n[정렬후]\n");
	shell_sort(list, count);
	print(list, count);

	free(list);
	fclose(fp);
	return 0;
}