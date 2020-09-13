#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	
	FILE *fp;	// ���������� ��������
	int m_row = 0, m_col = 3;  // ����� ũ�⸦ 0���� �ʱ�ȭ
	int **matrix;
	int temp1, temp2, temp3;
	int i,j;

	fp = fopen("data.txt", "r");	// data.txt������ �б���� ���� ������ FILE����ü�� fp�� �Ҵ�
	if(fp==NULL)	// ���� fopen�Լ����� ������ �߻��Ͽ� fp�� NULL���� ����Ǿ��ٸ� ���Ͽ������
	{
		printf("���Ͽ� ������ �ʾҽ��ϴ�.\n");
		return 0;	// �޼��� ����ϰ� ���α׷� ����
	}

	// ����� ũ�⸦ ����� 
	while(!feof(fp))
	{
		// fscanf �� ���� ���� ������ ���. ������ -1
		if (fscanf(fp, "%d%d%d", &temp1, &temp2, &temp3) < 0)
			break;
		m_row++;
	}
			
	// Dynamic �迭�� ũ�⿡ ���� �Ҵ�
	matrix = (int**) malloc(sizeof(int *) * m_row);
	for(i = 0; i < m_row; i++) 
	{
		matrix[i] = (int*) malloc(sizeof(int ) * m_col);
	}
	rewind(fp);

	// ���Ͽ��� �о�� ����� ũ�⸦ ������ �׸�ŭ�� ��� ������ �о� ��
	for(i = 0; i < m_row; i++)  // ���� ���� ��Ŵ
	{ 
		for(j = 0; j < m_col; j++) // ���� ���� ��Ŵ
		{
			fscanf(fp, "%d", &matrix[i][j]);  // �࿭�� ���� ���Ͽ��� �ϳ��� �о��
		}
	}
	fclose(fp);

	printf("=== �Էµ� ��� ===\n");	
	for(i = 0; i < m_row; i++)  // ���� ���� ��Ŵ
	{
		for(j = 0; j < m_col; j++) // ���� ���� ��Ŵ
		{
			printf("%3d ", matrix[i][j]); // ȭ�鿡 ���
		}
		printf("\n");  // ȭ�鿡 ���๮�� ���
	}

	// Dynamic���� �Ҵ�� �迭�� ����
	for(i = 0; i < m_row; i++)  free(matrix[i]);
	free(matrix);

	return 0;
}