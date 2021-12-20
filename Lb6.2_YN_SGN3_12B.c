#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

int** memoryAllocate(int, int);
void matrixFree(int**, int);
void matrixInput(int**, int, int);
void matrixOutput(int**, int, int);
int lookForMin(int**, int, int);
void matrixShuffle(int**, int, int);

int main()
{
	int** squareMatrix;
	int matrixSizeVertical, matrixSizeHorizontal, minRaw;
	printf("Please, enter size of the matrix (one digit): ");
	scanf_s("%d", &matrixSizeVertical);
	if(matrixSizeVertical <= 1) {
		printf("Error: size of the matrix must be higher than 1\a");
		return 0;
	}
	matrixSizeHorizontal = matrixSizeVertical; //По условию матрица задается квадратной, но для задания ей нужны как и вертикальное, так и горизонтальное измерение.
	squareMatrix = memoryAllocate(matrixSizeVertical, matrixSizeHorizontal);
	if (squareMatrix == NULL) {
		printf("An error in memory allocation has occurred!\a");
		return 0;
	}
	matrixInput(squareMatrix, matrixSizeVertical, matrixSizeHorizontal);
	matrixOutput(squareMatrix, matrixSizeVertical, matrixSizeHorizontal);
	minRaw = lookForMin(squareMatrix, matrixSizeVertical, matrixSizeHorizontal);
	matrixShuffle(squareMatrix, matrixSizeVertical, matrixSizeHorizontal, minRaw);
	free(*(squareMatrix + matrixSizeVertical - 1));
	matrixSizeVertical -= 1;
	printf("\n");
	matrixOutput(squareMatrix, matrixSizeVertical, matrixSizeHorizontal);
	matrixFree(squareMatrix, matrixSizeVertical);
	return 0;
}

int** memoryAllocate(int matrixSizeV, int matixSizeH)
{
	int** matrix = (int**)malloc(sizeof(int*) * matrixSizeV);
	if (matrix == NULL) {
		return matrix;
	}
	for (int i = 0; i < matrixSizeV; i++) {
		*(matrix + i) = (int*)malloc(sizeof(int) * matixSizeH);
		if(*(matrix + i) == NULL) {
			matrixFree(matrix, i);
			return matrix;
		}
	}
	return matrix;
}

void matrixFree(int** matrixName, int matrixSizeV)
{
	for (int i = 0; i < matrixSizeV; i++){
		free(*(matrixName + i));
	}
	free(matrixName);
}

void matrixInput(int** matrixName, int matrixSizeV, int matrixSizeH)
{
	for (int i = 0; i < matrixSizeV; i++) {
		for (int j = 0; j < matrixSizeH; j++) {
			printf("matrix[%d][%d] = ", i, j);
			scanf_s("%d", &*(*(matrixName + i) + j));
		}
	}
}

void matrixOutput(int** matrixName, int matrixSizeV, int matrixSizeH)
{
	for (int i = 0; i < matrixSizeV; i++) {
		printf("\n");
		for (int j = 0; j < matrixSizeH; j++) {
			printf(" %d ", *(*(matrixName + i) + j));
		}
	}
}

int lookForMin(int** matrixName, int matrixSizeV, int matrixSizeH)
{
	int minLine = 1, minimum = *(*(matrixName + 1) + 0);
	for (int i = 2; i < matrixSizeV; i++) {
		for (int j = 0; j < i; j++) {
			if (*(*(matrixName + i) + j) < minimum) {
				minimum = *(*(matrixName + i) + j);
				minLine = i;
			}
		}
	}
	return minLine;
}

void matrixShuffle(int** matrixName, int matrixSizeV, int matrixSizeH, int minRaw)
{
	for (int i = minRaw; i < matrixSizeV - 1; i++) {
		for (int j = 0; j < matrixSizeH; j++) {
			*(*(matrixName + i) + j) = *(*(matrixName + i + 1) + j);
		}
	}
}