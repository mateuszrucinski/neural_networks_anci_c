#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include<stdlib.h>

void makeMatrix(int*** array, int* row, int* col);
int isMultiplicationOfMatrixPossible(int col1, int row2);
void multiplyTwoMatrix(int** mat1, int** mat2, int*** matmult, int row1, int col1, int row2, int col2);
void freeArray(int** array, int rows);

void allocateMemoryForTheMatMult(int ***matmult, int row1, int col2);

int main() {
    //input
    int row1;
    int col1;
    int row2;
    int col2;

    int** mat1;
    makeMatrix(&mat1, &row1, &col1);
    int** mat2;
    makeMatrix(&mat2, &row2, &col2);
    int** matmult;
    multiplyTwoMatrix(mat1, mat2, &matmult, row1, col1, row2, col2);
    freeArray(mat1, row1);
    freeArray(mat2, row2);
    getch();
    return 0;
}

void multiplyTwoMatrix(int** mat1, int** mat2, int*** matmult, int row1, int col1, int row2, int col2)  {
    if(isMultiplicationOfMatrixPossible(col1, row2)) {
        allocateMemoryForTheMatMult(matmult, row1, col2);
        int sum = 0;
        printf("\nMultiplying the two matrix...\n");
        for (int i = 0; i < row1; i++) {
            for (int j = 0; j < col2; j++) {
                sum = 0;
                for (int k = 0; k < col1; k++) {
                    sum = sum + mat1[i][k] * mat2[k][j];
                }
                (*matmult)[i][j] = sum;
            }
        }
        printf("The multiplication result (resultant matrix) is:\n");
        for (int i = 0; i < row1; i++) {
            for (int j = 0; j < col2; j++)
                printf("%d ", (*matmult)[i][j]);
            printf("\n");
        }
        freeArray((int **) matmult, row1);
    }
}

int isMultiplicationOfMatrixPossible(int col1, int row2) {
    if (col1 != row2) {
        printf("\nMultiplication not possible!");
        printf("\nExiting...\n");
        printf("Press any key...");
        getch();
        return 0;
    }
    return 1;
}

void allocateMemoryForTheMatMult(int ***matmult, int row1, int col2) {
    *matmult = (int **)malloc(row1 * sizeof(int *));
    for (int i = 0; i < row1; i++) {
        (*matmult)[i] = (int *)malloc(col2 * sizeof(int));
    }
}

void makeMatrix(int*** array, int* row, int* col) {
    printf("Enter size of first matrix:\n");
    printf("Enter row size: ");
    scanf("%d", row);
    printf("Enter column size: ");
    scanf("%d", col);

    // Allocate memory for the array
    *array = (int **)malloc(*row * sizeof(int *));

    for (int i = 0; i < *row; i++) {
        (*array)[i] = (int *)malloc(*col * sizeof(int));
    }

    printf("\nEnter the element of first matrix:\n");
    for (int i = 0; i < *row; i++) {
        for (int j = 0; j < *col; j++)
            scanf("%d", &(*array)[i][j]);
    }
}

void freeArray(int **array, int rows) {
    // Free the memory
    for (int i = 0; i < rows; i++) {
        free(array[i]);
    }
    free(array);
}
