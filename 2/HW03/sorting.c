/*
	text.txt 파일에 있는 문자 데이터를 읽어
	들여 지금까지 배운 정렬 방법들(삽입, 선택
	버블, 쉘, 퀵, 히프, 합병)을 모두 적용하여
	정렬하는 프로그램을 작성하고 각 정렬별
	수행 시간 결과를 토대로 성능을
	분석하시오
	- 제공하는 프로그램으로 문자를 랜덤하게 생성해서 저장할 것
	- 동적 할당을 이용하여 메모리를 할당 할 것
	작성일: 2020년 11월 28일(토)
	학번: 20184014
	이름: 이승준
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LENGTH	100	// 입력받는 문자열 길이

typedef struct {
	clock_t start, end;
} Runtime;

typedef struct {
	char** heap;
	int heap_size;
} HeapType;

// 수행시간 반환 함수
float getRuntime(Runtime runtime)
{
	return (float)(runtime.end-runtime.start)/CLOCKS_PER_SEC;
}

// 에러 출력 함수
void error(char *msg)
{
	printf("%s", msg);
	exit(1);
}

// 동적할당 해제 함수
void free_list(char **list, int size)
{
	int i;
	for (i=0; i<size; ++i)
		free(list[i]);
	free(list);
}

// 한 프로그램에서 여러 정렬을 구현하려면 배열 복사가 필요했음
// copied 에 list 의 내용을 복사하는 함수
void copy(char **copied, char **list, int size)
{
	int i;
	for (i=0; i<size; ++i)
		strcpy(copied[i], list[i]);
}

// #define SWAP(x, y, temp) ((temp) = (x), (x) = (y), (y) = (temp))
// 매크로는 효율 떨어짐, 50번 하면 50번 다 교체해야됨
void swap(char **x, char **y)
{
	char *temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

// 배열 출력 함수
void print(char **list, int size)
{
	int i;
	for (i=0; i<size; ++i)
		printf("[%d] %s\n", i, list[i]);
	printf("\n");
}

/* ***********************삽입 정렬************************* */

void insertion_sort(char** list, int n)
{
	int i, j;
	char* temp;

	// 정렬이 안된 list[0] 과 정렬이 된 나머지를 비교
	for (i=1; i<n; ++i) {
		temp = list[i];

		for (j=i-1; j>=0 && strcmp(list[j], temp) > 0; --j) {
			list[j+1] = list[j];	// 레코드를 오른쪽으로 이동
		}

		list[j+1] = temp;
	}
}

/* ***********************선택 정렬************************* */
// 정렬이 안된 숫자 중에서 최소 숫자를 선택
void selection_sort(char** list, int n)
{
	int i, j;
	int least;	// 최소값
	char* temp;
	// 왜 n-1 일까? 하나가 정렬 되어있다고 가정하기 때문
	for (i=0; i<n-1; ++i) {
		least = i;	// 실제 최소값일지는 모르지만 초기값 설정
		for (j=i+1; j<n; ++j) {
			if (strcmp(list[j], list[least]) < 0)
				least = j;
		}
		temp = list[i];
		list[i] = list[least];
		list[least] = temp;
	}
}

/* ***********************버블 정렬************************* */

