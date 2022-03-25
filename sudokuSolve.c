#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
int sudoku[9][9];

void print(int arr[9][9])
{
	for(int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				printf("%d ", arr[i][j]);
			}
			printf("\n");
		}
}

//threads down below
void *solveThreadY()
{
	int tempArray[9];
	printf("I am the Y solver thread");
}

void *solveThreadX()
{
	int tempArray[9];
	printf("I am the X solver thread");
}

void *solveThreadSquare()
{
	int tempArray[9];
	printf("I am the Square solver thread");
}

int main (int argc, char *argv[])
{
//temporary array until the read function is made;
	
	//read function below
	//does not work for now
	/*
	FILE *fp;
	fp = fopen("sudoku", "r");//opens puzzle in read mode

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
	*/
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
	checkSudoku(sudokuArray);
	//print(sudokuArray2);


}

int checkSudoku (int puzzle[9][9])
{
	pthread_t t1;
	pthread_t t2;
	pthread_t t3;
	pthread_create(&t1, NULL, &solveThreadSquare, NULL);
	pthread_create(&t2, NULL, &solveThreadY, NULL);
	pthread_create(&t3, NULL, &solveThreadX, NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_join(t3,NULL);
	return 1;
}



