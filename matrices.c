/*---------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

double *input_matrix(int *rows,int *columns,char *name);
int matrix_multiply(double *m1, int m1rows, int m1columns, double *m2, int m2rows, int m2columns, double *m3);
void output_matrix (double *matrix, int rows, int columns);
/*---------------------------------------------------------------------------*/
int main(void) {

    double *m1,*m2,*m3;
    int m1_rows,m1_columns,m2_rows,m2_columns;

    if (((m1 = input_matrix(&m1_rows,&m1_columns,"Matrix 1")) != NULL) &&
((m2 = input_matrix(&m2_rows,&m2_columns,"Matrix 2")) != NULL) &&
((m3 = malloc(m1_rows*m2_columns*sizeof(double))) != NULL)) {
        printf("Matrix 1\n");
        output_matrix(m1,m1_rows,m1_columns);
        printf("Matrix 2\n");
        output_matrix(m2,m2_rows,m2_columns);
        if (matrix_multiply(m1,m1_rows,m1_columns,m2,m2_rows,m2_columns,m3)) {
            printf("Product\n");
            output_matrix(m3,m1_rows,m2_columns);
            free(m1);
            free(m2);
            free(m3);
            return(0);
        } else {
            printf("Error in dimensions\n");
            free(m1);
            free(m2);
            free(m3);
            return(-1);
        }
    } else {
        free(m1);
        free(m2);
        free(m3);
        printf("Error allocating memory\n");
        return(-2);
    }
}

double *input_matrix(int *rows,int *columns,char *name) {
//-- matrix that's being created
    double *input_matrix;

//-- gets the row and column numbers from the user
    printf("Please enter the number of rows and columns for %s: \n", name);
    scanf("%d %d", rows, columns);

//-- dynamically allocates memory from the heap
    input_matrix = (double *)malloc((*rows) * (*columns) * sizeof(double));

//-- fill the matrix with user inputs
    for (int i = 0; i < (*rows * *columns); ++i) {
        printf("Enter a value for %s\n", name);
        scanf("%lf", &input_matrix[i]);
}

//-- return the created matrix 
    return input_matrix;
}

int matrix_multiply(double *m1, int m1rows, int m1columns, double *m2, int m2rows, int m2columns, double *m3) {

//-- Check to make sure the dimensions are appropriate for matrix multiplication, ie that the number of columns in the first matrix is equal to the number of rows in the second matrix
    if (m1columns != m2rows) {
        printf("Inappropriate dimensions for matrix multiplication");
	return 0;
}   else {
//-- Perform matrix multiplication if dimensions are appropriate
        for (int i = 0; i < m1rows; ++i) {
  	    for (int j = 0; j < m2columns; ++j) {
                m3[i * m2columns + j] = 0;
                for(int k = 0; k < m2rows; ++k) {
                    m3[i * m2columns + j] += m1[i * m1columns + k] * m2[k * m2columns + j];
                }
            }
        }
    return 1;
    }
}

void output_matrix (double *matrix, int rows, int columns) {
//-- print out the matrix
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < columns; ++j) {
            printf("%lf\n", matrix[i * columns + j]);
        }
    }
}
