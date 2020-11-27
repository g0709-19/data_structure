/*
	퀵 정렬
	작성일: 2020년 11월 27일(금)
	학번: 20184014
	이름: 이승준
*/

#include <stdio.h>
#include <stdlib.h>

// #define SWAP(x, y, temp) ((temp) = (x), (x) = (y), (y) = (temp))
// 매크로는 효율 떨어짐, 50번 하면 50번 다 교체해야됨
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
	// low는 피벗보다 작으면 우측으로(++) 이동, 크면 정지
	// high는 피벗보다 크면 좌측으로(--) 이동, 작으면 정지
	int low, high;

	low = left;
	high = right+1;
	pivot = list[left];

	printf("\n\nPivot : %d\n", pivot);

	do { // low와 high가 엇갈리면 중단

		do {
			++low;
		} while (low <= right && list[low] < pivot);	// 피벗보다 작은 경우 반복, low <= right 는 방어 코드
		
		do {
			--high;
		} while (high >= left && list[high] > pivot);	// 피벗보다 큰 경우 반복, high >= left 는 방어 코드
		
		// low와 high 모두 invalid 값을 가지는 array 인덱스
		printf("Low : %d High : %d", list[low], list[high]);
		print(list, right);

		if (low < high) {
			printf("%d와 %d를 스왑\n", list[low], list[high]);
			swap(&list[low], &list[high], &temp);
			print(list, right);
		}

	} while (low < high);

	swap(&list[left], &list[high], &temp);
	
	return high; // pivot 을 중간 자리(high)로 리턴해서 high 가 pivot 임
}

void quick_sort(int list[], int left, int right)
{
	// 요소가 하나만 있으면 left == right, 돌릴 필요 없음
	if (left < right)
	{
		int q = partition(list, left, right);
		quick_sort(list, left, q-1);	// q가 가운데니까 한 칸 왼쪽으로
		quick_sort(list, q+1, right);	// q가 가운데니까 한 칸 오른쪽으로
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

	printf("정렬전 리스트 >\n");	for (i = 0; i < count; i++) {		printf("%d >", list[i]);	}
	
	quick_sort(list, 0, count-1); // 왜 count-1 일까?

	printf("%d", count);	printf("\n\n정렬된 리스트 >\n");	for (i = 0; i < count; i++) {		printf("%d >", list[i]);	}

	printf("\n\n");

	fclose(fp);
	return 0;
}