/*
	﻿﻿data.txt 파일에 학번, 이름, 총점이 저장 되어 있다.
	이 정보를 동적 할당을 이용하여 단순 연결 리스트로 입력 받아 저장하고,
	이 연결리스트를 이용하여 학번, 이름, 총점 순으로 정렬이 되도록 프로그램을 작성하시오.

	- 학번으로 정렬: 선배 먼저
	- 이름으로 정렬: ㄱ 먼저
	- 총점으로 정렬:높은 점수 먼저

	작성자:	이승준
	학번:	20184014
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE	20

typedef double SCORE_DATA_TYPE;

typedef struct Student
{
	int id;
	char name[NAME_SIZE];
	SCORE_DATA_TYPE score;
}
Student;

typedef struct List
{
	Student data;
	struct List *link;
}
List;

void initList(List **item)
{
	*item = (List*)malloc(sizeof(List));
}

void set(List **item, int id, char name[], SCORE_DATA_TYPE score)
{
	(*item)->data.id = id;
	strcpy((*item)->data.name, name);
	(*item)->data.score = score;
	(*item)->link = NULL;
}

void swap(List **list1, List **list2)
{
	Student temp = (*list1)->data;
	(*list1)->data = (*list2)->data;
	(*list2)->data = temp;
}

void sortById(List *head)
{
	List *p = head;

	// 모든 요소 검사
	while(p != NULL)
	{
		List *p2 = p->link;
		// p를 포함하지 않는 모든 요소 검사
		while(p2 != NULL)
		{
			// 오름차순 정렬
			if (p->data.id > p2->data.id)
			{
				swap(&p, &p2);
			}
			p2 = p2->link;
		}
		p = p->link;
	}
}

void sortByName(List *head)
{
	List *p = head;

	// 모든 요소 검사
	while(p != NULL)
	{
		List *p2 = p->link;
		// p를 포함하지 않는 모든 요소 검사
		while(p2 != NULL)
		{
			// 오름차순 정렬
			if (strcmp(p->data.name, p2->data.name) > 0)
			{
				swap(&p, &p2);
			}
			p2 = p2->link;
		}
		p = p->link;
	}
}

void sortByScore(List *head)
{
	List *p = head;

	// 모든 요소 검사
	while(p != NULL)
	{
		List *p2 = p->link;
		// p를 포함하지 않는 모든 요소 검사
		while(p2 != NULL)
		{
			// 내림차순 정렬
			if (p->data.score < p2->data.score)
			{
				swap(&p, &p2);
			}
			p2 = p2->link;
		}
		p = p->link;
	}
}

void printList(List *head)
{
	List *tempList;

	printf("학번\t\t이름\t총점\n");
	for (tempList = head; tempList != NULL; tempList = tempList->link)
	{
		printf("%d\t%s\t%.1lf\n", tempList->data.id, tempList->data.name, tempList->data.score);
	}
	printf("\n");
}

int countList(FILE *fp)
{
	int size = 0;

	int tempId;
	char tempName[NAME_SIZE];
	SCORE_DATA_TYPE tempScore;

	while (!feof(fp))
	{
		fscanf(fp, "%d %s %lf", &tempId, &tempName, &tempScore);
		++size;
	}

	rewind(fp);
	return size;
}

void inputList(FILE *fp, List **head, int size)
{
	int i;

	List **current;
	int tempId;
	char tempName[NAME_SIZE];
	SCORE_DATA_TYPE tempScore;

	for (i=0; i<size; ++i)
	{
		fscanf(fp, "%d %s %lf", &tempId, &tempName, &tempScore);

		// Head 없으면 생성
		if (*head == NULL)
		{
			initList(&(*head));
			set(&(*head), tempId, tempName, tempScore);
			current = head;
		}

		// Head 있으면 현재 요소 뒤에 삽입
		else
		{
			List *item;
			initList(&item);
			set(&item, tempId, tempName, tempScore);
			(*current)->link = item;
			current = &(*current)->link;
		}
	}
	printf("학생 %d명의 정보를 불러왔습니다.\n", size);
}

int main()
{
	int size = 0;
	List *head = NULL;
	FILE *fp = NULL;

	fp = fopen("data.txt", "r");

	// 개수 세기
	size = countList(fp);	

	// 입력
	inputList(fp, &head, size);

	// 학번 순 정렬 출력
	printf("학번 순 정렬 출력\n");
	sortById(head);
	printList(head);

	// 이름 순 정렬 출력
	printf("이름 순 정렬 출력\n");
	sortByName(head);
	printList(head);

	// 총점 순 정렬 출력
	printf("총점 순 정렬 출력\n");
	sortByScore(head);
	printList(head);

	fclose(fp);
	return 0;
}