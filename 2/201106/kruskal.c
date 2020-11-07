/*
	프로그램명: Kruskal 최소 비용 신장 트리
	작성일: 2020년 11월 6일(금)
	학번: 20184014
	이름: 이승준
*/
#include <stdio.h>

#define MAX_VERTICES	100

* union find 에서 사용하는 코드 */
int parent[MAX_VERTICES];
int num[MAX_VERTICES];

void set_init(int n)
{
	int i;

	for (i=0; i<n; ++i) {
		parent[i] = -1;
		num[i] = 1;
	}
}

int set_find(int vertex)
{
	int p, s, i = -1;
	for (i=vertex; (p = parent[i]) >= 0; i = p);

	s = i;

	for (i=vertex; (p = parent[i]) >= 0; i = p)
		parent[i] = s;

	return s;
}

// 두개의 vertex 가 속한 그래프를 merge
int set_union(int s1, int s2)
{
	if (num[s1] < num[s2]) {
		parent[s1] = s2;
		num[s2] += num[s1];
	}
	else {
		parent[s2] = s1;
		num[s1] += num[s2];
	}
}

* min heap tree 를 위한 코드 */
typedef struct {
	int key;		// weight
	int u;			// from node
	int v;			// to node
} element;

typedef struct {
	element heap[MAX_VERTICES];
	int heap_size;
} HeapType;

void init(HeapType *h)
{
	h->heap_size = 0;
}

int is_empty(HeapType *h)
{
	return h->heap_size == 0;
}

void insert_min_heap(HeapType *h, element item)
{
	int i;
	i = ++(h->heap_size);

	// 루트 노드가 아니고, 입력받은 값이 부모 노드의 값보다 작으면 위로 이동
	while ((i != 1) && (item.key < h->heap[i/2].key)) {
		h->heap[i] = h->heap[i/2];
		i /= 2;
	}
	h->heap[i] = item;
}

element delete_min_heap(HeapType *h){	int parent, child;	element item, temp;	item = h->heap[1];	temp = h->heap[(h->heap_size)--];	parent = 1;	child = 2;	while (child <= h->heap_size)	{		if ((child < h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key)			++child;		if (temp.key <= h->heap[child].key)			break;		h->heap[parent] = h->heap[child];		parent = child;		child *= 2;	}	h->heap[parent] = temp;	return item;}

* kruskal 알고리즘 */

void insert_heap_edge(HeapType *h, int u, int v, int weight)
{
	element e;
	e.u = u;
	e.v = v;
	e.key = weight;

	insert_min_heap(h, e);
}

void insert_all_edge(HeapType *h)
{
	FILE *fp;
	int temp1, temp2, temp3;

	fp = fopen("data2.txt", "r");
	if (fp == NULL) {
		printf("file not found");
		return;
	}

	while (!feof(fp)) {
		fscanf(fp, "%d %d %d", &temp1, &temp2, &temp3);
		insert_heap_edge(h, temp1, temp2, temp3);
	}

	fclose(fp);
}

void kruskal(int n) // n = node count
{
	int edge_accepted = 0;
	int uset, vset;
	HeapType h;
	element e;

	init(&h);				// initialize heap tree
	insert_all_edge(&h);	// read-in the data file and insert into heap tree
	set_init(n);			// initialize union-find variables
	// data fetch and insert into min heap tree

	// min spanning tree
	while (edge_accepted < (n - 1)) {
		e = delete_min_heap(&h);
		uset = set_find(e.u);
		vset = set_find(e.v);

		if (uset != vset) {
			// 사이클이 아님
			printf("(%d, %d) %d\n", e.u, e.v, e.key);
			++edge_accepted;
			set_union(uset, vset);
		}
	}
}

int main()
{
	int temp1, temp2, temp3;	// from vertex, to vertex, weight
	int max = 0;					// 노드가 얼마나 있는지 카운트
	FILE *fp;
	fp = fopen("data2.txt", "r");
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

	kruskal(max + 1);			// 0 노드부터 시작하므로 실제 개수는 하나 더 많음

	fclose(fp);
	return 0;
}