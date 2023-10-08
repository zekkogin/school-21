#include "../s21_parser.h"

int create_matrix_vertexes(int rows, int columns, matrix_t *current) {
  int error = 0;
  if (rows <= 0 || columns <= 0 || current == NULL) {
    error = 1;
  }
  if (!error) {
    current->rows = rows;
    current->columns = columns;
    current->max_value = 0;
    current->matrix = (double **)calloc(sizeof(double *), rows + 1);
    for (int i = 0; i < rows; i++) {
      current->matrix[i] = (double *)calloc(sizeof(double), columns + 1);
    }
  }
  return error;
}

void print_matrix_vertexes(matrix_t *current) {
  for (int number_of_rows = 0; number_of_rows < current->rows;
       number_of_rows++) {
    for (int number_of_columns = 0; number_of_columns < current->columns;
         number_of_columns++) {
      printf("%lf ", current->matrix[number_of_rows][number_of_columns]);
    }
    printf("\n");
  }
}

void remove_matrix_vertexes(matrix_t *A) {
  if (A == NULL) {
  } else {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
    A->matrix = NULL;
    A->columns = 0;
    A->rows = 0;
  }
}
