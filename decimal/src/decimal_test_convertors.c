#include "decimal_test.h"

START_TEST(s21_from_int_to_decimal_test) {
    {
        s21_decimal test;
        int num = 25;
        int error = s21_from_int_to_decimal(num, &test);
        int check = 0b00000000000000000000000000011001;
        ck_assert_int_eq(test.bits[RARE], check);
        ck_assert_int_eq(test.bits[MEDIUM], 0);
        ck_assert_int_eq(test.bits[WELL], 0);
        ck_assert_int_eq(test.bits[DATA], 0b00000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test;
        int num = 283656534;
        int error = s21_from_int_to_decimal(num, &test);
        int check = 0b00010000111010000100000101010110;
        ck_assert_int_eq(test.bits[RARE], check);
        ck_assert_int_eq(test.bits[MEDIUM], 0);
        ck_assert_int_eq(test.bits[WELL], 0);
        ck_assert_int_eq(test.bits[DATA], 0b00000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test;
        int num = -25;
        int error = s21_from_int_to_decimal(num, &test);
        int check = 0b00000000000000000000000000011001;
        ck_assert_int_eq(test.bits[RARE], check);
        ck_assert_int_eq(test.bits[MEDIUM], 0);
        ck_assert_int_eq(test.bits[WELL], 0);
        ck_assert_int_eq(test.bits[DATA], (int)0b10000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test;
        int num = -283656534;
        int error = s21_from_int_to_decimal(num, &test);
        int check = 0b00010000111010000100000101010110;
        ck_assert_int_eq(test.bits[RARE], check);
        ck_assert_int_eq(test.bits[MEDIUM], 0);
        ck_assert_int_eq(test.bits[WELL], 0);
        ck_assert_int_eq(test.bits[DATA], (int)0b10000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test;
        int num = 0;
        int error = s21_from_int_to_decimal(num, &test);
        int check = 0b00000000000000000000000000000000;
        ck_assert_int_eq(test.bits[RARE], check);
        ck_assert_int_eq(test.bits[MEDIUM], 0);
        ck_assert_int_eq(test.bits[WELL], 0);
        ck_assert_int_eq(test.bits[DATA], 0b00000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test;
        int num = INT_MAX;
        int error = s21_from_int_to_decimal(num, &test);
        int check = 0b01111111111111111111111111111111;
        ck_assert_int_eq(test.bits[RARE], check);
        ck_assert_int_eq(test.bits[MEDIUM], 0);
        ck_assert_int_eq(test.bits[WELL], 0);
        ck_assert_int_eq(test.bits[DATA], 0b00000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test;
        int num = INT_MIN;
        int error = s21_from_int_to_decimal(num, &test);
        int check = 0b10000000000000000000000000000000;
        ck_assert_int_eq(test.bits[RARE], check);
        ck_assert_int_eq(test.bits[MEDIUM], 0);
        ck_assert_int_eq(test.bits[WELL], 0);
        ck_assert_int_eq(test.bits[DATA], (int)0b10000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test;
        int error = s21_from_int_to_decimal((int)INFINITY, &test);
        int check = 0b01111111111111111111111111111111;
        ck_assert_int_eq(test.bits[RARE], check);
        ck_assert_int_eq(test.bits[MEDIUM], 0);
        ck_assert_int_eq(test.bits[WELL], 0);
        ck_assert_int_eq(test.bits[DATA], 0b00000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test;
        int error = s21_from_int_to_decimal((int)-INFINITY, &test);
        int check = 0b10000000000000000000000000000000;
        ck_assert_int_eq(test.bits[RARE], check);
        ck_assert_int_eq(test.bits[MEDIUM], 0);
        ck_assert_int_eq(test.bits[WELL], 0);
        ck_assert_int_eq(test.bits[DATA], (int)0b10000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test;
        int error = s21_from_int_to_decimal((int)NAN, &test);
        int check = 0b00000000000000000000000000000000;
        ck_assert_int_eq(test.bits[RARE], check);
        ck_assert_int_eq(test.bits[MEDIUM], 0);
        ck_assert_int_eq(test.bits[WELL], 0);
        ck_assert_int_eq(test.bits[DATA], 0b00000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test;
        int error = s21_from_int_to_decimal(+0, &test);
        int check = 0b00000000000000000000000000000000;
        ck_assert_int_eq(test.bits[RARE], check);
        ck_assert_int_eq(test.bits[MEDIUM], 0);
        ck_assert_int_eq(test.bits[WELL], 0);
        ck_assert_int_eq(test.bits[DATA], 0b00000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test;
        int error = s21_from_int_to_decimal(-0, &test);
        int check = 0b00000000000000000000000000000000;
        ck_assert_int_eq(test.bits[RARE], check);
        ck_assert_int_eq(test.bits[MEDIUM], 0);
        ck_assert_int_eq(test.bits[WELL], 0);
        ck_assert_int_eq(test.bits[DATA], 0b00000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test;
        int error = s21_from_int_to_decimal(' ', &test);
        int check = ' ';
        ck_assert_int_eq(test.bits[RARE], check);
        ck_assert_int_eq(test.bits[MEDIUM], 0);
        ck_assert_int_eq(test.bits[WELL], 0);
        ck_assert_int_eq(test.bits[DATA], 0b00000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
}
END_TEST

START_TEST(s21_from_decimal_to_int_test) {
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00000000000000000000000000101110;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0;
        int result;
        int error = s21_from_decimal_to_int(test_one, &result);
        ck_assert_int_eq(result, 46);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00000000000000000000000000101110;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        int result;
        int error = s21_from_decimal_to_int(test_one, &result);
        ck_assert_int_eq(result, -46);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00000000000000000001001001010010;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0;
        int result;
        int error = s21_from_decimal_to_int(test_one, &result);
        ck_assert_int_eq(result, 4690);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00000000000000000001001001010010;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        int result;
        int error = s21_from_decimal_to_int(test_one, &result);
        ck_assert_int_eq(result, -4690);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00000000000010110101110011110010;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0;
        int result;
        int error = s21_from_decimal_to_int(test_one, &result);
        ck_assert_int_eq(result, 744690);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00000000000010110101110011110010;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        int result;
        int error = s21_from_decimal_to_int(test_one, &result);
        ck_assert_int_eq(result, -744690);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00000100011100001000101111010010;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0;
        int result;
        int error = s21_from_decimal_to_int(test_one, &result);
        ck_assert_int_eq(result, 74484690);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00000100011100001000101111010010;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        int result;
        int error = s21_from_decimal_to_int(test_one, &result);
        ck_assert_int_eq(result, -74484690);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b01101000000000000100000000110111;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0;
        int result;
        int error = s21_from_decimal_to_int(test_one, &result);
        ck_assert_int_eq(result, 1744846903);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b01101000000000000100000000110111;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        int result;
        int error = s21_from_decimal_to_int(test_one, &result);
        ck_assert_int_eq(result, -1744846903);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b10100000000110000011110100010111;
        test_one.bits[MEDIUM] = 0b00000000000000000000000000101000;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0;
        int result;
        int error = s21_from_decimal_to_int(test_one, &result);
        ck_assert_int_eq(result, INT_MIN);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b01101000000000000100000000110111;
        test_one.bits[MEDIUM] = 0b00000000000000000000000000101000;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        int result;
        int error = s21_from_decimal_to_int(test_one, &result);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b1111111111111111111111111111111;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0;
        int result;
        int error = s21_from_decimal_to_int(test_one, &result);
        ck_assert_int_eq(result, INT_MAX);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b10000000000000000000000000000000;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        int result;
        int error = s21_from_decimal_to_int(test_one, &result);
        ck_assert_int_eq(result, INT_MIN);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b1111111111111111111111111111111;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0;
        int result;
        int error = s21_from_decimal_to_int(test_one, &result);
        ck_assert_int_eq(result, INT_MAX);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b10000000000000000000000000000000;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0b00000000000000100000000000000000;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        int result;
        int error = s21_from_decimal_to_int(test_one, &result);
        ck_assert_int_eq(result, INT_MIN);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00000000000000000000000101011001;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b00000000000000100000000000000000;
        int result;
        int error = s21_from_decimal_to_int(test_one, &result);
        ck_assert_int_eq(result, 3);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00000000000000000000000101011001;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000000100000000000000000;
        int result;
        int error = s21_from_decimal_to_int(test_one, &result);
        ck_assert_int_eq(result, -3);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00000000000000001000011011110001;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b00000000000001000000000000000000;
        int result;
        int error = s21_from_decimal_to_int(test_one, &result);
        ck_assert_int_eq(result, 3);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00000000000000001000011011110001;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000001000000000000000000;
        int result;
        int error = s21_from_decimal_to_int(test_one, &result);
        ck_assert_int_eq(result, -3);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00000000100000111100000010110001;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b00000000000001100000000000000000;
        int result;
        int error = s21_from_decimal_to_int(test_one, &result);
        ck_assert_int_eq(result, 8);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00000000100000111100000010110001;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000001100000000000000000;
        int result;
        int error = s21_from_decimal_to_int(test_one, &result);
        ck_assert_int_eq(result, -8);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00110100000000110101100010110001;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b00000000000010000000000000000000;
        int result;
        int error = s21_from_decimal_to_int(test_one, &result);
        ck_assert_int_eq(result, 8);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00110100000000110101100010110001;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000010000000000000000000;
        int result;
        int error = s21_from_decimal_to_int(test_one, &result);
        ck_assert_int_eq(result, -8);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b01010001010010110111010010001111;
        test_one.bits[MEDIUM] = 0b00000000000000000000000000010100;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b00000000000010100000000000000000;
        int result;
        int error = s21_from_decimal_to_int(test_one, &result);
        ck_assert_int_eq(result, 8);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b01010001010010110111010010001111;
        test_one.bits[MEDIUM] = 0b00000000000000000000000000010100;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000010100000000000000000;
        int result;
        int error = s21_from_decimal_to_int(test_one, &result);
        ck_assert_int_eq(result, -8);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b10010011101101011011001100111111;
        test_one.bits[MEDIUM] = 0b00000000000000110001100110100111;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b00000000000011100000000000000000;
        int result;
        int error = s21_from_decimal_to_int(test_one, &result);
        ck_assert_int_eq(result, 8);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b10010011101101011011001100111111;
        test_one.bits[MEDIUM] = 0b00000000000000110001100110100111;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000011100000000000000000;
        int result;
        int error = s21_from_decimal_to_int(test_one, &result);
        ck_assert_int_eq(result, -8);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00111011010101110011001100111111;
        test_one.bits[MEDIUM] = 0b00000000001110000110010000010011;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b00000000000100000000000000000000;
        int result;
        int error = s21_from_decimal_to_int(test_one, &result);
        ck_assert_int_eq(result, 1);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00111011010101110011001100111111;
        test_one.bits[MEDIUM] = 0b00000000001110000110010000010011;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000100000000000000000000;
        int result;
        int error = s21_from_decimal_to_int(test_one, &result);
        ck_assert_int_eq(result, -1);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00001010111110101101101100111111;
        test_one.bits[MEDIUM] = 0b00010110000001110001100000100011;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b00000000000100100000000000000000;
        int result;
        int error = s21_from_decimal_to_int(test_one, &result);
        ck_assert_int_eq(result, 1);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00001010111110101101101100111111;
        test_one.bits[MEDIUM] = 0b00010110000001110001100000100011;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000100100000000000000000;
        int result;
        int error = s21_from_decimal_to_int(test_one, &result);
        ck_assert_int_eq(result, -1);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b01011011000000101101101100111111;
        test_one.bits[MEDIUM] = 0b01111000010111001111011110000010;
        test_one.bits[WELL] = 0b00000000000000000000000000001011;
        test_one.bits[DATA] = 0b00000000000101000000000000000000;
        int result;
        int error = s21_from_decimal_to_int(test_one, &result);
        ck_assert_int_eq(result, 2);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b01011011000000101101101100111111;
        test_one.bits[MEDIUM] = 0b01111000010111001111011110000010;
        test_one.bits[WELL] = 0b00000000000000000000000000001011;
        test_one.bits[DATA] = 0b10000000000101000000000000000000;
        int result;
        int error = s21_from_decimal_to_int(test_one, &result);
        ck_assert_int_eq(result, -2);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b10110000010100100101101011101111;
        test_one.bits[MEDIUM] = 0b10110010111010001100000111110011;
        test_one.bits[WELL] = 0b00000000010111000100110110000101;
        test_one.bits[DATA] = 0b00000000000110100000000000000000;
        int result;
        int error = s21_from_decimal_to_int(test_one, &result);
        ck_assert_int_eq(result, 1);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b10110000010100100101101011101111;
        test_one.bits[MEDIUM] = 0b10110010111010001100000111110011;
        test_one.bits[WELL] = 0b00000000010111000100110110000101;
        test_one.bits[DATA] = 0b10000000000110100000000000000000;
        int result;
        int error = s21_from_decimal_to_int(test_one, &result);
        ck_assert_int_eq(result, -1);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b11100001111100111001001100101111;
        test_one.bits[MEDIUM] = 0b11100010111010111100001100110000;
        test_one.bits[WELL] = 0b00100100000011100100100000111001;
        test_one.bits[DATA] = 0b00000000111000000000000000000;
        int result;
        int error = s21_from_decimal_to_int(test_one, &result);
        ck_assert_int_eq(result, 1);
        ck_assert_int_eq(error, 0);
    }

    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b11100001111100111001001100101111;
        test_one.bits[MEDIUM] = 0b11100010111010111100001100110000;
        test_one.bits[WELL] = 0b00100100000011100100100000111001;
        test_one.bits[DATA] = 0b10000000111000000000000000000;
        int result;
        int error = s21_from_decimal_to_int(test_one, &result);
        ck_assert_int_eq(result, 1);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b01000111010010011001100111000010;
        test_one.bits[MEDIUM] = 0b11010111111110100100000111111011;
        test_one.bits[WELL] = 0b01000101011000111001000110000001;
        test_one.bits[DATA] = 0b00000000111000000000000000000;
        int result;
        int error = s21_from_decimal_to_int(test_one, &result);
        ck_assert_int_eq(result, 2);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b11100001111100111001001100101111;
        test_one.bits[MEDIUM] = 0b11100010111010111100001100110000;
        test_one.bits[WELL] = 0b00100100000011100100100000111001;
        test_one.bits[DATA] = 0b10000000111000000000000000000;
        int result;
        int error = s21_from_decimal_to_int(test_one, &result);
        ck_assert_int_eq(result, 1);
        ck_assert_int_eq(error, 0);
    }
}
END_TEST

START_TEST(s21_from_float_to_decimal_test) {
    {
        s21_decimal test_one;
        s21_decimal test_two;
        float f = 1234.00;
        s21_from_float_to_decimal(f, &test_one);
        s21_from_float_to_decimal(f, &test_two);
        float res;
        s21_from_decimal_to_float(test_one, &res);
        ck_assert_float_eq(res, 1234);
        int check = s21_is_equal(test_one, test_two);
        ck_assert_int_eq(check, 1);
    }
    {
        s21_decimal test_one;
        s21_decimal test_two;
        float f = 0.23456;
        s21_from_float_to_decimal(f, &test_one);
        s21_from_float_to_decimal(0.23456, &test_two);
        int check = s21_is_equal(test_one, test_two);
        ck_assert_int_eq(check, 1);
    }
    {
        s21_decimal test_one;
        s21_decimal test_two;
        float f = 123.123;
        s21_from_float_to_decimal(f, &test_one);
        s21_from_float_to_decimal(123.123, &test_two);
        int check = s21_is_equal(test_one, test_two);
        ck_assert_int_eq(check, 1);
    }
    {
        s21_decimal test_one;
        s21_decimal test_two;
        float f = 123;
        s21_from_float_to_decimal(f, &test_one);
        s21_from_float_to_decimal(123, &test_two);
        int check = s21_is_equal(test_one, test_two);
        ck_assert_int_eq(check, 1);
    }
    {
        float check = 82736458;
        float res = 0;
        s21_decimal test;
        s21_from_float_to_decimal(check, &test);
        s21_from_decimal_to_float(test, &res);
        ck_assert_float_eq(check, res);
    }
}
END_TEST

int TestConvertFunc() {
    Suite *suite = suite_create("s21_decimal_convert");
    TCase *getCase = tcase_create("Core");
    SRunner *runner = srunner_create(suite);
    int check = 0;

    suite_add_tcase(suite, getCase);
    tcase_add_test(getCase, s21_from_int_to_decimal_test);
    tcase_add_test(getCase, s21_from_float_to_decimal_test);
    tcase_add_test(getCase, s21_from_decimal_to_int_test);

    srunner_run_all(runner, CK_ENV);
    check = srunner_ntests_failed(runner);
    srunner_free(runner);
    return check;
}
