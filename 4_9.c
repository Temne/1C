#include <stdio.h>

/*4.9
 ����� �����, ���������� ����� �������� ������ ������ (��� �� ��������� � ������������)*/

int main()
{
	int a, b, sum = 0;

	printf_s("Enter your number: ");
	scanf_s("%d", &b);


	for (int i = 0; i < b; i++)
	{
		printf_s("Enter your number: ");
		scanf_s("%d", &a);
		sum += a;
	}
	printf_s("Sum is %d", sum);
}