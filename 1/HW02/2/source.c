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
	printf("������ �����ϼ���(+, -, *, /) : ");
	scanf("%c", &op);
	printf("�ݺ� Ƚ���� �Է��ϼ��� : ");
	scanf("%d", &loof);

	//�ð� ���� ����
	start = clock();
	//����ڰ� �Է��� ����ŭ �ݺ�
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
	//�ð� ���� ��
	end = clock();

	printf("\n�ɸ� �ð��� %.6lf�Դϴ�.\n", (double)(end - start)/CLOCKS_PER_SEC);
	return 0;
}