#include "s21_matrix.h"

// 0 - OK
// 1 - Ошибка, некорректная матрица
// 2 - Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой
// нельзя провести вычисления и т.д.)

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error = 0;
  if (rows <= 0 || columns <= 0 || result == NULL) {
    error = 1;
  }
  if (!error) {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(sizeof(double *), rows + 1);
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = (double *)calloc(sizeof(double), columns + 1);
    }
  }
  return error;
}

void s21_print_matrix(matrix_t *result) {
  for (int number_of_rows = 0; number_of_rows < result->rows;
       number_of_rows++) {
    for (int number_of_columns = 0; number_of_columns < result->columns;
         number_of_columns++) {
      printf("%lf ", result->matrix[number_of_rows][number_of_columns]);
    }
    printf("\n");
  }
}

void s21_remove_matrix(matrix_t *A) {
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

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int error = SUCCESS;
  if (A == NULL || B == NULL) {
    error = FAILURE;
  } else {
    if ((A->rows != B->rows || A->columns != B->columns) ||
        (A->rows <= 0 || A->columns <= 0)) {
      error = FAILURE;
    } else {
      if (A->rows == 1 && A->columns == 1) {
        if (fabs(A->matrix[0][0] - B->matrix[0][0]) >= 1E-7) {
          error = FAILURE;
        }
      }
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          if (fabs(A->matrix[i][j] - B->matrix[i][j]) >= 1E-7) {
            error = FAILURE;
            break;
          }
        }
      }
    }
  }
  return error;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = 0;
  if ((!correct_matrix(A) || !correct_matrix(B)) || result == NULL) {
    error = 1;
  } else if (!equal_size_of_two_matrix(A, B) && error == 0) {
    error = 2;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }
  return error;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = 0;
  if ((!correct_matrix(A) || !correct_matrix(B)) || result == NULL) {
    error = 1;
  } else if (!equal_size_of_two_matrix(A, B) && error == 0) {
    error = 2;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }
  return error;
}

int equal_size_of_two_matrix(matrix_t *A, matrix_t *B) {
  int correct = SUCCESS;
  int a_rows = A->rows;
  int a_columns = A->columns;
  int b_rows = B->rows;
  int b_columns = B->columns;
  if (a_rows != b_rows || a_columns != b_columns) {
    correct = FAILURE;
  }
  return correct;
}

int correct_matrix(matrix_t *A) {
  int correct = SUCCESS;
  if (A == NULL) {
    correct = FAILURE;
  } else if (A->rows <= 0 || A->columns <= 0 || A->matrix == NULL) {
    correct = FAILURE;
  } else {
    correct = SUCCESS;
  }
  return correct;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int error = 0;
  if (A == NULL || !correct_matrix(A) || result == NULL) {
    error = 1;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return error;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int error = 0;
  if (!correct_matrix(A) || result == NULL) {
    error = 1;
  } else {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  return error;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = 0;
  if ((!correct_matrix(A) || !correct_matrix(B)) || result == NULL) {
    error = 1;
  } else if ((A->columns != B->rows) && error == 0) {
    error = 2;
  } else {
    s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = mult_one_row_one_column(A, B, i, j);
      }
    }
  }
  return error;
}

double mult_one_row_one_column(matrix_t *A, matrix_t *B, int row, int columns) {
  double result = 0;
  for (int j = 0; j < A->columns; j++) {
    result += A->matrix[row][j] * B->matrix[j][columns];
  }
  return result;
}

int s21_determinant(matrix_t *A, double *result) {
  int error = 0;
  double temp_res = 0;
  if (!correct_matrix(A) || result == NULL) {
    error = 1;
  } else if (A->rows != A->columns && error == 0) {
    error = 2;
  } else {
    if (A->rows == 1) {
      *result = A->matrix[0][0];
    } else if (A->rows == 2) {
      *result = ((A->matrix[0][0] * A->matrix[1][1]) -
                 (A->matrix[1][0] * A->matrix[0][1]));
    } else {
      matrix_t buffer;
      *result = 0;
      s21_create_matrix(A->rows - 1, A->columns - 1, &buffer);
      for (int j = 0; j < A->rows; j++) {
        s21_get_minor(A, 0, j, &buffer);
        s21_determinant(&buffer, &temp_res);
        *result += pow(-1, j) * A->matrix[0][j] * temp_res;
      }
      s21_remove_matrix(&buffer);
    }
  }
  return error;
}

void s21_get_minor(matrix_t *A, int removed_row, int removed_column,
                   matrix_t *result) {
  int new_row = 0;
  int new_column = 0;
  result->rows = A->rows - 1;
  result->columns = A->columns - 1;
  for (int i = 0; i < A->rows - 1; i++) {
    if (i == removed_row) new_row = 1;
    for (int j = 0; j < A->columns - 1; j++) {
      if (j == removed_column) new_column = 1;
      result->matrix[i][j] = A->matrix[i + new_row][j + new_column];
    }
    new_column = 0;
  }
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error = 0;
  double temp_res = 0;
  if (!correct_matrix(A) || result == NULL) {
    error = 1;
  } else if (A->rows != A->columns) {
    error = 2;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    if (A->rows == 1 && A->columns == 1) {
      result->matrix[0][0] = A->matrix[0][0];
    } else {
      matrix_t buffer;
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          s21_create_matrix(A->rows - 1, A->columns - 1, &buffer);
          s21_get_minor(A, i, j, &buffer);
          s21_determinant(&buffer, &temp_res);
          result->matrix[i][j] = temp_res * pow(-1, i + j);
          s21_remove_matrix(&buffer);
          temp_res = 0;
        }
      }
    }
  }
  return error;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int error = 0;
  if (!correct_matrix(A) || result == NULL) {
    error = 1;
  } else if (A->rows != A->columns) {
    error = 2;
  } else {
    double determinant = 0;
    s21_determinant(A, &determinant);
    if (determinant == 0.0) {
      error = 2;
    } else {
      determinant = 1.0 / determinant;
      s21_create_matrix(A->rows, A->columns, result);
      if (A->rows == 1) {
        result->matrix[0][0] = determinant;
      } else {
        matrix_t buffer, buffer_transposed;
        s21_create_matrix(A->rows, A->columns, &buffer);
        s21_create_matrix(A->rows, A->columns, &buffer_transposed);
        s21_calc_complements(A, &buffer);
        s21_transpose(&buffer, &buffer_transposed);
        s21_mult_number(&buffer_transposed, determinant, result);
        s21_remove_matrix(&buffer);
        s21_remove_matrix(&buffer_transposed);
      }
    }
  }
  return error;
}
