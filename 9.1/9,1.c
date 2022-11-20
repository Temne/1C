#include <stdio.h>
#include <stdlib.h>

int Fibonnachi(number);


int main(void)
{
	int N;
	printf_s("print the index of Fibonnachi number");
	scanf_s("%d", &N);
	Fibonnachi(N);
	printf_s("%d", Fibonnachi(N));
}

int Fibonnachi(int number)
{
	int count = 0;
	int FirstNumber = 0;
	int SecondNumber = 1;
	int tmp;
	while (count <= number)
	{

		if (FirstNumber == 0)
		{
			FirstNumber = 0;
			SecondNumber = 1;
		}
		tmp = FirstNumber;
		FirstNumber = SecondNumber;
		SecondNumber += tmp;
		count++;
		return Fibonnachi(number);
	}
	return SecondNumber;
}