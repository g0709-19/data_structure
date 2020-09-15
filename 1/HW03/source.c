/*
	����: ��� ������ �����ϴ� ���α׷�
	����: ���� �����͸� �Է� �޾Ƽ� ��� ������ �����ϰ�
	�� ����� ȭ�鿡 ����ϴ� ���α׷�
	�ۼ�����: 2020�� 5�� 7��
	�̸�: �̽���
*/
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

#define MATRIX_AMOUNT 2
#define COLUMN 3 // ��, ��, ��
#define OPERATOR 3 // ���� ��

void printToDense(int **sparse, int *data);
int getUnionSize(int **A, int **B, int *data);
int** add(int **A, int **B, int *row, int *column, int *data, int *resultSize);
int** sub(int **A, int **B, int *row, int *column, int *data, int *resultSize);
int** mul(int **A, int **B, int *row, int *column, int *data, int *resultSize);

int main()
{
	int i, j; // �ݺ��� �ӽ� ����
	int _i, _j; // �ݺ��� ���� ��� ��� �ε���
	int count[MATRIX_AMOUNT] = {0}; // �о�� ���� ���� ��Ƶδ� �ӽ� ����
	int temp; // �о�� �� ��Ƶδ� �ӽ� ����
	int w; //  ��� �ε���
	int row[MATRIX_AMOUNT], column[MATRIX_AMOUNT]; // ���Ͽ��� �Է¹޴� ��, �� ��
	int **matrix[MATRIX_AMOUNT]; // �������� ����
	int **result[OPERATOR]; // ���� ���
	int resultSize[OPERATOR]; // ���� ����� ������ ����
	FILE *fp;
	fp = fopen("data.txt", "r");
	if (fp == NULL)
	{
		printf("FILE NOT FOUND\n");
		return 0;
	}
	// �����Ҵ� ���� ���� �˾Ƶα�
	for (w=0; w<MATRIX_AMOUNT; ++w)
	{
		fscanf(fp, "%d %d", &row[w], &column[w]);
		// row, column ��ŭ �а� �Ҵ��� 0�� �ƴ� ���� ������ŭ��
		i = j = 0;
		while (!feof(fp))
		{
			fscanf(fp, "%d", &temp);
			if (temp != 0)
				++count[w];
			// row, column ��ŭ �б� ���� ���ǹ�
			if (j+1 == column[w])
			{
				j = 0;
				if (++i == row[w])
					break;
			}
			else
			{
				++j;
			}
		}
	}
	rewind(fp);
	// �����Ҵ�, ������ ����
	for (w=0; w<MATRIX_AMOUNT; ++w)
	{
		matrix[w] = (int**)malloc(sizeof(int*)*count[w]);
		if (matrix[w] == NULL)
		{
			printf("MEMORY ALLOCATION ERROR\n");
			return 0;
		}
		for (i=0; i<count[w]; ++i)
		{
			matrix[w][i] = (int*)malloc(sizeof(int)*COLUMN);
			if (matrix[w][i] == NULL)
			{
				printf("MEMORY ALLOCATION ERROR\n");
				return 0;
			}
		}
		fscanf(fp, "%d %d", &row[w], &column[w]);
		// row, column ��ŭ �а� �Ҵ��� 0�� �ƴ� ���� ������ŭ��
		i = j = 0;
		_i = _j = 0;
		while (!feof(fp))
		{
			fscanf(fp, "%d", &temp);
			// 0�� �ƴ� ���� ����
			if (temp != 0)
			{
				matrix[w][_i][0] = i;
				matrix[w][_i][1] = j;
				matrix[w][_i][2] = temp;
				++_i;
			}
			// row, column ��ŭ �б� ���� ���ǹ�
			if (j+1 == column[w])
			{
				j = 0;
				if (++i == row[w])
					break;
			}
			else
			{
				++j;
			}
		}
	}
	//���
	result[0] = add(matrix[0], matrix[1], row, column, count, resultSize);
	result[1] = sub(matrix[0], matrix[1], row, column, count, resultSize);
	result[2] = mul(matrix[0], matrix[1], row, column, count, resultSize);



	//���
	for (w=0; w<MATRIX_AMOUNT; ++w)
	{
		printf("��� %d\n", w);
		printToDense(matrix[w], count[w]);
		printf("\n");
	}

	//��°� ���ÿ� result �Ҵ� ����
	printf("�� ����� ����, ����, ���� ���� ����� ������ �����ϴ�.\n\n");
	for (w=0; w<OPERATOR; ++w)
	{
		if (result[w] == NULL)
		{
			if (w == 0) printf("���� �� �����ϴ�.\n");
			else if (w == 1) printf("�� �� �����ϴ�.\n");
			else if (w == 2) printf("���� �� �����ϴ�.\n");
			continue;
		}
		printToDense(result[w], resultSize[w]);
		printf("\n");
		for (i=0; i<resultSize[w]; ++i)
			free(result[w][i]);
		free(result[w]);
	}

	for (w=0; w<MATRIX_AMOUNT; ++w)
	{
		for (i=0; i<count[w]; ++i)
			free(matrix[w][i]);
		free(matrix[w]);
	}
	fclose(fp);
	return 0;
}

