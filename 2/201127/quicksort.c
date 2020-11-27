/*
	�� ����
	�ۼ���: 2020�� 11�� 27��(��)
	�й�: 20184014
	�̸�: �̽���
*/

#include <stdio.h>
#include <stdlib.h>

// #define SWAP(x, y, temp) ((temp) = (x), (x) = (y), (y) = (temp))
// ��ũ�δ� ȿ�� ������, 50�� �ϸ� 50�� �� ��ü�ؾߵ�
void swap(int *x, int *y, int *temp)
{
	*temp = *x;
	*x = *y;
	*y = *temp;
}

void print(int list[], int right)
{
	int i;
	printf("[");
	for (i=0; i<right+1; ++i)
		printf("%d > ", list[i]);
	printf("]");
}

int partition(int list[], int left, int right)
{
	int pivot, temp, i;
	// low�� �ǹ����� ������ ��������(++) �̵�, ũ�� ����
	// high�� �ǹ����� ũ�� ��������(--) �̵�, ������ ����
	int low, high;

	low = left;
	high = right+1;
	pivot = list[left];

	printf("\n\nPivot : %d\n", pivot);

	do { // low�� high�� �������� �ߴ�

		do {
			++low;
		} while (low <= right && list[low] < pivot);	// �ǹ����� ���� ��� �ݺ�, low <= right �� ��� �ڵ�
		
		do {
			--high;
		} while (high >= left && list[high] > pivot);	// �ǹ����� ū ��� �ݺ�, high >= left �� ��� �ڵ�
		
		// low�� high ��� invalid ���� ������ array �ε���
		printf("Low : %d High : %d", list[low], list[high]);
		print(list, right);

		if (low < high) {
			printf("%d�� %d�� ����\n", list[low], list[high]);
			swap(&list[low], &list[high], &temp);
			print(list, right);
		}

	} while (low < high);

	swap(&list[left], &list[high], &temp);
	
	return high; // pivot �� �߰� �ڸ�(high)�� �����ؼ� high �� pivot ��
}

void quick_sort(int list[], int left, int right)
{
	// ��Ұ� �ϳ��� ������ left == right, ���� �ʿ� ����
	if (left < right)
	{
		int q = partition(list, left, right);
		quick_sort(list, left, q-1);	// q�� ����ϱ� �� ĭ ��������
		quick_sort(list, q+1, right);	// q�� ����ϱ� �� ĭ ����������
	}
}

int main()
{
	int temp;
	int i, count = 0;
	int *list;
	FILE *fp;
	fp = fopen("data2.txt", "r");
	if (fp == NULL) {
		printf("File not found\n");
		return 0;
	}
	
	while (!feof(fp)) {
		fscanf(fp, "%d", &temp);
		++count;
	}

	list = (int*)malloc(sizeof(int)*count);
	rewind(fp);
	count = 0;

	while (!feof(fp)) {
		fscanf(fp, "%d", &temp);
		list[count++] = temp;
	}

	printf("������ ����Ʈ >\n");	for (i = 0; i < count; i++) {		printf("%d >", list[i]);	}
	
	quick_sort(list, 0, count-1); // �� count-1 �ϱ�?

	printf("%d", count);	printf("\n\n���ĵ� ����Ʈ >\n");	for (i = 0; i < count; i++) {		printf("%d >", list[i]);	}

	printf("\n\n");

	fclose(fp);
	return 0;
}