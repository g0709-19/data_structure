//////////////////////////////////////////////////////
// 작성자 : 이승준
// 작성일 : 2020년 3월 26일
// 프로그램명 : 파일입출력을 이용한 최대, 최소값 출력
//////////////////////////////////////////////////////

#include <stdio.h>

#define MAX_DATA 10000 // 불러온 데이터를 저장할 배열의 크기
#define MIN_DATA 50 // 불러온 데이터의 최소 개수
#define WIDTH 5 // 출력한 정수가 차지하는 공간의 길이

int main() {
	int i = 0, j = 0; // 반복문을 위한 임시 변수
	int pos = 0; // 최대값, 최소값 여부 출력 위치를 위한 변수
	int max = 0, min = 0; // 최대값, 최소값
	int each = 0, line = 0; // 한 줄에 출력할 데이터 개수, 출력할 줄 수
	int data[MAX_DATA] = { 0, }, size = 0; // 파일에서 불러온 데이터, 불러온 데이터 개수
	FILE *fp = NULL;
	fp = fopen("data.txt", "r");
	if(fp == NULL) // 파일이 오류없이 불려왔는지 검사
	{
		printf("파일을 불러올 수 없습니다.\n");
		return 0;
	}
	for(i=0; !feof(fp); ++i) // 파일에서 읽어온 데이터를 배열에 저장하는 동시에 최대값, 최소값 판별
	{
		if(i>=MAX_DATA) // 저장되어 있는 정수의 수가 범위를 벗어나는지 검사
		{
			size = MIN_DATA-1;
			break;
		}
		fscanf(fp, "%d", &data[i]);
		if(i == 0) // 다른 값들과 비교하기 위한 초기값 설정
		{
			max = min = data[i];
		}
		if(data[i] > max) // 최대값 판별
		{
			max = data[i];
		}
		else if(data[i] < min) // 최소값 판별
		{
			min = data[i];
		}
		++size;
	}
	if(size < MIN_DATA) // 저장되어 있는 정수의 수가 범위를 벗어나는지 검사
	{
		printf("저장되어 있는 정수는 %d개 이상 %d개 이하여야 합니다.\n", MIN_DATA, MAX_DATA);
		return 0;
	}
	printf("몇개의 데이터씩 출력할지를 선택해 주세요: ");
	scanf("%d", &each);
	for(i=0; i<each; ++i) // 1, 2, 3, ..., each 출력
	{
		printf("%*d", WIDTH, i+1);
	}
	printf("\n");
	for(i=0; i<each*WIDTH; ++i) // ====....== 출력
	{
		printf("=");
	}
	printf("\n");
	line = size / (double)each + (size % each == 0 ? 0 : 1);
	for(i=0; i<line; ++i) // line 만큼 줄 출력
	{
		for(j=i*each; j<each*(i+1) && j<size; ++j) // each 만큼 데이터 출력
		{
			printf("%*d", WIDTH, data[j]);
		}
		printf("%\n");
		pos = 0; // 줄이 바뀌므로 출력 위치 초기화
		for(j=i*each; j<each*(i+1) && j<size; ++j) // 최대값, 최소값 여부 출력을 위해 모든 데이터 검사
		{
			for(; pos<(j-(i*each))*WIDTH; ++pos) // 현재 데이터의 칸으로 커서 이동
			{
				printf(" ");
			}
			if(data[j] == max) // 최대값 여부 검사 후 출력
			{
				printf("최대값");
				pos += 6;
			}
			else if(data[j] == min) // 최소값 여부 검사 후 출력
			{
				printf("최소값");
				pos += 6;
			}
		}
		printf("\n");
		for(j=0; j<each*WIDTH; ++j) // ----....-- 출력
		{
			printf("-");
		}
		printf("\n");
	}
	printf("\n");
	fclose(fp);
	return 0;
}