void printToDense(int **sparse, int size)
{
	int row, column, temp; // �ӽ� ����
	int _temp = 0; // �´��� �ƴ���
	int r = 0, c = 0; // ��� ��� ������
	int i, j;
	int _i, _j;
	// �����Ͱ� ������ ����� �ʿ䰡 ����
	if (size == 0)
		return;
	// ���� ��� ���·� ������ �۾�
	for (i = 0; i<size; ++i)
		if (r < sparse[i][0])
			r = sparse[i][0];
	for (i = 0; i<size; ++i)
		if (c < sparse[i][1])
			c = sparse[i][1];
	++r, ++c;
	for (i=0; i<r; ++i)
	{
		for (j=0; j<c; ++j)
		{
			for (_i=0; _i<size; ++_i)
			{
				row = sparse[_i][0];
				column = sparse[_i][1];
				temp = sparse[_i][2];
				if (i == row && j == column)
				{
					printf("%3d ", temp);
					_temp = 1;
				}
			}
			// ������ �����Ϳ� ���Ե��� ������
			if (_temp == 0)
				printf("%3d ", 0);
			_temp = 0;
		}
		printf("\n");
	}
}

int getUnionSize(int **A, int **B, int *data)
{
	int i, j;
	int same = 0;
	for (i=0; i<data[0]; ++i)
	{
		for (j=0; j<data[1]; ++j)
		{
			if (A[i][0] == B[j][0] && A[i][1] == B[j][1])
			{
				++same;
				break;
			}
		}
	}
	return data[0] + data[1] - same;
}

