/*
	����, ����, ���� ����
	�ۼ���: 2020�� 11�� 20��(��)
	�й�: 20184014
	�̸�: �̽���
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Student {
	char name[20];
	int id;
	int rank;
} Student;

void print(Student list[], int n)
{
	int i;
	for (i=0; i<n; ++i) {
		printf("%s %d %d\n", list[i].name, list[i].id, list[i].rank);
	}
}

// ������ �ȵ� ���� �߿��� �ּ� ���ڸ� ����
void selection_sort(Student list[], int n)
{
	int i, j;
	int least;	// �ּҰ�
	Student temp;
	// �� n-1 �ϱ�? �ϳ��� ���� �Ǿ��ִٰ� �����ϱ� ����
	for (i=0; i<n-1; ++i) {
		least = i;	// ���� �ּҰ������� ������ �ʱⰪ ����
		for (j=i+1; j<n; ++j) {
			if (list[j].rank < list[least].rank)
				least = j;
		}
		temp = list[i];
		list[i] = list[least];
		list[least] = temp;
	}
}

void insertion_sort(Student list[], int n)
{
	int i, j;
	Student temp;

	// ������ �ȵ� list[0] �� ������ �� �������� ��
	for (i=1; i<n; ++i) {
		temp = list[i];

		for (j=i-1; j>=0 && list[j].id > temp.id; --j) {
			list[j+1] = list[j];	// ���ڵ带 ���������� �̵�
		}

		list[j+1] = temp;
	}
}

void bubble_sort(Student list[], int n)
{
	int i, j;
	Student temp;

	for (i=n-1; i>0; --i) {
		for (j=0; j<i; ++j) {
			if (strcmp(list[j].name, list[j+1].name) > 0) {
				temp = list[j];
				list[j] = list[j+1];
				list[j+1] = temp;
			}
		}
	}
}

int main()
{
	int count = 0;
	Student temp, *list;

	FILE *fp;
	fp = fopen("data1.txt", "r");
	if (fp == NULL) {
		printf("File not found\n");
		return 0;
	}

	while (!feof(fp)) {
		fscanf(fp, "%s %d %d", temp.name, &temp.id, &temp.rank);
		++count;
	}

	list = (Student*)malloc(sizeof(Student)*count);
	
	rewind(fp);
	count = 0;

	while (!feof(fp)) {
		fscanf(fp, "%s %d %d", list[count].name, &list[count].id, &list[count].rank);
		++count;	
	}

	printf("[������]\n");
	print(list, count);

	printf("\n[Selection sort]\n");
	selection_sort(list, count);
	print(list, count);

	printf("\n[Insertion sort]\n");
	insertion_sort(list, count);
	print(list, count);

	printf("\n[Bubble sort]\n");
	bubble_sort(list, count);
	print(list, count);

	fclose(fp);
	return 0;
}