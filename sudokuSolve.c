#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int puzzle[9][9]={
		{5, 3, 4, 6, 7, 8, 9, 1, 2},
		{6, 7, 2, 1, 9, 5, 3, 4, 8},
		{1, 9, 8, 3, 4, 2, 5, 6, 7},
		{8, 5, 9, 7, 6, 1, 4, 2, 3},
		{4, 2, 6, 8, 5, 3, 7, 9, 1},
		{7, 1, 3, 9, 2, 4, 8, 5, 6},
		{9, 6, 1, 5, 3, 7, 2, 8, 4},
		{2, 8, 7, 4, 1, 9, 6, 3, 5},
		{3, 4, 5, 2, 8, 6, 1, 7, 9}
	};

int valid(int[9][9], int, int, int);
int solve(int[9][9]);
int find_empty_cell(int[9][9], int *, int *);


//struct to pass 2 ints to a thread
struct Coor {
	int x;
	int y;
}

//find next empty cell
int find_empty_cell(int puzzle[9][9], int *row, int *column) 
{
	for (int x = 0; x < 9; x++)
	{
		for (int y = 0; y < 9; y++)
		{
			if (!puzzle[x][y])
			{
        	*row = x;
        	*column = y;
        	return 1;
      		}
    	}
  	}
  return 0;
}

int valid(int puzzle[9][9], int row, int column, int guess)
{
	int corner_x = row / 3 * 3;
	int corner_y = column / 3 * 3;

	for (int x = 0; x < 9; ++x) 
	{
		if (puzzle[row][x] == guess) return 0;
		if (puzzle[x][column] == guess) return 0;
    	if (puzzle[corner_x + (x % 3)][corner_y + (x / 3)] == guess) return 0;
 	}
  	return 1;
}

int solve(int puzzle[9][9])
{
	int row;
	int column;	
	if(!find_empty_cell(puzzle, &row, &column)) return 1;	
	for (int guess = 1; guess < 10; guess++)
	{
		if (valid(puzzle, row, column, guess))
		{
			puzzle[row][column] = guess;	
			if(solve(puzzle)) return 1;
			puzzle[row][column] = 0;
		}
	}
  return 0;
}
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
void *checkThreadY(void *args)
{
	//debugging code
	printf("I am the Y checker thread\n \n");
	//allocates an int for returning
	int *result = malloc(sizeof(int));
	*result = 0;
	//Loops through array to check if each collumn sums to 45
	for (int x = 0; x<9; x++)
	{
		int temp = 0;
		for (int y = 0; y<9; y++)
		{
			printf("%d\n", puzzle[y][x]);
			temp += puzzle[y][x];
		}
		//debugging code ignore
		printf("Temp value is:\n %d \n ", temp);
		if (temp != 45)
		{
			*result = 1;
		}	
	}
	return ((void *) result);
}
//old code (did not work)
int i, j, k, total;
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


void *checkThreadX(void *args)
{
	//debugging code
	printf("I am the Y checker thread\n \n");
	//allocates an int for returning
	int *result = malloc(sizeof(int));
	*result = 0;
	//Loops through array to check if each row sums to 45
	for (int y = 0; y<9; y++)
	{
		int temp = 0;
		for (int x = 0; x<9; x++)
		{
			printf("%d\n", puzzle[y][x]);
			temp += puzzle[y][x];
		}
		//debugging code ignore
		printf("Temp value is:\n %d \n ", temp);
		if (temp != 45)
		{
			*result = 1;
		}	
	}
	return ((void *) result);
};


