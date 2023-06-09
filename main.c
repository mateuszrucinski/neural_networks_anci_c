#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include<stdlib.h>
#include <time.h>
#include <math.h>

#define E 2.718 //liczba eulera

void makeMatrix(int ***array, int *row, int *col);

int isMultiplicationOfMatrixPossible(int col1, int row2);

void multiplyTwoMatrix(int **mat1, int **mat2, double*** matmult, int row1, int col1, int row2, int col2);

void freeArray(int **array, int rows);

void allocateMemoryForTheMatMult(double*** matmult, int row1, int col2);

int addBiasToNeuron(int neuronWithoutBias);

long double activationFunction(int bias);

int main() {
    srand(time(0));
    //input
    int col1 = 0;
    int col2 = 0;

    int **matX;
    int row1 = 1;
    makeMatrix(&matX, &row1, &col1);
    int **matWage;
    int row2 = 2;
    makeMatrix(&matWage, &row2, &col2);
    int **matmult;
    multiplyTwoMatrix(matX, matWage, &matmult, row1, col1, row2, col2);
    freeArray(matX, row1);
    freeArray(matWage, row2);
    getch();
    return 0;
}

void multiplyTwoMatrix(int **mat1, int **mat2, double*** matmult, int row1, int col1, int row2, int col2) {
    if (isMultiplicationOfMatrixPossible(col1, row2)) {
        allocateMemoryForTheMatMult(matmult, row1, col2);
        int sum = 0;
        printf("\nMultiplying the two matrix...\n");
        for (int i = 0; i < row1; i++) {
            for (int j = 0; j < col2; j++) {
                sum = 0;
                for (int k = 0; k < col1; k++) {
                    sum = sum + mat1[i][k] * mat2[k][j];
                }
                int neuronWithoutBias = sum; 
                int neuronWithBias = addBiasToNeuron(neuronWithoutBias);
                long double neuron = activationFunction(neuronWithBias);
                (*matmult)[i][j] = neuron;
            }
        }
        printf("The multiplication result (resultant matrix) is:\n");
        for (int i = 0; i < row1; i++) {
            for (int j = 0; j < col2; j++)
                printf("%lf ", (*matmult)[i][j]);
            printf("\n");
        }
        freeArray((int **) matmult, row1);
    }
}

long double activationFunction(int bias) {
//    //Gauss function
    int a = 1 + rand() % 6;
    int b = rand() % 6;
//    int c = 1 + rand() % 6;
//
//    double licznik = pow(bias - b, 2);
//    double mianownik = 2 * pow(c, 2);
//    double x = 1 / (a * E);
//    double y = licznik / mianownik;
//    long double result = powl(x, y);

    int result = a * bias + b;
    return result;
}

int addBiasToNeuron(int neuronWithoutBias) {
    int randomNumberIndex = rand() % 6;
    return neuronWithoutBias + randomNumberIndex;
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

void allocateMemoryForTheMatMult(double*** matmult, int row1, int col2) {
    *matmult = (double **) malloc(row1 * sizeof(double *));
    for (int i = 0; i < row1; i++) {
        (*matmult)[i] = (double *) malloc(col2 * sizeof(double));
    }
}

void makeMatrix(int ***array, int *row, int *col) {
    if (*row == 0) {
        printf("Enter size of matrix:\n");
        printf("Enter row size: ");
        scanf("%d", row);
    }
    if (*col == 0) {
        printf("Enter size of matrix:\n");
        printf("Enter column size: ");
        scanf("%d", col);
    }
    // Allocate memory for the array
    *array = (int **) malloc(*row * sizeof(int *));

    for (int i = 0; i < *row; i++) {
        (*array)[i] = (int *) malloc(*col * sizeof(int));
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
