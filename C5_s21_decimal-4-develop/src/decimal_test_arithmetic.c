#include "decimal_test.h"

START_TEST(s21_add_test_part_rare) {
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
    s21_decimal test_res;
    test_res.bits[RARE] = 0;
    test_res.bits[MEDIUM] = 0;
    test_res.bits[WELL] = 0;
    test_res.bits[DATA] = 0;

    {
        s21_from_int_to_decimal(2, &test_one);
        s21_from_int_to_decimal(2, &test_two);
        int error = s21_add(test_one, test_two, &test_res);
        int check = 0b00000000000000000000000000000100;
        ck_assert(test_res.bits[RARE] == check);
        ck_assert(test_res.bits[DATA] == 0b00000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_from_int_to_decimal(-2, &test_one);
        s21_from_int_to_decimal(-2, &test_two);
        int error = s21_add(test_one, test_two, &test_res);
        int check = 0b00000000000000000000000000000100;
        ck_assert(test_res.bits[RARE] == check);
        ck_assert(test_res.bits[DATA] == (int)0b10000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_from_int_to_decimal(2, &test_one);
        s21_from_int_to_decimal(25, &test_two);
        int error = s21_add(test_one, test_two, &test_res);
        int check = 0b00000000000000000000000000011011;
        ck_assert(test_res.bits[RARE] == check);
        ck_assert(test_res.bits[DATA] == 0b00000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_from_int_to_decimal(-2, &test_one);
        s21_from_int_to_decimal(-25, &test_two);
        int error = s21_add(test_one, test_two, &test_res);
        int check = 0b00000000000000000000000000011011;
        ck_assert(test_res.bits[RARE] == check);
        ck_assert(test_res.bits[DATA] == (int)0b10000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_from_int_to_decimal(59, &test_one);
        s21_from_int_to_decimal(194, &test_two);
        int error = s21_add(test_one, test_two, &test_res);
        int check = 0b00000000000000000000000011111101;
        ck_assert(test_res.bits[RARE] == check);
        ck_assert(test_res.bits[DATA] == 0b00000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_from_int_to_decimal(-59, &test_one);
        s21_from_int_to_decimal(-194, &test_two);
        int error = s21_add(test_one, test_two, &test_res);
        int check = 0b00000000000000000000000011111101;
        ck_assert(test_res.bits[RARE] == check);
        ck_assert(test_res.bits[DATA] == (int)0b10000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_from_int_to_decimal(842, &test_one);
        s21_from_int_to_decimal(9520, &test_two);
        int error = s21_add(test_one, test_two, &test_res);
        int check = 0b00000000000000000010100001111010;
        ck_assert(test_res.bits[RARE] == check);
        ck_assert(test_res.bits[DATA] == 0b00000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_from_int_to_decimal(-842, &test_one);
        s21_from_int_to_decimal(-9520, &test_two);
        int error = s21_add(test_one, test_two, &test_res);
        int check = 0b00000000000000000010100001111010;
        ck_assert(test_res.bits[RARE] == check);
        ck_assert(test_res.bits[DATA] == (int)0b10000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_from_int_to_decimal(9562, &test_one);
        s21_from_int_to_decimal(72559, &test_two);
        int error = s21_add(test_one, test_two, &test_res);
        int check = 0b00000000000000010100000011001001;
        ck_assert(test_res.bits[RARE] == check);
        ck_assert(test_res.bits[DATA] == 0b00000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_from_int_to_decimal(-9562, &test_one);
        s21_from_int_to_decimal(-72559, &test_two);
        int error = s21_add(test_one, test_two, &test_res);
        int check = 0b00000000000000010100000011001001;
        ck_assert(test_res.bits[RARE] == check);
        ck_assert(test_res.bits[DATA] == (int)0b10000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_from_int_to_decimal(85624, &test_one);
        s21_from_int_to_decimal(802568, &test_two);
        int error = s21_add(test_one, test_two, &test_res);
        int check = 0b00000000000011011000110110000000;
        ck_assert(test_res.bits[RARE] == check);
        ck_assert(test_res.bits[DATA] == 0b00000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_from_int_to_decimal(-85624, &test_one);
        s21_from_int_to_decimal(-802568, &test_two);
        int error = s21_add(test_one, test_two, &test_res);
        int check = 0b00000000000011011000110110000000;
        ck_assert(test_res.bits[RARE] == check);
        ck_assert(test_res.bits[DATA] == (int)0b10000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_from_int_to_decimal(857294, &test_one);
        s21_from_int_to_decimal(9812745, &test_two);
        int error = s21_add(test_one, test_two, &test_res);
        int check = 0b00000000101000101100111111010111;
        ck_assert(test_res.bits[RARE] == check);
        ck_assert(test_res.bits[DATA] == 0b00000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_from_int_to_decimal(-857294, &test_one);
        s21_from_int_to_decimal(-9812745, &test_two);
        int error = s21_add(test_one, test_two, &test_res);
        int check = 0b00000000101000101100111111010111;
        ck_assert(test_res.bits[RARE] == check);
        ck_assert(test_res.bits[DATA] == (int)0b10000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_from_int_to_decimal(1111111, &test_one);
        s21_from_int_to_decimal(11111111, &test_two);
        int error = s21_add(test_one, test_two, &test_res);
        int check = 0b00000000101110100111111100001110;
        ck_assert(test_res.bits[RARE] == check);
        ck_assert(test_res.bits[DATA] == 0b00000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_from_int_to_decimal(-1111111, &test_one);
        s21_from_int_to_decimal(-11111111, &test_two);
        int error = s21_add(test_one, test_two, &test_res);
        int check = 0b00000000101110100111111100001110;
        ck_assert(test_res.bits[RARE] == check);
        ck_assert(test_res.bits[DATA] == (int)0b10000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_from_int_to_decimal(85637562, &test_one);
        s21_from_int_to_decimal(374562905, &test_two);
        int error = s21_add(test_one, test_two, &test_res);
        int check = 85637562 + 374562905;
        ck_assert(test_res.bits[RARE] == check);
        ck_assert(test_res.bits[DATA] == 0b00000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_from_int_to_decimal(-85637562, &test_one);
        s21_from_int_to_decimal(-374562905, &test_two);
        int error = s21_add(test_one, test_two, &test_res);
        int check = 85637562 + 374562905;
        ck_assert(test_res.bits[RARE] == check);
        ck_assert(test_res.bits[DATA] == (int)0b10000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_from_int_to_decimal(138485923, &test_one);
        s21_from_int_to_decimal(INT_MAX, &test_two);
        int error = s21_add(test_one, test_two, &test_res);
        unsigned int check_one = 0b10001000010000010010000010100010;
        ck_assert(test_res.bits[RARE] == (int)check_one);
        ck_assert(test_res.bits[DATA] == 0b00000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }

    {
        test_one.bits[RARE] = 0b00000000000000000001111111111111;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0;
        test_two.bits[RARE] = 0b00000000000000000001111111111111;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0;
        int error = s21_add(test_one, test_two, &test_res);
        ck_assert(test_res.bits[RARE] == 0b0000000000000000011111111111110);
        ck_assert(test_res.bits[MEDIUM] == 0);
        ck_assert(test_res.bits[WELL] == 0);
        ck_assert(test_res.bits[DATA] == 0);
        ck_assert_int_eq(error, 0);
    }
    {
        test_one.bits[RARE] = 0b00000000000000000001111111111111;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        test_two.bits[RARE] = 0b00000000000000000001111111111111;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b10000000000000000000000000000000;
        int error = s21_add(test_one, test_two, &test_res);
        ck_assert(test_res.bits[RARE] == 0b0000000000000000011111111111110);
        ck_assert(test_res.bits[MEDIUM] == 0);
        ck_assert(test_res.bits[WELL] == 0);
        ck_assert(test_res.bits[DATA] == (int)0b10000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
}
END_TEST

START_TEST(s21_add_test_part_medium) {
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0;
        test_one.bits[MEDIUM] = 1;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0;
        s21_decimal test_two;
        test_two.bits[RARE] = 0;
        test_two.bits[MEDIUM] = 1;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0;
        s21_decimal test_res;
        int error = s21_add(test_one, test_two, &test_res);
        ck_assert_int_eq(test_res.bits[RARE], 0b00000000000000000000000000000000);
        ck_assert_int_eq(test_res.bits[MEDIUM], 0b00000000000000000000000000000010);
        ck_assert_int_eq(test_res.bits[WELL], 0b00000000000000000000000000000000);
        ck_assert_int_eq(test_res.bits[DATA], 0b00000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0;
        test_one.bits[MEDIUM] = 1;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0;
        test_two.bits[MEDIUM] = 1;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_res;
        int error = s21_add(test_one, test_two, &test_res);
        ck_assert(test_res.bits[RARE] == 0b00000000000000000000000000000000);
        ck_assert(test_res.bits[MEDIUM] == 0b00000000000000000000000000000010);
        ck_assert(test_res.bits[WELL] == 0b00000000000000000000000000000000);
        ck_assert(test_res.bits[DATA] == (int)0b10000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b01001110100010010111100000010100;
        test_one.bits[MEDIUM] = 0b00000000000000000000000000001100;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b10101111000110110010000110100011;
        test_two.bits[MEDIUM] = 0b00000000000000000000000010000111;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0;
        s21_decimal test_res;
        int error = s21_add(test_one, test_two, &test_res);
        ck_assert(test_res.bits[RARE] == (int)0b11111101101001001001100110110111);
        ck_assert(test_res.bits[MEDIUM] == 0b00000000000000000000000010010011);
        ck_assert(test_res.bits[WELL] == 0b00000000000000000000000000000000);
        ck_assert(test_res.bits[DATA] == 0b00000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b01001110100010010111100000010100;
        test_one.bits[MEDIUM] = 0b00000000000000000000000000001100;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b10101111000110110010000110100011;
        test_two.bits[MEDIUM] = 0b00000000000000000000000010000111;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_res;
        int error = s21_add(test_one, test_two, &test_res);
        ck_assert(test_res.bits[RARE] == (int)0b11111101101001001001100110110111);
        ck_assert(test_res.bits[MEDIUM] == 0b00000000000000000000000010010011);
        ck_assert(test_res.bits[WELL] == 0b00000000000000000000000000000000);
        ck_assert(test_res.bits[DATA] == (int)0b10000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b10000010110010000100110110101010;
        test_one.bits[MEDIUM] = 0b00000000000000000000000010000111;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b10100110100011100000111111010000;
        test_two.bits[MEDIUM] = 0b100101001110000;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0;
        s21_decimal test_res;
        int error = s21_add(test_one, test_two, &test_res);
        ck_assert(test_res.bits[RARE] == 0b00101001010101100101110101111010);
        ck_assert(test_res.bits[MEDIUM] == 0b00000000000000000100101011111000);
        ck_assert(test_res.bits[WELL] == 0);
        ck_assert(test_res.bits[DATA] == 0);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b10000010110010000100110110101010;
        test_one.bits[MEDIUM] = 0b00000000000000000000000010000111;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b10100110100011100000111111010000;
        test_two.bits[MEDIUM] = 0b100101001110000;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_res;
        int error = s21_add(test_one, test_two, &test_res);
        ck_assert(test_res.bits[RARE] == 0b00101001010101100101110101111010);
        ck_assert(test_res.bits[MEDIUM] == 0b00000000000000000100101011111000);
        ck_assert(test_res.bits[WELL] == 0);
        ck_assert(test_res.bits[DATA] == (int)0b10000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b10100100110001100111111111111111;
        test_one.bits[MEDIUM] = 0b00000000000000111000110101111110;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b01101111110000010000000000000000;
        test_two.bits[MEDIUM] = 0b00000000001000111000011011110010;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0;
        s21_decimal test_res;
        int error = s21_add(test_one, test_two, &test_res);
        ck_assert(test_res.bits[RARE] == 0b00010100100001110111111111111111);
        ck_assert(test_res.bits[MEDIUM] == 0b00000000001001110001010001110001);
        ck_assert(test_res.bits[WELL] == 0);
        ck_assert(test_res.bits[DATA] == 0);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b10100100110001100111111111111111;
        test_one.bits[MEDIUM] = 0b00000000000000111000110101111110;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b01101111110000010000000000000000;
        test_two.bits[MEDIUM] = 0b00000000001000111000011011110010;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_res;
        int error = s21_add(test_one, test_two, &test_res);
        ck_assert(test_res.bits[RARE] == 0b00010100100001110111111111111111);
        ck_assert(test_res.bits[MEDIUM] == 0b00000000001001110001010001110001);
        ck_assert(test_res.bits[WELL] == 0);
        ck_assert(test_res.bits[DATA] == (int)0b10000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b10111110110100010100110011000100;
        test_one.bits[MEDIUM] = 0b00000000000000011010110100111001;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b01001110001000100000101000000100;
        test_two.bits[MEDIUM] = 0b00000000000000011011110111101001;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0;
        s21_decimal test_res;
        int error = s21_add(test_one, test_two, &test_res);
        ck_assert(test_res.bits[RARE] == 0b00001100111100110101011011001000);
        ck_assert(test_res.bits[MEDIUM] == 0b00000000000000110110101100100011);
        ck_assert(test_res.bits[WELL] == 0);
        ck_assert(test_res.bits[DATA] == 0);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b10111110110100010100110011000100;
        test_one.bits[MEDIUM] = 0b00000000000000011010110100111001;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b01001110001000100000101000000100;
        test_two.bits[MEDIUM] = 0b00000000000000011011110111101001;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_res;
        int error = s21_add(test_one, test_two, &test_res);
        ck_assert(test_res.bits[RARE] == 0b00001100111100110101011011001000);
        ck_assert(test_res.bits[MEDIUM] == 0b00000000000000110110101100100011);
        ck_assert(test_res.bits[WELL] == 0);
        ck_assert(test_res.bits[DATA] == (int)0b10000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b10011101101100001001111011101001;
        test_one.bits[MEDIUM] = 0b00000000000101000101101011101100;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b10111111111000101010111010011000;
        test_two.bits[MEDIUM] = 0b00000011100000001000111000011010;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0;
        s21_decimal test_res;
        int error = s21_add(test_one, test_two, &test_res);
        ck_assert(test_res.bits[RARE] == 0b01011101100100110100110110000001);
        ck_assert(test_res.bits[MEDIUM] == 0b00000011100101001110100100000111);
        ck_assert(test_res.bits[WELL] == 0);
        ck_assert(test_res.bits[DATA] == 0);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b10011101101100001001111011101001;
        test_one.bits[MEDIUM] = 0b00000000000101000101101011101100;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b10111111111000101010111010011000;
        test_two.bits[MEDIUM] = 0b00000011100000001000111000011010;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_res;
        int error = s21_add(test_one, test_two, &test_res);
        ck_assert(test_res.bits[RARE] == 0b01011101100100110100110110000001);
        ck_assert(test_res.bits[MEDIUM] == 0b00000011100101001110100100000111);
        ck_assert(test_res.bits[WELL] == 0);
        ck_assert(test_res.bits[DATA] == (int)0b10000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00010011111101011100010111101000;
        test_one.bits[MEDIUM] = 0b10000000110110011011101101011100;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b00100010010110110101101000101001;
        test_two.bits[MEDIUM] = 0b00001110011000001001111000000100;
        test_two.bits[WELL] = 0b00000000000000000000000000000001;
        test_two.bits[DATA] = 0;
        s21_decimal test_res;
        int error = s21_add(test_one, test_two, &test_res);
        ck_assert(test_res.bits[RARE] == (int)0b00110110010100010010000000010001);
        ck_assert(test_res.bits[MEDIUM] == (int)0b10001111001110100101100101100000);
        ck_assert(test_res.bits[WELL] == 0b00000000000000000000000000000001);
        ck_assert(test_res.bits[DATA] == 0);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00010011111101011100010111101000;
        test_one.bits[MEDIUM] = 0b10000000110110011011101101011100;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b00100010010110110101101000101001;
        test_two.bits[MEDIUM] = 0b00001110011000001001111000000100;
        test_two.bits[WELL] = 0b00000000000000000000000000000001;
        test_two.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_res;
        int error = s21_add(test_one, test_two, &test_res);
        ck_assert(test_res.bits[RARE] == (int)0b00110110010100010010000000010001);
        ck_assert(test_res.bits[MEDIUM] == (int)0b10001111001110100101100101100000);
        ck_assert(test_res.bits[WELL] == 0b00000000000000000000000000000001);
        ck_assert(test_res.bits[DATA] == (int)0b10000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b10011011010001110001111011001000;
        test_one.bits[MEDIUM] = 0b00001111101101100111010011110010;
        test_one.bits[WELL] = 0b00000000000000000000001000000010;
        test_one.bits[DATA] = 0;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b01011111001110010101101100110010;
        test_two.bits[MEDIUM] = 0b00011001011101000010111011001101;
        test_two.bits[WELL] = 0b00000000000000000000110001010111;
        test_two.bits[DATA] = 0;
        s21_decimal test_res;
        int error = s21_add(test_one, test_two, &test_res);
        ck_assert(test_res.bits[RARE] == (int)0b11111010100000000111100111111010);
        ck_assert(test_res.bits[MEDIUM] == 0b00101001001010101010001110111111);
        ck_assert(test_res.bits[WELL] == 0b00000000000000000000111001011001);
        ck_assert(test_res.bits[DATA] == 0);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b10011011010001110001111011001000;
        test_one.bits[MEDIUM] = 0b00001111101101100111010011110010;
        test_one.bits[WELL] = 0b00000000000000000000001000000010;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b01011111001110010101101100110010;
        test_two.bits[MEDIUM] = 0b00011001011101000010111011001101;
        test_two.bits[WELL] = 0b00000000000000000000110001010111;
        test_two.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_res;
        int error = s21_add(test_one, test_two, &test_res);
        ck_assert(test_res.bits[RARE] == (int)0b11111010100000000111100111111010);
        ck_assert(test_res.bits[MEDIUM] == 0b00101001001010101010001110111111);
        ck_assert(test_res.bits[WELL] == 0b00000000000000000000111001011001);
        ck_assert(test_res.bits[DATA] == (int)0b10000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b01101011011011111110010001111101;
        test_one.bits[MEDIUM] = 0b00011101000110110100101110000111;
        test_one.bits[WELL] = 0b00000000000001001101001001110001;
        test_one.bits[DATA] = 0;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b01101011011011111110010001111101;
        test_two.bits[MEDIUM] = 0b00011101000110110100101110000111;
        test_two.bits[WELL] = 0b00000000000001001101001001110001;
        test_two.bits[DATA] = 0;
        s21_decimal test_res;
        int error = s21_add(test_one, test_two, &test_res);
        ck_assert(test_res.bits[RARE] == (int)0b11010110110111111100100011111010);
        ck_assert(test_res.bits[MEDIUM] == 0b00111010001101101001011100001110);
        ck_assert(test_res.bits[WELL] == 0b00000000000010011010010011100010);
        ck_assert(test_res.bits[DATA] == 0);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b01101011011011111110010001111101;
        test_one.bits[MEDIUM] = 0b00011101000110110100101110000111;
        test_one.bits[WELL] = 0b00000000000001001101001001110001;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b01101011011011111110010001111101;
        test_two.bits[MEDIUM] = 0b00011101000110110100101110000111;
        test_two.bits[WELL] = 0b00000000000001001101001001110001;
        test_two.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_res;
        int error = s21_add(test_one, test_two, &test_res);
        ck_assert(test_res.bits[RARE] == (int)0b11010110110111111100100011111010);
        ck_assert(test_res.bits[MEDIUM] == 0b00111010001101101001011100001110);
        ck_assert(test_res.bits[WELL] == 0b00000000000010011010010011100010);
        ck_assert(test_res.bits[DATA] == (int)0b10000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00100110110011001111010001110110;
        test_one.bits[MEDIUM] = 0b10111110001110010101101001111010;
        test_one.bits[WELL] = 0b00000000001111101011100100010001;
        test_one.bits[DATA] = 0;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b01111011010100111001110001101101;
        test_two.bits[MEDIUM] = 0b10011011101111111110011110100010;
        test_two.bits[WELL] = 0b00000010111000000110111100111111;
        test_two.bits[DATA] = 0;
        s21_decimal test_res;
        int error = s21_add(test_one, test_two, &test_res);
        ck_assert(test_res.bits[RARE] == (int)0b10100010001000001001000011100011);
        ck_assert(test_res.bits[MEDIUM] == 0b01011001111110010100001000011100);
        ck_assert(test_res.bits[WELL] == 0b11000111110010100001010001);
        ck_assert(test_res.bits[DATA] == 0);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00100110110011001111010001110110;
        test_one.bits[MEDIUM] = 0b10111110001110010101101001111010;
        test_one.bits[WELL] = 0b00000000001111101011100100010001;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b01111011010100111001110001101101;
        test_two.bits[MEDIUM] = 0b10011011101111111110011110100010;
        test_two.bits[WELL] = 0b00000010111000000110111100111111;
        test_two.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_res;
        int error = s21_add(test_one, test_two, &test_res);
        ck_assert(test_res.bits[RARE] == (int)0b10100010001000001001000011100011);
        ck_assert(test_res.bits[MEDIUM] == 0b01011001111110010100001000011100);
        ck_assert(test_res.bits[WELL] == 0b11000111110010100001010001);
        ck_assert(test_res.bits[DATA] == (int)0b10000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00010101011100111101110010110001;
        test_one.bits[MEDIUM] = 0b01001011010110000011100111111011;
        test_one.bits[WELL] = 0b00010010000101011001011000111110;
        test_one.bits[DATA] = 0;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b11001110101000101000100100111111;
        test_two.bits[MEDIUM] = 0b10011110100111000110010010001100;
        test_two.bits[WELL] = 0b00011001010110111111001100100011;
        test_two.bits[DATA] = 0;
        s21_decimal test_res;
        int error = s21_add(test_one, test_two, &test_res);
        ck_assert(test_res.bits[RARE] == (int)0b11100100000101100110010111110000);
        ck_assert(test_res.bits[MEDIUM] == (int)0b11101001111101001001111010000111);
        ck_assert(test_res.bits[WELL] == 0b00101011011100011000100101100001);
        ck_assert(test_res.bits[DATA] == 0);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00010101011100111101110010110001;
        test_one.bits[MEDIUM] = 0b01001011010110000011100111111011;
        test_one.bits[WELL] = 0b00010010000101011001011000111110;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b11001110101000101000100100111111;
        test_two.bits[MEDIUM] = 0b10011110100111000110010010001100;
        test_two.bits[WELL] = 0b00011001010110111111001100100011;
        test_two.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_res;
        int error = s21_add(test_one, test_two, &test_res);
        ck_assert(test_res.bits[RARE] == (int)0b11100100000101100110010111110000);
        ck_assert(test_res.bits[MEDIUM] == (int)0b11101001111101001001111010000111);
        ck_assert(test_res.bits[WELL] == 0b00101011011100011000100101100001);
        ck_assert(test_res.bits[DATA] == (int)0b10000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b01100111000111000111000111000111;
        test_one.bits[MEDIUM] = 0b01000101000011001010110101001111;
        test_one.bits[WELL] = 0b00100011111001101110010101001100;
        test_one.bits[DATA] = 0;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b01100111000111000111000111000111;
        test_two.bits[MEDIUM] = 0b01000101000011001010110101001111;
        test_two.bits[WELL] = 0b00100011111001101110010101001100;
        test_two.bits[DATA] = 0;
        s21_decimal test_res;
        int error = s21_add(test_one, test_two, &test_res);
        ck_assert(test_res.bits[RARE] == (int)0b11001110001110001110001110001110);
        ck_assert(test_res.bits[MEDIUM] == (int)0b10001010000110010101101010011110);
        ck_assert(test_res.bits[WELL] == 0b1000111110011011100101010011000);
        ck_assert(test_res.bits[DATA] == 0);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b01100111000111000111000111000111;
        test_one.bits[MEDIUM] = 0b01000101000011001010110101001111;
        test_one.bits[WELL] = 0b00100011111001101110010101001100;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b01100111000111000111000111000111;
        test_two.bits[MEDIUM] = 0b01000101000011001010110101001111;
        test_two.bits[WELL] = 0b00100011111001101110010101001100;
        test_two.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_res;
        int error = s21_add(test_one, test_two, &test_res);
        ck_assert(test_res.bits[RARE] == (int)0b11001110001110001110001110001110);
        ck_assert(test_res.bits[MEDIUM] == (int)0b10001010000110010101101010011110);
        ck_assert(test_res.bits[WELL] == 0b1000111110011011100101010011000);
        ck_assert(test_res.bits[DATA] == (int)0b10000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b01011101110011110011000111000111;
        test_one.bits[MEDIUM] = 0b00111110001001010000001001001100;
        test_one.bits[WELL] = 0b00100000010011111100111001011110;
        test_one.bits[DATA] = 0;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b01100111000111000111000111000111;
        test_two.bits[MEDIUM] = 0b01000101000011001010110101001111;
        test_two.bits[WELL] = 0b100011111001101110010101001100;
        test_two.bits[DATA] = 0;
        s21_decimal test_res;
        int error = s21_add(test_one, test_two, &test_res);
        ck_assert(test_res.bits[RARE] == (int)0b11000100111010111010001110001110);
        ck_assert(test_res.bits[MEDIUM] == (int)0b10000011001100011010111110011011);
        ck_assert(test_res.bits[WELL] == 0b01000100001101101011001110101010);
        ck_assert(test_res.bits[DATA] == 0);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b01011101110011110011000111000111;
        test_one.bits[MEDIUM] = 0b00111110001001010000001001001100;
        test_one.bits[WELL] = 0b00100000010011111100111001011110;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b01100111000111000111000111000111;
        test_two.bits[MEDIUM] = 0b01000101000011001010110101001111;
        test_two.bits[WELL] = 0b100011111001101110010101001100;
        test_two.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_res;
        int error = s21_add(test_one, test_two, &test_res);
        ck_assert(test_res.bits[RARE] == (int)0b11000100111010111010001110001110);
        ck_assert(test_res.bits[MEDIUM] == (int)0b10000011001100011010111110011011);
        ck_assert(test_res.bits[WELL] == 0b01000100001101101011001110101010);
        ck_assert(test_res.bits[DATA] == (int)0b10000000000000000000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b10111011100111100110001110001111;
        test_one.bits[MEDIUM] = 0b01111100010010100000010010011000;
        test_one.bits[WELL] = 0b10000001001111111001110010111100;
        test_one.bits[DATA] = 0;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b01100111000111000111000111000111;
        test_two.bits[MEDIUM] = 0b01000101000011001010110101001111;
        test_two.bits[WELL] = 0b00100011111001101110010101001100;
        test_two.bits[DATA] = 0;
        s21_decimal test_res;
        int error = s21_add(test_one, test_two, &test_res);
        ck_assert_int_eq(error, 0);
        ck_assert(test_res.bits[RARE] == 0b00100010101110101101010101010110);
        ck_assert(test_res.bits[MEDIUM] == (int)0b11000001010101101011000111101000);
        ck_assert(test_res.bits[WELL] == (int)0b10100101001001101000001000001000);
        ck_assert(test_res.bits[DATA] == 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b10111011100111100110001110001111;
        test_one.bits[MEDIUM] = 0b01111100010010100000010010011000;
        test_one.bits[WELL] = 0b10000001001111111001110010111100;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b01100111000111000111000111000111;
        test_two.bits[MEDIUM] = 0b01000101000011001010110101001111;
        test_two.bits[WELL] = 0b00100011111001101110010101001100;
        test_two.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_res;
        int error = s21_add(test_one, test_two, &test_res);
        ck_assert_int_eq(error, 0);
        ck_assert(test_res.bits[RARE] == 0b00100010101110101101010101010110);
        ck_assert(test_res.bits[MEDIUM] == (int)0b11000001010101101011000111101000);
        ck_assert(test_res.bits[WELL] == (int)0b10100101001001101000001000001000);
        ck_assert(test_res.bits[DATA] == (int)0b10000000000000000000000000000000);
    }
}
END_TEST

START_TEST(s21_add_test_error) {
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00100110110011001111010001110110;
        test_one.bits[MEDIUM] = 0b10111110001110010101101001111010;
        test_one.bits[WELL] = 0b00000000001111101011100100010001;
        test_one.bits[DATA] = 0;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b01111011010100111001110001101101;
        test_two.bits[MEDIUM] = 0b10011011101111111110011110100010;
        test_two.bits[WELL] = 0b00000010111000000110111100111111;
        test_two.bits[DATA] = 0;
        int error = s21_add(test_one, test_two, NULL);
        ck_assert_int_eq(error, 1);
    }
    {
        s21_decimal test_one_error;
        test_one_error.bits[RARE] = 0;
        test_one_error.bits[MEDIUM] = 0;
        test_one_error.bits[WELL] = 0b11111111111111111111111111111111;
        test_one_error.bits[DATA] = 0;
        s21_decimal test_two_error;
        test_two_error.bits[RARE] = 0;
        test_two_error.bits[MEDIUM] = 0;
        test_two_error.bits[WELL] = 0b11111111111111111111111111111111;
        test_two_error.bits[DATA] = 0;
        s21_decimal test_res_error;
        int error = s21_add(test_one_error, test_two_error, &test_res_error);
        ck_assert_int_eq(error, 1);
    }
}
END_TEST

START_TEST(s21_add_test_fractiomal) {
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00000000000000000000000000011000;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b00000000000000000000100101100000;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b00000000000000100000000000000000;
        s21_decimal test_res;
        int error = s21_add(test_one, test_two, &test_res);
        ck_assert_int_eq(error, 0);
        ck_assert(test_res.bits[RARE] == 0b00000000000000000001001011000000);
        ck_assert(test_res.bits[MEDIUM] == 0);
        ck_assert(test_res.bits[WELL] == 0);
        ck_assert(test_res.bits[DATA] == 0b00000000000000100000000000000000);
    }
    {
        // 467 - ст 0
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00000000000000000000000111010011;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0;
        // 892373295 - ст 5
        s21_decimal test_two;
        test_two.bits[RARE] = 0b00110101001100001000100100101111;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b00000000000001010000000000000000;
        s21_decimal test_res;
        int error = s21_add(test_one, test_two, &test_res);
        ck_assert_int_eq(error, 0);
        ck_assert_int_eq(test_res.bits[RARE], 0b00110111111110010001111100001111);
        ck_assert_int_eq(test_res.bits[MEDIUM], 0);
        ck_assert_int_eq(test_res.bits[WELL], 0);
        ck_assert_int_eq(test_res.bits[DATA], 0b00000000000001010000000000000000);
    }
    {
        // 467 - ст 0
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00000000000000000000000111010011;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0;
        // 892373295 - ст 5
        s21_decimal test_two;
        test_two.bits[RARE] = 0b00110101001100001000100100101111;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b00000000000001010000000000000000;
        s21_decimal test_res;
        int error = s21_add(test_two, test_one, &test_res);
        ck_assert_int_eq(error, 0);
        ck_assert_int_eq(test_res.bits[RARE], 0b00110111111110010001111100001111);
        ck_assert_int_eq(test_res.bits[MEDIUM], 0);
        ck_assert_int_eq(test_res.bits[WELL], 0);
        ck_assert_int_eq(test_res.bits[DATA], 0b00000000000001010000000000000000);
    }
    {
        // 23432532324532 - ст 4
        // 101010100111111001111110000111111000010110100
        s21_decimal test_one;
        test_one.bits[RARE] = 0b11001111110000111111000010110100;
        test_one.bits[MEDIUM] = 0b00000000000000000001010101001111;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b00000000000001000000000000000000;
        // 800932473345 - ст 5
        // 1011101001111011010010111010101000000001
        s21_decimal test_two;
        test_two.bits[RARE] = 0b01111011010010111010101000000001;
        test_two.bits[MEDIUM] = 0b00000000000000000000000010111010;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b00000000000001010000000000000000;
        s21_decimal test_res;
        int error = s21_add(test_one, test_two, &test_res);
        ck_assert_int_eq(error, 0);
        ck_assert_int_eq(test_res.bits[RARE], (int)0b10011000111100110001000100001001);
        ck_assert_int_eq(test_res.bits[MEDIUM], 0b00000000000000001101010111011000);
        ck_assert_int_eq(test_res.bits[WELL], 0);
        ck_assert_int_eq(test_res.bits[DATA], 0b00000000000001010000000000000000);
    }
    {
        // 6478236478293462789365278 - 14
        s21_decimal test_one;
        test_one.bits[RARE] = 0b10010000111000111001111000011110;
        test_one.bits[MEDIUM] = 0b11100111001101101111000000000100;
        test_one.bits[WELL] = 0b00000000000001010101101111010001;
        test_one.bits[DATA] = 0b00000000000011100000000000000000;
        // 325343 - 5
        s21_decimal test_two;
        test_two.bits[RARE] = 0b00000000000001001111011011011111;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b00000000000001010000000000000000;
        s21_decimal test_res;
        int error = s21_add(test_one, test_two, &test_res);
        ck_assert_int_eq(error, 0);
        ck_assert_int_eq((unsigned int)test_res.bits[RARE], (unsigned int)0b01100010110101011001010000011110);
        ck_assert_int_eq((unsigned int)test_res.bits[MEDIUM],
                         (unsigned int)0b11100111001110000001011111101010);
        ck_assert_int_eq(test_res.bits[WELL], 0b00000000000001010101101111010001);
        ck_assert_int_eq((unsigned int)test_res.bits[DATA], (unsigned int)0b00000000000011100000000000000000);
    }
}
END_TEST

START_TEST(s21_mul_test) {
    {
        s21_decimal test_value_1;
        s21_decimal test_value_2;
        s21_decimal result_dec;
        int result_int;
        s21_from_int_to_decimal(-5996, &test_value_1);
        test_value_1.bits[RARE] = 0b00000000000000000001011101101100;
        test_value_1.bits[MEDIUM] = 0;
        test_value_1.bits[WELL] = 0;
        test_value_1.bits[DATA] = 0b10000000000000000000000000000000;
        s21_from_int_to_decimal(1004, &test_value_2);
        test_value_2.bits[RARE] = 0b00000000000000000000001111101100;
        test_value_2.bits[MEDIUM] = 0;
        test_value_2.bits[WELL] = 0;
        test_value_2.bits[DATA] = 0b10000000000000000000000000000000;
        int error = s21_mul(test_value_1, test_value_2, &result_dec);
        result_dec.bits[RARE] = 0b00000000010110111101101110010000;
        result_dec.bits[MEDIUM] = 0;
        result_dec.bits[WELL] = 0;
        result_dec.bits[DATA] = 0b10000000000000000000000000000000;
        s21_from_decimal_to_int(result_dec, &result_int);
        ck_assert_int_eq(result_int, (-5996 * 1004));
        ck_assert_int_eq(error, 0);
    }

    {
        s21_decimal test_value_1;
        s21_decimal test_value_2;
        s21_decimal result_dec;
        int result_int;
        s21_from_int_to_decimal(7765, &test_value_1);
        test_value_1.bits[RARE] = 0b00000000000000000001111001010101;
        test_value_1.bits[MEDIUM] = 0;
        test_value_1.bits[WELL] = 0;
        test_value_1.bits[DATA] = 0b00000000000000000000000000000000;
        s21_from_int_to_decimal(1234, &test_value_2);
        test_value_2.bits[RARE] = 0b00000000000000000000010011010010;
        test_value_2.bits[MEDIUM] = 0;
        test_value_2.bits[WELL] = 0;
        test_value_2.bits[DATA] = 0b00000000000000000000000000000000;
        int error = s21_mul(test_value_1, test_value_2, &result_dec);
        result_dec.bits[RARE] = 0b00000000100100100011010110111010;
        result_dec.bits[MEDIUM] = 0;
        result_dec.bits[WELL] = 0;
        result_dec.bits[DATA] = 0b00000000000000000000000000000000;
        s21_from_decimal_to_int(result_dec, &result_int);
        ck_assert_int_eq(result_int, (7765 * 1234));
        ck_assert_int_eq(error, 0);
    }

    {
        s21_decimal test_value_1;
        s21_decimal test_value_2;
        s21_decimal result_dec;
        int result_int;
        s21_from_int_to_decimal(-7765, &test_value_1);
        test_value_1.bits[RARE] = 0b00000000000000000001111001010101;
        test_value_1.bits[MEDIUM] = 0;
        test_value_1.bits[WELL] = 0;
        test_value_1.bits[DATA] = 0b10000000000000000000000000000000;
        s21_from_int_to_decimal(-1234, &test_value_2);
        test_value_2.bits[RARE] = 0b00000000000000000000010011010010;
        test_value_2.bits[MEDIUM] = 0;
        test_value_2.bits[WELL] = 0;
        test_value_2.bits[DATA] = 0b10000000000000000000000000000000;
        int error = s21_mul(test_value_1, test_value_2, &result_dec);
        s21_from_decimal_to_int(result_dec, &result_int);
        result_dec.bits[RARE] = 0b00000000100100100011010110111010;
        result_dec.bits[MEDIUM] = 0;
        result_dec.bits[WELL] = 0;
        result_dec.bits[DATA] = 0b00000000000000000000000000000000;
        ck_assert_int_eq(result_int, (-7765 * -1234));
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_value_1;
        CleanDecimal(&test_value_1);
        s21_decimal test_value_2;
        CleanDecimal(&test_value_2);
        int error = s21_mul(test_value_1, test_value_2, NULL);
        ck_assert_int_eq(error, 1);
    }
    {
        s21_decimal test_value_1;
        s21_decimal test_value_2;
        s21_decimal result_dec;
        float result_int;
        s21_from_int_to_decimal(INT_MAX, &test_value_1);
        test_value_1.bits[RARE] = 0b01111111111111111111111111111111;
        test_value_1.bits[MEDIUM] = 0;
        test_value_1.bits[WELL] = 0;
        test_value_1.bits[DATA] = 0b00000000000000000000000000000000;
        s21_from_int_to_decimal(INT_MAX, &test_value_2);
        test_value_2.bits[RARE] = 0b01111111111111111111111111111111;
        test_value_2.bits[MEDIUM] = 0;
        test_value_2.bits[WELL] = 0;
        test_value_2.bits[DATA] = 0b00000000000000000000000000000000;
        int error = s21_mul(test_value_1, test_value_2, &result_dec);
        result_dec.bits[RARE] = 0b00000000000000000000000000000001;
        result_dec.bits[MEDIUM] = 0b00111111111111111111111111111111;
        result_dec.bits[WELL] = 0;
        result_dec.bits[DATA] = 0b00000000000000000000000000000000;
        s21_from_decimal_to_float(result_dec, &result_int);
        ck_assert_float_eq(result_int, ((float)INT_MAX * (float)INT_MAX));
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_value_1;
        s21_decimal test_value_2;
        s21_decimal result_dec;
        float result_int;
        s21_from_int_to_decimal(INT_MIN, &test_value_1);
        test_value_1.bits[RARE] = 0b10000000000000000000000000000000;
        test_value_1.bits[MEDIUM] = 0;
        test_value_1.bits[WELL] = 0;
        test_value_1.bits[DATA] = 0b10000000000000000000000000000000;
        s21_from_int_to_decimal(INT_MIN, &test_value_2);
        test_value_2.bits[RARE] = 0b10000000000000000000000000000000;
        test_value_2.bits[MEDIUM] = 0;
        test_value_2.bits[WELL] = 0;
        test_value_2.bits[DATA] = 0b00000000000000000000000000000000;
        int error = s21_mul(test_value_1, test_value_2, &result_dec);
        result_dec.bits[RARE] = 0b00000000000000000000000000000000;
        result_dec.bits[MEDIUM] = 0b01000000000000000000000000000000;
        result_dec.bits[WELL] = 0;
        result_dec.bits[DATA] = 0b00000000000000000000000000000000;
        s21_from_decimal_to_float(result_dec, &result_int);
        ck_assert_float_eq(result_int, ((float)INT_MIN * (float)INT_MIN));
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_value_1;
        s21_decimal test_value_2;
        s21_decimal result_dec;
        float result_int;
        s21_from_int_to_decimal(INT_MIN, &test_value_1);
        test_value_1.bits[RARE] = 0b10000000000000000000000000000000;
        test_value_1.bits[MEDIUM] = 0;
        test_value_1.bits[WELL] = 0;
        test_value_1.bits[DATA] = 0b10000000000000000000000000000000;
        s21_from_int_to_decimal(INT_MAX, &test_value_2);
        test_value_2.bits[RARE] = 0b01111111111111111111111111111111;
        test_value_2.bits[MEDIUM] = 0;
        test_value_2.bits[WELL] = 0;
        test_value_2.bits[DATA] = 0b00000000000000000000000000000000;
        int error = s21_mul(test_value_1, test_value_2, &result_dec);
        result_dec.bits[RARE] = 0b10000000000000000000000000000000;
        result_dec.bits[MEDIUM] = 0b00111111111111111111111111111111;
        result_dec.bits[WELL] = 0;
        result_dec.bits[DATA] = 0b10000000000000000000000000000000;
        s21_from_decimal_to_float(result_dec, &result_int);
        ck_assert_float_eq(result_int, ((float)INT_MIN * (float)INT_MAX));
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_value_1;
        s21_decimal test_value_2;
        s21_decimal result_dec;
        float result_int;
        s21_from_int_to_decimal(INT_MIN, &test_value_1);
        test_value_1.bits[RARE] = 0b10000000000000000000000000000000;
        test_value_1.bits[MEDIUM] = 0;
        test_value_1.bits[WELL] = 0;
        test_value_1.bits[DATA] = 0b10000000000000000000000000000000;
        s21_from_int_to_decimal(INT_MAX, &test_value_2);
        test_value_2.bits[RARE] = 0b01111111111111111111111111111111;
        test_value_2.bits[MEDIUM] = 0;
        test_value_2.bits[WELL] = 0;
        test_value_2.bits[DATA] = 0b00000000000000000000000000000000;
        int error = s21_mul(test_value_2, test_value_1, &result_dec);
        result_dec.bits[RARE] = 0b10000000000000000000000000000000;
        result_dec.bits[MEDIUM] = 0b00111111111111111111111111111111;
        result_dec.bits[WELL] = 0;
        result_dec.bits[DATA] = 0b10000000000000000000000000000000;
        s21_from_decimal_to_float(result_dec, &result_int);
        ck_assert_float_eq(result_int, ((float)INT_MIN * (float)INT_MAX));
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_value_1;
        s21_decimal test_value_2;
        s21_decimal result_dec;
        float result_int;
        s21_from_int_to_decimal(0, &test_value_1);
        test_value_1.bits[RARE] = 0;
        test_value_1.bits[MEDIUM] = 0;
        test_value_1.bits[WELL] = 0;
        test_value_1.bits[DATA] = 0;
        s21_from_int_to_decimal(0, &test_value_2);
        test_value_2.bits[RARE] = 0;
        test_value_2.bits[MEDIUM] = 0;
        test_value_2.bits[WELL] = 0;
        test_value_2.bits[DATA] = 0;
        int error = s21_mul(test_value_2, test_value_1, &result_dec);
        result_dec.bits[RARE] = 0;
        result_dec.bits[MEDIUM] = 0;
        result_dec.bits[WELL] = 0;
        result_dec.bits[DATA] = 0;
        s21_from_decimal_to_float(result_dec, &result_int);
        ck_assert_float_eq(result_int, (0 * 0));
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_value_1;
        s21_decimal test_value_2;
        s21_decimal result_dec;
        float result_int;
        s21_from_int_to_decimal(-0, &test_value_1);
        test_value_1.bits[RARE] = 0;
        test_value_1.bits[MEDIUM] = 0;
        test_value_1.bits[WELL] = 0;
        test_value_1.bits[DATA] = 0b10000000000000000000000000000000;
        s21_from_int_to_decimal(+0, &test_value_2);
        test_value_2.bits[RARE] = 0;
        test_value_2.bits[MEDIUM] = 0;
        test_value_2.bits[WELL] = 0;
        test_value_2.bits[DATA] = 0;
        int error = s21_mul(test_value_2, test_value_1, &result_dec);
        result_dec.bits[RARE] = 0;
        result_dec.bits[MEDIUM] = 0;
        result_dec.bits[WELL] = 0;
        result_dec.bits[DATA] = 0b10000000000000000000000000000000;
        s21_from_decimal_to_float(result_dec, &result_int);
        ck_assert_float_eq(result_int, (-0 * +0));
        ck_assert_int_eq(error, 0);
    }
}
END_TEST

START_TEST(s21_sub_test) {
    {
        s21_decimal test_one;
        s21_from_int_to_decimal(54, &test_one);
        s21_decimal test_two;
        s21_from_int_to_decimal(4, &test_two);
        s21_decimal result_dec;
        s21_sub(test_one, test_two, &result_dec);
        ck_assert_int_eq(result_dec.bits[RARE], 0b0000000000000000000000000110010);
        ck_assert_int_eq(result_dec.bits[MEDIUM], 0);
        ck_assert_int_eq(result_dec.bits[WELL], 0);
        ck_assert_int_eq(result_dec.bits[DATA], 0);
    }
    {
        s21_decimal test_one;
        s21_from_int_to_decimal(54, &test_one);
        s21_decimal test_two;
        s21_from_int_to_decimal(4, &test_two);
        s21_decimal result_dec;
        s21_sub(test_two, test_one, &result_dec);
        ck_assert_uint_eq(result_dec.bits[RARE], 0b0000000000000000000000000110010);
        ck_assert_uint_eq(result_dec.bits[MEDIUM], 0);
        ck_assert_uint_eq(result_dec.bits[WELL], 0);
        ck_assert_int_eq((unsigned int)result_dec.bits[DATA],
                         (unsigned int)0b10000000000000000000000000000000);
    }
    {
        s21_decimal test_one;
        s21_from_int_to_decimal(-54, &test_one);
        s21_decimal test_two;
        s21_from_int_to_decimal(-4, &test_two);
        s21_decimal result_dec;
        s21_sub(test_one, test_two, &result_dec);
        ck_assert_int_eq(result_dec.bits[RARE], 0b0000000000000000000000000110010);
        ck_assert_uint_eq(result_dec.bits[MEDIUM], 0);
        ck_assert_uint_eq(result_dec.bits[WELL], 0);
        ck_assert_int_eq((unsigned int)result_dec.bits[DATA],
                         (unsigned int)0b10000000000000000000000000000000);
    }
    {
        s21_decimal test_one;
        s21_from_int_to_decimal(-54, &test_one);
        s21_decimal test_two;
        s21_from_int_to_decimal(-4, &test_two);
        s21_decimal result_dec;
        s21_sub(test_two, test_one, &result_dec);
        int result_int;
        s21_from_decimal_to_int(result_dec, &result_int);
        ck_assert_uint_eq(result_dec.bits[RARE], 0b0000000000000000000000000110010);
        ck_assert_uint_eq(result_dec.bits[MEDIUM], 0);
        ck_assert_uint_eq(result_dec.bits[WELL], 0);
        ck_assert_int_eq((unsigned int)result_dec.bits[DATA],
                         (unsigned int)0b00000000000000000000000000000000);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00000000000000000001110100101001;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b00000000000000000000000000111101;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0;
        s21_decimal result_dec;
        s21_sub(test_one, test_two, &result_dec);
        ck_assert_int_eq(result_dec.bits[RARE], 0b00000000000000000001110011101100);
        ck_assert_int_eq(result_dec.bits[MEDIUM], 0);
        ck_assert_int_eq(result_dec.bits[WELL], 0);
        ck_assert_int_eq(result_dec.bits[DATA], 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00000000000000000001110100101001;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b00000000000000000000000000111101;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0;
        s21_decimal result_dec;
        s21_sub(test_two, test_one, &result_dec);
        ck_assert_uint_eq(result_dec.bits[RARE], 0b00000000000000000001110011101100);
        ck_assert_uint_eq(result_dec.bits[MEDIUM], 0);
        ck_assert_uint_eq(result_dec.bits[WELL], 0);
        ck_assert_int_eq((unsigned int)result_dec.bits[DATA],
                         (unsigned int)0b10000000000000000000000000000000);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00000000000000001000011100000001;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b00000000000000000000000111000100;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal result_dec;
        s21_sub(test_two, test_one, &result_dec);
        ck_assert_uint_eq(result_dec.bits[RARE], 0b00000000000000001000010100111101);
        ck_assert_uint_eq(result_dec.bits[MEDIUM], 0);
        ck_assert_uint_eq(result_dec.bits[WELL], 0);
        ck_assert_int_eq((unsigned int)result_dec.bits[DATA],
                         (unsigned int)0b00000000000000000000000000000000);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00000000000001110010100100011010;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b0000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b00000000000000000000110110001000;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal result_dec;
        s21_sub(test_one, test_two, &result_dec);
        ck_assert_uint_eq(result_dec.bits[RARE], 0b00000000000001110011011010100010);
        ck_assert_uint_eq(result_dec.bits[MEDIUM], 0);
        ck_assert_uint_eq(result_dec.bits[WELL], 0);
        ck_assert_int_eq((unsigned int)result_dec.bits[DATA],
                         (unsigned int)0b00000000000000000000000000000000);
        s21_sub(test_two, test_one, &result_dec);
        ck_assert_uint_eq(result_dec.bits[RARE], 0b00000000000001110011011010100010);
        ck_assert_uint_eq(result_dec.bits[MEDIUM], 0);
        ck_assert_uint_eq(result_dec.bits[WELL], 0);
        ck_assert_int_eq((unsigned int)result_dec.bits[DATA],
                         (unsigned int)0b10000000000000000000000000000000);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00000000011100100011010011101010;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b00000000000000000001001000010001;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b00000000000000000000000000000000;
        s21_decimal result_dec;
        s21_sub(test_one, test_two, &result_dec);
        ck_assert_uint_eq(result_dec.bits[RARE], 0b00000000011100100100011011111011);
        ck_assert_uint_eq(result_dec.bits[MEDIUM], 0);
        ck_assert_uint_eq(result_dec.bits[WELL], 0);
        ck_assert_int_eq((unsigned int)result_dec.bits[DATA],
                         (unsigned int)0b10000000000000000000000000000000);
        s21_sub(test_two, test_one, &result_dec);
        ck_assert_uint_eq(result_dec.bits[RARE], 0b00000000011100100100011011111011);
        ck_assert_uint_eq(result_dec.bits[MEDIUM], 0);
        ck_assert_uint_eq(result_dec.bits[WELL], 0);
        ck_assert_int_eq((unsigned int)result_dec.bits[DATA],
                         (unsigned int)0b00000000000000000000000000000000);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00100001100101010101101110010101;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b00000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b00000000000000001110010100101100;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b00000000000000000000000000000000;
        s21_decimal result_dec;
        s21_sub(test_one, test_two, &result_dec);
        ck_assert_uint_eq(result_dec.bits[RARE], 0b00100001100101000111011001101001);
        ck_assert_uint_eq(result_dec.bits[MEDIUM], 0);
        ck_assert_uint_eq(result_dec.bits[WELL], 0);
        ck_assert_int_eq((unsigned int)result_dec.bits[DATA],
                         (unsigned int)0b00000000000000000000000000000000);
        s21_sub(test_two, test_one, &result_dec);
        ck_assert_uint_eq(result_dec.bits[RARE], 0b00100001100101000111011001101001);
        ck_assert_uint_eq(result_dec.bits[MEDIUM], 0);
        ck_assert_uint_eq(result_dec.bits[WELL], 0);
        ck_assert_int_eq((unsigned int)result_dec.bits[DATA],
                         (unsigned int)0b10000000000000000000000000000000);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00100010111010011010100101001101;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b00000000000001101100000111011010;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal result_dec;
        s21_sub(test_one, test_two, &result_dec);
        ck_assert_uint_eq(result_dec.bits[RARE], 0b00100010111000101110011101110011);
        ck_assert_uint_eq(result_dec.bits[MEDIUM], 0);
        ck_assert_uint_eq(result_dec.bits[WELL], 0);
        ck_assert_int_eq((unsigned int)result_dec.bits[DATA],
                         (unsigned int)0b10000000000000000000000000000000);
        s21_sub(test_two, test_one, &result_dec);
        ck_assert_uint_eq(result_dec.bits[RARE], 0b00100010111000101110011101110011);
        ck_assert_uint_eq(result_dec.bits[MEDIUM], 0);
        ck_assert_uint_eq(result_dec.bits[WELL], 0);
        ck_assert_int_eq((unsigned int)result_dec.bits[DATA],
                         (unsigned int)0b00000000000000000000000000000000);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b01001111001010101101010111010100;
        test_one.bits[MEDIUM] = 0b00000000000000000000000000001011;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b00000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b00000000000001101111110110001000;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal result_dec;
        s21_sub(test_one, test_two, &result_dec);
        ck_assert_uint_eq(result_dec.bits[RARE], 0b01001111001100011101001101011100);
        ck_assert_uint_eq(result_dec.bits[MEDIUM], 0b00000000000000000000000000001011);
        ck_assert_uint_eq(result_dec.bits[WELL], 0);
        ck_assert_int_eq((unsigned int)result_dec.bits[DATA],
                         (unsigned int)0b00000000000000000000000000000000);
        s21_sub(test_two, test_one, &result_dec);
        ck_assert_uint_eq(result_dec.bits[RARE], 0b01001111001100011101001101011100);
        ck_assert_uint_eq(result_dec.bits[MEDIUM], 0b00000000000000000000000000001011);
        ck_assert_uint_eq(result_dec.bits[WELL], 0);
        ck_assert_int_eq((unsigned int)result_dec.bits[DATA],
                         (unsigned int)0b10000000000000000000000000000000);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b11101010010001000100011111011011;
        test_one.bits[MEDIUM] = 0b00000000000000000000000010000111;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b00000011100000110010110101001000;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b00000000000000000000000000000000;
        s21_decimal result_dec;
        s21_sub(test_one, test_two, &result_dec);
        ck_assert_int_eq((unsigned int)result_dec.bits[RARE],
                         (unsigned int)0b11101101110001110111010100100011);
        ck_assert_int_eq(result_dec.bits[MEDIUM], 0b00000000000000000000000010000111);
        ck_assert_int_eq(result_dec.bits[WELL], 0);
        ck_assert_int_eq((unsigned int)result_dec.bits[DATA],
                         (unsigned int)0b10000000000000000000000000000000);
        s21_sub(test_two, test_one, &result_dec);
        ck_assert_int_eq((unsigned int)result_dec.bits[RARE],
                         (unsigned int)0b11101101110001110111010100100011);
        ck_assert_int_eq(result_dec.bits[MEDIUM], 0b00000000000000000000000010000111);
        ck_assert_int_eq(result_dec.bits[WELL], 0);
        ck_assert_int_eq((unsigned int)result_dec.bits[DATA],
                         (unsigned int)0b00000000000000000000000000000000);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b01101010010101010110001001111010;
        test_one.bits[MEDIUM] = 0b00000000000011011010100110101011;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b00000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b00000010111001110001001111000111;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal result_dec;
        s21_sub(test_one, test_two, &result_dec);
        ck_assert_int_eq((unsigned int)result_dec.bits[RARE],
                         (unsigned int)0b01101101001111000111011001000001);
        ck_assert_int_eq(result_dec.bits[MEDIUM], 0b00000000000011011010100110101011);
        ck_assert_int_eq(result_dec.bits[WELL], 0);
        ck_assert_int_eq((unsigned int)result_dec.bits[DATA],
                         (unsigned int)0b00000000000000000000000000000000);
        s21_sub(test_two, test_one, &result_dec);
        ck_assert_int_eq((unsigned int)result_dec.bits[RARE],
                         (unsigned int)0b01101101001111000111011001000001);
        ck_assert_int_eq(result_dec.bits[MEDIUM], 0b00000000000011011010100110101011);
        ck_assert_int_eq(result_dec.bits[WELL], 0);
        ck_assert_int_eq((unsigned int)result_dec.bits[DATA],
                         (unsigned int)0b10000000000000000000000000000000);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00100000010111100001100110110000;
        test_one.bits[MEDIUM] = 0b00000000110010000110000101000001;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b00000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b00000011011111110100101010110101;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b00000000000000000000000000000000;
        s21_decimal result_dec;
        s21_sub(test_one, test_two, &result_dec);
        ck_assert_int_eq((unsigned int)result_dec.bits[RARE],
                         (unsigned int)0b00011100110111101100111011111011);
        ck_assert_int_eq(result_dec.bits[MEDIUM], 0b00000000110010000110000101000001);
        ck_assert_int_eq(result_dec.bits[WELL], 0);
        ck_assert_int_eq((unsigned int)result_dec.bits[DATA],
                         (unsigned int)0b00000000000000000000000000000000);
        s21_sub(test_two, test_one, &result_dec);
        ck_assert_int_eq((unsigned int)result_dec.bits[RARE],
                         (unsigned int)0b00011100110111101100111011111011);
        ck_assert_int_eq(result_dec.bits[MEDIUM], 0b00000000110010000110000101000001);
        ck_assert_int_eq(result_dec.bits[WELL], 0);
        ck_assert_int_eq((unsigned int)result_dec.bits[DATA],
                         (unsigned int)0b10000000000000000000000000000000);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b10010010100000111110011100101011;
        test_one.bits[MEDIUM] = 0b00001000001100100001010000000001;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b00000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b00101101001100111110000111000100;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b00000000000000000000000000000000;
        s21_decimal result_dec;
        s21_sub(test_one, test_two, &result_dec);
        ck_assert_int_eq((unsigned int)result_dec.bits[RARE],
                         (unsigned int)0b01100101010100000000010101100111);
        ck_assert_int_eq(result_dec.bits[MEDIUM], 0b00001000001100100001010000000001);
        ck_assert_int_eq(result_dec.bits[WELL], 0);
        ck_assert_int_eq((unsigned int)result_dec.bits[DATA],
                         (unsigned int)0b00000000000000000000000000000000);
        s21_sub(test_two, test_one, &result_dec);
        ck_assert_int_eq((unsigned int)result_dec.bits[RARE],
                         (unsigned int)0b01100101010100000000010101100111);
        ck_assert_int_eq(result_dec.bits[MEDIUM], 0b00001000001100100001010000000001);
        ck_assert_int_eq(result_dec.bits[WELL], 0);
        ck_assert_int_eq((unsigned int)result_dec.bits[DATA],
                         (unsigned int)0b10000000000000000000000000000000);
    }
}
END_TEST

START_TEST(s21_div_test) {
    {
        s21_decimal test_one;
        s21_from_int_to_decimal(-60, &test_one);
        s21_decimal test_two;
        s21_from_int_to_decimal(2, &test_two);
        s21_decimal result_dec;
        int error = s21_div(test_one, test_two, &result_dec);
        int result_int;
        s21_from_decimal_to_int(result_dec, &result_int);
        ck_assert_int_eq(result_int, -60 / 2);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        s21_from_int_to_decimal(100, &test_one);
        s21_decimal test_two;
        s21_from_int_to_decimal(5, &test_two);
        s21_decimal result_dec;
        int error = s21_div(test_one, test_two, &result_dec);
        int result_int;
        s21_from_decimal_to_int(result_dec, &result_int);
        ck_assert_int_eq(result_int, 100 / 5);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test_one;
        s21_from_int_to_decimal(10, &test_one);
        s21_decimal test_two;
        s21_from_int_to_decimal(0, &test_two);
        s21_decimal result_dec;
        int error = s21_div(test_one, test_two, &result_dec);
        int result_int;
        s21_from_decimal_to_int(result_dec, &result_int);
        ck_assert_int_eq(error, 3);
    }
    {
        s21_decimal test_one;
        s21_from_float_to_decimal(12.5, &test_one);
        s21_decimal test_two;
        s21_from_float_to_decimal(5, &test_two);
        s21_decimal result_dec;
        int error = s21_div(test_one, test_two, &result_dec);
        float result_float;
        s21_from_decimal_to_float(result_dec, &result_float);
        ck_assert_float_eq(result_float, 12.5 / 5);
        ck_assert_int_eq(error, 0);
    }
}

int TestS21_ADD() {
    Suite *suite = suite_create("s21_decimal_add");
    TCase *getCase = tcase_create("Core");
    SRunner *runner = srunner_create(suite);
    int check = 0;

    suite_add_tcase(suite, getCase);
    tcase_add_test(getCase, s21_add_test_part_rare);
    tcase_add_test(getCase, s21_add_test_part_medium);
    tcase_add_test(getCase, s21_add_test_error);
    tcase_add_test(getCase, s21_add_test_fractiomal);
    tcase_add_test(getCase, s21_sub_test);

    srunner_run_all(runner, CK_ENV);
    check = srunner_ntests_failed(runner);
    srunner_free(runner);
    return check;
}

int TestMulFunc() {
    Suite *suite = suite_create("s21_decimal_mul");
    TCase *getCase = tcase_create("Core");
    SRunner *runner = srunner_create(suite);
    int check = 0;

    suite_add_tcase(suite, getCase);
    tcase_add_test(getCase, s21_mul_test);
    tcase_add_test(getCase, s21_div_test);

    srunner_run_all(runner, CK_ENV);
    check = srunner_ntests_failed(runner);
    srunner_free(runner);
    return check;
}
