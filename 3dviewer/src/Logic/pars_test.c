#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#include "../s21_parser.h"

START_TEST(test_points) {
    struct data* data_object = malloc(sizeof(struct data));
    char* src = "../objects/diamond.obj";
    init_data(data_object);
    firstRead(data_object, src);
    int flag = create_matrix_vertexes(data_object->counter_vertexes + 1, 3,
                                    &data_object->matrix_3d);
    ck_assert_int_eq(flag, 0);
    data_object->polygons = (polygon_t *)malloc(sizeof(polygon_t) * (data_object->counter_facets + 1));
    secondRead(data_object, src);

    ck_assert_int_eq(data_object->counter_vertexes, 6);
    free(data_object->polygons);
    remove_matrix_vertexes(&data_object->matrix_3d);
    free(data_object);
}
END_TEST

START_TEST(test_lines) {
    struct data* data_object = malloc(sizeof(struct data));
    char* src = "../objects/diamond.obj";
    init_data(data_object);
    firstRead(data_object, src);
    int flag = create_matrix_vertexes(data_object->counter_vertexes + 1, 3,
                                    &data_object->matrix_3d);
    ck_assert_int_eq(flag, 0);
    data_object->polygons = (polygon_t *)malloc(sizeof(polygon_t) * (data_object->counter_facets + 1));
    secondRead(data_object, src);

    ck_assert_int_eq(data_object->counter_facets, 9);
    free(data_object->polygons);
    remove_matrix_vertexes(&data_object->matrix_3d);
    free(data_object);
}
END_TEST

START_TEST(test_opengl_vertexes) {
    struct data* data_object = malloc(sizeof(struct data));
    char* src = "../objects/diamond.obj";
    init_data(data_object);
    firstRead(data_object, src);
    int flag = create_matrix_vertexes(data_object->counter_vertexes + 1, 3,
                                    &data_object->matrix_3d);
    ck_assert_int_eq(flag, 0);
    data_object->polygons = (polygon_t *)malloc(sizeof(polygon_t) * (data_object->counter_facets + 1));
    secondRead(data_object, src);

    double *check_array = (double *)calloc((data_object->counter_vertexes * 3), sizeof(double));
    to_vertex_opengl(data_object, check_array);

    double fixed_array[18] = {0.000000, 0.000000, 78.0000, 45.0000, 45.0000,
     0.000000, 45.0000, -45.0000, 0.000000, -45.0000, -45.0000, 0.000000,
      -45.0000, 45.0000, 0.000000, 0.000000, 0.000000, -78.0000};
    for(int i = 0; i < 18; i++) ck_assert_double_eq(check_array[i], fixed_array[i]/78);

    free(check_array);
    free(data_object->polygons);
    remove_matrix_vertexes(&data_object->matrix_3d);
    free(data_object);
}
END_TEST

START_TEST(test_opengl_facets) {
    struct data* data_object = malloc(sizeof(struct data));
    char* src = "../objects/diamond.obj";
    init_data(data_object);
    firstRead(data_object, src);
    int flag = create_matrix_vertexes(data_object->counter_vertexes + 1, 3,
                                    &data_object->matrix_3d);
    ck_assert_int_eq(flag, 0);
    data_object->polygons = (polygon_t *)malloc(sizeof(polygon_t) * (data_object->counter_facets + 1));
    secondRead(data_object, src);

    unsigned int *check_array = (unsigned int *)calloc(
        (data_object->counter_index * 2 + 1), sizeof(unsigned int));

    unsigned int fixed_array[66] = 
      {1, 2, 2, 3, 3, 4, 4, 1,
      1, 3, 3, 4, 4, 1,
      1, 4, 4, 5, 5, 1,
      1, 5, 5, 2, 2, 5, 5, 1,
      6, 5, 5, 4, 4, 6,
      6, 4, 4, 3, 3, 6,
      6, 3, 3, 2, 2, 3, 3, 2, 2, 6,
      6, 2, 2, 1, 1, 6,
      6, 1, 1, 5, 5, 1, 1, 1, 1, 6};

    to_facets_opengl(data_object, check_array);

    for(int i = 0; i < 66; i++) ck_assert_uint_eq(check_array[i], fixed_array[i]-1);
    
    free(check_array);
    free(data_object->polygons);
    remove_matrix_vertexes(&data_object->matrix_3d);
    free(data_object);
}
END_TEST

Suite *suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Parser check");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_points);
  tcase_add_test(tc_core, test_lines);
  tcase_add_test(tc_core, test_opengl_vertexes);
  tcase_add_test(tc_core, test_opengl_facets);
  suite_add_tcase(s, tc_core);

  return s;
}

int parser_test_func() {
  int no_failed = 0;

  Suite *s;
  SRunner *runner;

  s = suite();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return no_failed;
}

int main() {
  int no_failed = 0;

  no_failed |= parser_test_func();

  // return 0;
  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
