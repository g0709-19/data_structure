/*
	제목: 행렬 연산을 수행하는 프로그램
	내용: 파일 데이터를 입력 받아서 행렬 연산을 수행하고
	그 결과를 화면에 출력하는 프로그램
	작성일자: 2020년 5월 7일
	이름: 이승준
*/
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

#define MATRIX_AMOUNT 2
#define COLUMN 3 // 행, 열, 값
#define OPERATOR 3 // 연산 수

void printToDense(int **sparse, int *data);
int getUnionSize(int **A, int **B, int *data);
int** add(int **A, int **B, int *row, int *column, int *data, int *resultSize);
int** sub(int **A, int **B, int *row, int *column, int *data, int *resultSize);
int** mul(int **A, int **B, int *row, int *column, int *data, int *resultSize);

int main()
{
	int i, j; // 반복문 임시 변수
	int _i, _j; // 반복문 안의 희소 행렬 인덱스
	int count[MATRIX_AMOUNT] = {0}; // 읽어온 값의 개수 담아두는 임시 변수
	int temp; // 읽어온 값 담아두는 임시 변수
	int w; //  행렬 인덱스
	int row[MATRIX_AMOUNT], column[MATRIX_AMOUNT]; // 파일에서 입력받는 행, 열 값
	int **matrix[MATRIX_AMOUNT]; // 희소행렬을 저장
	int **result[OPERATOR]; // 연산 결과
	int resultSize[OPERATOR]; // 연산 결과의 데이터 개수
	FILE *fp;
	fp = fopen("data.txt", "r");
	if (fp == NULL)
	{
		printf("FILE NOT FOUND\n");
		return 0;
	}
	// 동적할당 전에 개수 알아두기
	for (w=0; w<MATRIX_AMOUNT; ++w)
	{
		fscanf(fp, "%d %d", &row[w], &column[w]);
		// row, column 만큼 읽고 할당은 0이 아닌 값의 개수만큼만
		i = j = 0;
		while (!feof(fp))
		{
			fscanf(fp, "%d", &temp);
			if (temp != 0)
				++count[w];
			// row, column 만큼 읽기 위한 조건문
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
	// 동적할당, 데이터 저장
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
		// row, column 만큼 읽고 할당은 0이 아닌 값의 개수만큼만
		i = j = 0;
		_i = _j = 0;
		while (!feof(fp))
		{
			fscanf(fp, "%d", &temp);
			// 0이 아닌 값만 저장
			if (temp != 0)
			{
				matrix[w][_i][0] = i;
				matrix[w][_i][1] = j;
				matrix[w][_i][2] = temp;
				++_i;
			}
			// row, column 만큼 읽기 위한 조건문
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
	//결과
	result[0] = add(matrix[0], matrix[1], row, column, count, resultSize);
	result[1] = sub(matrix[0], matrix[1], row, column, count, resultSize);
	result[2] = mul(matrix[0], matrix[1], row, column, count, resultSize);



	//출력
	for (w=0; w<MATRIX_AMOUNT; ++w)
	{
		printf("행렬 %d\n", w);
		printToDense(matrix[w], count[w]);
		printf("\n");
	}

	//출력과 동시에 result 할당 해제
	printf("두 행렬의 덧셈, 뺄셈, 곱셈 연산 결과는 다음과 같습니다.\n\n");
	for (w=0; w<OPERATOR; ++w)
	{
		if (result[w] == NULL)
		{
			if (w == 0) printf("더할 수 없습니다.\n");
			else if (w == 1) printf("뺄 수 없습니다.\n");
			else if (w == 2) printf("곱할 수 없습니다.\n");
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
	int row, column, temp; // 임시 변수
	int _temp = 0; // 맞는지 아닌지
	int r = 0, c = 0; // 출력 행렬 사이즈
	int i, j;
	int _i, _j;
	// 데이터가 없으면 출력할 필요가 없음
	if (size == 0)
		return;
	// 원래 행렬 상태로 돌리는 작업
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
			// 희소행렬 데이터에 포함되지 않으면
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
	// 결과행렬의 크기 = A행렬과 B행렬의 합집합의 크기
	int i, j;
	int temp = 0; // 맞는지 아닌지 임시 변수
	int _i = 0; // result 를 가르키는 인덱스
	int size = 0; // result 의 데이터의 수
	int **result;
	// 행렬 A와 B의 크기가 같지 않으면 연산 X
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
		// A[i][0] = 행, A[i][1] = 열, A[i][2] = 데이터
		// R에 저장
		// A[0] ~ A[N] 까지 가는데 하나하나당 B[0] ~ B[N] 과 검사해서 행, 열 같은 건 더해서 R에 저장
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
		// B와 맞는게 하나도 없는데 0이 아닌 경우 그냥 추가
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
		// B[i][0] = 행, B[i][1] = 열, B[i][2] = 데이터
		// R에 남은 B 추가
		for (j=0; j<_i; ++j)
		{
			//B를 검사하는데 R에 없는거 추가하되 중복 방지도
			if (B[i][0] == result[j][0] && B[i][1] == result[j][1])
			{
				temp = 1;
				break;
			}
		}
		// R에 없는 경우
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
	// 결과행렬의 크기 = A행렬과 B행렬의 합집합의 크기 - 값을 뺐을 때 0이 되는 경우
	int i, j;
	int temp = 0; // 맞는지 아닌지 임시 변수
	int _i = 0; // result 를 가르키는 인덱스
	int zero = 0; // 값을 뺐을 때 0이 되는 경우의 수
	int size = 0; // result 의 데이터의 수
	int **result;
	// 행렬 A와 B의 크기가 같지 않으면 연산 X
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
		// A[i][0] = 행, A[i][1] = 열, A[i][2] = 데이터
		// R에 저장
		// A[0] ~ A[N] 까지 가는데 하나하나당 B[0] ~ B[N] 과 검사해서 행, 열 같은 건 빼서 R에 저장
		// 뺀 값이 0이라면 저장하지 않음
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
		// B와 맞는게 하나도 없는데 0이 아닌 경우 그냥 추가
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
		// B[i][0] = 행, B[i][1] = 열, B[i][2] = 데이터
		// R에 남은 B 추가
		for (j=0; j<_i; ++j)
		{
			//B를 검사하는데 R에 없는거 추가하되 중복 방지도
			if (B[i][0] == result[j][0] && B[i][1] == result[j][1])
			{
				temp = 1;
				break;
			}
		}
		// R에 없는 경우
		if (temp == 0)
		{
			// A - B 가 0 이라면 스킵
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
	int a = 0, b = 0; // 희소행렬에서 찾아온 값
	int temp = 0; // 곱한 값을 담는 임시 변수
	int _i = 0; // result 를 가르키는 인덱스
	int **result;
	// 행렬 A의 열과 행렬 B의 행이 같지 않으면 연산 X
	if (column[0] != row[1])
		return NULL;

	// r행과 c열에 해당하는 A와 B의 원소를 곱해서 더함
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
			// temp 가 0이 아니라면 저장
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