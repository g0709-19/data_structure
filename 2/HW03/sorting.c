/*
	text.txt ���Ͽ� �ִ� ���� �����͸� �о�
	�鿩 ���ݱ��� ��� ���� �����(����, ����
	����, ��, ��, ����, �պ�)�� ��� �����Ͽ�
	�����ϴ� ���α׷��� �ۼ��ϰ� �� ���ĺ�
	���� �ð� ����� ���� ������
	�м��Ͻÿ�
	- �����ϴ� ���α׷����� ���ڸ� �����ϰ� �����ؼ� ������ ��
	- ���� �Ҵ��� �̿��Ͽ� �޸𸮸� �Ҵ� �� ��
	�ۼ���: 2020�� 11�� 28��(��)
	�й�: 20184014
	�̸�: �̽���
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LENGTH	100	// �Է¹޴� ���ڿ� ����

typedef struct {
	clock_t start, end;
} Runtime;

typedef struct {
	char** heap;
	int heap_size;
} HeapType;

// ����ð� ��ȯ �Լ�
float getRuntime(Runtime runtime)
{
	return (float)(runtime.end-runtime.start)/CLOCKS_PER_SEC;
}

// ���� ��� �Լ�
void error(char *msg)
{
	printf("%s", msg);
	exit(1);
}

// �����Ҵ� ���� �Լ�
void free_list(char **list, int size)
{
	int i;
	for (i=0; i<size; ++i)
		free(list[i]);
	free(list);
}

// �� ���α׷����� ���� ������ �����Ϸ��� �迭 ���簡 �ʿ�����
// copied �� list �� ������ �����ϴ� �Լ�
void copy(char **copied, char **list, int size)
{
	int i;
	for (i=0; i<size; ++i)
		strcpy(copied[i], list[i]);
}

// #define SWAP(x, y, temp) ((temp) = (x), (x) = (y), (y) = (temp))
// ��ũ�δ� ȿ�� ������, 50�� �ϸ� 50�� �� ��ü�ؾߵ�
void swap(char **x, char **y)
{
	char *temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

// �迭 ��� �Լ�
void print(char **list, int size)
{
	int i;
	for (i=0; i<size; ++i)
		printf("[%d] %s\n", i, list[i]);
	printf("\n");
}

/* ***********************���� ����************************* */

void insertion_sort(char** list, int n)
{
	int i, j;
	char* temp;

	// ������ �ȵ� list[0] �� ������ �� �������� ��
	for (i=1; i<n; ++i) {
		temp = list[i];

		for (j=i-1; j>=0 && strcmp(list[j], temp) > 0; --j) {
			list[j+1] = list[j];	// ���ڵ带 ���������� �̵�
		}

		list[j+1] = temp;
	}
}

/* ***********************���� ����************************* */
// ������ �ȵ� ���� �߿��� �ּ� ���ڸ� ����
void selection_sort(char** list, int n)
{
	int i, j;
	int least;	// �ּҰ�
	char* temp;
	// �� n-1 �ϱ�? �ϳ��� ���� �Ǿ��ִٰ� �����ϱ� ����
	for (i=0; i<n-1; ++i) {
		least = i;	// ���� �ּҰ������� ������ �ʱⰪ ����
		for (j=i+1; j<n; ++j) {
			if (strcmp(list[j], list[least]) < 0)
				least = j;
		}
		temp = list[i];
		list[i] = list[least];
		list[least] = temp;
	}
}

/* ***********************���� ����************************* */

void bubble_sort(char** list, int n)
{
	int i, j;
	char* temp;
	
	// i�� ������ ��������
	for (i=n-1; i>0; --i) {
		for (j=0; j<i; ++j) {
			if (strcmp(list[j], list[j+1]) > 0) {
				temp = list[j];
				list[j] = list[j+1];
				list[j+1] = temp;
			}
		}
	}
}

/* ***********************�� ����************************* */

void inc_insertion_sort(char **list, int first, int last, int gap)
{
	int i, j;
	char *key;

	// i�� j���� �׻� �� ĭ �ڿ� �ִ� �ε����� ����Ŵ
	for (i=first+gap; i<=last; i=i+gap) {
		key = list[i];	// key �� �����ϴ� ���� ���� ������ ���۷����� �Ѱ��൵ ��� ����

		// j�� i���� �׻� �� ĭ �տ� �ִ� �ε����� ����Ű�鼭
		// j�� i�� ��, �� key ���� ũ�� i�� ��ġ�� j�� ���� �־���
		for (j=i-gap; j>=first && strcmp(list[j], key) > 0; j=j-gap) {
			list[j+gap] = list[j];
		}

		// j=j-gap ���� j�� ���� ��ġ���� �� ĭ ������ �����Ƿ� j+gap �� i�� �ִ� ��, �� key �� �־���
		list[j+gap] = key;
	}
}

