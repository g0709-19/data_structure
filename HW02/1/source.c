#include <stdio.h>
#include <string.h>
#include <time.h>
#define DIGITS 10 // 배열의 크기. DIGITS 가 10이면 9자리의 수

typedef char big_integer[DIGITS]; // big_integer 는 char[DIGITS]d

void to_big_integer(big_integer); // 문자로 된 수를 연산을 쉽게 하기 위해 -'0'
int power(int, int); 
void add(big_integer a, big_integer b, big_integer result); // a와 b를 더해 result에 저장
void multiply(big_integer a, big_integer b, big_integer result); // a와 b를 곱해 result에 저장
int compare(big_integer a, big_integer b); // a와 b를 비교해 a가 크면 0, b가 크면 1 출력

int main()
{
	int choice, loof; // 알고리즘 선택과 반복 횟수
	big_integer number = "01"; // 거꾸로 입력. 뒤에서부터 읽음
	big_integer result = ""; // 연산에서 나온 결과
	big_integer one = "1"; // 반복문 증감식에서 사용
	big_integer temp = "0", temp2 = "", temp3 = "0", temp4 = ""; // 반복문 조건을 위한 임시 변수
	big_integer sum = ""; // 연산의 결과를 담기 위한 변수
	int i, j, k;
	clock_t start, end; // 수행시간 측정을 위한 변수
	
	//연산을 위해 모든 문자에 -'0'
	to_big_integer(sum);
	to_big_integer(number);
	to_big_integer(temp);
	to_big_integer(temp3);
	to_big_integer(one);

	printf("알고리즘을 선택하세요(1, 2, 3) : ");
	scanf("%d", &choice);
	printf("숫자를 입력하세요 : ");
	scanf("%d", &loof);

	//시간 측정 시작
	start = clock();
	//사용자가 정한만큼 반복
	for(i=0; i<loof; ++i)
	{
		//알고리즘 선택
		switch(choice)
		{
		case 1: //A
			multiply(number, number, result);
			break;
		case 2: //B
			//DIGITS-1번 반복
			for(;compare(temp, number);)
			{
				//sum += number 와 같은 작업
				add(sum, number, result);
				strcpy(sum, result);
				//증감식
				add(temp, one, temp2);
				strcpy(temp, temp2);
			}
			break;
		case 3: //C
			//DIGITS-1번 반복
			for(;compare(temp, number);)
			{
				//DIGITS-1번 반복
				for(;compare(temp3, number);)
				{
					//sum = sum+1 과 같은 작업
					add(sum, one, result);
					strcpy(sum, result);
					//증감식
					add(temp3, one, temp4);
					strcpy(temp3, temp4);
				}
				//증감식
				add(temp, one, temp2);
				strcpy(temp, temp2);
			}
			strcpy(sum, result);
			break;
		}
	}
	//시간 측정 끝
	end = clock();
	printf("\n");
	printf("\n걸린 시간은 %.6lf입니다.\n", (double)(end - start)/CLOCKS_PER_SEC);
	return 0;
}

void to_big_integer(big_integer number)
{
	int i;
	for(i=0; i<DIGITS; ++i)
		if(number[i] != 0)
			number[i] -= '0';
}

int power(int num, int m)
{
	if(m == 0)
		return 1;
	else
		return num * power(num, m-1);
}

void add(big_integer a, big_integer b, big_integer result)
{
	int i;
	char c = 0;
	int length = strlen(a);
	//0을 NULL로 인식하는 경우 처리
	if(length == 0 && a[0] == 0)
		++length;
	//a와 b의 길이가 같기 때문에 가능
	for(i=0; i<length; ++i)
	{
		c = a[i] + b[i];
		//자리올림수 처리
		if(c/10 > 0)
		{
			result[i] += c%10;
			//DIGITS 를 넘어가는 자리올림은 무시
			if(i+1 < DIGITS)
				result[i+1] = c/10;
		}
		else
		{
			result[i] += c;
		}
	}
	result[DIGITS-1] = NULL;
}

void multiply(big_integer a, big_integer b, big_integer result)
{
	int i, j, k, tttt;
	int temp = 0;
	char c = 0;
	int length = strlen(a);
	//0을 NULL로 인식하는 경우 처리
	if(length == 0 && a[0] == 0)
		++length;
	//a와 b의 길이가 같기 때문에 가능
	for(i=0; i<length; ++i)
	{
		// a[i]와 b[0]~b[length-1] 까지 곱함
		for(j=0; j<length; ++j)
		{
			c = a[i] * b[j];
			//자리올림수 처리
			if(c/10 > 0)
			{
				result[j+i] += c%10;
				//자리올림수 처리
				if(result[j+i]/10 > 0)
				{
					result[j+i+1] += result[j+i]/10;
					result[j+i] %= 10;
				}
				//자리올림수 처리
				for(k=1+j+i; c/10>0; ++k)
				{
					temp = c/power(10, k);
					result[k] += c/10;
					c /= 10;
				}
			}
			else
			{
				result[j+i] += c;
				//자리올림수 처리
				if(result[j+i]/10 > 0)
				{
					result[j+i+1] += result[j+i]/10;
					result[j+i] %= 10;
				}
			}
		}
	}
	result[DIGITS-1] = NULL;
}

int compare(big_integer a, big_integer b)
{
	int i, compare = 0;
	for(i=0; i<DIGITS; ++i)
	{
		//같은 경우는 무시
		if(a[i] > b[i])
			compare = 0;
		else if(a[i] < b[i])
			compare = 1;
	}
	return compare;
}