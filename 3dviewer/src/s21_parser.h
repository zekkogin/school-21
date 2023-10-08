#ifndef SRC_S21_PARSER_H_
#define SRC_S21_PARSER_H_

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ASCII_DIGIT_START 48
#define ASCII_DIGIT_END 57

/**
 * @brief data-structure of all vertexes, matrix[rows][x,y,z]
 */
typedef struct Matrix_Vertex {
  double **matrix;
  int rows;
  int columns;
  double max_value;
} matrix_t;
/**
 * @brief data-structure of all facets
 */
typedef struct facets {
  int *vertexes;
  int numbers_of_vertexes_in_facets;
} polygon_t;
/**
 * @brief data-structure of all data
 */
struct data {
  unsigned int counter_vertexes;
  unsigned int counter_facets;
  unsigned int counter_index;
  matrix_t matrix_3d;
  polygon_t *polygons;
};

/**
 * @brief Function to copy all matrix[i][x,y,z] to array like
 * array[x1,y1,z1,x2,y2,z2...]
 * @param all data
 * @param fixed array
 */
void to_vertex_opengl(struct data *data_object, double *array);
/**
 * @brief Function to copy all vertexes[i][0,1,2...] to array like
 * array[0,1,2,3...]
 * @param all data
 * @param fixed array
 */
void to_facets_opengl(struct data *data_object, unsigned int *array);
/**
 * @brief Main function (first and second read)
 * @param all data
 * @param path to file
 * @return flag error
 */
int parser(struct data *data_object, char *src);
/**
 * @brief Shift left indexes of vertexes
 * @param all data
 * @param current row of facets
 */
void shiftLeft(struct data *data_object, int row_facets);
/**
 * @brief Find maximum vertex
 * @param all data
 * @param current row of vertexes
 */
void checkMax(struct data *data, double *array);
/**
 * @brief Init data->matrix3d
 */
int create_matrix_vertexes(int rows, int columns, matrix_t *current);
void print_matrix_vertexes(matrix_t *result);
/**
 * @brief Init data
 */
void init_data(struct data *data);
/**
 * @brief Set data->count_vertexes && data->count_facets
 */
void firstRead(struct data *data_object, char *file_name);
/**
 * @brief Set data->polygons && data->matrix3d
 */
void secondRead(struct data *data_object, char *file_name);
/**
 * @brief Check char is digit
 */
bool isDigit(char c);
/**
 * @brief temp function
 */
void remove_matrix_vertexes(matrix_t *A);

#endif // SRC_S21_PARSER_H_