void *checkThreadSquare(void *args)
{

	TODO: #1 Finish this up
	//int (*puzzle)[9] = (int(*)[9]) (args);
	printf("I am the Square checker thread");
	

	//for (k=1;k<=3;k++) {
    //    	l = (1+(k-1)*3);
    //    	for (i=l;i<=k*3;i++) {
	//	    	for(j=1;j<=3;j++) {
	//	        	total1 = total1 + puzzle[i][j];
	//	    		}
	//	    	for (j=4;j<=6;j++) {
	//	       	total2 = total2 + puzzle[i][j];
	//	    		}
	//	    	for (j=7;j<=9;j++) {
	//	        	total3 = total3 + puzzle[i][j];
	//	    		}
    //    	}
    //    	if (total1!=45||total2!=45||total3!=45) { //each square must equal 45 as 1+2+3+4+5+6+7+8+9=45
    //        		printf("Current Square solution not correct");
	//		pthread_exit(0);
	//		}
	//}
	printf("Squares solution correct");
	pthread_exit(0);
}
int main(int argc, char const *argv[])
{
	int *res = 0;
	int resultMaster = 0;

	// temporary array until the read function is made;
	TODO: #2 Make Read Function
	TODO: #3 Make Print Fucnction
	TODO: #4 Make interactable Y/N menu
	//read function below
	//does not work for now
	/*
	FILE *fp;
	fp = fopen("puzzle.txt", "r");//opens puzzle in read mode

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
		{5, 3, 4, 6, 7, 8, 9, 1, 2},
		{6, 7, 2, 1, 9, 5, 3, 4, 8},
		{1, 9, 8, 3, 4, 2, 5, 6, 7},
		{8, 5, 9, 7, 6, 1, 4, 2, 3},
		{4, 2, 6, 8, 5, 3, 7, 9, 1},
		{7, 1, 3, 9, 2, 4, 8, 5, 6},
		{9, 6, 1, 5, 3, 7, 2, 8, 4},
		{2, 8, 7, 4, 1, 9, 6, 3, 5},
		{3, 4, 5, 2, 8, 6, 1, 7, 9}
	};

	int sudokuArray2[9][9]={
		{1, 7, 4, 0, 9, 0, 6, 0, 0},
        {0, 0, 0, 0, 3, 8, 1, 5, 7},
        {5, 3, 0, 7, 0, 1, 0, 0, 4},
        {0, 0, 7, 3, 4, 9, 8, 0, 0},
        {8, 4, 0, 5, 0, 0, 3, 6, 0},
        {3, 0, 5, 0, 0, 6, 4, 7, 0},
        {2, 8, 6, 9, 0, 0, 0, 0, 1},
        {0, 0, 0, 6, 2, 7, 0, 3, 8},
        {0, 5, 3, 0, 8, 0, 0, 9, 6}
		};
	// TESTING CODE BELOW
	structs Coor test;
	coor.x = 0;
	coor.y = 0;
	pthread_t th;
	if (pthread_create(&th, NULL, checkThreadSquare, *test)!=0){
		perror("thread creation failed");
	}

	if (pthread_join(th, (void**) &res)!=0){
		perror("thread join failed");
	}

	/*
	if(solve(sudokuArray2)){
		print(sudokuArray2);
	}
	if(checkSudoku(sudokuArray2)==1){
		printf("Sudoku has been succesfully solved");
	};
	*/
	printf("Result: %d\n", resultMaster);
}

void assignToGlobal(){
	//asigns read array to the global one
}


int checkSudoku ()
{
	int returnVal = 0;
	int *res = 0;
	//coor squares[9];
	pthread_t thy;
	pthread_t thx;
	pthread_t th[10];


	//creates one instance of the x and y threads
	if (pthread_create(&thy, NULL, &checkThreadY, NULL)!=0){
		perror("thread creation failed");
	}
	if (pthread_create(&thx, NULL, &checkThreadX, NULL)!=0){
		perror("thread creation failed");
	}
	//loops and creates 9 squareChecker threads
	for (int i = 0; i < 10; i++)
	{
		if (pthread_create(&th[i], NULL,checkThreadSquare,  ))
	}

	//joins x and y threads
	if (pthread_join(thy, (void**) &res)!=0){
		perror("thread join failed");
	}
	returnVal += *res;
	if (pthread_join(thx, (void**) &res)!=0){
		perror("thread join failed");
	}


	returnVal += *res;

	return returnVal;
}



