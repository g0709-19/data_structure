/*
	�׷��� ���� ���� ���α׷�
	�ۼ���: 2020�� 11�� 13��(��)
	�й�: 20184014
	�̸�: �̽���
*/

#include <stdio.h>
#include <stdlib.h>

#define TRUE	1
#define FALSE	1
#define MAX_VERTICES	50
#define MAX_STACK_SIZE	100

void error(char *msg)
{
	fprintf(stdout, msg);
	exit(1);
}

typedef struct GraphNode {
	int vertex;
	struct GraphNode *link;
} GraphNode;

typedef struct GraphType {
	int n;
	GraphNode *adj_list[MAX_VERTICES];
} GraphType;

void graph_init(GraphType *g)
{
	int v;
	g->n = 0;
	for (v=0; v<MAX_VERTICES; ++v)
		g->adj_list[v] = NULL;
}

void insert_vertex(GraphType *g, int v)
{
	if ((g->n + 1) > MAX_VERTICES)
		error("�׷��� ������ �ʰ�\n");
	++g->n;
}

void insert_edge(GraphType *g, int u, int v)
{
	GraphNode *node;

	if (u >= g->n || v >= g->n)
		error("�׷��� ���� ����\n");

	node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = v; // v = 0; u = 2, 3, ...
	if (g->adj_list[u] != NULL)
		printf("�� ��� %d\n", g->adj_list[u]->vertex);
	node->link = g->adj_list[u]; // �������� �ϳ��� ����
	g->adj_list[u] = node;
}

// ���� �ҽ� Ȱ��
typedef int element;
typedef struct {
	element stack[MAX_STACK_SIZE];
	int top;
} StackType;

void init(StackType *s)
{
	s->top = -1;
}

int is_empty(StackType *s)
{
	return s->top == -1;
}

int is_full(StackType *s)
{
	return s->top == MAX_STACK_SIZE;
}

void push(StackType *s, element item)
{
	if (is_full(s))
		error("Stack full\n");
	s->stack[++s->top] = item;
}

element pop(StackType *s)
{
	if (is_empty(s))
		error("Stack underflow\n");
	return s->stack[s->top--];
}

element peek(StackType *s)
{
	if (is_empty(s))
		error("Stack underflow\n");
	return s->stack[s->top];
}

void topo_sort(GraphType *g)
{
	int i, u, w;
	int *in_degree;
	StackType s;
	GraphNode *node;
	init(&s);

	in_degree = (int*)malloc(g->n * sizeof(int));

	// �������� �迭 �ʱ�ȭ
	for (i=0; i<g->n; ++i)
		in_degree[i] = 0;

	for (i=0; i<g->n; ++i) {
		node = g->adj_list[i];
		// ��������Ʈ�� �ϳ��� ������ �������� ���
		while (node != NULL) {
			++in_degree[node->vertex];
			node = node->link;
		}
	}

	// ���� �ʱ�ȭ
	init(&s);

	for (i=0; i<g->n; ++i)
		if (in_degree[i] == 0)	// ���������� 0�� ��� ����
			push(&s, i);

	while (!is_empty(&s)) {		// ���������� 0�� ��尡 ����������..
		w = pop(&s);
		printf("%d ", w);
		node = g->adj_list[w];

		while (node != NULL) {	// ���������� 0�� ���� ����� ��� ������ ����
			u = node->vertex;
			--in_degree[u];
			if (in_degree[u] == 0)
				push(&s, u);	// ���� ���� �� ���������� 0�� �Ǹ� ���ÿ� ����
			node = node->link;
		}
	}

	free(in_degree);
}

int main()
{
	int i, j;	// two dimensional array
	char flag;	// v or e
	int ver1, edge1, edge2;

	GraphType g;

	FILE *fp;
	fp = fopen("data2.txt", "r");
	if (fp == NULL) error("File not found!\n");

	graph_init(&g);
	
	// ����ġ �Ҵ�
	while (!feof(fp)) {
		fscanf(fp, "%c", &flag);
		
		if (flag == 'v') {
			fscanf(fp, "%d", &ver1);
			
			insert_vertex(&g, ver1);	// node count++
		}
		else if (flag == 'e') {
			fscanf(fp, "%d %d", &edge1, &edge2);

			insert_edge(&g, edge1, edge2); // ���Ḯ��Ʈ�� �������� ����
		}
	}

	topo_sort(&g);
	printf("\n");

	fclose(fp);
	return 0;
}