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
void *checkThreadY(int puzzle[9][9])
{
	printf("I am the Y checker thread");
	
	int puzzle[9][9], i, j, k, total;
	for (j=1;j<=9;j++) {
		for(k=j;k==j;k++) {
			total=0;
			for (i=1;i<=9;i++) {
				total = total + puzzle[i][j];
				}
			if (total!=45) {//column must equal 45 as 1+2+3+4+5+6+7+8+9=45
				printf("Current Y solution not correct");
				pthread_exit(0);
			}
		}
         }
        printf("Y solution correct");
	pthread_exit(0);
}

void *checkThreadX(int puzzle[9][9])
{
	printf("I am the X checker thread");
	
	int puzzle[9][9], i, j, k, total;
	for (i=1;i<=9;i++) {
		for (k=i;k==i;k++) {
			total=0;
			for (j=1;j<=9;j++) {
				total = total + puzzle[i][j];
				}

			if(total!=45) { //row must equal 45 as 1+2+3+4+5+6+7+8+9=45
				printf("Current X solution not correct");
				pthread_exit(0);
			}
		}
        }
        printf("X solution correct");
	pthread_exit(0);
}

void *checkThreadSquare(int puzzle[9][9])
{
	printf("I am the Square checker thread");
	
	int puzzle[9][9], i, j, k, l, total1, total2, total3;
	for (k=1;k<=3;k++) {
        	l = (1+(k-1)*3);
        	for (i=l;i<=k*3;i++) {
		    	for(j=1;j<=3;j++) {
		        	total1 = total1 + puzzle[i][j];
		    		}
		    	for (j=4;j<=6;j++) {
		       	total2 = total2 + puzzle[i][j];
		    		}
		    	for (j=7;j<=9;j++) {
		        	total3 = total3 + puzzle[i][j];
		    		}
        	}
        	if (total1!=45||total2!=45||total3!=45) { //each square must equal 45 as 1+2+3+4+5+6+7+8+9=45
            		printf("Current Square solution not correct");
			pthread_exit(0);
			}
	}
	printf("Squares solution correct");
	pthread_exit(0);
}


void solveSudoku(int puzzle[9][9]){
	
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
	pthread_create(&t1, NULL, &checkThreadSquare, puzzle);
	pthread_create(&t2, NULL, &checkThreadY, puzzle);
	pthread_create(&t3, NULL, &checkThreadX, puzzle);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_join(t3,NULL);
	return 1;
}



