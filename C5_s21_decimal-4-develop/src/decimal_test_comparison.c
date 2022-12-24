#include "decimal_test.h"

START_TEST(s21_comparison_test_is_less) {
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 100;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0;
        s21_decimal test_two;
        test_two.bits[RARE] = 0;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0;
        int check = s21_is_less(test_two, test_one);
        ck_assert_int_eq(check, 1);
        int check_two = s21_is_less(test_one, test_two);
        ck_assert_int_eq(check_two, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00000000000000000000000001100100;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b00000000000000000000000001100100;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0;
        int check = s21_is_less(test_two, test_one);
        ck_assert_int_eq(check, 0);
        int check_two = s21_is_less(test_one, test_two);
        ck_assert_int_eq(check_two, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0;
        s21_decimal test_two;
        test_two.bits[RARE] = 0;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0;
        int check = s21_is_less(test_two, test_one);
        ck_assert_int_eq(check, 0);
        int check_two = s21_is_less(test_one, test_two);
        ck_assert_int_eq(check_two, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b10000000000000000000000000000000;
        int check = s21_is_less(test_two, test_one);
        ck_assert_int_eq(check, 0);
        int check_two = s21_is_less(test_one, test_two);
        ck_assert_int_eq(check_two, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b00000000000000000000000000000000;
        int check = s21_is_less(test_two, test_one);
        ck_assert_int_eq(check, 0);
        int check_two = s21_is_less(test_one, test_two);
        ck_assert_int_eq(check_two, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b00000000000000000000000000000000;
        int check = s21_is_less(test_two, test_one);
        ck_assert_int_eq(check, 0);
        int check_two = s21_is_less(test_one, test_two);
        ck_assert_int_eq(check_two, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b11001001101101010110010101010111;
        test_one.bits[MEDIUM] = 0b10100100000110100000101000101010;
        test_one.bits[WELL] = 0b00000000000100111100000000001111;
        test_one.bits[DATA] = 0b00000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b11111111111111111111111111111111;
        test_two.bits[MEDIUM] = 0b11111111111111111111111111111111;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b00000000000000000000000000000000;
        int check = s21_is_less(test_two, test_one);
        ck_assert_int_eq(check, 1);
        int check_two = s21_is_less(test_one, test_two);
        ck_assert_int_eq(check_two, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b11001001101101010110010101010111;
        test_one.bits[MEDIUM] = 0b10100100000110100000101000101010;
        test_one.bits[WELL] = 0b00000000000100111100000000001111;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b11111111111111111111111111111111;
        test_two.bits[MEDIUM] = 0b11111111111111111111111111111111;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b00000000000000000000000000000000;
        int check = s21_is_less(test_two, test_one);
        ck_assert_int_eq(check, 0);
        int check_two = s21_is_less(test_one, test_two);
        ck_assert_int_eq(check_two, 1);
    }
}
END_TEST

START_TEST(s21_comparison_test_is_greater) {
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 100;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0;
        s21_decimal test_two;
        test_two.bits[RARE] = 0;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0;
        int check = s21_is_greater(test_two, test_one);
        ck_assert_int_eq(check, 0);
        int check_two = s21_is_greater(test_one, test_two);
        ck_assert_int_eq(check_two, 1);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00000000000000000000000001100100;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b00000000000000000000000001100100;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0;
        int check = s21_is_greater(test_two, test_one);
        ck_assert_int_eq(check, 0);
        int check_two = s21_is_greater(test_one, test_two);
        ck_assert_int_eq(check_two, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0;
        s21_decimal test_two;
        test_two.bits[RARE] = 0;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0;
        int check = s21_is_greater(test_two, test_one);
        ck_assert_int_eq(check, 0);
        int check_two = s21_is_greater(test_one, test_two);
        ck_assert_int_eq(check_two, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b10000000000000000000000000000000;
        int check = s21_is_greater(test_two, test_one);
        ck_assert_int_eq(check, 0);
        int check_two = s21_is_greater(test_one, test_two);
        ck_assert_int_eq(check_two, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b00000000000000000000000000000000;
        int check = s21_is_greater(test_two, test_one);
        ck_assert_int_eq(check, 0);
        int check_two = s21_is_greater(test_one, test_two);
        ck_assert_int_eq(check_two, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b00000000000000000000000000000000;
        int check = s21_is_greater(test_two, test_one);
        ck_assert_int_eq(check, 0);
        int check_two = s21_is_greater(test_one, test_two);
        ck_assert_int_eq(check_two, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b11001001101101010110010101010111;
        test_one.bits[MEDIUM] = 0b10100100000110100000101000101010;
        test_one.bits[WELL] = 0b00000000000100111100000000001111;
        test_one.bits[DATA] = 0b00000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b11111111111111111111111111111111;
        test_two.bits[MEDIUM] = 0b11111111111111111111111111111111;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b00000000000000000000000000000000;
        int check = s21_is_greater(test_two, test_one);
        ck_assert_int_eq(check, 0);
        int check_two = s21_is_greater(test_one, test_two);
        ck_assert_int_eq(check_two, 1);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b11001001101101010110010101010111;
        test_one.bits[MEDIUM] = 0b10100100000110100000101000101010;
        test_one.bits[WELL] = 0b00000000000100111100000000001111;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b11111111111111111111111111111111;
        test_two.bits[MEDIUM] = 0b11111111111111111111111111111111;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b00000000000000000000000000000000;
        int check = s21_is_greater(test_two, test_one);
        ck_assert_int_eq(check, 1);
        int check_two = s21_is_greater(test_one, test_two);
        ck_assert_int_eq(check_two, 0);
    }
}
END_TEST

START_TEST(s21_comparison_test_is_less_or_equal) {
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 100;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0;
        s21_decimal test_two;
        test_two.bits[RARE] = 0;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0;
        int check = s21_is_less_or_equal(test_two, test_one);
        ck_assert_int_eq(check, 1);
        int check_two = s21_is_less_or_equal(test_one, test_two);
        ck_assert_int_eq(check_two, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00000000000000000000000001100100;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b00000000000000000000000001100100;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0;
        int check = s21_is_less_or_equal(test_two, test_one);
        ck_assert_int_eq(check, 1);
        int check_two = s21_is_less_or_equal(test_one, test_two);
        ck_assert_int_eq(check_two, 1);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0;
        s21_decimal test_two;
        test_two.bits[RARE] = 0;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0;
        int check = s21_is_less_or_equal(test_two, test_one);
        ck_assert_int_eq(check, 1);
        int check_two = s21_is_less_or_equal(test_one, test_two);
        ck_assert_int_eq(check_two, 1);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b10000000000000000000000000000000;
        int check = s21_is_less_or_equal(test_two, test_one);
        ck_assert_int_eq(check, 1);
        int check_two = s21_is_less_or_equal(test_one, test_two);
        ck_assert_int_eq(check_two, 1);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b00000000000000000000000000000000;
        int check = s21_is_less_or_equal(test_two, test_one);
        ck_assert_int_eq(check, 1);
        int check_two = s21_is_less_or_equal(test_one, test_two);
        ck_assert_int_eq(check_two, 1);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b00000000000000000000000000000000;
        int check = s21_is_less_or_equal(test_two, test_one);
        ck_assert_int_eq(check, 1);
        int check_two = s21_is_less_or_equal(test_one, test_two);
        ck_assert_int_eq(check_two, 1);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b11001001101101010110010101010111;
        test_one.bits[MEDIUM] = 0b10100100000110100000101000101010;
        test_one.bits[WELL] = 0b00000000000100111100000000001111;
        test_one.bits[DATA] = 0b00000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b11111111111111111111111111111111;
        test_two.bits[MEDIUM] = 0b11111111111111111111111111111111;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b00000000000000000000000000000000;
        int check = s21_is_less_or_equal(test_two, test_one);
        ck_assert_int_eq(check, 1);
        int check_two = s21_is_less_or_equal(test_one, test_two);
        ck_assert_int_eq(check_two, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b11001001101101010110010101010111;
        test_one.bits[MEDIUM] = 0b10100100000110100000101000101010;
        test_one.bits[WELL] = 0b00000000000100111100000000001111;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b11111111111111111111111111111111;
        test_two.bits[MEDIUM] = 0b11111111111111111111111111111111;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b00000000000000000000000000000000;
        int check = s21_is_less_or_equal(test_two, test_one);
        ck_assert_int_eq(check, 0);
        int check_two = s21_is_less_or_equal(test_one, test_two);
        ck_assert_int_eq(check_two, 1);
    }
}
END_TEST

START_TEST(s21_comparison_test_is_greater_or_equal) {
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 100;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0;
        s21_decimal test_two;
        test_two.bits[RARE] = 0;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0;
        int check = s21_is_greater_or_equal(test_two, test_one);
        ck_assert_int_eq(check, 0);
        int check_two = s21_is_greater_or_equal(test_one, test_two);
        ck_assert_int_eq(check_two, 1);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00000000000000000000000001100100;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b00000000000000000000000001100100;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0;
        int check = s21_is_greater_or_equal(test_two, test_one);
        ck_assert_int_eq(check, 1);
        int check_two = s21_is_greater_or_equal(test_one, test_two);
        ck_assert_int_eq(check_two, 1);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0;
        s21_decimal test_two;
        test_two.bits[RARE] = 0;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0;
        int check = s21_is_greater_or_equal(test_two, test_one);
        ck_assert_int_eq(check, 1);
        int check_two = s21_is_greater_or_equal(test_one, test_two);
        ck_assert_int_eq(check_two, 1);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b10000000000000000000000000000000;
        int check = s21_is_greater_or_equal(test_two, test_one);
        ck_assert_int_eq(check, 1);
        int check_two = s21_is_greater_or_equal(test_one, test_two);
        ck_assert_int_eq(check_two, 1);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b00000000000000000000000000000000;
        int check = s21_is_greater_or_equal(test_two, test_one);
        ck_assert_int_eq(check, 1);
        int check_two = s21_is_greater_or_equal(test_one, test_two);
        ck_assert_int_eq(check_two, 1);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b00000000000000000000000000000000;
        int check = s21_is_greater_or_equal(test_two, test_one);
        ck_assert_int_eq(check, 1);
        int check_two = s21_is_greater_or_equal(test_one, test_two);
        ck_assert_int_eq(check_two, 1);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b11001001101101010110010101010111;
        test_one.bits[MEDIUM] = 0b10100100000110100000101000101010;
        test_one.bits[WELL] = 0b00000000000100111100000000001111;
        test_one.bits[DATA] = 0b00000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b11111111111111111111111111111111;
        test_two.bits[MEDIUM] = 0b11111111111111111111111111111111;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b00000000000000000000000000000000;
        int check = s21_is_greater_or_equal(test_two, test_one);
        ck_assert_int_eq(check, 0);
        int check_two = s21_is_greater_or_equal(test_one, test_two);
        ck_assert_int_eq(check_two, 1);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b11001001101101010110010101010111;
        test_one.bits[MEDIUM] = 0b10100100000110100000101000101010;
        test_one.bits[WELL] = 0b00000000000100111100000000001111;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b11111111111111111111111111111111;
        test_two.bits[MEDIUM] = 0b11111111111111111111111111111111;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b00000000000000000000000000000000;
        int check = s21_is_greater_or_equal(test_two, test_one);
        ck_assert_int_eq(check, 1);
        int check_two = s21_is_greater_or_equal(test_one, test_two);
        ck_assert_int_eq(check_two, 0);
    }
}
END_TEST

START_TEST(s21_comparison_test_is_equal) {
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 100;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0;
        s21_decimal test_two;
        test_two.bits[RARE] = 0;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0;
        int check = s21_is_equal(test_two, test_one);
        ck_assert_int_eq(check, 0);
        int check_two = s21_is_equal(test_one, test_two);
        ck_assert_int_eq(check_two, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00000000000000000000000001100100;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b00000000000000000000000001100100;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0;
        int check = s21_is_equal(test_two, test_one);
        ck_assert_int_eq(check, 1);
        int check_two = s21_is_equal(test_one, test_two);
        ck_assert_int_eq(check_two, 1);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0;
        s21_decimal test_two;
        test_two.bits[RARE] = 0;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0;
        int check = s21_is_equal(test_two, test_one);
        ck_assert_int_eq(check, 1);
        int check_two = s21_is_equal(test_one, test_two);
        ck_assert_int_eq(check_two, 1);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b10000000000000000000000000000000;
        int check = s21_is_equal(test_two, test_one);
        ck_assert_int_eq(check, 1);
        int check_two = s21_is_equal(test_one, test_two);
        ck_assert_int_eq(check_two, 1);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b00000000000000000000000000000000;
        int check = s21_is_equal(test_two, test_one);
        ck_assert_int_eq(check, 1);
        int check_two = s21_is_equal(test_one, test_two);
        ck_assert_int_eq(check_two, 1);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b00000000000000000000000000000000;
        int check = s21_is_equal(test_two, test_one);
        ck_assert_int_eq(check, 1);
        int check_two = s21_is_equal(test_one, test_two);
        ck_assert_int_eq(check_two, 1);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b11001001101101010110010101010111;
        test_one.bits[MEDIUM] = 0b10100100000110100000101000101010;
        test_one.bits[WELL] = 0b00000000000100111100000000001111;
        test_one.bits[DATA] = 0b00000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b11111111111111111111111111111111;
        test_two.bits[MEDIUM] = 0b11111111111111111111111111111111;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b00000000000000000000000000000000;
        int check = s21_is_equal(test_two, test_one);
        ck_assert_int_eq(check, 0);
        int check_two = s21_is_equal(test_one, test_two);
        ck_assert_int_eq(check_two, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b11001001101101010110010101010111;
        test_one.bits[MEDIUM] = 0b10100100000110100000101000101010;
        test_one.bits[WELL] = 0b00000000000100111100000000001111;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b11111111111111111111111111111111;
        test_two.bits[MEDIUM] = 0b11111111111111111111111111111111;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b00000000000000000000000000000000;
        int check = s21_is_equal(test_two, test_one);
        ck_assert_int_eq(check, 0);
        int check_two = s21_is_equal(test_one, test_two);
        ck_assert_int_eq(check_two, 0);
    }
}
END_TEST

START_TEST(s21_comparison_test_is_not_equal) {
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 100;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0;
        s21_decimal test_two;
        test_two.bits[RARE] = 0;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0;
        int check = s21_is_not_equal(test_two, test_one);
        ck_assert_int_eq(check, 1);
        int check_two = s21_is_not_equal(test_one, test_two);
        ck_assert_int_eq(check_two, 1);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00000000000000000000000001100100;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b00000000000000000000000001100100;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0;
        int check = s21_is_not_equal(test_two, test_one);
        ck_assert_int_eq(check, 0);
        int check_two = s21_is_not_equal(test_one, test_two);
        ck_assert_int_eq(check_two, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0;
        s21_decimal test_two;
        test_two.bits[RARE] = 0;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0;
        int check = s21_is_not_equal(test_two, test_one);
        ck_assert_int_eq(check, 0);
        int check_two = s21_is_not_equal(test_one, test_two);
        ck_assert_int_eq(check_two, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b10000000000000000000000000000000;
        int check = s21_is_not_equal(test_two, test_one);
        ck_assert_int_eq(check, 0);
        int check_two = s21_is_not_equal(test_one, test_two);
        ck_assert_int_eq(check_two, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b00000000000000000000000000000000;
        int check = s21_is_not_equal(test_two, test_one);
        ck_assert_int_eq(check, 0);
        int check_two = s21_is_not_equal(test_one, test_two);
        ck_assert_int_eq(check_two, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b00000000000000000000000000000000;
        int check = s21_is_not_equal(test_two, test_one);
        ck_assert_int_eq(check, 0);
        int check_two = s21_is_not_equal(test_one, test_two);
        ck_assert_int_eq(check_two, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b11001001101101010110010101010111;
        test_one.bits[MEDIUM] = 0b10100100000110100000101000101010;
        test_one.bits[WELL] = 0b00000000000100111100000000001111;
        test_one.bits[DATA] = 0b00000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b11111111111111111111111111111111;
        test_two.bits[MEDIUM] = 0b11111111111111111111111111111111;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b00000000000000000000000000000000;
        int check = s21_is_not_equal(test_two, test_one);
        ck_assert_int_eq(check, 1);
        int check_two = s21_is_not_equal(test_one, test_two);
        ck_assert_int_eq(check_two, 1);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b11001001101101010110010101010111;
        test_one.bits[MEDIUM] = 0b10100100000110100000101000101010;
        test_one.bits[WELL] = 0b00000000000100111100000000001111;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b11111111111111111111111111111111;
        test_two.bits[MEDIUM] = 0b11111111111111111111111111111111;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b00000000000000000000000000000000;
        int check = s21_is_not_equal(test_two, test_one);
        ck_assert_int_eq(check, 1);
        int check_two = s21_is_not_equal(test_one, test_two);
        ck_assert_int_eq(check_two, 1);
    }
}
END_TEST

int TestComparisonFunc() {
    Suite *suite = suite_create("s21_decimal_comparison");
    TCase *getCase = tcase_create("Core");
    SRunner *runner = srunner_create(suite);
    int check = 0;

    suite_add_tcase(suite, getCase);
    tcase_add_test(getCase, s21_comparison_test_is_less);
    tcase_add_test(getCase, s21_comparison_test_is_greater);
    tcase_add_test(getCase, s21_comparison_test_is_less_or_equal);
    tcase_add_test(getCase, s21_comparison_test_is_greater_or_equal);
    tcase_add_test(getCase, s21_comparison_test_is_equal);
    tcase_add_test(getCase, s21_comparison_test_is_not_equal);

    srunner_run_all(runner, CK_ENV);
    check = srunner_ntests_failed(runner);
    srunner_free(runner);
    return check;
}
