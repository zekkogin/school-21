#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_
#define SUCCESS 1
#define FAILURE 0

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// 0 - OK
// 1 - Ошибка, некорректная матрица
// 2 - Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой
// нельзя провести вычисления и т.д.)

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);

int s21_eq_matrix(matrix_t *A, matrix_t *B);

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

int s21_transpose(matrix_t *A, matrix_t *result);

int s21_calc_complements(matrix_t *A, matrix_t *result);

int s21_determinant(matrix_t *A, double *result);

int s21_inverse_matrix(matrix_t *A, matrix_t *result);

// вспомогательные функции
void s21_print_matrix(matrix_t *result);
int equal_size_of_two_matrix(matrix_t *A, matrix_t *B);
int correct_matrix(matrix_t *A);
double mult_one_row_one_column(matrix_t *A, matrix_t *B, int row, int columns);
void s21_get_minor(matrix_t *A, int removed_row, int removed_column,
                   matrix_t *result);

#endif  // SRC_S21_MATRIX_H_