#include "../s21_parser.h"

int parser(struct data *data_object, char *src) {
  init_data(data_object);
  firstRead(data_object, src);
  int flag = create_matrix_vertexes(data_object->counter_vertexes + 1, 3,
                                    &data_object->matrix_3d);
  if (flag != 0) {
    fprintf(stderr, "Error in building matrix of vertexes.");
    return 0;
  }
  data_object->polygons = (polygon_t *)malloc(
      sizeof(polygon_t) * (data_object->counter_facets + 1));
  secondRead(data_object, src);
  return 0;
}

void secondRead(struct data *data_object, char *file_name) {
  FILE *streamObject = fopen(file_name, "r");
  char *line = (char *)malloc(1024 * sizeof(char));
  int row_vertex = 0;
  int row_facets = 0;
  bool canWrite = true;
  bool sameDigit = false;
  while (fgets(line, 1024, streamObject)) {
    size_t size_of_line = strlen(line);
    char *ptr_line = line;
    if (size_of_line > 2 && ptr_line[0] == 'v' && ptr_line[1] == ' ') {
      char *next0;
      data_object->matrix_3d.matrix[row_vertex][0] =
          strtod(ptr_line + 2, &next0);
      char *next1;
      data_object->matrix_3d.matrix[row_vertex][1] = strtod(next0, &next1);
      data_object->matrix_3d.matrix[row_vertex][2] = strtod(next1, NULL);
      checkMax(data_object, data_object->matrix_3d.matrix[row_vertex]);
      row_vertex++;
      continue;
    }
    if (size_of_line > 2 && ptr_line[0] == 'f') {
      data_object->polygons[row_facets].numbers_of_vertexes_in_facets = 0;
      for (char *temp = line + 2; *temp != '\0' && *temp != '\n'; temp++) {
        if (canWrite && isDigit(*temp) && !sameDigit) {
          data_object->polygons[row_facets].numbers_of_vertexes_in_facets++;
          data_object->counter_index++;
          sameDigit = true;
        }
        if (*temp == '/')
          canWrite = false;
        if (*temp == ' ') {
          canWrite = true;
          sameDigit = false;
        }
      }
      canWrite = true;
      sameDigit = false;
      data_object->polygons[row_facets].vertexes = (int *)calloc(
          data_object->polygons[row_facets].numbers_of_vertexes_in_facets * 2,
          sizeof(int));
      ptr_line++;
      for (int k = 0; *ptr_line != '\0' && *ptr_line != '\n'; ptr_line++) {
        char *temp;
        if (*ptr_line == '/')
          canWrite = false;
        if (canWrite) {
          data_object->polygons[row_facets].vertexes[k] =
              (int)strtod(ptr_line, &temp);
          if (k != 0) {
            k++;
            data_object->polygons[row_facets].vertexes[k] =
                data_object->polygons[row_facets].vertexes[k - 1];
          }
          k++;
          ptr_line = temp;
        }
        if (*ptr_line == '/')
          canWrite = false;
        if (*ptr_line == ' ')
          canWrite = true;
      }
      data_object->polygons[row_facets].vertexes[(
          data_object->polygons[row_facets].numbers_of_vertexes_in_facets * 2 -
          1)] = data_object->polygons[row_facets].vertexes[0];
      shiftLeft(data_object, row_facets);
      canWrite = true;
      row_facets++;
    }
  }
  fclose(streamObject);
  free(line);
}

void firstRead(struct data *data_object, char *file_name) {
  FILE *streamObject = fopen(file_name, "r");
  char *line = (char *)malloc(1024 * sizeof(char));
  while (fgets(line, 1024, streamObject)) {
    size_t size_of_line = strlen(line);
    char *ptr_line = line;
    if (size_of_line > 2 && ptr_line[0] == 'v' && ptr_line[1] == ' ') {
      data_object->counter_vertexes++;
    }
    if (size_of_line > 2 && ptr_line[0] == 'f') {
      data_object->counter_facets++;
    }
  }
  fclose(streamObject);
  free(line);
}

bool isDigit(char c) {
  bool ans = false;
  if ((c >= ASCII_DIGIT_START && c <= ASCII_DIGIT_END) || c == '.' || c == ',')
    ans = true;
  return ans;
}

void init_data(struct data *data) {
  data->counter_facets = 0;
  data->counter_vertexes = 0;
  data->polygons = NULL;
  data->counter_index = 0;
}

// matrix_t *copy_matrix(matrix_t *matrix) {
//   matrix_t *result = (matrix_t *)malloc(sizeof(matrix_t));
//   int flag = create_matrix_vertexes(matrix->rows + 1, 3, result);
//   if (flag != 0) {
//     fprintf(stderr, "Error in building matrix of vertexes.");
//     return 0;
//   }
//   for (int i = 1; i < matrix->rows; i++) {
//     result->matrix[i][0] = matrix->matrix[i][0];
//     result->matrix[i][1] = matrix->matrix[i][1];
//     result->matrix[i][2] = matrix->matrix[i][2];
//   }
//   result->columns = matrix->columns;
//   result->rows = matrix->rows;
//   return result;
// }

void shiftLeft(struct data *data_object, int row_facets) {
  for (int i = 0;
       i < data_object->polygons[row_facets].numbers_of_vertexes_in_facets * 2;
       i++) {
    data_object->polygons[row_facets].vertexes[i] -= 1;
  }
}

void to_vertex_opengl(struct data *data_object, double *array) {
  unsigned int size = 0;
  for (unsigned int i = 0; i < data_object->counter_vertexes; i++) {
    array[size] =
        data_object->matrix_3d.matrix[i][0] / data_object->matrix_3d.max_value;
    size++;
    array[size] =
        data_object->matrix_3d.matrix[i][1] / data_object->matrix_3d.max_value;
    size++;
    array[size] =
        data_object->matrix_3d.matrix[i][2] / data_object->matrix_3d.max_value;
    size++;
  }
}

void to_facets_opengl(struct data *data_object, unsigned int *array) {
  unsigned int size = 0;
  for (unsigned int i = 0; i < data_object->counter_facets; i++) {
    for (int j = 0;
         j < data_object->polygons[i].numbers_of_vertexes_in_facets * 2; j++) {
      array[size] = data_object->polygons[i].vertexes[j];
      size++;
    }
  }
}

void checkMax(struct data *data, double *array) {
  for (int i = 0; i < 3; i++) {
    if (data->matrix_3d.max_value < fabs(array[i])) {
      data->matrix_3d.max_value = fabs(array[i]);
    }
  }
}