void shell_sort(char **list, int n)
{
	int i, gap;

	for (gap=n/2; gap>0; gap/=2) {
		if ((gap%2) == 0) ++gap;

		for (i=0; i<gap; ++i) {
			inc_insertion_sort(list, i, n-1, gap);
			/*
				5 4 3 2 1
				5     2
				  4     1
					3
			*/
		}
	}
}

/* ***********************�� ����************************* */
int partition(char **list, int left, int right)
{
	char *pivot;
	// low�� �ǹ����� ������ ��������(++) �̵�, ũ�� ����
	// high�� �ǹ����� ũ�� ��������(--) �̵�, ������ ����
	int low, high;

	low = left;
	high = right+1;
	pivot = list[left];

	do { // low�� high�� �������� �ߴ�

		do {
			++low;
		} while (low < right && strcmp(list[low], pivot) < 0);	// �ǹ����� ���� ��� �ݺ�, low <= right �� ��� �ڵ�

		do {
			--high;
		} while (high >= left && strcmp(list[high], pivot) > 0);	// �ǹ����� ū ��� �ݺ�, high >= left �� ��� �ڵ�

		if (low < high)
			swap(&list[low], &list[high]);

	} while (low < high);

	swap(&list[left], &list[high]);
	
	return high; // pivot �� �߰� �ڸ�(high)�� �����ؼ� high �� pivot ��
}

void quick_sort(char **list, int left, int right)
{
	// ��Ұ� �ϳ��� ������ left == right, ���� �ʿ� ����
	if (left < right)
	{
		int q = partition(list, left, right);
		quick_sort(list, left, q-1);	// q�� ����ϱ� �� ĭ ��������
		quick_sort(list, q+1, right);	// q�� ����ϱ� �� ĭ ����������
	}
}

/* ***********************���� ����*********************** */

void init_heap(HeapType *h, int size)
{
	int i;
	size += 1;
	h->heap = (char**)malloc(sizeof(char*)*(size+1));	// heap �� �ε����� 1���� �����ϹǷ� ���� ũ�⺸�� 1 ���� �Ҵ�
	for (i=0; i<size; ++i)
		h->heap[i] = (char*)malloc(sizeof(char)*MAX_LENGTH);
	h->heap_size = 0;
}

void insert_min_heap(HeapType *h, char *data)
{
	int i;
	i = ++(h->heap_size);

	while ( (i != 1) && strcmp(data, h->heap[i/2]) < 0 ) {
		strcpy(h->heap[i], h->heap[i/2]);
		i /= 2;
	}
	strcpy(h->heap[i], data);
}

void delete_min_heap(HeapType *h, char **t)
{
	int parent, child;
	char *temp;
	
	strcpy(*t, h->heap[1]);	// item = h->heap[1] �� ���� �� ���۷����� ����ż� heap ���� ���� ���� ������ �־���
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// ���� �ڽĿ��� �ٿ��ֱ� ���� ���ǹ�
		if ((child < h->heap_size) &&
			strcmp(h->heap[child], h->heap[child + 1]) > 0)
			++child;
		// �� ��� temp �� child �� ���� ������ ����
		if (strcmp(temp, h->heap[child]) <= 0)
			break;
		strcpy(h->heap[parent], h->heap[child]);
		parent = child;
		child *= 2;
	}

	strcpy(h->heap[parent], temp);
}

void heap_sort(char **list, int size)
{
	int i;
	char *temp = (char*)malloc(sizeof(char)*MAX_LENGTH);	// heap ���� ������ �� ��Ƶδ� ����
	HeapType h;
	init_heap(&h, size);

	for (i=0; i<size; ++i) {
		insert_min_heap(&h, list[i]);
	}

	for (i=0; i<size; ++i) {
		delete_min_heap(&h, &temp);
		strcpy(list[i], temp);
	}

	free(temp);
	free_list(h.heap, size);
}

/* ***********************�պ� ����*********************** */

char **sorted;	// �߰� ���� �ʿ�

void merge(char **list, int left, int mid, int right)
{
	int i, j, k, l;
	i = left;
	j = mid + 1;
	k = left;

	// ���� ���ĵ� list�� �պ�
	while (i <= mid && j <= right) {
		if (strcmp(list[i], list[j]) <= 0)
			sorted[k++] = list[i++];
		else
			sorted[k++] = list[j++];
	}
	if (i>mid)	// ���� �ִ� ���ڵ��� �ϰ� ����
		for (l=j; l<=right; ++l)
			sorted[k++] = list[l];
	else
		for (l=i; l<=mid; ++l)
			sorted[k++] = list[l];
	// �迭 sorted�� ����Ʈ�� �迭 list�� �纹��
	for (l=left; l<=right; ++l)
		list[l] = sorted[l];
}

