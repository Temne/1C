#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define NUMBER_OF_DIGITS 32
#define MAX_NAME 101
#define MEM_ERR "MEMORY ALLOCATION ERROR!"

int countBinNumberDivision(int);
int* createBinNumber(int);
void binNumberTransormation(int*, int*, int);
int SumElementsOfNumber(int);

int main(int argc, char* argv[])
{

    FILE* input, * output;
    printf_s("Enter an input and output file names\n>");
    char* inputFileName = malloc(MAX_NAME * sizeof(char));
    char* outputFileName = malloc(MAX_NAME * sizeof(char));
    if (!(inputFileName || outputFileName))
    {
        printf_s(MEM_ERR);
        exit(1);
    }
    scanf_s("%s %s", inputFileName, 100, outputFileName, 100);

    if (fopen_s(&input, "input.txt", "r"))
    {
        perror("Input file: ");
        exit(1);
    }
    if (fopen_s(&output, "output.txt", "r+"))
    {
        perror("Output file: ");
        exit(1);
    }

    char* checkString = (char*)malloc(13 * sizeof(char));
    char* intMinString = "-2147483648";
    char* intMaxString = "2147483647";
    if (fgets(checkString, 13, input))
    {
        for (int i = 1; i < strlen(checkString); i++)
        {
            if (!(checkString[i] >= '0' && checkString[i] <= '9') && !(checkString[i] == '-'))
            {
                printf_s("Enter the number correctly!");
                exit(1);
            }
        }
    }
    else
    {
        printf_s("No numbers in input file!");
        exit(1);
    }
    fseek(input, 0, 0);
    if (fgets(checkString, 13, input))
    {
        if (checkString[0] == '-')
        {
            if (strlen(intMinString) < strlen(checkString))
            {
                printf_s("Too small number");
                exit(1);
            }
            else if (strlen(intMinString) == strlen(checkString))
            {
                for (int i = 1; i < strlen(checkString); i++)
                {
                    if (intMinString[i] < checkString[i])
                    {
                        printf_s("Too small number");
                        exit(1);
                    }
                }
            }
        }
        else
        {
            if (strlen(intMaxString) < strlen(checkString))
            {
                printf_s("Too big number");
                exit(1);
            }
            else if (strlen(intMaxString) == strlen(checkString))
            {
                for (int i = 0; i < strlen(checkString); i++)
                {
                    if (intMaxString[i] < checkString[i])
                    {
                        printf_s("Too big number");
                        exit(1);
                    }
                }
            }
        }
    }
    fseek(input, 0, 0);
    int inputDecNumber;
    if (!(fscanf_s(input, "%d", &inputDecNumber)))
    {
        perror("No numbers in input file!");
        exit(1);
    }
    int count = countBinNumberDivision(inputDecNumber);

    int* binaryNumber = createBinNumber(inputDecNumber);//{1, 1, 0}
    if (!(binaryNumber))
    {
        printf_s(MEM_ERR);
        exit(1);
    }

    int* digits32BinNumber = (int*)calloc(NUMBER_OF_DIGITS, sizeof(int));//0000..0110
    if (!(digits32BinNumber))
    {
        printf_s(MEM_ERR);
        exit(1);
    }
    binNumberTransormation(digits32BinNumber, binaryNumber, inputDecNumber);
    free(binaryNumber);
    printf_s("%d\n\n", SumElementsOfNumber(inputDecNumber));
    for (int i = 0; i < NUMBER_OF_DIGITS; i++)
    {
        if (i % 4 == 0 && i != 0)
        {
            printf_s(" ");
        }
        printf_s("%d ", digits32BinNumber[i]);
    }
    for (int i = 0; i < NUMBER_OF_DIGITS; i++)
    {
        if (i % 4 == 0 && i != 0)
        {
            fprintf_s(output, " ");
        }
        fprintf_s(output, "%d", digits32BinNumber[i]);
    }
    free(digits32BinNumber);
    fclose(input);
    fclose(output);
    return 0;
}

int countBinNumberDivision(int decNumber)
{
    int count = 0;
    decNumber = abs(decNumber);
    while (decNumber != 0)
    {
        decNumber /= 2;
        count++;
    }
    return count;
}

int* createBinNumber(int decNumber)//6
{
    int absDecNumber = abs(decNumber);//6
    int binDigitsCount = countBinNumberDivision(decNumber);//6 110
    int* binaryArray = (int*)calloc(binDigitsCount, sizeof(int));//3
    if (!(binaryArray))
    {
        printf_s(MEM_ERR);
        exit(1);
    }
    for (int i = binDigitsCount - 1; i >= 0; i--)
    {
        if (absDecNumber % 2 == 0)
        {
            binaryArray[i] = 0;
        }
        else
        {
            binaryArray[i] = 1;
        }
        absDecNumber /= 2;
    }
    return binaryArray;
}

void binNumberTransormation(int* bytes4BinNumber, int* binNumber, int decNumber)
{
    int count = countBinNumberDivision(decNumber);//6 110 3 
    for (int i = 0; i < count; i++)// i = 0, 1, 2
    {
        bytes4BinNumber[i + NUMBER_OF_DIGITS - count] = binNumber[i];//000..00110
    }

    if (decNumber < 0)
    {
        for (int i = 0; i < NUMBER_OF_DIGITS; i++)
        {
            if (bytes4BinNumber[i] == 0)
            {
                bytes4BinNumber[i] = 1;
            }
            else
            {
                bytes4BinNumber[i] = 0;
            }
        }

        for (int i = NUMBER_OF_DIGITS - 1; i >= 0; i--)
        {
            if (bytes4BinNumber[i] == 0)
            {
                bytes4BinNumber[i] = 1;
                break;
            }
            else
            {
                bytes4BinNumber[i] = 0;
            }
        }
    }
}

int SumElementsOfNumber(int number)//5443 âîò â ýòîì ÷èñëå ìû ìîæåì óìåñòèòü "10" 544 ðàçà 
{
    int sum = 0;
    while (number != 0)
    {
        sum += (number % 10);//0 + 3 + 4 + 4 + 5
        number /= 10;//0
    }
    return abs(sum);
}