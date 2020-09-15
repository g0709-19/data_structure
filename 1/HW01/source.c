//////////////////////////////////////////////////////
// �ۼ��� : �̽���
// �ۼ��� : 2020�� 3�� 26��
// ���α׷��� : ����������� �̿��� �ִ�, �ּҰ� ���
//////////////////////////////////////////////////////

#include <stdio.h>

#define MAX_DATA 10000 // �ҷ��� �����͸� ������ �迭�� ũ��
#define MIN_DATA 50 // �ҷ��� �������� �ּ� ����
#define WIDTH 5 // ����� ������ �����ϴ� ������ ����

int main() {
	int i = 0, j = 0; // �ݺ����� ���� �ӽ� ����
	int pos = 0; // �ִ밪, �ּҰ� ���� ��� ��ġ�� ���� ����
	int max = 0, min = 0; // �ִ밪, �ּҰ�
	int each = 0, line = 0; // �� �ٿ� ����� ������ ����, ����� �� ��
	int data[MAX_DATA] = { 0, }, size = 0; // ���Ͽ��� �ҷ��� ������, �ҷ��� ������ ����
	FILE *fp = NULL;
	fp = fopen("data.txt", "r");
	if(fp == NULL) // ������ �������� �ҷ��Դ��� �˻�
	{
		printf("������ �ҷ��� �� �����ϴ�.\n");
		return 0;
	}
	for(i=0; !feof(fp); ++i) // ���Ͽ��� �о�� �����͸� �迭�� �����ϴ� ���ÿ� �ִ밪, �ּҰ� �Ǻ�
	{
		if(i>=MAX_DATA) // ����Ǿ� �ִ� ������ ���� ������ ������� �˻�
		{
			size = MIN_DATA-1;
			break;
		}
		fscanf(fp, "%d", &data[i]);
		if(i == 0) // �ٸ� ����� ���ϱ� ���� �ʱⰪ ����
		{
			max = min = data[i];
		}
		if(data[i] > max) // �ִ밪 �Ǻ�
		{
			max = data[i];
		}
		else if(data[i] < min) // �ּҰ� �Ǻ�
		{
			min = data[i];
		}
		++size;
	}
	if(size < MIN_DATA) // ����Ǿ� �ִ� ������ ���� ������ ������� �˻�
	{
		printf("����Ǿ� �ִ� ������ %d�� �̻� %d�� ���Ͽ��� �մϴ�.\n", MIN_DATA, MAX_DATA);
		return 0;
	}
	printf("��� �����;� ��������� ������ �ּ���: ");
	scanf("%d", &each);
	for(i=0; i<each; ++i) // 1, 2, 3, ..., each ���
	{
		printf("%*d", WIDTH, i+1);
	}
	printf("\n");
	for(i=0; i<each*WIDTH; ++i) // ====....== ���
	{
		printf("=");
	}
	printf("\n");
	line = size / (double)each + (size % each == 0 ? 0 : 1);
	for(i=0; i<line; ++i) // line ��ŭ �� ���
	{
		for(j=i*each; j<each*(i+1) && j<size; ++j) // each ��ŭ ������ ���
		{
			printf("%*d", WIDTH, data[j]);
		}
		printf("%\n");
		pos = 0; // ���� �ٲ�Ƿ� ��� ��ġ �ʱ�ȭ
		for(j=i*each; j<each*(i+1) && j<size; ++j) // �ִ밪, �ּҰ� ���� ����� ���� ��� ������ �˻�
		{
			for(; pos<(j-(i*each))*WIDTH; ++pos) // ���� �������� ĭ���� Ŀ�� �̵�
			{
				printf(" ");
			}
			if(data[j] == max) // �ִ밪 ���� �˻� �� ���
			{
				printf("�ִ밪");
				pos += 6;
			}
			else if(data[j] == min) // �ּҰ� ���� �˻� �� ���
			{
				printf("�ּҰ�");
				pos += 6;
			}
		}
		printf("\n");
		for(j=0; j<each*WIDTH; ++j) // ----....-- ���
		{
			printf("-");
		}
		printf("\n");
	}
	printf("\n");
	fclose(fp);
	return 0;
}