void bubble_sort(char** list, int n)
{
	int i, j;
	char* temp;
	
	// i는 끝에서 왼쪽으로
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

/* ***********************쉘 정렬************************* */

void inc_insertion_sort(char **list, int first, int last, int gap)
{
	int i, j;
	char *key;

	// i는 j보다 항상 한 칸 뒤에 있는 인덱스를 가리킴
	for (i=first+gap; i<=last; i=i+gap) {
		key = list[i];	// key 를 변경하는 일은 없기 때문에 레퍼런스를 넘겨줘도 상관 없음

		// j는 i보다 항상 한 칸 앞에 있는 인덱스를 가리키면서
		// j가 i의 값, 즉 key 보다 크면 i의 위치에 j의 값을 넣어줌
		for (j=i-gap; j>=first && strcmp(list[j], key) > 0; j=j-gap) {
			list[j+gap] = list[j];
		}

		// j=j-gap 으로 j의 원래 위치보다 한 칸 앞으로 왔으므로 j+gap 에 i에 있던 값, 즉 key 를 넣어줌
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

/* ***********************퀵 정렬************************* */
int partition(char **list, int left, int right)
{
	char *pivot;
	// low는 피벗보다 작으면 우측으로(++) 이동, 크면 정지
	// high는 피벗보다 크면 좌측으로(--) 이동, 작으면 정지
	int low, high;

	low = left;
	high = right+1;
	pivot = list[left];

	do { // low와 high가 엇갈리면 중단

		do {
			++low;
		} while (low < right && strcmp(list[low], pivot) < 0);	// 피벗보다 작은 경우 반복, low <= right 는 방어 코드

		do {
			--high;
		} while (high >= left && strcmp(list[high], pivot) > 0);	// 피벗보다 큰 경우 반복, high >= left 는 방어 코드

		if (low < high)
			swap(&list[low], &list[high]);

	} while (low < high);

	swap(&list[left], &list[high]);
	
	return high; // pivot 을 중간 자리(high)로 리턴해서 high 가 pivot 임
}

void quick_sort(char **list, int left, int right)
{
	// 요소가 하나만 있으면 left == right, 돌릴 필요 없음
	if (left < right)
	{
		int q = partition(list, left, right);
		quick_sort(list, left, q-1);	// q가 가운데니까 한 칸 왼쪽으로
		quick_sort(list, q+1, right);	// q가 가운데니까 한 칸 오른쪽으로
	}
}

/* ***********************히프 정렬*********************** */

void init_heap(HeapType *h, int size)
{
	int i;
	size += 1;
	h->heap = (char**)malloc(sizeof(char*)*(size+1));	// heap 은 인덱스를 1부터 지정하므로 원래 크기보다 1 많이 할당
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
	
	strcpy(*t, h->heap[1]);	// item = h->heap[1] 로 했을 때 레퍼런스가 복사돼서 heap 에서 꺼낸 값에 변경이 있었음
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// 작은 자식에게 붙여주기 위한 조건문
		if ((child < h->heap_size) &&
			strcmp(h->heap[child], h->heap[child + 1]) > 0)
			++child;
		// 이 경우 temp 가 child 와 같은 레벨에 있음
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
	char *temp = (char*)malloc(sizeof(char)*MAX_LENGTH);	// heap 에서 가져온 값 담아두는 변수
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

/* ***********************합병 정렬*********************** */

char **sorted;	// 추가 공간 필요

void merge(char **list, int left, int mid, int right)
{
	int i, j, k, l;
	i = left;
	j = mid + 1;
	k = left;

	// 분할 정렬된 list의 합병
	while (i <= mid && j <= right) {
		if (strcmp(list[i], list[j]) <= 0)
			sorted[k++] = list[i++];
		else
			sorted[k++] = list[j++];
	}
	if (i>mid)	// 남아 있는 레코드의 일괄 복사
		for (l=j; l<=right; ++l)
			sorted[k++] = list[l];
	else
		for (l=i; l<=mid; ++l)
			sorted[k++] = list[l];
	// 배열 sorted의 리스트를 배열 list로 재복사
	for (l=left; l<=right; ++l)
		list[l] = sorted[l];
}

void merge_sort(char **list, int left, int right)
{
	int mid;
	if (left<right) {
		mid = (left + right) / 2;		// 리스트의 균등 분할
		merge_sort(list, left, mid);	// 부분 리스트 정렬
		merge_sort(list, mid+1, right);	// 부분 리스트 정렬
		merge(list, left, mid, right);	// 합병
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

	// text.txt 파일에 있는 문자 데이터의 개수 측정
	while(!feof(fp)) {
		// 제공된 프로그램 사용해서 만들어진 텍스트 파일은 끝에 공백이 하나 포함되어 생성됨
		// 그래서 마지막 공백 문자까지 입력받던걸 예외 처리했음
		if (fscanf(fp, "%s", temp) == EOF)
			break;
		++count;
	}

	list = (char**)malloc(sizeof(char*)*count);		// 입력받은 문자열 개수만큼 char형 배열 담을 배열 동적할당
	copied = (char**)malloc(sizeof(char*)*count);	// 여러 정렬 구현하기 위해 복사할 배열
	sorted = (char**)malloc(sizeof(char*)*count);	// 합병 정렬을 위한 추가 배열

	rewind(fp);
	i = 0;

	// text.txt 파일에 있는 문자 데이터를 list에 삽입
	while(!feof(fp)) {
		if (fscanf(fp, "%s", temp) == EOF)
			break;

		list[i] = (char*)malloc(sizeof(char)*MAX_LENGTH);	// 문자열 받을 공간 동적할당, 동적할당과 삽입 동시에 해서 시간 절약
		copied[i] = (char*)malloc(sizeof(char)*MAX_LENGTH);	// 여러 정렬 구현하기 위해 복사할 배열
		sorted[i] = (char*)malloc(sizeof(char)*MAX_LENGTH);	// 합병 정렬을 위한 추가 배열

		strcpy(list[i], temp);
		++i;
	}
	
	printf("입력받은 문자열의 개수: %d\n", count);
	printf("\n[정렬 결과]\n");

	// 삽입 정렬
	copy(copied, list, count);

	runtime.start = clock();
	insertion_sort(copied, count); // 인덱스는 n-1 까지 있음
	runtime.end = clock();

	printf("삽입 정렬: %f초\n", getRuntime(runtime));

	// 선택 정렬
	copy(copied, list, count);

	runtime.start = clock();
	selection_sort(copied, count); // 인덱스는 n-1 까지 있음
	runtime.end = clock();

	printf("선택 정렬: %f초\n", getRuntime(runtime));

	// 버블 정렬
	copy(copied, list, count);

	runtime.start = clock();
	bubble_sort(copied, count); // 인덱스는 n-1 까지 있음
	runtime.end = clock();

	printf("버블 정렬: %f초\n", getRuntime(runtime));

	// 쉘 정렬
	copy(copied, list, count);

	runtime.start = clock();
	shell_sort(copied, count); // 인덱스는 n-1 까지 있음
	runtime.end = clock();

	printf("쉘 정렬: %f초\n", getRuntime(runtime));

	// 퀵 정렬
	copy(copied, list, count);

	runtime.start = clock();
	quick_sort(copied, 0, count-1); // 인덱스는 n-1 까지 있음
	runtime.end = clock();

	printf("퀵 정렬: %f초\n", getRuntime(runtime));
	
	// 히프 정렬
	copy(copied, list, count);

	runtime.start = clock();
	heap_sort(copied, count); // 인덱스는 n-1 까지 있음
	runtime.end = clock();

	printf("히프 정렬: %f초\n", getRuntime(runtime));

	// 합병 정렬
	copy(copied, list, count);

	runtime.start = clock();
	merge_sort(copied, 0, count-1); // 인덱스는 n-1 까지 있음
	runtime.end = clock();

	printf("합병 정렬: %f초\n", getRuntime(runtime));

	// 동적할당 해제
	for (i=0; i<count; ++i)
		free(list[i]);
	free(list);

	fclose(fp);	// 파일 닫기
	return 0;
}