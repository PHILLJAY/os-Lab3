#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>

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


//find next empty cell
int find_empty_cell(int sudoku[9][9], int *row, int *column) 
{
	for (int x = 0; x < 9; x++)
	{
		for (int y = 0; y < 9; y++)
		{
			if (!sudoku[x][y])
			{
        	*row = x;
        	*column = y;
        	return 1;
      		}
    	}
  	}
  return 0;
}

int valid(int sudoku[9][9], int row, int column, int guess)
{
	int corner_x = row / 3 * 3;
	int corner_y = column / 3 * 3;

	for (int x = 0; x < 9; ++x) 
	{
		if (sudoku[row][x] == guess) return 0;
		if (sudoku[x][column] == guess) return 0;
    	if (sudoku[corner_x + (x % 3)][corner_y + (x / 3)] == guess) return 0;
 	}
  	return 1;
}

int solve(int sudoku[9][9])
{
	int row;
	int column;	
	if(!find_empty_cell(sudoku, &row, &column)) return 1;	
	for (int guess = 1; guess < 10; guess++)
	{
		if (valid(sudoku, row, column, guess))
		{
			sudoku[row][column] = guess;	
			if(solve(sudoku)) return 1;
			sudoku[row][column] = 0;
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
	//allocates an int for returning
	int *result = malloc(sizeof(int));
	*result = 0;
	//Loops through array to check if each collumn sums to 45
	for (int x = 0; x<9; x++)
	{
		int temp = 0;
		for (int y = 0; y<9; y++)
		{
			//printf("%d\n", puzzle[y][x]);
			temp += puzzle[y][x];
		}
		//debugging code ignore
		//printf("Temp value is:\n %d \n ", temp);
		if (temp != 45)
		{
			*result = 1;
		}	
	}
	return ((void *) result);
}

void *checkThreadX(void *args)
{
	//debugging code
	//allocates an int for returning
	int *result = malloc(sizeof(int));
	*result = 0;
	//Loops through array to check if each row sums to 45
	for (int y = 0; y<9; y++)
	{
		int temp = 0;
		for (int x = 0; x<9; x++)
		{
			//printf("%d\n", puzzle[y][x]);
			temp += puzzle[y][x];
		}
		//debugging code ignore
		//printf("Temp value is:\n %d \n ", temp);
		if (temp != 45)
		{
			*result = 1;
		}	
	}
	return ((void *) result);
};

void *checkThreadSquare(void *args)
{
	int index = *(int *)args;
	int *result = malloc(sizeof(int));
	*result = 0;
	int x1 = 0;
	int y1 = 0;
	x1 = ((int)floor(index / 3)) * 3;
	//printf("Your x1 value is: %d\n", x1);
	y1 = (index % 3) * 3;
	//printf("Your y1 value is: %d\n", y1);

	//printf("I am the Square checker thread\n");
	//printf("The index you passed to me is: %d\n", index);
	int temp = 0;
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			//printf("%d \n", puzzle[y+y1][x+x1]);
			temp += puzzle[y+y1][x+x1];
		}
	}
	//printf("Your temp value is %d\n", temp);
	if (temp!=45)
	{
		*result = 1;
	}
	free(args);
	return ((void *) result);
}
int main(int argc, char const *argv[])
{
	//opening file code
	FILE *FILE1;
	FILE1 = fopen("puzzle.txt", "r");
	if(FILE1 == NULL){
		//throw error
		printf("Error opening file.\n");
		exit(1);
	}

	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			fscanf(FILE1, "%d", &puzzle[i][j]);
		}
	}

	fclose(FILE1);
	printf("Your sudoku puzzle is: \n");
	print(puzzle);
	printf("\n");

	printf("\nSolving the given puzzle......\n");

	solve(puzzle);

	print(puzzle);
	printf("\n");

	int *res = 0;
	if (checkSudoku()>=1)
	{
		printf("Sudoku Solution is invalid \n"); 
	}
	else
	{
		printf("Sudoku Solution is valid \n"); 
		FILE *FILE2;

        FILE2= fopen("solution.txt","w+"); //open of create file named solution.txt
        if(FILE2 == NULL){ // chek for error
			printf("Error opening/creating file.\n");
			exit(1);
        }

        for(int i = 0; i < 9; i++){ //for loop to add text to file
			for(int j = 0; j < 9; j++){
				fprintf(FILE2,"%d ", puzzle[i][j]);
			}
			fprintf(FILE2,"\n");
        }
		fclose(FILE2);
		printf("Solution printed to solution.txt\n");
	}
	
	

	

	// if (pthread_create(&th, NULL, &checkThreadSquare, test)!=0){
	// 	perror("thread creation failed");
	// } else{
	// 	printf("I have created the thread\n");
	// }

	// if (pthread_join(th, (void**) &res)!=0){
	// 	perror("thread join failed");
	// }

	/*
	if(solve(sudokuArray2)){
		print(sudokuArray2);
	}
	if(checkSudoku(sudokuArray2)==1){
		printf("Sudoku has been succesfully solved");
	};
	*/
	//printf("Result: %d\n", resultMaster);
}
int checkSudoku ()
{
	int returnVal = 0;
	int *res = 0;
	//coor squares[9];
	pthread_t thy;
	pthread_t thx;
	pthread_t th[9];


	//creates one instance of the x and y threads
	if (pthread_create(&thy, NULL, &checkThreadY, NULL)!=0){
		perror("thread creation failed");
	}
	if (pthread_create(&thx, NULL, &checkThreadX, NULL)!=0){
		perror("thread creation failed");
	}
	//loops and creates 9 squareChecker threads
	
	for (int i = 0; i < 9; i++)
	{
		int *a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(&th[i], NULL,checkThreadSquare, a));
	}

	//joins x and y threads
	if (pthread_join(thy, (void**) &res)!=0){
		perror("thread join failed");
	}
	returnVal += *res;
	if (pthread_join(thx, (void**) &res)!=0){
		perror("thread join failed");
	}

	for (int i = 0; i < 9; i++)
	{
		if (pthread_join(th[i], (void**) &res)!=0){
			perror("thread join failed");
		};
		returnVal += *res;
	}

	returnVal += *res;

	return returnVal;
}



