#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define N 9

void print(int arr[N][N])
{
	for(int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				printf("%d ", arr[i][j]);
			}
			printf("\n");
		}
}

int main (int argc, char *argv[])
{
//temporary array until the read function is made;
	FILE *fp;
	fp = fopen("Lab3 puzzle.txt", "r");//opens puzzle in read mode

	if (fp == NULL)
	{
		perror("Error while opening file.\n");
		exit(0);
	}
	int sudokuArray2[9][9];
	
	for(int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			
			fscanf(fp, "%d", sudokuArray2[i][j]);
			printf("%d", sudokuArray2[i][j]);
			printf("\n");
		}

	}
	int sudokuArray[9][9]={
	{5,3,4,6,7,8,9,1,2},
	{6,7,2,1,9,5,3,4,8},
	{1,9,8,3,4,2,5,6,7},
	{8,5,9,7,6,1,4,2,3},
	{4,2,6,8,5,3,7,9,1},
	{7,1,3,9,2,4,8,5,6},
	{9,6,1,5,3,7,2,8,4},
	{2,8,7,4,1,9,6,3,5},
	{3,4,5,2,8,6,1,7,9},
	};
	print(sudokuArray2);

}

int checkSudoku (int puzzle[9][9])
{
	return 1;
}

//threads down below
void *solveThreadY()
{

}

void *solveThreadX()
{

}

void *solveThreadSquare()
{

}