void merge_sort(char **list, int left, int right)
{
	int mid;
	if (left<right) {
		mid = (left + right) / 2;		// ����Ʈ�� �յ� ����
		merge_sort(list, left, mid);	// �κ� ����Ʈ ����
		merge_sort(list, mid+1, right);	// �κ� ����Ʈ ����
		merge(list, left, mid, right);	// �պ�
	}
}

/* **************************************************** */

int main()
{
	char temp[MAX_LENGTH];
	char **list;
	char **copied;
	int i, count;

	Runtime runtime;
	FILE *fp;

	fp = fopen("text.txt", "r");
	if (fp == NULL)
		error("File not found\n");

	count = 0;

	// text.txt ���Ͽ� �ִ� ���� �������� ���� ����
	while(!feof(fp)) {
		// ������ ���α׷� ����ؼ� ������� �ؽ�Ʈ ������ ���� ������ �ϳ� ���ԵǾ� ������
		// �׷��� ������ ���� ���ڱ��� �Է¹޴��� ���� ó������
		if (fscanf(fp, "%s", temp) == EOF)
			break;
		++count;
	}

	list = (char**)malloc(sizeof(char*)*count);		// �Է¹��� ���ڿ� ������ŭ char�� �迭 ���� �迭 �����Ҵ�
	copied = (char**)malloc(sizeof(char*)*count);	// ���� ���� �����ϱ� ���� ������ �迭
	sorted = (char**)malloc(sizeof(char*)*count);	// �պ� ������ ���� �߰� �迭

	rewind(fp);
	i = 0;

	// text.txt ���Ͽ� �ִ� ���� �����͸� list�� ����
	while(!feof(fp)) {
		if (fscanf(fp, "%s", temp) == EOF)
			break;

		list[i] = (char*)malloc(sizeof(char)*MAX_LENGTH);	// ���ڿ� ���� ���� �����Ҵ�, �����Ҵ�� ���� ���ÿ� �ؼ� �ð� ����
		copied[i] = (char*)malloc(sizeof(char)*MAX_LENGTH);	// ���� ���� �����ϱ� ���� ������ �迭
		sorted[i] = (char*)malloc(sizeof(char)*MAX_LENGTH);	// �պ� ������ ���� �߰� �迭

		strcpy(list[i], temp);
		++i;
	}
	
	printf("�Է¹��� ���ڿ��� ����: %d\n", count);
	printf("\n[���� ���]\n");

	// ���� ����
	copy(copied, list, count);

	runtime.start = clock();
	insertion_sort(copied, count); // �ε����� n-1 ���� ����
	runtime.end = clock();

	printf("���� ����: %f��\n", getRuntime(runtime));

	// ���� ����
	copy(copied, list, count);

	runtime.start = clock();
	selection_sort(copied, count); // �ε����� n-1 ���� ����
	runtime.end = clock();

	printf("���� ����: %f��\n", getRuntime(runtime));

	// ���� ����
	copy(copied, list, count);

	runtime.start = clock();
	bubble_sort(copied, count); // �ε����� n-1 ���� ����
	runtime.end = clock();

	printf("���� ����: %f��\n", getRuntime(runtime));

	// �� ����
	copy(copied, list, count);

	runtime.start = clock();
	shell_sort(copied, count); // �ε����� n-1 ���� ����
	runtime.end = clock();

	printf("�� ����: %f��\n", getRuntime(runtime));

	// �� ����
	copy(copied, list, count);

	runtime.start = clock();
	quick_sort(copied, 0, count-1); // �ε����� n-1 ���� ����
	runtime.end = clock();

	printf("�� ����: %f��\n", getRuntime(runtime));
	
	// ���� ����
	copy(copied, list, count);

	runtime.start = clock();
	heap_sort(copied, count); // �ε����� n-1 ���� ����
	runtime.end = clock();

	printf("���� ����: %f��\n", getRuntime(runtime));

	// �պ� ����
	copy(copied, list, count);

	runtime.start = clock();
	merge_sort(copied, 0, count-1); // �ε����� n-1 ���� ����
	runtime.end = clock();

	printf("�պ� ����: %f��\n", getRuntime(runtime));

	// �����Ҵ� ����
	for (i=0; i<count; ++i)
		free(list[i]);
	free(list);

	fclose(fp);	// ���� �ݱ�
	return 0;
}