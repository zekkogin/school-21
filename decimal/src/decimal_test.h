#ifndef SRC_DECIMAL_TEST_H_
#define SRC_DECIMAL_TEST_H_

#include <check.h>

#include "s21_decimal.h"

#define ARRAY_SIZE(arr) sizeof(arr) / sizeof(arr[0])

static const unsigned b_zero[3] = {0};

#define ASSERT_DECIMAL_EQ                                                                        \
    for (size_t i = 0; i < 4; i++) {                                                             \
        ck_assert_msg(result.bits[i] == expected.bits[i], "[%zu] %#x != %#x", i, result.bits[i], \
                      expected.bits[i]);                                                         \
    }

#define ASSERT_UINT192_EQ                                                                        \
    for (size_t i = 0; i < 6; i++) {                                                             \
        ck_assert_msg(result.bits[i] == expected.bits[i], "[%zu] %#x != %#x", i, result.bits[i], \
                      expected.bits[i]);                                                         \
    }

#define MASK_32 0xFFFFFFFFl
#define SCALE_SHIFT 16
#define SIGN_SHIFT 31

enum comparison_result {
    LT = -1,
    EQ = 0,
    GT = 1,
};

#define DSIZE sizeof(s21_decimal)

static const s21_decimal DEC_ZERO = {{0, 0, 0, 0}};
static const s21_decimal DEC_ONE = {{1, 0, 0, 0}};
static const s21_decimal DEC_FIVE = {{5, 0, 0, 0}};
static const s21_decimal DEC_TEN = {{10, 0, 0, 0}};
static const s21_decimal DEC_MAX = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
static const s21_decimal DEC_INT_MAX = {{INT_MAX, 0, 0, 0}};
static const s21_decimal DEC_INT_MIN = {{INT_MIN, 0, 0, 1}};
static const unsigned int max32bit = 4294967295;
static const unsigned int maxScale = 1835008;

int TestConvertFunc();
int TestS21_ADD();
int TestComparisonFunc();
int TestMulFunc();
int TestOther_func();

#endif  // SRC_DECIMAL_TEST_H_
