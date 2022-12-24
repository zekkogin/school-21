#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
--------------------------------------------------------------------------------------------------------------------------------------------
хранится число
0 - младшие биты
1 - средние биты
2 - старшие биты
00000000000000000000000000000000    00000000000000000000000000000000    00000000000000000000000000000000
31 - хранит знак числа
с 30 по 24 не используются
с 23 по 16 - хранит степень
с 15 по 0 - не использутся
0 0000000 0000000 0000000000000000
знак: 0 - число полодительное 1 - число отрицательное
--------------------------------------------------------------------------------------------------------------------------------------------
*/
typedef enum { RARE, MEDIUM, WELL, DATA } PART_DECIMAL;

typedef struct {
    int bits[4];
} s21_decimal;

typedef struct {
    int bits[7];
} s21_long_decimal;

// вспомогательные структуры
typedef struct DATA_FOR_EQUALIZE {
    int difference;
    int st_search;
    int sign_save;
    s21_decimal cursor;
    s21_decimal *res;
} DATA_FOR_EQUALIZE;

// арифметика
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_add_long_decimal(s21_long_decimal value_1, s21_long_decimal value_2, s21_long_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// операторы сравнения
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

// функции конвертации
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
void from_s21_decimal_to_s21_long_decimal(s21_decimal src, s21_long_decimal *dst);
int from_s21_long_decimal_to_s21_decimal(s21_long_decimal src, s21_decimal *dst);

// другие функции
int s21_negate(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
// операции над битами
void AddBitInDecimal(int new_bit, char *buffer_decimal, int counter_buffer_decimal, int *save_bit);

// маски
void CleanSign(int *num);
int CheckRigtBit(int num);
int CheckLeftBit(int num);
int CheckBitInTwoInt(int num_one, int num_two);
void AddSign(int *part_decimal, const int src);
void AddBit(int *num);
int CheckNotZero(int num);
int CheckFraction(int num);

// вспомогательные функции
void PrintDecimalBinary(s21_decimal decimal);
void PrintLongDecimalBinary(s21_long_decimal decimal);
void s21_reverse_string(char *line_for_num, int size);
unsigned int ConvertSignInt(int src);
void CleanDecimal(s21_decimal *dst);
void ReverseBits(int *num);
void ConvertStringToDecimal(const char *buffer_decimal, s21_decimal *result);
void ConvertStringToLongDecimal(const char *buffer_decimal, s21_long_decimal *result);
int CheckOverflow(int save_bit, int st_val_1, int st_val_2);
int Summation(s21_decimal value_1, s21_decimal value_2, char *buffer_decimal);
int SummationLongDecimal(s21_long_decimal value_1, s21_long_decimal value_2, char *buffer_decimal);
int CheckSignForSummation(s21_decimal value_1, s21_decimal value_2);
int GetFractionStDecimal(int num);
int CheckFractionDecimal(int val_1, int val_2);
void BufferForEqualizeDecimal(s21_decimal *value_1, s21_decimal *value_2);
int EqualizeDecimal(s21_decimal *value_1, s21_decimal *value_2);
void GetDataForEqualizeDecimal(s21_decimal *value_1, s21_decimal *value_2, DATA_FOR_EQUALIZE *data);
int ShiftLeft(s21_decimal *num);
int ShiftLeftLongDecimal(s21_long_decimal *num);
int ShifRigtLongDecimal(s21_long_decimal *num);
void ChangeDegree(int sign, int *num);
int DivInTen(s21_decimal *value);
int DivInTenLongDecimal(s21_long_decimal *value);
int CheckLostNum(s21_decimal value);
int ReduceDegree(s21_decimal *value);
int ReduceDegreeLongDecimal(s21_long_decimal *value);
// zeckodin - вспомогательные функции - начало
int getBinaryExp(unsigned int fbits);
void setMantissa(s21_decimal *dst, int binaryScale);
void setFloat(s21_decimal *dst, int binaryScale, unsigned int fbits);
int CheckNotZeroDecimal(s21_decimal *decimal);
void ShiftRightCycle(s21_decimal *num, int counter);
void ShiftRightCycleLongDecinal(s21_long_decimal *num, int counter);
void s21_div_simple_dimple(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_is_greater_or_equal_simple(s21_decimal value_1, s21_decimal value_2);
int signific_bits(s21_decimal value);
void setMaxDecimal(s21_decimal *value);
// zeckodin - вспомогательные функции - конец
// alessand - вспомогательные функции - начало
int s21_get_long_bit(s21_long_decimal number, int bit_position);
void s21_set_sign(s21_decimal *number, int sign);
int s21_get_scale(s21_decimal number);
void s21_set_scale(s21_decimal *number, int scale);
int s21_get_highest_bit(s21_long_decimal number);
int s21_get_bit(s21_decimal number, int bit_position);
void s21_shift_left(s21_decimal *number);
void s21_set_bit(int *source_number, int bit_position, int bit);
int s21_get_sign(s21_decimal number);
// alessand - вспомогательные функции - конец
// qylenett - вспомогательные функции - начало
void subtraction(const s21_decimal *value_1, s21_decimal *value_2, s21_decimal *result);
int check_bit_depth(s21_decimal value);
int inversion(s21_decimal *value);
int check_last_bit(s21_decimal value);
int set_last_bit(s21_decimal *value);
int shifting(s21_decimal *result, int depth);
// qylenett - вспомогательные функции - конец

#endif  // SRC_S21_DECIMAL_H_