int** add(int **A, int **B, int *row, int *column, int *data, int *resultSize)
{
	// �������� ũ�� = A��İ� B����� �������� ũ��
	int i, j;
	int temp = 0; // �´��� �ƴ��� �ӽ� ����
	int _i = 0; // result �� ����Ű�� �ε���
	int size = 0; // result �� �������� ��
	int **result;
	// ��� A�� B�� ũ�Ⱑ ���� ������ ���� X
	if (row[0] != row[1] || column[0] != column[1])
		return NULL;
	size = getUnionSize(A, B, data);
	result = (int**)malloc(sizeof(int*)*size);
	if (result == NULL)
	{
		printf("MEMORY ALLOCATION ERROR\n");
		return NULL;
	}
	for (i=0; i<size; ++i)
	{
		result[i] = (int*)malloc(sizeof(int)*COLUMN);
		if (result[i] == NULL)
		{
			printf("MEMORY ALLOCATION ERROR\n");
			return NULL;
		}
	}
	for (i=0; i<data[0]; ++i)
	{
		// A[i][0] = ��, A[i][1] = ��, A[i][2] = ������
		// R�� ����
		// A[0] ~ A[N] ���� ���µ� �ϳ��ϳ��� B[0] ~ B[N] �� �˻��ؼ� ��, �� ���� �� ���ؼ� R�� ����
		for (j=0; j<data[1]; ++j)
		{
			if (A[i][0] == B[j][0] && A[i][1] == B[j][1])
			{
				result[_i][0] = A[i][0];
				result[_i][1] = A[i][1];
				result[_i][2] = A[i][2] + B[j][2];
				++_i;
				temp = 1;
			}
		}
		// B�� �´°� �ϳ��� ���µ� 0�� �ƴ� ��� �׳� �߰�
		if (temp == 0 && A[i][2] != 0)
		{
			result[_i][0] = A[i][0];
			result[_i][1] = A[i][1];
			result[_i][2] = A[i][2];
			++_i;
		}
		temp = 0;
	}
	for (i=0; i<data[1]; ++i)
	{
		// B[i][0] = ��, B[i][1] = ��, B[i][2] = ������
		// R�� ���� B �߰�
		for (j=0; j<_i; ++j)
		{
			//B�� �˻��ϴµ� R�� ���°� �߰��ϵ� �ߺ� ������
			if (B[i][0] == result[j][0] && B[i][1] == result[j][1])
			{
				temp = 1;
				break;
			}
		}
		// R�� ���� ���
		if (temp == 0)
		{
			result[_i][0] = B[i][0];
			result[_i][1] = B[i][1];
			result[_i][2] = B[i][2];
			if (++_i == size)
			{
				resultSize[0] = size;
				return result;
			}
		}
		temp = 0;
	}
	resultSize[0] = size;
	return result;
}

int** sub(int **A, int **B, int *row, int *column, int *data, int *resultSize)
{
	// �������� ũ�� = A��İ� B����� �������� ũ�� - ���� ���� �� 0�� �Ǵ� ���
	int i, j;
	int temp = 0; // �´��� �ƴ��� �ӽ� ����
	int _i = 0; // result �� ����Ű�� �ε���
	int zero = 0; // ���� ���� �� 0�� �Ǵ� ����� ��
	int size = 0; // result �� �������� ��
	int **result;
	// ��� A�� B�� ũ�Ⱑ ���� ������ ���� X
	if (row[0] != row[1] || column[0] != column[1])
		return NULL;
	for (i=0; i<data[0]; ++i)
		for (j=0; j<data[1]; ++j)
			if ((A[i][0] == B[j][0] && A[i][1] == B[j][1]) &&
				(A[i][2] - B[j][2] == 0))
			{
				++zero;
				break;
			}
	size = getUnionSize(A, B, data)-zero;
	result = (int**)malloc(sizeof(int*)*size);
	if (result == NULL)
	{
		printf("MEMORY ALLOCATION ERROR\n");
		return NULL;
	}
	for (i=0; i<size; ++i)
	{
		result[i] = (int*)malloc(sizeof(int)*COLUMN);
		if (result[i] == NULL)
		{
			printf("MEMORY ALLOCATION ERROR\n");
			return NULL;
		}
	}
	for (i=0; i<data[0]; ++i)
	{
		// A[i][0] = ��, A[i][1] = ��, A[i][2] = ������
		// R�� ����
		// A[0] ~ A[N] ���� ���µ� �ϳ��ϳ��� B[0] ~ B[N] �� �˻��ؼ� ��, �� ���� �� ���� R�� ����
		// �� ���� 0�̶�� �������� ����
		for (j=0; j<data[1]; ++j)
		{
			if (A[i][0] == B[j][0] && A[i][1] == B[j][1])
			{
				temp = 1;
				if (A[i][2] - B[j][2] != 0)
				{
					result[_i][0] = A[i][0];
					result[_i][1] = A[i][1];
					result[_i][2] = A[i][2] - B[j][2];
					++_i;
				}
			}
		}
		// B�� �´°� �ϳ��� ���µ� 0�� �ƴ� ��� �׳� �߰�
		if (temp == 0 && A[i][2] != 0)
		{
			result[_i][0] = A[i][0];
			result[_i][1] = A[i][1];
			result[_i][2] = A[i][2];
			++_i;
		}
		temp = 0;
	}
	for (i=0; i<data[1]; ++i)
	{
		// B[i][0] = ��, B[i][1] = ��, B[i][2] = ������
		// R�� ���� B �߰�
		for (j=0; j<_i; ++j)
		{
			//B�� �˻��ϴµ� R�� ���°� �߰��ϵ� �ߺ� ������
			if (B[i][0] == result[j][0] && B[i][1] == result[j][1])
			{
				temp = 1;
				break;
			}
		}
		// R�� ���� ���
		if (temp == 0)
		{
			// A - B �� 0 �̶�� ��ŵ
			for (j=0; j<data[0]; ++j)
				if (B[i][0] == A[j][0] && B[i][1] == A[j][1])
					temp = 1;
			if (temp == 1)
			{
				temp = 0;
				continue;
			}
			result[_i][0] = B[i][0];
			result[_i][1] = B[i][1];
			result[_i][2] = 0 - B[i][2];
			if (++_i == size)
			{
				resultSize[1] = size;
				return result;
			}
		}
		temp = 0;
	}
	resultSize[1] = _i;
	return result;
}

