#include <stdio.h>
#include <time.h>

int main()
{
	char op;
	int i;
	int temp;
	int loof;
	int start, end;
	int left = 10, right = 5;
	printf("연산을 선택하세요(+, -, *, /) : ");
	scanf("%c", &op);
	printf("반복 횟수를 입력하세요 : ");
	scanf("%d", &loof);

	//시간 측정 시작
	start = clock();
	//사용자가 입력한 수만큼 반복
	for(i=0; i<loof; ++i)
	{
		switch(op)
		{
		case '+':
			temp = left + right;
			break;
		case '-':
			temp = left - right;
			break;
		case '*':
			temp = left * right;
			break;
		case '/':
			temp = left / right;
			break;
		}
	}
	//시간 측정 끝
	end = clock();

	printf("\n걸린 시간은 %.6lf입니다.\n", (double)(end - start)/CLOCKS_PER_SEC);
	return 0;
}