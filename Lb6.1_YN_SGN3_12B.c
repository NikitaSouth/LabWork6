#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

void matrixInput(int**, int);
void matrixOutput(int**, int);
void matrixShuffle(int**, int);
void matrixFree(int**, int);
int** memoryAllocate(int);

int main()
{
	int** squareMatrix;
	int matrixSize; //В комментарии от лектора было сказано, что создается евадратная матрица, поэтому её измерения равны и равны matrixSize
	printf("Enter size of the matrix:");
	scanf_s("%d", &matrixSize);
	if (matrixSize <= 1){
		printf("Size of the matrix can't be equal one or below");
		return 0;
	}
	squareMatrix = memoryAllocate(matrixSize);
	if (squareMatrix == NULL) {
		printf("An error in memory allocation has occurred\a");
		return 0;
	}
	matrixInput(squareMatrix, matrixSize);
	matrixOutput(squareMatrix, matrixSize);
	matrixShuffle(squareMatrix, matrixSize);
	printf("\nmatrix after:\n");
	matrixOutput(squareMatrix, matrixSize);
	matrixFree(squareMatrix, matrixSize);
	return 0;
}

void matrixInput(int** matrixName, int matrixSize)
{
	for (int i = 0; i < matrixSize; i++) {
		for (int j = 0; j < matrixSize; j++) {
			printf("matrix[%d][%d] = ", i, j);
			scanf_s("%d", &*(*(matrixName + i) + j));
		}
	}
}

void matrixOutput(int** matrixName, int matrixSize)
{
	for (int i = 0; i < matrixSize; i++) {
		printf("\n");
		for (int j = 0; j < matrixSize; j++) {
			printf(" %d ", *(*(matrixName + i) + j));
		}
	}
}

void matrixShuffle(int** matrixName, int matrixSize)
{

for (int i = 0; i < matrixSize - 1; i++)
	for (int j = 0; j < (matrixSize - 1) - i; j++) {
		int temp = *(*(matrixName + i) + j);
		*(*(matrixName + i) + j) = *(*(matrixName + (matrixSize - 1) - j) + (matrixSize - 1) - i);
		*(*(matrixName + (matrixSize - 1) - j) + (matrixSize - 1) - i) = temp;
	}
}

void matrixFree(int** matrixName, int matrixSize){
	for (int i = 0; i < matrixSize; i++) {
		free(*(matrixName + i));
	}
	free(matrixName);
}

int** memoryAllocate(int matrixSize)
{
	int** matrix = (int**)malloc(sizeof(int*) * matrixSize);
	if (matrix == NULL) {
		return matrix;
	}
	for (int i = 0; i < matrixSize; i++) {
		*(matrix + i) = (int*)malloc(sizeof(int) * matrixSize);
		if (*(matrix + i) == NULL) {
			matrixFree(matrix, i);
			return matrix;
		}
	}
	return matrix;
}