int** mul(int **A, int **B, int *row, int *column, int *data, int *resultSize)
{
	int i, j;
	int r, c, t;
	int a = 0, b = 0; // �����Ŀ��� ã�ƿ� ��
	int temp = 0; // ���� ���� ��� �ӽ� ����
	int _i = 0; // result �� ����Ű�� �ε���
	int **result;
	// ��� A�� ���� ��� B�� ���� ���� ������ ���� X
	if (column[0] != row[1])
		return NULL;

	// r��� c���� �ش��ϴ� A�� B�� ���Ҹ� ���ؼ� ����
	for (r=0; r<row[0]; ++r)
	{
		for (c=0; c<column[1]; ++c)
		{
			for (j=0; j<column[0]; ++j)
			{
				for (i=0; i<data[0]; ++i)
				{
					if (A[i][0] == r && A[i][1] == j)
					{
						a = A[i][2];
						break;
					}
				}
				for (i=0; i<data[1]; ++i)
				{
					if (B[i][0] == j && B[i][1] == c)
					{
						b = B[i][2];
						break;
					}
				}
				temp += a * b;
				//temp += A[r][j] * B[j][c];
				a = b = 0;
			}
			if (temp != 0)
				++_i;
			//result[r][c] = temp;
			temp = 0;
		}
	}

	result = (int**)malloc(sizeof(int*)*_i);
	if (result == NULL)
	{
		printf("MEMORY ALLOCATION ERROR\n");
		return NULL;
	}
	for (i=0; i<_i; ++i)
	{
		result[i] = (int*)malloc(sizeof(int)*COLUMN);
		if (result[i] == NULL)
		{
			printf("MEMORY ALLOCATION ERROR\n");
			return NULL;
		}
	}


	_i = 0;
	for (r=0; r<row[0]; ++r)
	{
		for (c=0; c<column[1]; ++c)
		{
			for (t=0; t<column[0]; ++t)
			{
				for (i=0; i<data[0]; ++i)
					if (A[i][0] == r && A[i][1] == t)
					{
						a = A[i][2];
						break;
					}
				for (i=0; i<data[1]; ++i)
					if (B[i][0] == t && B[i][1] == c)
					{
						b = B[i][2];
						break;
					}
				temp += a * b;
				a = b = 0;
				//temp += A[r][t] * B[t][c];
			}
			// temp �� 0�� �ƴ϶�� ����
			if (temp != 0)
			{
				result[_i][0] = r;
				result[_i][1] = c;
				result[_i][2] = temp;
				++_i;
			}
			//result[r][c] = temp;
			a = b = temp = 0;
		}
	}
	resultSize[2] = _i;
	return result;
}