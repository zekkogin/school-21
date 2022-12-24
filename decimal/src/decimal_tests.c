#include "decimal_test.h"

void copy_full(s21_decimal *dest, const s21_decimal *src) { memcpy(dest, src, sizeof(s21_decimal)); }

START_TEST(taken_tests) {
    {
        s21_decimal dec1;
        s21_decimal dec2;
        int tmp1 = 100;
        int tmp2 = 99999;
        int res_s21 = 0;
        int res = 100099;
        s21_decimal res1;
        s21_from_int_to_decimal(tmp1, &dec1);
        s21_from_int_to_decimal(tmp2, &dec2);
        s21_add(dec1, dec2, &res1);
        s21_from_decimal_to_int(res1, &res_s21);
        ck_assert_int_eq(res_s21, res);
    }
    {
        s21_decimal dec1;
        s21_decimal dec2;
        int tmp1 = -100;
        int tmp2 = -99999;
        int res_s21 = 0;
        int res = -100099;
        s21_decimal res1;
        s21_from_int_to_decimal(tmp1, &dec1);
        s21_from_int_to_decimal(tmp2, &dec2);
        s21_add(dec1, dec2, &res1);
        s21_from_decimal_to_int(res1, &res_s21);
        ck_assert_int_eq(res_s21, res);
    }
    {
        s21_decimal dec1;
        s21_decimal dec2;
        dec1.bits[3] = 0;
        dec1.bits[2] = 0;
        dec1.bits[1] = 0xF;
        dec1.bits[0] = 0x67E4FEEF;
        dec2.bits[3] = 0;
        dec2.bits[2] = 0;
        dec2.bits[1] = 0xFF;
        dec2.bits[0] = 0x67E4FFFF;
        s21_decimal res;
        res.bits[3] = 0;
        res.bits[2] = 0;
        res.bits[1] = 0x10E;
        res.bits[0] = 0xCFC9FEEE;
        s21_decimal res1;
        s21_add(dec1, dec2, &res1);
        ck_assert_int_eq(res.bits[3], res1.bits[3]);
        ck_assert_int_eq(res.bits[2], res1.bits[2]);
        ck_assert_int_eq(res.bits[1], res1.bits[1]);
        ck_assert_int_eq(res.bits[0], res1.bits[0]);
    }
    {
        s21_decimal dec1 = {{4294967295, 4294967295, 4294967295, 0}};
        s21_decimal dec2 = {{1, 0, 0, 0}};
        s21_decimal res1;
        int ret_s21 = s21_add(dec1, dec2, &res1);
        ck_assert_int_eq(1, ret_s21);
    }
    {
        s21_decimal dec;
        s21_from_int_to_decimal(0, &dec);
        ck_assert_int_eq(dec.bits[0], 0);
        ck_assert_int_eq(dec.bits[1], 0);
        ck_assert_int_eq(dec.bits[2], 0);
        ck_assert_int_eq(dec.bits[3], 0);

        s21_from_int_to_decimal(-128, &dec);
        ck_assert_int_eq(dec.bits[0], 128);
        ck_assert_int_eq(dec.bits[1], 0);
        ck_assert_int_eq(dec.bits[2], 0);
        ck_assert(dec.bits[3] == (int)0b10000000000000000000000000000000);

        s21_from_int_to_decimal(-2147483648, &dec);
        ck_assert(dec.bits[0] == (int)2147483648);
        ck_assert_int_eq(dec.bits[1], 0);
        ck_assert_int_eq(dec.bits[2], 0);
        ck_assert(dec.bits[3] == (int)0b10000000000000000000000000000000);

        s21_from_int_to_decimal(2147483647, &dec);
        ck_assert_int_eq(dec.bits[0], 2147483647);
        ck_assert_int_eq(dec.bits[1], 0);
        ck_assert_int_eq(dec.bits[2], 0);
        ck_assert_int_eq(dec.bits[3], 0);
    }

    {
        s21_decimal dec;
        int result = 0;
        int number = 0;
        dec.bits[0] = 2147483647;
        dec.bits[1] = 0;
        dec.bits[2] = 0;
        dec.bits[3] = 0;
        result = s21_from_decimal_to_int(dec, &number);
        ck_assert_float_eq(number, 2147483647);
        ck_assert_int_eq(result, 0);
    }
    {
        s21_decimal dec;
        int result = 0;
        int number = 0;
        dec.bits[0] = 133141;
        dec.bits[1] = 0;
        dec.bits[2] = 0;
        dec.bits[3] = 0;
        result = s21_from_decimal_to_int(dec, &number);
        ck_assert_int_eq(number, 133141);
        ck_assert_int_eq(result, 0);
    }
    {
        s21_decimal dec;
        int result = 0;
        int number = 0;
        dec.bits[0] = 2147483648;
        dec.bits[1] = 0;
        dec.bits[2] = 0;
        dec.bits[3] = 0b10000000000000000000000000000000;
        result = s21_from_decimal_to_int(dec, &number);
        ck_assert_int_eq(number, -2147483648);
        ck_assert_int_eq(result, 0);
    }
    {
        s21_decimal dec;
        int result = 0, number = 0;
        dec.bits[0] = 123451234;
        dec.bits[1] = 0;
        dec.bits[2] = 0;
        dec.bits[3] = 2147483648;
        result = s21_from_decimal_to_int(dec, &number);
        ck_assert_int_eq(number, -123451234);
        ck_assert_int_eq(result, 0);
    }
    {
        s21_decimal dec;
        int result = 0, number = 0;
        dec.bits[0] = 18;
        dec.bits[1] = 0;
        dec.bits[2] = 0;
        dec.bits[3] = 2147483648;
        result = s21_from_decimal_to_int(dec, &number);
        ck_assert_int_eq(number, -18);
        ck_assert_int_eq(result, 0);
    }
    {
        int a = 10;
        int res_a = 0;
        s21_decimal dec;
        s21_from_int_to_decimal(a, &dec);
        s21_decimal res;
        s21_negate(dec, &res);
        s21_from_decimal_to_int(res, &res_a);
        ck_assert_int_eq(-10, res_a);
    }
    {
        float a = 10.12345;
        float res_a = 0;
        s21_decimal dec;
        s21_from_float_to_decimal(a, &dec);
        s21_decimal res;
        s21_negate(dec, &res);
        s21_from_decimal_to_float(res, &res_a);
        ck_assert_float_eq(-10.12345, res_a);
    }
    {
        float a = 10.1234e5;
        float res_a = 0;
        s21_decimal src;
        s21_from_float_to_decimal(a, &src);
        s21_decimal res;
        s21_negate(src, &res);
        s21_from_decimal_to_float(res, &res_a);
        ck_assert_float_eq(-10.1234e5, res_a);
    }
    {
        float a = -10;
        float res_a = 0;
        s21_decimal dec;
        s21_from_float_to_decimal(a, &dec);
        s21_decimal res;
        s21_negate(dec, &res);
        s21_from_decimal_to_float(res, &res_a);
        ck_assert_float_eq(10, res_a);
    }
    {
        float a = -10;
        float res_a = 0;
        s21_decimal dec;
        s21_from_float_to_decimal(a, &dec);
        s21_decimal res;
        s21_negate(dec, &res);
        s21_from_decimal_to_float(res, &res_a);
        ck_assert_float_eq(10, res_a);
    }
    {
        s21_decimal dec1 = {{4, 0, 0, 0}};
        s21_decimal dec2 = {{10, 0, 0, 0}};

        s21_decimal d22;
        s21_mul(dec1, dec2, &d22);

        int qqqq = 0;
        s21_from_decimal_to_int(d22, &qqqq);
        ck_assert_int_eq(qqqq, 40);
    }
    {
        s21_decimal dec1 = {{100, 0, 0, 0}};                                      // 100
        s21_decimal dec2 = {{999999, 0, 0, 0b00000000000000100000000000000000}};  // 9999.99
        s21_decimal res1;
        s21_mul(dec1, dec2, &res1);
        float g;
        int error = s21_from_decimal_to_float(res1, &g);
        ck_assert_int_eq(error, 0);
        ck_assert_float_eq_tol(g, 999999, 0.1);
    }
    {
        s21_decimal dec1 = {{0b11111111111111111111111111111111 - 1, 0b11111111111111111111111111111111 - 1,
                             0b11111111111111111111111111111111 - 1, 0}};
        s21_decimal dec2 = {{2, 0, 0, 0}};
        s21_decimal res;
        int ret = s21_mul(dec1, dec2, &res);
        ck_assert_int_eq(ret, 1);
    }
    {
        s21_decimal dec5 = {{12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
        s21_decimal dec6 = {{12, 0, 0, 0b10000000000000010000000000000000}};     // -1.2;
        ck_assert_int_eq(s21_is_less(dec5, dec6), 0);
        ck_assert_int_eq(s21_is_less(dec6, dec5), 1);

        s21_decimal dec7 = {{12345, 0, 0, 0b10000000000001000000000000000000}};  // -1.2345
        s21_decimal dec8 = {{12, 0, 0, 0b00000000000000010000000000000000}};     //  1.2;
        ck_assert_int_eq(s21_is_less(dec7, dec8), 1);
        ck_assert_int_eq(s21_is_less(dec8, dec7), 0);

        s21_decimal dec1 = {{12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
        s21_decimal dec2 = {{12, 0, 0, 0b00000000000000010000000000000000}};     //  1.2;
        ck_assert_int_eq(s21_is_less(dec1, dec2), 0);
        ck_assert_int_eq(s21_is_less(dec2, dec1), 1);

        s21_decimal dec3 = {{12345, 0, 0, 0b10000000000001000000000000000000}};  // -1.2345
        s21_decimal dec4 = {{12, 0, 0, 0b10000000000000010000000000000000}};     // -1.2;
        ck_assert_int_eq(s21_is_less(dec3, dec4), 1);
        ck_assert_int_eq(s21_is_less(dec4, dec3), 0);

        s21_decimal dec9 = {{12345, 0, 0, 0}};
        s21_decimal dec10 = {{12345, 0, 0, 0}};
        ck_assert_int_eq(s21_is_less(dec9, dec10), 0);
        ck_assert_int_eq(s21_is_less(dec10, dec9), 0);

        s21_decimal dec11 = {{0, 0, 0, 0}};
        s21_decimal dec12 = {{0, 0, 0, 0}};
        ck_assert_int_eq(s21_is_less(dec11, dec12), 0);
        ck_assert_int_eq(s21_is_less(dec12, dec11), 0);
    }
    {
        s21_decimal dec5 = {{12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
        s21_decimal dec6 = {{12, 0, 0, 0b10000000000000010000000000000000}};     // -1.2;
        ck_assert_int_eq(s21_is_less_or_equal(dec5, dec6), 0);
        ck_assert_int_eq(s21_is_less_or_equal(dec6, dec5), 1);

        s21_decimal dec7 = {{12345, 0, 0, 0b10000000000001000000000000000000}};  // -1.2345
        s21_decimal dec8 = {{12, 0, 0, 0b00000000000000010000000000000000}};     //  1.2;
        ck_assert_int_eq(s21_is_less_or_equal(dec7, dec8), 1);
        ck_assert_int_eq(s21_is_less_or_equal(dec8, dec7), 0);

        s21_decimal dec1 = {{12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
        s21_decimal dec2 = {{12, 0, 0, 0b00000000000000010000000000000000}};     //  1.2;
        ck_assert_int_eq(s21_is_less_or_equal(dec1, dec2), 0);
        ck_assert_int_eq(s21_is_less_or_equal(dec2, dec1), 1);

        s21_decimal dec3 = {{12345, 0, 0, 0b10000000000001000000000000000000}};  // -1.2345
        s21_decimal dec4 = {{12, 0, 0, 0b10000000000000010000000000000000}};     // -1.2;
        ck_assert_int_eq(s21_is_less_or_equal(dec3, dec4), 1);
        ck_assert_int_eq(s21_is_less_or_equal(dec4, dec3), 0);

        s21_decimal dec9 = {{12345, 0, 0, 0}};
        s21_decimal dec10 = {{12345, 0, 0, 0}};
        ck_assert_int_eq(s21_is_less_or_equal(dec9, dec10), 1);
        ck_assert_int_eq(s21_is_less_or_equal(dec10, dec9), 1);

        s21_decimal dec11 = {{0, 0, 0, 0}};
        s21_decimal dec12 = {{0, 0, 0, 0}};
        ck_assert_int_eq(s21_is_less_or_equal(dec11, dec12), 1);
        ck_assert_int_eq(s21_is_less_or_equal(dec12, dec11), 1);
    }
    {
        s21_decimal dec5 = {{12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
        s21_decimal dec6 = {{12, 0, 0, 0b10000000000000010000000000000000}};     // -1.2;
        ck_assert_int_eq(s21_is_greater(dec5, dec6), 1);
        ck_assert_int_eq(s21_is_greater(dec6, dec5), 0);

        s21_decimal dec7 = {{12345, 0, 0, 0b10000000000001000000000000000000}};  // -1.2345
        s21_decimal dec8 = {{12, 0, 0, 0b00000000000000010000000000000000}};     //  1.2;
        ck_assert_int_eq(s21_is_greater(dec7, dec8), 0);
        ck_assert_int_eq(s21_is_greater(dec8, dec7), 1);

        s21_decimal dec1 = {{12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
        s21_decimal dec2 = {{12, 0, 0, 0b00000000000000010000000000000000}};     //  1.2;
        ck_assert_int_eq(s21_is_greater(dec1, dec2), 1);
        ck_assert_int_eq(s21_is_greater(dec2, dec1), 0);

        s21_decimal dec3 = {{12345, 0, 0, 0b10000000000001000000000000000000}};  // -1.2345
        s21_decimal dec4 = {{12, 0, 0, 0b10000000000000010000000000000000}};     // -1.2;
        ck_assert_int_eq(s21_is_greater(dec3, dec4), 0);
        ck_assert_int_eq(s21_is_greater(dec4, dec3), 1);
    }
    {
        s21_decimal dec5 = {{12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
        s21_decimal dec6 = {{12, 0, 0, 0b10000000000000010000000000000000}};     // -1.2;
        ck_assert_int_eq(s21_is_greater_or_equal(dec5, dec6), 1);
        ck_assert_int_eq(s21_is_greater_or_equal(dec6, dec5), 0);

        s21_decimal dec7 = {{12345, 0, 0, 0b10000000000001000000000000000000}};  // -1.2345
        s21_decimal dec8 = {{12, 0, 0, 0b00000000000000010000000000000000}};     //  1.2;
        ck_assert_int_eq(s21_is_greater_or_equal(dec7, dec8), 0);
        ck_assert_int_eq(s21_is_greater_or_equal(dec8, dec7), 1);

        s21_decimal dec1 = {{12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
        s21_decimal dec2 = {{12, 0, 0, 0b00000000000000010000000000000000}};     //  1.2;
        ck_assert_int_eq(s21_is_greater_or_equal(dec1, dec2), 1);
        ck_assert_int_eq(s21_is_greater_or_equal(dec2, dec1), 0);

        s21_decimal dec3 = {{12345, 0, 0, 0b10000000000001000000000000000000}};  // -1.2345
        s21_decimal dec4 = {{12, 0, 0, 0b10000000000000010000000000000000}};     // -1.2;
        ck_assert_int_eq(s21_is_greater_or_equal(dec3, dec4), 0);
        ck_assert_int_eq(s21_is_greater_or_equal(dec4, dec3), 1);

        s21_decimal dec9 = {{12345, 0, 0, 0}};
        s21_decimal dec10 = {{12345, 0, 0, 0}};
        ck_assert_int_eq(s21_is_greater_or_equal(dec9, dec10), 1);
        ck_assert_int_eq(s21_is_greater_or_equal(dec10, dec9), 1);

        s21_decimal dec11 = {{0, 0, 0, 0}};
        s21_decimal dec12 = {{0, 0, 0, 0}};
        ck_assert_int_eq(s21_is_greater_or_equal(dec11, dec12), 1);
        ck_assert_int_eq(s21_is_greater_or_equal(dec12, dec11), 1);
    }
    {
        s21_decimal dec1 = {{12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
        s21_decimal dec2 = {{12, 0, 0, 0b10000000000000010000000000000000}};     // -1.2;
        ck_assert_int_eq(s21_is_equal(dec1, dec2), 0);

        s21_decimal dec3 = {{120000, 0, 0, 0b00000000000001000000000000000000}};  //  12.0000
        s21_decimal dec4 = {{12, 0, 0, 0b00000000000000000000000000000000}};      //  12;
        ck_assert_int_eq(s21_is_equal(dec3, dec4), 1);

        s21_decimal dec5 = {{0, 0, 0, 0b00000000000000000000000000000000}};  //  0
        s21_decimal dec6 = {{0, 0, 0, 0b00000000000000010000000000000000}};  //  0.0;
        ck_assert_int_eq(s21_is_equal(dec5, dec6), 1);

        s21_decimal dec7 = {{0, 0, 0, 0b00000000000000000000000000000000}};  //   0
        s21_decimal dec8 = {{0, 0, 0, 0b10000000000000000000000000000000}};  //  -0;
        ck_assert_int_eq(s21_is_equal(dec7, dec8), 1);
    }
    {
        s21_decimal dec1, dec2;
        s21_from_int_to_decimal(0, &dec1);
        s21_from_int_to_decimal(0, &dec2);
        dec1.bits[3] = 0;
        ck_assert_int_eq(s21_is_equal(dec1, dec2), 1);
    }
    {
        s21_decimal dec1 = {{12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
        s21_decimal dec2 = {{12, 0, 0, 0b10000000000000010000000000000000}};     // -1.2;
        ck_assert_int_eq(s21_is_not_equal(dec1, dec2), 1);

        s21_decimal dec3 = {{120000, 0, 0, 0b00000000000001000000000000000000}};  //  12.0000
        s21_decimal dec4 = {{12, 0, 0, 0b00000000000000000000000000000000}};      //  12;
        ck_assert_int_eq(s21_is_not_equal(dec3, dec4), 0);

        s21_decimal dec5 = {{0, 0, 0, 0b00000000000000000000000000000000}};   //  0
        s21_decimal dec6 = {{00, 0, 0, 0b00000000000000010000000000000000}};  //  0.0;
        ck_assert_int_eq(s21_is_not_equal(dec5, dec6), 1);

        s21_decimal dec7 = {{0, 0, 0, 0b00000000000000000000000000000000}};  //   0
        s21_decimal dec8 = {{0, 0, 0, 0b10000000000000000000000000000000}};  //  -0;
        ck_assert_int_eq(s21_is_not_equal(dec7, dec8), 0);
    }
    {
        s21_decimal dec1;
        s21_decimal dec2;
        int tmp1 = -2147483647;
        int tmp2 = 2147483647;
        int res_s21 = 0;
        int res = 0;
        s21_decimal res1;
        s21_from_int_to_decimal(tmp1, &dec1);
        s21_from_int_to_decimal(tmp2, &dec2);
        s21_add(dec1, dec2, &res1);
        s21_from_decimal_to_int(res1, &res_s21);
        ck_assert_int_eq(res_s21, res);
    }
    {
        s21_decimal dec1 = {{4294967295, 4294967295, 4294967295, (unsigned int)pow(2, 31)}};
        s21_decimal dec2 = {{1, 0, 0, (unsigned int)pow(2, 31)}};
        s21_decimal res1;
        int ret_s21 = s21_add(dec1, dec2, &res1);
        ck_assert_int_eq(1, ret_s21);
    }
    {
        s21_decimal dec1 = {{101, 0, 0, 0b00000000000000100000000000000000}};   // 1.01
        s21_decimal dec2 = {{1021, 0, 0, 0b00000000000000100000000000000000}};  // 10.21
        s21_decimal res1;
        s21_add(dec1, dec2, &res1);
        float g;
        s21_from_decimal_to_float(res1, &g);
        ck_assert_float_eq(g, 11.22);
    }
    {
        s21_decimal dec1 = {{101, 0, 0, 0b10000000000000100000000000000000}};   // -1.01
        s21_decimal dec2 = {{1021, 0, 0, 0b10000000000000100000000000000000}};  // -10.21
        s21_decimal res1;
        s21_add(dec1, dec2, &res1);
        float g;
        s21_from_decimal_to_float(res1, &g);
        ck_assert_float_eq(g, -11.22);
    }

    {
        s21_decimal dec1 = {{100, 0, 0, 0b10000000000000000000000000000000}};     // -100
        s21_decimal dec2 = {{999999, 0, 0, 0b00000000000000100000000000000000}};  // 9999.99
        s21_decimal res1;
        s21_mul(dec1, dec2, &res1);
        float g;
        s21_from_decimal_to_float(res1, &g);
        ck_assert_float_eq_tol(g, -999999, 0.1);
    }
    {
        s21_decimal dec1 = {{1002, 0, 0, 0b10000000000000010000000000000000}};    // -100.2
        s21_decimal dec2 = {{999999, 0, 0, 0b10000000000000100000000000000000}};  // -9999.99
        s21_decimal res1;
        s21_mul(dec1, dec2, &res1);
        float g;
        s21_from_decimal_to_float(res1, &g);
        ck_assert_float_eq_tol(g, 1001998.998, 1e-06);
    }
    {
        s21_decimal dec1 = {{0, 0, 0, 0b10000000000000000000000000000000}};       // -0.0
        s21_decimal dec2 = {{999999, 0, 0, 0b10000000000000100000000000000000}};  // -9999.99
        s21_decimal res1;
        s21_mul(dec1, dec2, &res1);
        int g;
        s21_from_decimal_to_int(res1, &g);
        float r = (float)g * pow(10, -s21_get_scale(res1));
        ck_assert_float_eq(r, 0.0);
    }
    {
        s21_decimal dec1 = {{123456789, 0, 0, 0b00000000000010100000000000000000}};
        s21_decimal dec2 = {{123456789, 0, 0, 0b00000000000010100000000000000000}};
        s21_decimal res;
        s21_mul(dec1, dec2, &res);
        float g;
        s21_from_decimal_to_float(res, &g);
        ck_assert_float_eq_tol(g, 0.00015241578512359410524368286132812, 1e-06);
    }
    {
        s21_decimal dec1 = {{0b11111111111111111111111111111111 - 1, 0b11111111111111111111111111111111 - 1,
                             0b11111111111111111111111111111111 - 1, 0b10000000000000000000000000000000}};
        s21_decimal dec2 = {{2, 0, 0, 0}};
        s21_decimal res;
        int ret = s21_mul(dec1, dec2, &res);
        ck_assert_int_eq(ret, 1);
    }

    {
        s21_decimal dec;
        s21_from_float_to_decimal(-128.023, &dec);
        float tmp = 0;
        s21_from_decimal_to_float(dec, &tmp);
        ck_assert_float_eq_tol(tmp, -128.023, 1e-06);
    }
    {
        s21_decimal dec;
        s21_from_float_to_decimal(-2.1474836E+09, &dec);
        float tmp = 0;
        s21_from_decimal_to_float(dec, &tmp);
        ck_assert_float_eq_tol(tmp, -2.1474836E+09, 1e-06);
    }
    {
        s21_decimal dec;
        s21_from_float_to_decimal(22.14836E+03, &dec);
        float tmp = 0;
        s21_from_decimal_to_float(dec, &tmp);
        ck_assert_float_eq_tol(tmp, 22.14836E+03, 1e-06);
    }
    {
        s21_decimal dec;
        s21_from_float_to_decimal(1.02E+08, &dec);
        float tmp = 0;
        s21_from_decimal_to_float(dec, &tmp);
        ck_assert_float_eq_tol(tmp, 1.02E+08, 1e-06);
    }
    {
        s21_decimal dec;
        s21_from_float_to_decimal(-333.2222, &dec);
        float tmp = 0;
        s21_from_decimal_to_float(dec, &tmp);
        ck_assert_float_eq_tol(tmp, -333.2222, 1e-06);
    }
    {
        s21_decimal dec;
        float a = 1.0 / 0.0;
        int ret = s21_from_float_to_decimal(a, &dec);
        ck_assert_int_eq(ret, 1);
    }
    {
        s21_decimal dec;
        float a = -1.0 / 0.0;
        s21_from_float_to_decimal(a, &dec);
        ck_assert_int_eq(dec.bits[0], 0);
        ck_assert_int_eq(dec.bits[1], 0);
        ck_assert_int_eq(dec.bits[2], 0);
        ck_assert_int_eq(dec.bits[3], 0);
    }
    {
        s21_decimal dec;
        float a = INFINITY;
        s21_from_float_to_decimal(a, &dec);
        ck_assert_int_eq(dec.bits[0], 0);
        ck_assert_int_eq(dec.bits[1], 0);
        ck_assert_int_eq(dec.bits[2], 0);
        ck_assert_int_eq(dec.bits[3], 0);
    }
    {
        s21_decimal dec;
        float i = 29228162514264337593543950330.;
        s21_from_float_to_decimal(i, &dec);
        float tmp = 0;
        s21_from_decimal_to_float(dec, &tmp);
        ck_assert_float_eq_tol(tmp, i, 1e-06);
    }
    {
        s21_decimal dec;
        int result = 0;
        float number = 0.0;
        dec.bits[0] = 18122;
        dec.bits[1] = 0;
        dec.bits[2] = 0;
        dec.bits[3] = 2147680256;
        result = s21_from_decimal_to_float(dec, &number);
        ck_assert_float_eq(number, -18.122);
        ck_assert_int_eq(result, 0);
    }
    {
        s21_decimal dec;
        int result = 0;
        float number = 0.0;
        dec.bits[0] = 1812;
        dec.bits[1] = 0;
        dec.bits[2] = 0;
        dec.bits[3] = 2147483648;
        result = s21_from_decimal_to_float(dec, &number);
        ck_assert_float_eq(number, -1812);
        ck_assert_int_eq(result, 0);
    }
    {
        s21_decimal dec;
        int result = 0;
        float number = 0.0;

        dec.bits[0] = 0XFFFFFF;
        dec.bits[1] = 0;
        dec.bits[2] = 0;
        dec.bits[3] = 0;
        result = s21_from_decimal_to_float(dec, &number);
        ck_assert_float_eq(number, 16777215);
        ck_assert_int_eq(result, 0);
    }
    {
        s21_decimal dec;
        float tmp = 0;
        float tmp1 = 0.03;
        s21_from_float_to_decimal(tmp1, &dec);
        s21_from_decimal_to_float(dec, &tmp);
        ck_assert_float_eq_tol(tmp, tmp1, 1e-06);
    }
    {
        s21_decimal dec;
        int result = 0;
        float number = 0.0;

        dec.bits[0] = 4294967295;
        dec.bits[1] = 4294967295;
        dec.bits[2] = 0;
        dec.bits[3] = 0;
        result = s21_from_decimal_to_float(dec, &number);
        ck_assert_float_eq(number, 0xFFFFFFFFFFFFFFFF);
        ck_assert_int_eq(result, 0);
    }
    {
        s21_decimal value_1 = {{55555, 0, 0, 0}};
        s21_decimal value_2 = {{66666, 0, 0, 262144}};
        s21_decimal result = {{0}};
        s21_decimal correct_answer = {{555616666, 0, 0, 262144}};
        int function_returned = s21_add(value_1, value_2, &result);

        ck_assert_uint_eq(function_returned, 0);
        ck_assert_uint_eq(result.bits[0], correct_answer.bits[0]);
        ck_assert_uint_eq(result.bits[1], correct_answer.bits[1]);
        ck_assert_uint_eq(result.bits[2], correct_answer.bits[2]);
        ck_assert_uint_eq(result.bits[3], correct_answer.bits[3]);
    }
    {
        s21_decimal input1 = {{0x26687e73, 0, 0, 0b10000000000001000000000000000000}};
        s21_decimal input2 = {{0xd3, 0, 0, 0b10000000000000010000000000000000}};
        s21_decimal expected = {{0xa82038c9, 0x1f, 0, 0b00000000000001010000000000000000}};
        s21_decimal result;
        int status = s21_mul(input1, input2, &result);

        ASSERT_DECIMAL_EQ
        ck_assert_int_eq(status, 0);
    }
    {
        s21_decimal input1 = {{0x400, 0, 0, 0b10000000000000100000000000000000}};
        s21_decimal input2 = {{0x400, 0, 0, 0b10000000000000100000000000000000}};
        s21_decimal expected = {{0x100000, 0, 0, 0b00000000000001000000000000000000}};
        s21_decimal result;
        int status = s21_mul(input1, input2, &result);

        ASSERT_DECIMAL_EQ
        ck_assert_int_eq(status, 0);
    }
    {
        s21_decimal input = {{1}}, result = {{0}}, expected = {{1, 0, 0, 0b10000000000000000000000000000000}};
        int status = s21_negate(input, &result);

        ASSERT_DECIMAL_EQ
        ck_assert_int_eq(status, 0);
    }
    {
        s21_decimal input = {{1, 0, 0, 0b10000000000000000000000000000000}}, result = {{0}}, expected = {{1}};
        int status = s21_negate(input, &result);

        ASSERT_DECIMAL_EQ
        ck_assert_int_eq(status, 0);
    }
    {
        s21_decimal a = {{0, 0, 0, 0}};
        s21_decimal b = {{0, 0, 0, 0}};
        ck_assert_int_eq(s21_is_less(a, b), 0);
        ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
        ck_assert_int_eq(s21_is_greater(a, b), 0);
        ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
        ck_assert_int_eq(s21_is_equal(a, b), 1);
        ck_assert_int_eq(s21_is_not_equal(a, b), 0);
    }
    {
        s21_decimal a = {{123, 123, 123, 0}};
        s21_decimal b = {{123, 123, 123, 0}};
        ck_assert_int_eq(s21_is_less(a, b), 0);
        ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
        ck_assert_int_eq(s21_is_greater(a, b), 0);
        ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
        ck_assert_int_eq(s21_is_equal(a, b), 1);
        ck_assert_int_eq(s21_is_not_equal(a, b), 0);
    }
    {
        s21_decimal a = {{123, 0, 0, 0}};
        s21_decimal b = {{123, 0, 0, -2147483648}};
        ck_assert_int_eq(s21_is_less(a, b), 0);
        ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);
        ck_assert_int_eq(s21_is_greater(a, b), 1);
        ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
        ck_assert_int_eq(s21_is_equal(a, b), 0);
        ck_assert_int_eq(s21_is_not_equal(a, b), 1);
    }
    {
        s21_decimal a = {{0xffffffff, 0xffffffff, 0, 1835008}};
        s21_decimal b = {{0xffffffff, 0xfffffffe, 0, 1835008}};
        ck_assert_int_eq(s21_is_less(a, b), 0);
        ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);
        ck_assert_int_eq(s21_is_greater(a, b), 1);
        ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
        ck_assert_int_eq(s21_is_equal(a, b), 0);
        ck_assert_int_eq(s21_is_not_equal(a, b), 1);
    }
    {
        s21_decimal a = {{0xffffffff, 0xffffffff, 0xffffffff, 65536}};
        s21_decimal b = {{0xffffffff, 0xffffffff, 0xffffffff, 196608}};
        ck_assert_int_eq(s21_is_less(a, b), 0);
        ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);
        ck_assert_int_eq(s21_is_greater(a, b), 1);
        ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
        ck_assert_int_eq(s21_is_equal(a, b), 0);
        ck_assert_int_eq(s21_is_not_equal(a, b), 1);
    }
    {
        s21_decimal a = {{0xffffffff, 0xffffffff, 0xffffffff, 65536}};
        s21_decimal b = {{0xffffffff, 0xffffffff, 0xffffffff, 196608}};
        ck_assert_int_eq(s21_is_less(a, b), 0);
        ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);
        ck_assert_int_eq(s21_is_greater(a, b), 1);
        ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
        ck_assert_int_eq(s21_is_equal(a, b), 0);
        ck_assert_int_eq(s21_is_not_equal(a, b), 1);
    }
    {
        s21_decimal a = {{0x99999999, 0xfefefefe, 0xffffffff, -2147483648}};
        s21_decimal b = {{0x99999999, 0xfefefefe, 0xffffffee, -2147483648}};
        ck_assert_int_eq(s21_is_less(a, b), 1);
        ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
        ck_assert_int_eq(s21_is_greater(a, b), 0);
        ck_assert_int_eq(s21_is_greater_or_equal(a, b), 0);
        ck_assert_int_eq(s21_is_equal(a, b), 0);
        ck_assert_int_eq(s21_is_not_equal(a, b), 1);
    }
    {
        s21_decimal a = {{12345600, 0, 0, 196608}};
        s21_decimal b = {{123456, 0, 0, 65536}};
        ck_assert_int_eq(s21_is_less(a, b), 0);
        ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
        ck_assert_int_eq(s21_is_greater(a, b), 0);
        ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
        ck_assert_int_eq(s21_is_equal(a, b), 1);
        ck_assert_int_eq(s21_is_not_equal(a, b), 0);
    }
    {
        s21_decimal a = {{12345678, 0, 0, 0}};
        s21_decimal b = {{123456781, 0, 0, 65536}};
        ck_assert_int_eq(s21_is_less(a, b), 1);
        ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
        ck_assert_int_eq(s21_is_greater(a, b), 0);
        ck_assert_int_eq(s21_is_greater_or_equal(a, b), 0);
        ck_assert_int_eq(s21_is_equal(a, b), 0);
        ck_assert_int_eq(s21_is_not_equal(a, b), 1);
    }
    {
        s21_decimal a = {{0, 0, 0, 0}};
        s21_decimal b = {{0, 0, 0, -2147483648}};
        ck_assert_int_eq(s21_is_less(a, b), 0);
        ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
        ck_assert_int_eq(s21_is_greater(a, b), 0);
        ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
        ck_assert_int_eq(s21_is_equal(a, b), 1);
        ck_assert_int_eq(s21_is_not_equal(a, b), 0);
    }
    {
        int src = INT_MIN;
        s21_decimal expected = {{INT_MIN, 0, 0, 0b10000000000000000000000000000000}};
        s21_decimal result;
        int status = s21_from_int_to_decimal(src, &result);

        ASSERT_DECIMAL_EQ
        ck_assert_int_eq(status, 0);
    }
    {
        int src = INT_MAX;
        s21_decimal expected = {{INT_MAX, 0, 0, 0}};
        s21_decimal result;
        int status = s21_from_int_to_decimal(src, &result);

        ASSERT_DECIMAL_EQ
        ck_assert_int_eq(status, 0);
    }
    {
        int src = 0;
        s21_decimal expected = {{0}};
        s21_decimal result;
        int status = s21_from_int_to_decimal(src, &result);

        ASSERT_DECIMAL_EQ
        ck_assert_int_eq(status, 0);
    }
    {
        float zero = 0.0, val = zero;
        s21_decimal dec_1, dec_2;
        s21_from_float_to_decimal(val, &dec_1);
        ck_assert_float_eq(val, 0.0);
        copy_full(&dec_2, &dec_1);
        float res;
        s21_from_decimal_to_float(dec_2, &res);
        ck_assert_float_eq(val, res);
    }
    {
        float zero = 0.0, val = (0 / zero);
        s21_decimal dec_1;
        int res = s21_from_float_to_decimal(val, &dec_1);
        ck_assert_int_eq(res, 1);
    }
    {
        float zero = 0.0, val = (1.0 / zero);
        s21_decimal dec_1;
        int res = s21_from_float_to_decimal(val, &dec_1);
        ck_assert_int_eq(res, 1);
    }
    {
        float val = 1e-29;
        s21_decimal dec_1;
        int res = s21_from_float_to_decimal(val, &dec_1);
        ck_assert_int_eq(res, 1);
        ck_assert_int_eq(dec_1.bits[0], 0);
    }
    {
        float val = 792281625142643.3;
        s21_decimal dec_1, dec_2;
        s21_from_float_to_decimal(val, &dec_1);
        copy_full(&dec_2, &dec_1);
        float res;
        s21_from_decimal_to_float(dec_2, &res);
        ck_assert_float_eq_tol(val, res, FLT_EPSILON);
    }
    {
        float val = -792281625142643.3;
        s21_decimal dec_1, dec_2;
        s21_from_float_to_decimal(val, &dec_1);
        copy_full(&dec_2, &dec_1);
        float res;
        s21_from_decimal_to_float(dec_2, &res);
        ck_assert_float_eq(val, res);
    }
    {
        s21_decimal dec1;

        dec1.bits[3] = 0x000A0000;
        dec1.bits[2] = 0x0;
        dec1.bits[1] = 0xFFFFFFFF;
        dec1.bits[0] = 0xFFFFFFFF;
        s21_decimal result;
        result.bits[3] = 0x0;
        result.bits[2] = 0x0;
        result.bits[1] = 0x0;
        result.bits[0] = 0x6DF37F67;
        s21_decimal res1;
        s21_truncate(dec1, &res1);
        ck_assert_float_eq(res1.bits[0], result.bits[0]);
        ck_assert_float_eq(res1.bits[1], result.bits[1]);
        ck_assert_float_eq(res1.bits[2], result.bits[2]);
        ck_assert_float_eq(res1.bits[3], result.bits[3]);
    }
    {
        s21_decimal dec1;
        dec1.bits[3] = 0x800C0000;
        dec1.bits[2] = 0x0;
        dec1.bits[1] = 0xFFFFFFFF;
        dec1.bits[0] = 0xFFFFFFFF;
        s21_decimal result;
        result.bits[3] = 0x80000000;
        result.bits[2] = 0x0;
        result.bits[1] = 0x0;
        result.bits[0] = 0x1197998;
        s21_decimal res1;
        s21_truncate(dec1, &res1);
        ck_assert_float_eq(res1.bits[0], result.bits[0]);
        ck_assert_float_eq(res1.bits[1], result.bits[1]);
        ck_assert_float_eq(res1.bits[2], result.bits[2]);
        ck_assert_float_eq(res1.bits[3], result.bits[3]);
    }
    {
        s21_decimal dec1;
        dec1.bits[3] = 0x80000000;
        dec1.bits[2] = 0x0;
        dec1.bits[1] = 0xFFFFFFFF;
        dec1.bits[0] = 0xFFFFFFFF;
        s21_decimal result;
        result.bits[3] = 0x80000000;
        result.bits[2] = 0x0;
        result.bits[1] = 0xFFFFFFFF;
        result.bits[0] = 0xFFFFFFFF;
        s21_decimal res1;
        s21_truncate(dec1, &res1);
        ck_assert_float_eq(res1.bits[0], result.bits[0]);
        ck_assert_float_eq(res1.bits[1], result.bits[1]);
        ck_assert_float_eq(res1.bits[2], result.bits[2]);
        ck_assert_float_eq(res1.bits[3], result.bits[3]);
    }
    {
        s21_decimal dec1;
        dec1.bits[0] = 0b00000000000000000000000001101101;
        dec1.bits[1] = 0b00000000000011000110010101011011;
        dec1.bits[2] = 0b00000000000000000011000000111001;
        dec1.bits[3] = 0b00000000000011100000000000000000;
        s21_decimal result;
        result.bits[0] = 0b10000111101111000001011000011110;
        result.bits[1] = 0b00000000000000000000000000000000;
        result.bits[2] = 0b00000000000000000000000000000000;
        result.bits[3] = 0b00000000000000000000000000000000;
        s21_decimal res1;
        s21_truncate(dec1, &res1);
        ck_assert_float_eq(res1.bits[0], result.bits[0]);
        ck_assert_float_eq(res1.bits[1], result.bits[1]);
        ck_assert_float_eq(res1.bits[2], result.bits[2]);
        ck_assert_float_eq(res1.bits[3], result.bits[3]);
    }
    {
        s21_decimal dec1;
        dec1.bits[0] = 0b11011110101001001000000010110110;
        dec1.bits[1] = 0b01011111101001011101111110100000;
        dec1.bits[2] = 0b00011111111010011010111101100000;
        dec1.bits[3] = 0b00000000000010010000000000000000;
        s21_decimal result;
        result.bits[0] = 0b00110100101011011100000100111110;
        result.bits[1] = 0b10001001000100001000011110111001;
        result.bits[2] = 0b00000000000000000000000000000000;
        result.bits[3] = 0b00000000000000000000000000000000;
        s21_decimal res1;
        s21_truncate(dec1, &res1);
        ck_assert_float_eq(res1.bits[0], result.bits[0]);
        ck_assert_float_eq(res1.bits[1], result.bits[1]);
        ck_assert_float_eq(res1.bits[2], result.bits[2]);
        ck_assert_float_eq(res1.bits[3], result.bits[3]);
    }
    {
        s21_decimal dec1;
        dec1.bits[3] = 0x80090000;
        dec1.bits[2] = 0;
        dec1.bits[1] = 0xFFFFEA34;
        dec1.bits[0] = 0xFF837E4F;
        s21_decimal result;
        s21_truncate(dec1, &result);
        s21_decimal res1;
        res1.bits[3] = 0x80000000;
        res1.bits[2] = 0;
        res1.bits[1] = 0x4;
        res1.bits[0] = 0x4B829C70;
        ck_assert_int_eq(res1.bits[3], result.bits[3]);
        ck_assert_int_eq(res1.bits[2], result.bits[2]);
        ck_assert_int_eq(res1.bits[1], result.bits[1]);
        ck_assert_int_eq(res1.bits[0], result.bits[0]);
    }
    {
        s21_decimal dec1;
        dec1.bits[3] = 0x80090000;
        dec1.bits[2] = 0;
        dec1.bits[1] = 0xFFFFEA34;
        dec1.bits[0] = 0xFF837E4F;
        s21_decimal result;
        s21_truncate(dec1, &result);
        s21_decimal res1;

        res1.bits[3] = 0x80000000;
        res1.bits[2] = 0;
        res1.bits[1] = 0x4;
        res1.bits[0] = 0x4B829C70;
        ck_assert_int_eq(res1.bits[3], result.bits[3]);
        ck_assert_int_eq(res1.bits[2], result.bits[2]);
        ck_assert_int_eq(res1.bits[1], result.bits[1]);
        ck_assert_int_eq(res1.bits[0], result.bits[0]);
    }
    {
        s21_decimal dec1;
        dec1.bits[0] = 0b11010000101000110011000001101101;
        dec1.bits[1] = 0b00011111100110100110101101011000;
        dec1.bits[2] = 0;
        dec1.bits[3] = 0b00000000000010010000000000000000;
        s21_decimal result;
        s21_truncate(dec1, &result);
        s21_decimal result_origin;
        result_origin.bits[3] = 0;
        result_origin.bits[2] = 0;
        result_origin.bits[1] = 0;
        result_origin.bits[0] = 0b10000111101111000001011000011110;
        ck_assert_int_eq(result_origin.bits[3], result.bits[3]);
        ck_assert_int_eq(result_origin.bits[2], result.bits[2]);
        ck_assert_int_eq(result_origin.bits[1], result.bits[1]);
        ck_assert_int_eq(result_origin.bits[0], result.bits[0]);
    }
    {
        s21_decimal dec1;
        dec1.bits[0] = 0b11010000101000110011000001101101;
        dec1.bits[1] = 0b00011111100110100110101101011000;
        dec1.bits[2] = 0;
        dec1.bits[3] = 0b00000000000010010000000000000000;
        s21_decimal result;
        s21_truncate(dec1, &result);
        s21_decimal result_origin;
        result_origin.bits[3] = 0;
        result_origin.bits[2] = 0;
        result_origin.bits[1] = 0;
        result_origin.bits[0] = 0b10000111101111000001011000011110;
        ck_assert_int_eq(result_origin.bits[3], result.bits[3]);
        ck_assert_int_eq(result_origin.bits[2], result.bits[2]);
        ck_assert_int_eq(result_origin.bits[1], result.bits[1]);
        ck_assert_int_eq(result_origin.bits[0], result.bits[0]);
    }
    {
        s21_decimal dec1;
        dec1.bits[0] = 0b01111000101001111011110011000110;
        dec1.bits[1] = 0b10011111111111001111101010000100;
        dec1.bits[2] = 0b00011111111010011010111101101101;
        dec1.bits[3] = 0b00000000000111000000000000000000;
        s21_decimal result;
        result.bits[0] = 0b00000000000000000000000000000000;
        result.bits[1] = 0b00000000000000000000000000000000;
        result.bits[2] = 0b00000000000000000000000000000000;
        result.bits[3] = 0b00000000000000000000000000000000;
        s21_decimal res1;
        s21_truncate(dec1, &res1);
        ck_assert_float_eq(res1.bits[0], result.bits[0]);
        ck_assert_float_eq(res1.bits[1], result.bits[1]);
        ck_assert_float_eq(res1.bits[2], result.bits[2]);
        ck_assert_float_eq(res1.bits[3], result.bits[3]);
    }
    {
        s21_decimal input = {{0, 0, 0, 0b00000000000011110000000000000000}};
        s21_decimal expected = {{0}};
        s21_decimal result;
        s21_truncate(input, &result);
        ASSERT_DECIMAL_EQ
    }
    {
        s21_decimal input = {{362732873, 0, 0, 0b10000000000000000000000000000000}};
        s21_decimal expected = {{362732873, 0, 0, 0b10000000000000000000000000000000}};
        s21_decimal result;
        s21_truncate(input, &result);
        ASSERT_DECIMAL_EQ
    }
    {
        s21_decimal input = {{572963473, 0, 0, 0b00000000000001000000000000000000}};
        s21_decimal expected = {{57296, 0, 0, 0}};
        s21_decimal result;
        s21_truncate(input, &result);
        ASSERT_DECIMAL_EQ
    }
    {
        s21_decimal input = {{0xb54ac285, 0x9bde85, 0, 0b10000000000010000000000000000000}};
        s21_decimal expected = {{0x1a268848, 0, 0, 0b10000000000000000000000000000000}};
        s21_decimal result;
        s21_truncate(input, &result);
        ASSERT_DECIMAL_EQ
    }
    {
        s21_decimal input = {{0x4C577A00, 0xC0D845D, 0, 0b00000000000010000000000000000000}};
        s21_decimal expected = {{0x5A9F2BA, 0x2, 0, 0b00000000000000000000000000000000}};
        s21_decimal result;
        s21_truncate(input, &result);
        ASSERT_DECIMAL_EQ
    }
    {
        s21_decimal input = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0b10000000000111000000000000000000}};
        s21_decimal expected = {{7, 0, 0, 0b10000000000000000000000000000000}};
        s21_decimal result;
        s21_truncate(input, &result);
        ASSERT_DECIMAL_EQ
    }
    {
        s21_decimal input = {
            {0b11111111111111111111111111111110, 0xFFFFFFFF, 0xFFFFFFFF, 0b10000000000111000000000000000000}};
        s21_decimal expected = {{7, 0, 0, 0b10000000000000000000000000000000}};
        s21_decimal result;
        s21_truncate(input, &result);
        ASSERT_DECIMAL_EQ
    }
    {
        s21_decimal input = {
            {0b11111111111111111111111111111100, 0xFFFFFFFF, 0xFFFFFFFF, 0b10000000000111000000000000000000}};
        s21_decimal expected = {{7, 0, 0, 0b10000000000000000000000000000000}};
        s21_decimal result;
        s21_truncate(input, &result);
        ASSERT_DECIMAL_EQ
    }
    {
        s21_decimal dec1;
        dec1.bits[0] = 0b00001111111111111111111111111111;
        dec1.bits[1] = 0b00111110001001010000001001100001;
        dec1.bits[2] = 0b00100000010011111100111001011110;
        dec1.bits[3] = 0b00000000000010100000000000000000;
        s21_decimal res1;
        s21_floor(dec1, &res1);
        s21_decimal result;
        result.bits[0] = 0b10100111011000111111111111111111;
        result.bits[1] = 0b00001101111000001011011010110011;
        result.bits[2] = 0b00000000000000000000000000000000;
        result.bits[3] = 0b00000000000000000000000000000000;
        ck_assert_float_eq(res1.bits[0], result.bits[0]);
        ck_assert_float_eq(res1.bits[1], result.bits[1]);
        ck_assert_float_eq(res1.bits[2], result.bits[2]);
        ck_assert_float_eq(res1.bits[3], result.bits[3]);
    }
    {
        s21_decimal dec1;
        dec1.bits[0] = 0b10111101001001111000010001010010;
        dec1.bits[1] = 0b00000000000000000000000000011100;
        dec1.bits[2] = 0b00000000000000000000000000000000;
        dec1.bits[3] = 0b10000000000010010000000000000000;
        s21_decimal res1;
        s21_floor(dec1, &res1);
        s21_decimal result;
        result.bits[0] = 0b00000000000000000000000001111100;
        result.bits[1] = 0b00000000000000000000000000000000;
        result.bits[2] = 0b00000000000000000000000000000000;
        result.bits[3] = 0b10000000000000000000000000000000;
        ck_assert_int_eq((unsigned int)res1.bits[0], (unsigned int)result.bits[0]);
        ck_assert_int_eq(res1.bits[1], result.bits[1]);
        ck_assert_int_eq(res1.bits[2], result.bits[2]);
        ck_assert_int_eq((unsigned int)res1.bits[3], (unsigned int)result.bits[3]);
    }
    {
        s21_decimal dec1;
        dec1.bits[0] = 0b10010011111100000001110001010010;
        dec1.bits[1] = 0b00000000000000000000000100100000;
        dec1.bits[2] = 0b00000000000000000000000000000000;
        dec1.bits[3] = 0b00000000000010100000000000000000;
        s21_decimal res1;
        s21_floor(dec1, &res1);
        s21_decimal result;
        result.bits[0] = 0b00000000000000000000000001111011;
        result.bits[1] = 0b00000000000000000000000000000000;
        result.bits[2] = 0b00000000000000000000000000000000;
        result.bits[3] = 0b00000000000000000000000000000000;
        ck_assert_float_eq(res1.bits[0], result.bits[0]);
        ck_assert_float_eq(res1.bits[1], result.bits[1]);
        ck_assert_float_eq(res1.bits[2], result.bits[2]);
        ck_assert_float_eq(res1.bits[3], result.bits[3]);
    }
    {
        s21_decimal dec1;
        dec1.bits[0] = 0b01010101001110101110101110110001;
        dec1.bits[1] = 0b00001101101101001101101001011111;
        dec1.bits[2] = 0b00000000000000000000000000000000;
        dec1.bits[3] = 0b10000000000100100000000000000000;
        s21_decimal res1;
        s21_floor(dec1, &res1);
        s21_decimal result;
        result.bits[0] = 0b00000000000000000000000000000001;
        result.bits[1] = 0b00000000000000000000000000000000;
        result.bits[2] = 0b00000000000000000000000000000000;
        result.bits[3] = 0b10000000000000000000000000000000;
        ck_assert_float_eq(res1.bits[0], result.bits[0]);
        ck_assert_float_eq(res1.bits[1], result.bits[1]);
        ck_assert_float_eq(res1.bits[2], result.bits[2]);
        ck_assert_float_eq(res1.bits[3], result.bits[3]);
    }
    {
        s21_decimal dec1;
        dec1.bits[0] = 0b01010101001110101110101110110001;
        dec1.bits[1] = 0b00001101101101001101101001011111;
        dec1.bits[2] = 0b00000000000000000000000000000000;
        dec1.bits[3] = 0b00000000000100100000000000000000;
        s21_decimal res1;
        s21_floor(dec1, &res1);
        s21_decimal result;
        result.bits[0] = 0b00000000000000000000000000000000;
        result.bits[1] = 0b00000000000000000000000000000000;
        result.bits[2] = 0b00000000000000000000000000000000;
        result.bits[3] = 0b00000000000000000000000000000000;
        ck_assert_float_eq(res1.bits[0], result.bits[0]);
        ck_assert_float_eq(res1.bits[1], result.bits[1]);
        ck_assert_float_eq(res1.bits[2], result.bits[2]);
        ck_assert_float_eq(res1.bits[3], result.bits[3]);
    }
    {
        s21_decimal dec1;
        dec1.bits[0] = 0b10010111011100111001111111111111;
        dec1.bits[1] = 0b00111100000010000011000110001101;
        dec1.bits[2] = 0b00000000000000000000000000000001;
        dec1.bits[3] = 0b00000000000001110000000000000000;
        s21_decimal result;
        s21_floor(dec1, &result);
        s21_decimal result_origin;
        result_origin.bits[3] = 0;
        result_origin.bits[2] = 0;
        result_origin.bits[1] = 0b00000000000000000000001000010010;
        result_origin.bits[0] = 0b00110110101101101000110000111111;
        ck_assert_int_eq(result_origin.bits[3], result.bits[3]);
        ck_assert_int_eq(result_origin.bits[2], result.bits[2]);
        ck_assert_int_eq(result_origin.bits[1], result.bits[1]);
        ck_assert_int_eq(result_origin.bits[0], result.bits[0]);
    }
    {
        s21_decimal input = {{0, 0, 0, 0b00000000000011110000000000000000}};
        s21_decimal expected = {{0, 0, 0, 0b00000000000000000000000000000000}};
        s21_decimal result;
        s21_floor(input, &result);
        ASSERT_DECIMAL_EQ
    }
    {
        s21_decimal input = {{362732873, 0, 0, 0b10000000000000000000000000000000}};
        s21_decimal expected = {{362732873, 0, 0, 0b10000000000000000000000000000000}};
        s21_decimal result;
        s21_floor(input, &result);
        ASSERT_DECIMAL_EQ
    }
    {
        s21_decimal input = {{0xb54ac285, 0x9bde85, 0, 0b10000000000010000000000000000000}};
        s21_decimal expected = {{0x1a268849, 0, 0, 0b10000000000000000000000000000000}};
        s21_decimal result;
        s21_floor(input, &result);
        ASSERT_DECIMAL_EQ
    }
    {
        s21_decimal input = {{0x4C577A00, 0xC0D845D, 0, 0b00000000000010000000000000000000}};
        s21_decimal expected = {{0x5A9F2BA, 0x2, 0, 0b00000000000000000000000000000000}};
        s21_decimal result;
        s21_floor(input, &result);
        ASSERT_DECIMAL_EQ
    }
    {
        s21_decimal input = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0b10000000000111000000000000000000}};
        s21_decimal expected = {{8, 0, 0, 0b10000000000000000000000000000000}};
        s21_decimal result;
        s21_floor(input, &result);
        ASSERT_DECIMAL_EQ
    }
    {
        float val = 0.7922816251426433, res;
        s21_decimal dec_1, dec_2;
        s21_from_float_to_decimal(val, &dec_1);
        copy_full(&dec_2, &dec_1);
        s21_from_decimal_to_float(dec_2, &res);
        ck_assert_float_eq(val, res);
    }
    {
        float val = -0.7922816251426433, res;
        s21_decimal dec_1, dec_2;
        s21_from_float_to_decimal(val, &dec_1);
        copy_full(&dec_2, &dec_1);
        s21_from_decimal_to_float(dec_2, &res);
        ck_assert_float_eq(val, res);
    }
    {
        float val = 0.0000000000000001, res;
        s21_decimal dec_1, dec_2;
        s21_from_float_to_decimal(val, &dec_1);
        copy_full(&dec_2, &dec_1);
        s21_from_decimal_to_float(dec_2, &res);
        ck_assert_float_eq(val, res);
    }
    {
        float val = 10000000000000000.0, res;
        s21_decimal dec_1, dec_2;
        s21_from_float_to_decimal(val, &dec_1);
        copy_full(&dec_2, &dec_1);
        s21_from_decimal_to_float(dec_2, &res);
        ck_assert_float_eq(val, res);
    }
    {
        s21_decimal dec_1 = {{123456, 0, 0, 196608}};
        float res;
        s21_from_decimal_to_float(dec_1, &res);
        ck_assert_float_eq(res, 123.456);
    }
    {
        s21_decimal dec_1 = {{12345678, 0, 0, -2147155968}};
        float res;
        s21_from_decimal_to_float(dec_1, &res);
        ck_assert_float_eq(res, -123.45678);
    }
    {
        s21_decimal dec_1 = {{1, 0, 0, -2147418112}};
        float res;
        s21_from_decimal_to_float(dec_1, &res);
        ck_assert_float_eq(res, -0.1);
    }
    {
        s21_decimal dec_1;
        int i = -1;
        s21_from_int_to_decimal(i, &dec_1);
        ck_assert_int_eq(dec_1.bits[RARE], 1);
        ck_assert_int_eq(dec_1.bits[MEDIUM], 0);
        ck_assert_int_eq(dec_1.bits[WELL], 0);
        ck_assert_int_eq((unsigned int)dec_1.bits[DATA], (unsigned int)0b10000000000000000000000000000000);
    }
    {
        s21_decimal input1 = {{0x1, 0, 0, 0b10000000000011100000000000000000}};
        s21_decimal input2 = {{0x1, 0, 0, 0b10000000000011100000000000000000}};
        s21_decimal expected = {{0x1, 0, 0, 0b00000000000111000000000000000000}};
        s21_decimal result;
        int status = s21_mul(input1, input2, &result);
        ASSERT_DECIMAL_EQ
        ck_assert_int_eq(status, 0);
    }
    {
        s21_decimal input1 = {{0}};
        s21_decimal input2 = {{0xffffffff, 0, 0, 0b10000000000000100000000000000000}};
        s21_decimal expected = {{0, 0, 0, 0b10000000000000100000000000000000}};
        s21_decimal result;
        int status = s21_mul(input1, input2, &result);

        ASSERT_DECIMAL_EQ
        ck_assert_int_eq(status, 0);
    }
    {
        s21_decimal input1 = {{0x4fd9f63, 0xe4eeca, 0, 0b00000000000010000000000000000000}};
        s21_decimal input2 = {{0x64, 0, 0, 0b00000000000000000000000000000000}};
        s21_decimal expected = {{0xf31242ac, 0x596d46e9, 0, 0b00000000000010000000000000000000}};
        s21_decimal result;
        int status = s21_mul(input1, input2, &result);

        ASSERT_DECIMAL_EQ
        ck_assert_int_eq(status, 0);
    }
    {
        s21_decimal input1 = {{0x1, 0, 0, 0b10000000000111100000000000000000}};
        s21_decimal input2 = {{0x1, 0, 0, 0b10000000000011100000000000000000}};
        s21_decimal result;
        int status = s21_mul(input1, input2, &result);
        ck_assert_int_eq(status, 2);
    }
    {
        s21_decimal value_1 = {{max32bit, 0, 0, 0}};
        s21_decimal value_2 = {{max32bit, 100, 0, 0}};
        s21_decimal result = {{0}};
        s21_decimal correct_answer = {{0, 100, 0, 2147483648}};
        int function_returned = s21_sub(value_1, value_2, &result);

        ck_assert_uint_eq(function_returned, 0);
        ck_assert_uint_eq(result.bits[0], correct_answer.bits[0]);
        ck_assert_uint_eq(result.bits[1], correct_answer.bits[1]);
        ck_assert_uint_eq(result.bits[2], correct_answer.bits[2]);
        ck_assert_uint_eq(result.bits[3], correct_answer.bits[3]);
    }
    {
        s21_decimal value_1 = {{max32bit, 345634, 0, 2147876864}};
        s21_decimal value_2 = {{23465246, 45634, 0, 327680}};
        s21_decimal result = {{0}};
        s21_decimal correct_answer = {{234652459, 801975, 0, 2147876864}};
        int function_returned = s21_sub(value_1, value_2, &result);

        ck_assert_uint_eq(function_returned, 0);
        ck_assert_uint_eq(result.bits[0], correct_answer.bits[0]);
        ck_assert_uint_eq(result.bits[1], correct_answer.bits[1]);
        ck_assert_uint_eq(result.bits[2], correct_answer.bits[2]);
        ck_assert_uint_eq(result.bits[3], correct_answer.bits[3]);
    }
    {
        s21_decimal input1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0, 0b10000000000001100000000000000000}};
        s21_decimal input2 = {{1}};
        s21_decimal expected = {{0xFFFFFFFF, 0xFFFFFFFF, 0, 0b10000000000001100000000000000000}};
        s21_decimal result;
        int status = s21_mul(input1, input2, &result);

        ASSERT_DECIMAL_EQ
        ck_assert_int_eq(status, 0);
    }
    {
        s21_decimal input1 = {{0x4fd9f63, 0xe4eeca, 0, 0b00000000000010000000000000000000}};
        s21_decimal input2 = {{0x64, 0, 0, 0b00000000000000000000000000000000}};
        s21_decimal expected = {{0xf31242ac, 0x596d46e9, 0, 0b00000000000010000000000000000000}};
        s21_decimal result;
        int status = s21_mul(input1, input2, &result);

        ASSERT_DECIMAL_EQ
        ck_assert_int_eq(status, 0);
    }
    {
        s21_decimal dec1;
        s21_decimal dec2;
        int tmp1 = 100;
        int tmp2 = 2;
        int res_s21 = 0;
        float res = tmp1 % tmp2;
        s21_from_int_to_decimal(tmp1, &dec1);
        s21_from_int_to_decimal(tmp2, &dec2);
        s21_decimal res1;
        s21_mod(dec1, dec2, &res1);
        s21_from_decimal_to_int(res1, &res_s21);
        ck_assert_int_eq(res_s21, res);
    }
    {
        s21_decimal dec1;
        s21_decimal dec2;
        int tmp1 = -100;
        int tmp2 = 2;
        float res_s21 = 0;
        float res = tmp1 % tmp2;
        s21_from_int_to_decimal(tmp1, &dec1);
        s21_from_int_to_decimal(tmp2, &dec2);
        s21_decimal res1;
        s21_mod(dec1, dec2, &res1);
        s21_from_decimal_to_float(res1, &res_s21);
        ck_assert_float_eq(res_s21, res);
    }
    {
        s21_decimal dec1;
        s21_decimal dec2;
        int tmp1 = 100;
        int tmp2 = 99999;
        int res_s21 = 0;
        int res = -99899;
        s21_decimal res1;
        s21_from_int_to_decimal(tmp1, &dec1);
        s21_from_int_to_decimal(tmp2, &dec2);
        s21_sub(dec1, dec2, &res1);
        s21_from_decimal_to_int(res1, &res_s21);
        ck_assert_int_eq(res_s21, res);
    }
    {
        s21_decimal dec1;
        s21_decimal dec2;
        int tmp1 = -100;
        int tmp2 = -99999;
        int res_s21 = 0;
        int res = 99899;
        s21_decimal res1;
        s21_from_int_to_decimal(tmp1, &dec1);
        s21_from_int_to_decimal(tmp2, &dec2);
        s21_sub(dec1, dec2, &res1);
        s21_from_decimal_to_int(res1, &res_s21);
        ck_assert_int_eq(res_s21, res);
    }
    {
        s21_decimal dec1;
        s21_decimal dec2;
        int tmp1 = -214748347;
        int tmp2 = 217483647;
        int res_s21 = 0;
        int res = -214748347 - 217483647;
        s21_from_int_to_decimal(tmp1, &dec1);
        s21_from_int_to_decimal(tmp2, &dec2);
        s21_decimal res1;
        s21_sub(dec1, dec2, &res1);
        s21_from_decimal_to_int(res1, &res_s21);
        ck_assert_int_eq(res_s21, res);
    }
    {
        s21_decimal dec1;
        s21_decimal dec2;
        int tmp1 = 214748347;
        int tmp2 = -217483647;
        int res_s21 = 0;
        int res = 214748347 - -217483647;
        s21_from_int_to_decimal(tmp1, &dec1);
        s21_from_int_to_decimal(tmp2, &dec2);
        s21_decimal res1;
        s21_sub(dec1, dec2, &res1);
        s21_from_decimal_to_int(res1, &res_s21);
        ck_assert_int_eq(res_s21, res);
    }
    {
        s21_decimal dec1 = {{4294967295, 4294967295, 4294967295, 0}};
        s21_decimal dec2 = {{1, 0, 0, (unsigned int)pow(2, 31)}};
        s21_decimal res1;
        int ret_s21 = s21_sub(dec1, dec2, &res1);
        ck_assert_int_eq(1, ret_s21);
    }
    {
        s21_decimal dec1 = {{101, 0, 0, 0b10000000000000100000000000000000}};   // -1.01
        s21_decimal dec2 = {{1021, 0, 0, 0b00000000000000100000000000000000}};  // 10.21
        s21_decimal res1;
        s21_sub(dec1, dec2, &res1);
        float g;
        s21_from_decimal_to_float(res1, &g);
        ck_assert_float_eq(g, -11.22);
    }
    {
        s21_decimal dec1 = {{101, 0, 0, 0b00000000000000100000000000000000}};   // 1.01
        s21_decimal dec2 = {{1021, 0, 0, 0b10000000000000100000000000000000}};  // -10.21
        s21_decimal res1;
        s21_sub(dec1, dec2, &res1);
        float g;
        s21_from_decimal_to_float(res1, &g);
        ck_assert_float_eq(g, 11.22);
    }
    {
        s21_decimal input = {{0, 0, 0, 0b00000000000011110000000000000000}};
        s21_decimal expected = {{0}};
        s21_decimal result;
        s21_round(input, &result);
        ASSERT_DECIMAL_EQ
    }
    {
        s21_decimal input = {{362732873, 0, 0, 0b10000000000000000000000000000000}};
        s21_decimal expected = {{362732873, 0, 0, 0b10000000000000000000000000000000}};
        s21_decimal result;
        s21_round(input, &result);
        ASSERT_DECIMAL_EQ
    }
    {
        s21_decimal input = {{45, 0, 0, 0b00000000000000010000000000000000}};
        s21_decimal expected = {{5, 0, 0, 0}};
        s21_decimal result;
        s21_round(input, &result);
        ASSERT_DECIMAL_EQ
    }
    {
        s21_decimal input = {{0xb54ac285, 0x9bde85, 0, 0b10000000000010000000000000000000}};
        s21_decimal expected = {{0x1a268848, 0, 0, 0b10000000000000000000000000000000}};
        s21_decimal result;
        s21_round(input, &result);
        ASSERT_DECIMAL_EQ
    }
    {
        s21_decimal input = {{0x4C577A00, 0xC0D845D, 0, 0b00000000000010000000000000000000}};
        s21_decimal expected = {{0x5A9F2BA, 0x2, 0, 0b00000000000000000000000000000000}};
        s21_decimal result;
        s21_round(input, &result);
        ASSERT_DECIMAL_EQ
    }
    {
        s21_decimal value_1 = {{max32bit, 0, 0, 327680}};
        s21_decimal value_2 = {{max32bit, 100, 0, 2148139008}};
        s21_decimal result = {{0}};
        s21_decimal correct_answer = {{4294867297, 99898, 0, 655360}};
        int function_returned = s21_add(value_1, value_2, &result);

        ck_assert_uint_eq(function_returned, 0);
        ck_assert_uint_eq(result.bits[0], correct_answer.bits[0]);
        ck_assert_uint_eq(result.bits[1], correct_answer.bits[1]);
        ck_assert_uint_eq(result.bits[2], correct_answer.bits[2]);
        ck_assert_uint_eq(result.bits[3], correct_answer.bits[3]);
    }
    {
        s21_decimal value_1 = {{max32bit, 0, 0, 327680}};
        s21_decimal value_2 = {{max32bit, 100, 0, 2148139008}};
        s21_decimal result = {{0}};
        s21_decimal correct_answer = {{4294867297, 99898, 0, 655360}};
        int function_returned = s21_add(value_1, value_2, &result);

        ck_assert_uint_eq(function_returned, 0);
        ck_assert_uint_eq(result.bits[0], correct_answer.bits[0]);
        ck_assert_uint_eq(result.bits[1], correct_answer.bits[1]);
        ck_assert_uint_eq(result.bits[2], correct_answer.bits[2]);
        ck_assert_uint_eq(result.bits[3], correct_answer.bits[3]);
    }
    {
        s21_decimal value_1 = {{max32bit, 613566756, 0, 2147811328}};
        s21_decimal value_2 = {{max32bit, 214748364, 0, 2147745792}};
        s21_decimal result = {{0}};
        s21_decimal correct_answer = {{4294967285, 2761050406, 0, 2147811328}};
        int function_returned = s21_add(value_1, value_2, &result);

        ck_assert_uint_eq(function_returned, 0);
        ck_assert_uint_eq(result.bits[0], correct_answer.bits[0]);
        ck_assert_uint_eq(result.bits[1], correct_answer.bits[1]);
        ck_assert_uint_eq(result.bits[2], correct_answer.bits[2]);
        ck_assert_uint_eq(result.bits[3], correct_answer.bits[3]);
    }

    {
        s21_decimal value_1 = {{55555, 0, 0, 0}};
        s21_decimal value_2 = {{66666, 0, 0, 262144}};
        s21_decimal result = {{0}};
        s21_decimal correct_answer = {{22222, 0, 0, 262144}};
        int function_returned = s21_mod(value_1, value_2, &result);

        ck_assert_uint_eq(function_returned, 0);
        ck_assert_uint_eq(result.bits[0], correct_answer.bits[0]);
        ck_assert_uint_eq(result.bits[1], correct_answer.bits[1]);
        ck_assert_uint_eq(result.bits[2], correct_answer.bits[2]);
        ck_assert_uint_eq(result.bits[3], correct_answer.bits[3]);
    }
    {
        s21_decimal value_1 = {{5555, 345635, 0, 327680}};
        s21_decimal value_2 = {{333333333, 56765, 0, 458752}};
        s21_decimal result = {{0}};
        s21_decimal correct_answer = {{3492319244, 50332, 0, 458752}};
        int function_returned = s21_mod(value_1, value_2, &result);

        ck_assert_uint_eq(function_returned, 0);
        ck_assert_uint_eq(result.bits[0], correct_answer.bits[0]);
        ck_assert_uint_eq(result.bits[1], correct_answer.bits[1]);
        ck_assert_uint_eq(result.bits[2], correct_answer.bits[2]);
        ck_assert_uint_eq(result.bits[3], correct_answer.bits[3]);
    }
    {
        s21_decimal value_1 = {{5555, 345635, 3456, 786432}};
        s21_decimal value_2 = {{333333333, 56765, 4567, 1114112}};
        s21_decimal result = {{0}};
        s21_decimal correct_answer = {{565121299, 203145210, 1416, 1114112}};
        int function_returned = s21_mod(value_1, value_2, &result);

        ck_assert_uint_eq(function_returned, 0);
        ck_assert_uint_eq(result.bits[0], correct_answer.bits[0]);
        ck_assert_uint_eq(result.bits[1], correct_answer.bits[1]);
        ck_assert_uint_eq(result.bits[2], correct_answer.bits[2]);
        ck_assert_uint_eq(result.bits[3], correct_answer.bits[3]);
    }
    {
        s21_decimal value_1 = {{0, 0, 0, 786432}};
        s21_decimal value_2 = {{2452, 45646, 4564, 1114112}};
        s21_decimal result = {{0}};
        s21_decimal correct_answer = {{0, 0, 0, 786432}};
        int function_returned = s21_mod(value_1, value_2, &result);

        ck_assert_uint_eq(function_returned, 0);
        ck_assert_uint_eq(result.bits[0], correct_answer.bits[0]);
        ck_assert_uint_eq(result.bits[1], correct_answer.bits[1]);
        ck_assert_uint_eq(result.bits[2], correct_answer.bits[2]);
        ck_assert_uint_eq(result.bits[3], correct_answer.bits[3]);
    }
    {
        // 79228162514264337593543950335 * 1.1 = INF
        s21_decimal input1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
        s21_decimal input2 = {{11, 0, 0, 0b00000000000000010000000000000000}};
        s21_decimal result;
        int status = s21_mul(input1, input2, &result);

        ck_assert_int_eq(status, 1);
    }
    {
        // -79228162514264337593543950335 * 79228162514264337593543950335 = -INF
        s21_decimal input1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0b10000000000000000000000000000000}};
        s21_decimal input2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
        s21_decimal result;
        int status = s21_mul(input1, input2, &result);

        ck_assert_int_eq(status, 1);
    }
    {
        float val = 79228162514264337593543950336.0;
        s21_decimal dec_1;
        int res = s21_from_float_to_decimal(val, &dec_1);
        ck_assert_int_eq(res, 1);
    }
    {
        float val = -79228162514264337593543950336.0;
        s21_decimal dec_1;
        int res = s21_from_float_to_decimal(val, &dec_1);
        ck_assert_int_eq(res, 1);
    }
    {
        s21_decimal val;

        s21_from_float_to_decimal(0.03, &val);
        ck_assert_int_eq(val.bits[0], 3);
        ck_assert_int_eq(val.bits[1], 0);
        ck_assert_int_eq(val.bits[2], 0);

        s21_from_float_to_decimal(127.1234, &val);
        ck_assert_int_eq(val.bits[0], 1271234);
        ck_assert_int_eq(val.bits[1], 0);
        ck_assert_int_eq(val.bits[2], 0);
    }
    {
        s21_decimal val;
        s21_from_float_to_decimal(-2.1474836E+09, &val);
        ck_assert_int_eq(val.bits[0], -2147483648);
        ck_assert_int_eq(val.bits[1], 0);
        ck_assert_int_eq(val.bits[2], 0);
        ck_assert_int_eq(val.bits[3], -2147483648);
    }
    {
        s21_decimal val;
        s21_from_float_to_decimal(22.14836E+03, &val);
        ck_assert_int_eq(val.bits[0], 2214836);
        ck_assert_int_eq(val.bits[1], 0);
        ck_assert_int_eq(val.bits[2], 0);
        ck_assert_int_eq(val.bits[3], 131072);
    }
    {
        s21_decimal val;
        s21_from_float_to_decimal(1.02E+09, &val);
        ck_assert_int_eq(val.bits[0], 1020000000);
        ck_assert_int_eq(val.bits[1], 0);
        ck_assert_int_eq(val.bits[2], 0);
        ck_assert_int_eq(val.bits[3], 0);
    }
    {
        s21_decimal val;
        s21_from_float_to_decimal(-333.2222, &val);
        ck_assert_int_eq(val.bits[0], 3332222);
        ck_assert_int_eq(val.bits[1], 0);
        ck_assert_int_eq(val.bits[2], 0);
        ck_assert_int_eq(val.bits[3], -2147221504);
    }
    {
        s21_decimal src1, src2;
        int a = -32768;
        int b = 32768;
        int res_our_dec = 0;
        s21_from_int_to_decimal(a, &src1);
        s21_from_int_to_decimal(b, &src2);
        int res_origin = -1073741824;
        s21_decimal res_od;
        s21_mul(src1, src2, &res_od);
        s21_from_decimal_to_int(res_od, &res_our_dec);
        ck_assert_int_eq(res_our_dec, res_origin);
    }
    {
        s21_decimal src1, src2;
        int a = -32768;
        int b = 2;
        int res_our_dec = 0;
        s21_from_int_to_decimal(a, &src1);
        s21_from_int_to_decimal(b, &src2);
        int res_origin = -65536;
        s21_decimal res_od;
        s21_mul(src1, src2, &res_od);
        s21_from_decimal_to_int(res_od, &res_our_dec);
        ck_assert_int_eq(res_our_dec, res_origin);
    }
    {
        s21_decimal src1, src2;
        int a = -32768;
        int b = 32768;
        int res_our_dec = 0;
        s21_from_int_to_decimal(a, &src1);
        s21_from_int_to_decimal(b, &src2);
        int res_origin = -1073741824;
        s21_decimal res_od;
        s21_mul(src1, src2, &res_od);
        s21_from_decimal_to_int(res_od, &res_our_dec);
        ck_assert_int_eq(res_our_dec, res_origin);
    }
    {
        s21_decimal dec1 = {{101, 0, 0, 0b00000000000000100000000000000000}};  // 1.01

        s21_decimal dec2 = {{1021, 0, 0, 0b10000000000000100000000000000000}};  // -10.21

        s21_decimal res1;
        s21_add(dec1, dec2, &res1);
        float g;
        s21_from_decimal_to_float(res1, &g);
        ck_assert_float_eq(g, -9.2);
    }
    {
        s21_decimal dec1;
        s21_decimal dec2;
        int tmp1 = 100;
        int tmp2 = 99999;
        int res_s21 = 0;
        int res = -99899;
        s21_decimal res1;
        s21_from_int_to_decimal(tmp1, &dec1);
        s21_from_int_to_decimal(tmp2, &dec2);
        s21_sub(dec1, dec2, &res1);
        s21_from_decimal_to_int(res1, &res_s21);
        ck_assert_int_eq(res_s21, res);
    }
    {
        s21_decimal value_1 = {{max32bit, 0, 0, 327680}};
        s21_decimal value_2 = {{max32bit, 100, 0, 2148139008}};
        s21_decimal result = {{0}};
        s21_decimal correct_answer = {{4294867297, 99898, 0, 655360}};
        int function_returned = s21_add(value_1, value_2, &result);

        ck_assert_uint_eq(function_returned, 0);
        ck_assert_uint_eq(result.bits[0], correct_answer.bits[0]);
        ck_assert_uint_eq(result.bits[1], correct_answer.bits[1]);
        ck_assert_uint_eq(result.bits[2], correct_answer.bits[2]);
        ck_assert_uint_eq(result.bits[3], correct_answer.bits[3]);
    }
    {
        s21_decimal value_1 = {{max32bit, 613566756, 0, 2147811328}};
        s21_decimal value_2 = {{max32bit, 214748364, 0, 2147745792}};
        s21_decimal result = {{0}};
        s21_decimal correct_answer = {{4294967285, 2761050406, 0, 2147811328}};
        int function_returned = s21_add(value_1, value_2, &result);

        ck_assert_uint_eq(function_returned, 0);
        ck_assert_uint_eq(result.bits[0], correct_answer.bits[0]);
        ck_assert_uint_eq(result.bits[1], correct_answer.bits[1]);
        ck_assert_uint_eq(result.bits[2], correct_answer.bits[2]);
        ck_assert_uint_eq(result.bits[3], correct_answer.bits[3]);
    }
    {
        s21_decimal value_1 = {{4294967294, max32bit, max32bit, 0}};
        s21_decimal value_2 = {{15, 0, 0, 65536}};

        s21_decimal result = {{0}};
        s21_decimal correct_answer = {{0b11111111111111111111111111111111, 0b11111111111111111111111111111111,
                                       0b11111111111111111111111111111111, 0}};
        int function_returned = s21_add(value_1, value_2, &result);
        // 111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111110
        // 79228162514264337593543950334
        // 00000000000000000000000000001111
        // ст 1
        // 1,5
        ck_assert_uint_eq(function_returned, 0);
        ck_assert_uint_eq(result.bits[0], correct_answer.bits[0]);
        ck_assert_uint_eq(result.bits[1], correct_answer.bits[1]);
        ck_assert_uint_eq(result.bits[2], correct_answer.bits[2]);
        ck_assert_uint_eq(result.bits[3], correct_answer.bits[3]);
    }
    {
        //
        s21_decimal test_one;
        test_one.bits[RARE] = 0b11111111111111111111111111111110;
        test_one.bits[MEDIUM] = 0b11111111111111111111111111111111;
        test_one.bits[WELL] = 0b11111111111111111111111111111111;
        test_one.bits[DATA] = 0;
        s21_decimal test_two;
        test_two.bits[RARE] = 4;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b00000000000000010000000000000000;
        s21_decimal result;
        int error = s21_add(test_one, test_two, &result);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal src1, src2;
        int a = -1234;
        float b = 1.234;
        float res_our_dec = 0.0;
        s21_from_int_to_decimal(a, &src1);
        s21_from_float_to_decimal(b, &src2);
        float res_origin = -1232.766;
        s21_decimal res_od;
        s21_add(src1, src2, &res_od);
        s21_from_decimal_to_float(res_od, &res_our_dec);
        ck_assert_float_eq(res_our_dec, res_origin);
    }
    {
        s21_decimal src1, src2;
        int a = -1234;
        float b = -1.234;
        float res_our_dec = 0.0;
        s21_from_int_to_decimal(a, &src1);
        s21_from_float_to_decimal(b, &src2);
        float res_origin = -1235.234;
        s21_decimal res_od;
        s21_add(src1, src2, &res_od);
        s21_from_decimal_to_float(res_od, &res_our_dec);
        ck_assert_float_eq(res_our_dec, res_origin);
    }
    {
        s21_decimal src1, src2;
        float a = -1234;
        float b = -221.234;
        float res_our_dec = 0.0;
        s21_from_float_to_decimal(a, &src1);
        s21_from_float_to_decimal(b, &src2);
        float res_origin = -1455.234;
        s21_decimal res_od;
        s21_add(src1, src2, &res_od);
        s21_from_decimal_to_float(res_od, &res_our_dec);
        ck_assert_float_eq(res_our_dec, res_origin);
    }
    {
        s21_decimal src1, src2;
        int a = -1234;
        float b = -221.234;
        float res_our_dec = 0.0;
        s21_from_float_to_decimal(a, &src1);
        s21_from_float_to_decimal(b, &src2);
        float res_origin = -1455.234;
        s21_decimal res_od;
        s21_add(src1, src2, &res_od);
        s21_from_decimal_to_float(res_od, &res_our_dec);
        ck_assert_float_eq(res_our_dec, res_origin);
    }
    {
        s21_decimal src1, src2;
        float a = -9403;
        float b = 0.00234;
        float res_our_dec = 0.0;
        s21_from_float_to_decimal(a, &src1);
        s21_from_float_to_decimal(b, &src2);
        float res_origin = -9402.99766;
        s21_decimal res_od;
        s21_add(src1, src2, &res_od);
        s21_from_decimal_to_float(res_od, &res_our_dec);
        ck_assert_float_eq(res_our_dec, res_origin);
    }
    {
        s21_decimal src1, src2;
        int a = -9403;
        int b = 234;
        int res_our_dec = 0;
        s21_from_int_to_decimal(a, &src1);
        s21_from_int_to_decimal(b, &src2);
        int res_origin = -9169;
        s21_decimal res_od;
        s21_add(src1, src2, &res_od);
        s21_from_decimal_to_int(res_od, &res_our_dec);
        ck_assert_int_eq(res_our_dec, res_origin);
    }
    {
        s21_decimal src1, src2;
        float a = -940.3;
        float b = 0.000234;
        float res_our_dec = 0.0;
        s21_from_float_to_decimal(a, &src1);
        s21_from_float_to_decimal(b, &src2);
        float res_origin = -940.299766;
        s21_decimal res_od;
        s21_add(src1, src2, &res_od);
        s21_from_decimal_to_float(res_od, &res_our_dec);
        ck_assert_float_eq(res_our_dec, res_origin);
    }
    {
        s21_decimal src1, src2;
        float a = -0.9403;
        float b = 0.000234;
        float res_our_dec = 0.0;
        s21_from_float_to_decimal(a, &src1);
        s21_from_float_to_decimal(b, &src2);
        float res_origin = -0.940066;
        s21_decimal res_od;
        s21_add(src1, src2, &res_od);
        s21_from_decimal_to_float(res_od, &res_our_dec);
        ck_assert_float_eq(res_our_dec, res_origin);
    }
    {
        s21_decimal src1, src2;
        float a = -0.9403;
        float b = 2.0234;
        float res_our_dec = 0.0;
        s21_from_float_to_decimal(a, &src1);
        s21_from_float_to_decimal(b, &src2);
        float res_origin = 1.0831;
        s21_decimal res_od;
        s21_add(src1, src2, &res_od);
        s21_from_decimal_to_float(res_od, &res_our_dec);
        ck_assert_float_eq_tol(res_our_dec, res_origin, 0.01);
    }
    {
        s21_decimal src1, src2;
        float a = -0.9403;
        float b = -112.0234;
        float res_our_dec = 0.0;
        s21_from_float_to_decimal(a, &src1);
        s21_from_float_to_decimal(b, &src2);
        float res_origin = -112.9637;
        s21_decimal res_od;
        s21_add(src1, src2, &res_od);
        s21_from_decimal_to_float(res_od, &res_our_dec);
        ck_assert_float_eq(res_our_dec, res_origin);
    }
    {
        s21_decimal src1, src2;
        float a = -0.94e03;
        float b = -112.0234;
        float res_our_dec = 0.0;
        s21_from_float_to_decimal(a, &src1);
        s21_from_float_to_decimal(b, &src2);
        float res_origin = -1052.0234;
        s21_decimal res_od;
        s21_add(src1, src2, &res_od);
        s21_from_decimal_to_float(res_od, &res_our_dec);
        ck_assert_float_eq(res_our_dec, res_origin);
    }
    {
        s21_decimal src1, src2;
        float a = -0.94e03;
        float b = -112.0e2;
        float res_our_dec = 0.0;
        s21_from_float_to_decimal(a, &src1);
        s21_from_float_to_decimal(b, &src2);
        float res_origin = -12140;
        s21_decimal res_od;
        s21_add(src1, src2, &res_od);
        s21_from_decimal_to_float(res_od, &res_our_dec);
        ck_assert_float_eq(res_our_dec, res_origin);
    }
    {
        s21_decimal src1, src2;
        int a = 9403;
        int b = 202;
        int res_origin = 9605;
        int res_our_dec = 0;
        s21_from_int_to_decimal(a, &src1);
        s21_from_int_to_decimal(b, &src2);
        s21_decimal res_od;
        s21_add(src1, src2, &res_od);
        s21_from_decimal_to_int(res_od, &res_our_dec);
        ck_assert_int_eq(res_our_dec, res_origin);
    }
    {
        s21_decimal src1, src2;
        src1.bits[3] = 0x300000;
        src1.bits[2] = 0;
        src1.bits[1] = 0xF;
        src1.bits[0] = 0x67E4FEEF;
        src2.bits[3] = 0x300000;
        src2.bits[2] = 0;
        src2.bits[1] = 0xFF;
        src2.bits[0] = 0x67E4FFFF;
        s21_decimal result_origin;
        result_origin.bits[3] = 0x300000;
        result_origin.bits[2] = 0;
        result_origin.bits[1] = 0x10E;
        result_origin.bits[0] = 0xCFC9FEEE;
        s21_decimal result_our;
        s21_add(src1, src2, &result_our);
        ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
        ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
        ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
        ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
    }
    {
        s21_decimal src1, src2;
        src1.bits[3] = 0x30000;
        src1.bits[2] = 0;
        src1.bits[1] = 0xFF;
        src1.bits[0] = 0x67E4F;
        src2.bits[3] = 0x60000;
        src2.bits[2] = 0;
        src2.bits[1] = 0xEA;
        src2.bits[0] = 0x67E4F;
        s21_decimal result_origin;
        result_origin.bits[3] = 0x60000;
        result_origin.bits[2] = 0;
        result_origin.bits[1] = 0x3E502;
        result_origin.bits[0] = 0x1963E2E7;
        s21_decimal result_our;
        s21_add(src1, src2, &result_our);
        ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
        ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
        ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
        ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
    }
    {
        s21_decimal src1, src2;
        src1.bits[3] = 0x30000;
        src1.bits[2] = 0;
        src1.bits[1] = 0xFFFF;
        src1.bits[0] = 0xFF837E4F;
        src2.bits[3] = 0x80070000;
        src2.bits[2] = 0;
        src2.bits[1] = 0xFFF;
        src2.bits[0] = 0xFF837E4F;
        s21_decimal result_origin;
        result_origin.bits[3] = 0x70000;
        result_origin.bits[2] = 0;
        result_origin.bits[1] = 0x270FEFED;
        result_origin.bits[0] = 0x00F26FA1;
        s21_decimal result_our;
        s21_add(src1, src2, &result_our);
        ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
        ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
        ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
        ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
    }
    {
        s21_decimal value_1 = {{346456, 53345, 0, 2147942400}};
        s21_decimal value_2 = {{567567, 3456567, 0, 262144}};
        s21_decimal result = {{0}};
        s21_decimal correct_answer = {{567220544, 3456513655, 0, 458752}};
        int function_returned = s21_add(value_1, value_2, &result);

        ck_assert_uint_eq(function_returned, 0);
        ck_assert_uint_eq(result.bits[0], correct_answer.bits[0]);
        ck_assert_uint_eq(result.bits[1], correct_answer.bits[1]);
        ck_assert_uint_eq(result.bits[2], correct_answer.bits[2]);
        ck_assert_uint_eq(result.bits[3], correct_answer.bits[3]);
    }
    {
        s21_decimal dec1;
        s21_decimal dec2;
        float tmp1 = 1.2;
        float tmp2 = 0.25;
        float res_s21 = 0.0;
        float res = fmod(tmp1, tmp2);
        s21_from_float_to_decimal(tmp1, &dec1);
        s21_from_float_to_decimal(tmp2, &dec2);
        s21_decimal res1;
        s21_mod(dec1, dec2, &res1);
        s21_from_decimal_to_float(res1, &res_s21);
        ck_assert_float_eq_tol(res_s21, res, 6);
    }
    {
        s21_decimal dec1;
        s21_decimal dec2;
        float tmp1 = 1.2;
        float tmp2 = 0.2;
        float res_s21 = 0.0;
        float res = fmod(tmp1, tmp2);
        s21_from_float_to_decimal(tmp1, &dec1);
        s21_from_float_to_decimal(tmp2, &dec2);
        s21_decimal res1;
        s21_mod(dec1, dec2, &res1);
        s21_from_decimal_to_float(res1, &res_s21);
        ck_assert_float_eq_tol(res_s21, res, 6);
    }
    {
        s21_decimal dec1;
        s21_decimal dec2;
        int tmp1 = 99;
        int tmp2 = -2;
        int res_s21 = 0;
        float res = tmp1 % tmp2;
        s21_from_int_to_decimal(tmp1, &dec1);
        s21_from_int_to_decimal(tmp2, &dec2);
        s21_decimal res1;
        s21_mod(dec1, dec2, &res1);
        s21_from_decimal_to_int(res1, &res_s21);
        ck_assert_int_eq(res_s21, res);
    }
    {
        s21_decimal dec1;
        s21_decimal dec2;
        int tmp1 = -99;
        int tmp2 = -2;
        int res_s21 = 0;
        int res = tmp1 % tmp2;
        s21_from_int_to_decimal(tmp1, &dec1);
        s21_from_int_to_decimal(tmp2, &dec2);
        s21_decimal res1;
        s21_mod(dec1, dec2, &res1);
        s21_from_decimal_to_int(res1, &res_s21);
        ck_assert_int_eq(res_s21, res);
    }
}
END_TEST

START_TEST(s21_decimal_vsp_func) {
    {
        s21_long_decimal test = {{18345743, 0, 0, 0, 0, 0, 0}};
        ReduceDegreeLongDecimal(&test);
    }
    {
        // 100101011111100010110110001111
        // 49836589346589347658936458738256834756
        // 4983658998002778560781637442414388577
        s21_long_decimal test = {{0, 0, 0, 0, 0, 0, 0}};
        test.bits[0] = 0b00000111100000111111000011000100;
        test.bits[1] = 0b01011111011111000001000011110110;
        test.bits[2] = 0b11000010111000010111100001000111;
        test.bits[3] = 0b00100101011111100010110110001111;
        test.bits[4] = 0;
        test.bits[5] = 0;
        test.bits[6] = 0;
        ReduceDegreeLongDecimal(&test);
        //
        // 00000011101111111101000101011011111110011100001101011000101100111110111111110010110011100111101111000001010000010010010101100001
    }
    {
        // 28, 27
        int check_one = 0b00000000000111000000000000000000;
        int check_two = 0b00000000000110110000000000000000;
        int res = CheckFractionDecimal(check_one, check_two);
        ck_assert(res == 1);
    }
    {
        // 26, 25
        int check_one = 0b00000000000110100000000000000000;
        int check_two = 0b00000000000110010000000000000000;
        int res = CheckFractionDecimal(check_one, check_two);
        ck_assert(res == 1);
    }
    {
        // 24, 23
        int check_one = 0b00000000000110000000000000000000;
        int check_two = 0b00000000000101110000000000000000;
        int res = CheckFractionDecimal(check_one, check_two);
        ck_assert(res == 1);
    }
    {
        // 22, 21
        int check_one = 0b00000000000101100000000000000000;
        int check_two = 0b00000000000101010000000000000000;
        int res = CheckFractionDecimal(check_one, check_two);
        ck_assert(res == 1);
    }
    {
        // 20, 19
        int check_one = 0b00000000000101000000000000000000;
        int check_two = 0b00000000000100110000000000000000;
        int res = CheckFractionDecimal(check_one, check_two);
        ck_assert(res == 1);
    }
    {
        // 18, 17
        int check_one = 0b00000000000100100000000000000000;
        int check_two = 0b00000000000100010000000000000000;
        int res = CheckFractionDecimal(check_one, check_two);
        ck_assert(res == 1);
    }
    {
        // 16, 15
        int check_one = 0b00000000000100000000000000000000;
        int check_two = 0b00000000000011110000000000000000;
        int res = CheckFractionDecimal(check_one, check_two);
        ck_assert(res == 1);
    }
    {
        // 14, 13
        int check_one = 0b00000000000011100000000000000000;
        int check_two = 0b00000000000011010000000000000000;
        int res = CheckFractionDecimal(check_one, check_two);
        ck_assert(res == 1);
    }
    {
        // 12, 11
        int check_one = 0b00000000000011000000000000000000;
        int check_two = 0b00000000000010110000000000000000;
        int res = CheckFractionDecimal(check_one, check_two);
        ck_assert(res == 1);
    }
    {
        // 10, 9
        int check_one = 0b00000000000010100000000000000000;
        int check_two = 0b00000000000010010000000000000000;
        int res = CheckFractionDecimal(check_one, check_two);
        ck_assert(res == 1);
    }
    {
        // 8, 7
        int check_one = 0b00000000000010000000000000000000;
        int check_two = 0b00000000000001110000000000000000;
        int res = CheckFractionDecimal(check_one, check_two);
        ck_assert(res == 1);
    }
    {
        // 6, 5
        int check_one = 0b00000000000001100000000000000000;
        int check_two = 0b00000000000001010000000000000000;
        int res = CheckFractionDecimal(check_one, check_two);
        ck_assert(res == 1);
    }
    {
        // 4, 3
        int check_one = 0b00000000000001000000000000000000;
        int check_two = 0b00000000000000110000000000000000;
        int res = CheckFractionDecimal(check_one, check_two);
        ck_assert(res == 1);
    }
    {
        // 2, 1
        int check_one = 0b00000000000000100000000000000000;
        int check_two = 0b00000000000000010000000000000000;
        int res = CheckFractionDecimal(check_one, check_two);
        ck_assert(res == 1);
    }
    {
        // 1, 0
        int check_one = 0b00000000000000010000000000000000;
        int check_two = 0b00000000000000000000000000000000;
        int res = CheckFractionDecimal(check_one, check_two);
        ck_assert(res == 1);
    }
    {
        // 4, 4
        int check_one = 0b00000000000001000000000000000000;
        int check_two = 0b00000000000001000000000000000000;
        int res = CheckFractionDecimal(check_one, check_two);
        ck_assert(res == 0);
    }
    {
        // 0, 0
        int check_one = 0b00000000000000000000000000000000;
        int check_two = 0b00000000000000000000000000000000;
        int res = CheckFractionDecimal(check_one, check_two);
        ck_assert(res == 0);
    }
    {
        s21_decimal test;
        test.bits[RARE] = 0b00000000000000000000000000000001;
        test.bits[MEDIUM] = 0b00000000000000000000000000000000;
        test.bits[WELL] = 0b00000000000000000000000000000000;
        test.bits[DATA] = 0b00000000000000000000000000000000;
        int check = ShiftLeft(&test);
        ck_assert(test.bits[RARE] == 0b00000000000000000000000000000010);
        ck_assert(test.bits[MEDIUM] == 0b00000000000000000000000000000000);
        ck_assert(test.bits[WELL] == 0b00000000000000000000000000000000);
        ck_assert(test.bits[DATA] == 0b00000000000000000000000000000000);
        ck_assert(check == 1);
    }
    {
        s21_decimal test;
        test.bits[RARE] = 0b11111111111111111111111111111111;
        test.bits[MEDIUM] = 0b00000000000000000000000000000000;
        test.bits[WELL] = 0b00000000000000000000000000000000;
        test.bits[DATA] = 0b00000000000000000000000000000000;
        int check = ShiftLeft(&test);
        ck_assert(test.bits[RARE] == (int)0b11111111111111111111111111111110);
        ck_assert(test.bits[MEDIUM] == 0b00000000000000000000000000000001);
        ck_assert(test.bits[WELL] == 0b00000000000000000000000000000000);
        ck_assert(test.bits[DATA] == 0b00000000000000000000000000000000);
        ck_assert(check == 1);
    }
    {
        s21_decimal test;
        test.bits[RARE] = 0b10000000000000000000000000000001;
        test.bits[MEDIUM] = 0b00000000000000000000000000000000;
        test.bits[WELL] = 0b00000000000000000000000000000000;
        test.bits[DATA] = 0b00000000000000000000000000000000;
        int check = ShiftLeft(&test);
        ck_assert(test.bits[RARE] == 0b00000000000000000000000000000010);
        ck_assert(test.bits[MEDIUM] == 0b00000000000000000000000000000001);
        ck_assert(test.bits[WELL] == 0b00000000000000000000000000000000);
        ck_assert(test.bits[DATA] == 0b00000000000000000000000000000000);
        ck_assert(check == 1);
    }
    {
        s21_decimal test;
        test.bits[RARE] = 0b11111111111111111111111111111111;
        test.bits[MEDIUM] = 0b11111111111111111111111111111111;
        test.bits[WELL] = 0b00000000000000000000000000000000;
        test.bits[DATA] = 0b00000000000000000000000000000000;
        int check = ShiftLeft(&test);
        ck_assert(test.bits[RARE] == (int)0b11111111111111111111111111111110);
        ck_assert(test.bits[MEDIUM] == (int)0b11111111111111111111111111111111);
        ck_assert(test.bits[WELL] == 0b00000000000000000000000000000001);
        ck_assert(test.bits[DATA] == 0b00000000000000000000000000000000);
        ck_assert(check == 1);
    }
    {
        s21_decimal test;
        test.bits[RARE] = 0b10000000000000000000000000000001;
        test.bits[MEDIUM] = 0b10000000000000000000000000000001;
        test.bits[WELL] = 0b00000000000000000000000000000000;
        test.bits[DATA] = 0b00000000000000000000000000000000;
        int check = ShiftLeft(&test);
        ck_assert(test.bits[RARE] == 0b00000000000000000000000000000010);
        ck_assert(test.bits[MEDIUM] == 0b00000000000000000000000000000011);
        ck_assert(test.bits[WELL] == 0b00000000000000000000000000000001);
        ck_assert(test.bits[DATA] == 0b00000000000000000000000000000000);
        ck_assert(check == 1);
    }
    {
        s21_decimal test;
        test.bits[RARE] = 0b11111111111111111111111111111111;
        test.bits[MEDIUM] = 0b11111111111111111111111111111111;
        test.bits[WELL] = 0b01111111111111111111111111111111;
        test.bits[DATA] = 0b00000000000000000000000000000000;
        int check = ShiftLeft(&test);
        ck_assert(test.bits[RARE] == (int)0b11111111111111111111111111111110);
        ck_assert(test.bits[MEDIUM] == (int)0b11111111111111111111111111111111);
        ck_assert(test.bits[WELL] == (int)0b11111111111111111111111111111111);
        ck_assert(test.bits[DATA] == 0b00000000000000000000000000000000);
        ck_assert(check == 1);
    }
    {
        s21_decimal test;
        test.bits[RARE] = 0b00000000000000000000000000000010;
        test.bits[MEDIUM] = 0b00000000000000000000000000000010;
        test.bits[WELL] = 0b11111111111111111111111111111111;
        test.bits[DATA] = 0b00000000000000000000000000000000;
        int check = ShiftLeft(&test);
        ck_assert(test.bits[RARE] == (int)0b00000000000000000000000000000010);
        ck_assert(test.bits[MEDIUM] == (int)0b00000000000000000000000000000010);
        ck_assert(test.bits[WELL] == (int)0b11111111111111111111111111111111);
        ck_assert(test.bits[DATA] == 0b00000000000000000000000000000000);
        ck_assert(check == 0);
    }
    {
        s21_decimal test;
        test.bits[RARE] = 0b00010000110001000001011000000000;
        test.bits[MEDIUM] = 0b10001001001000110000011100001001;
        test.bits[WELL] = 0b00011110011100001000100010010000;
        test.bits[DATA] = 0b00000000000000000000000000000000;
        int check = ShiftLeft(&test);
        ck_assert(test.bits[RARE] == 0b00100001100010000010110000000000);
        ck_assert(test.bits[MEDIUM] == 0b00010010010001100000111000010010);
        ck_assert(test.bits[WELL] == 0b00111100111000010001000100100001);
        ck_assert(test.bits[DATA] == 0b00000000000000000000000000000000);
        ck_assert(check == 1);
    }
    {
        s21_decimal test;
        test.bits[RARE] = 0b00010000110001000001011000000000;
        test.bits[MEDIUM] = 0b10001001001000110000011100001001;
        test.bits[WELL] = 0b10011110011100001000100010010000;
        test.bits[DATA] = 0b00000000000000000000000000000000;
        int check = ShiftLeft(&test);
        ck_assert(test.bits[RARE] == 0b00010000110001000001011000000000);
        ck_assert(test.bits[MEDIUM] == (int)0b10001001001000110000011100001001);
        ck_assert(test.bits[WELL] == (int)0b10011110011100001000100010010000);
        ck_assert(test.bits[DATA] == 0b00000000000000000000000000000000);
        ck_assert(check == 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00000000000000000000000000011011;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b10000000000000000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b00000000000000000000000100010010;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b00000000000000010000000000000000;
        EqualizeDecimal(&test_one, &test_two);
        ck_assert(test_one.bits[RARE] == 0b00000000000000000000000100001110);
        ck_assert(test_one.bits[MEDIUM] == 0);
        ck_assert(test_one.bits[WELL] == 0);
        ck_assert(test_one.bits[DATA] == (int)0b10000000000000010000000000000000);
        ck_assert(test_two.bits[RARE] == 0b00000000000000000000000100010010);
        ck_assert(test_two.bits[MEDIUM] == 0);
        ck_assert(test_two.bits[WELL] == 0);
        ck_assert(test_two.bits[DATA] == 0b00000000000000010000000000000000);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00000000000000000000000000011011;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b00000000111000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b00000000000000000000000100010010;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b10000000000110100000000000000000;
        EqualizeDecimal(&test_one, &test_two);
        ck_assert(test_one.bits[RARE] == 0b00000000000000000000000000011011);
        ck_assert(test_one.bits[MEDIUM] == 0);
        ck_assert(test_one.bits[WELL] == 0);
        ck_assert(test_one.bits[DATA] == 0b00000000111000000000000000000);
        ck_assert(test_two.bits[RARE] == 0b00000000000000000110101100001000);
        ck_assert(test_two.bits[MEDIUM] == 0);
        ck_assert(test_two.bits[WELL] == 0);
        ck_assert(test_two.bits[DATA] == (int)0b10000000000111000000000000000000);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00000000000000000000000000011011;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0;
        s21_decimal test_two;
        test_two.bits[RARE] = 0;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0;
        EqualizeDecimal(&test_one, &test_two);
        ck_assert(test_one.bits[RARE] == 0b00000000000000000000000000011011);
        ck_assert(test_one.bits[MEDIUM] == 0);
        ck_assert(test_one.bits[WELL] == 0);
        ck_assert(test_one.bits[DATA] == 0);
        ck_assert(test_two.bits[RARE] == 0);
        ck_assert(test_two.bits[MEDIUM] == 0);
        ck_assert(test_two.bits[WELL] == 0);
        ck_assert(test_two.bits[DATA] == 0);
    }
    {
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00000000100000010100100100001111;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b00000000000001000000000000000000;
        s21_decimal test_two;
        test_two.bits[RARE] = 0b0000000000000000010100101011111000;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b00000000000000100000000000000000;
        EqualizeDecimal(&test_one, &test_two);
        ck_assert(test_one.bits[RARE] == 0b00000000100000010100100100001111);
        ck_assert(test_one.bits[MEDIUM] == 0);
        ck_assert(test_one.bits[WELL] == 0);
        ck_assert(test_one.bits[DATA] == 0b00000000000001000000000000000000);
        ck_assert(test_two.bits[RARE] == 0b00000000100000010100100011100000);
        ck_assert(test_two.bits[MEDIUM] == 0);
        ck_assert(test_two.bits[WELL] == 0);
        ck_assert(test_two.bits[DATA] == 0b00000000000001000000000000000000);
    }
    {
        // 265 - 6
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00000000000000000000000100001001;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b00000000000001100000000000000000;
        // 789
        s21_decimal test_two;
        test_two.bits[RARE] = 0b00000000000000000000001100010101;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0;
        EqualizeDecimal(&test_one, &test_two);
        ck_assert(test_one.bits[RARE] == 0b00000000000000000000000100001001);
        ck_assert(test_one.bits[MEDIUM] == 0);
        ck_assert(test_one.bits[WELL] == 0);
        ck_assert(test_one.bits[DATA] == 0b00000000000001100000000000000000);
        ck_assert(test_two.bits[RARE] == 0b00101111000001110010111101000000);
        ck_assert(test_two.bits[MEDIUM] == 0);
        ck_assert(test_two.bits[WELL] == 0);
        ck_assert(test_two.bits[DATA] == 0b00000000000001100000000000000000);
    }
    {
        // 265 - 8
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00000000000000000000000100001001;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b00000000000010000000000000000000;
        // 789
        s21_decimal test_two;
        test_two.bits[RARE] = 0b00000000000000000000001100010101;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0;
        EqualizeDecimal(&test_one, &test_two);
        ck_assert(test_one.bits[RARE] == 0b00000000000000000000000100001001);
        ck_assert(test_one.bits[MEDIUM] == 0);
        ck_assert(test_one.bits[WELL] == 0);
        ck_assert(test_one.bits[DATA] == 0b00000000000010000000000000000000);
        ck_assert(test_two.bits[RARE] == 0b01011110110011100111010100000000);
        ck_assert(test_two.bits[MEDIUM] == 0b00000000000000000000000000010010);
        ck_assert(test_two.bits[WELL] == 0);
        ck_assert(test_two.bits[DATA] == 0b00000000000010000000000000000000);
    }
    {
        // 265 - 12
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00000000000000000000000100001001;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b00000000000011000000000000000000;
        // 789
        s21_decimal test_two;
        test_two.bits[RARE] = 0b00000000000000000000001100010101;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0;
        EqualizeDecimal(&test_one, &test_two);
        ck_assert(test_one.bits[RARE] == 0b00000000000000000000000100001001);
        ck_assert(test_one.bits[MEDIUM] == 0);
        ck_assert(test_one.bits[WELL] == 0);
        ck_assert(test_one.bits[DATA] == 0b00000000000011000000000000000000);
        ck_assert(test_two.bits[RARE] == 0b01100000101110100101000000000000);
        ck_assert(test_two.bits[MEDIUM] == 0b00000000000000101100110110010111);
        ck_assert(test_two.bits[WELL] == 0);
        ck_assert(test_two.bits[DATA] == 0b00000000000011000000000000000000);
    }
    {
        // 265 - 16
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00000000000000000000000100001001;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b00000000000100000000000000000000;
        // 789
        s21_decimal test_two;
        test_two.bits[RARE] = 0b00000000000000000000001100010101;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0;
        EqualizeDecimal(&test_one, &test_two);
        ck_assert(test_one.bits[RARE] == 0b00000000000000000000000100001001);
        ck_assert(test_one.bits[MEDIUM] == 0);
        ck_assert(test_one.bits[WELL] == 0);
        ck_assert(test_one.bits[DATA] == 0b00000000000100000000000000000000);
        ck_assert(test_two.bits[RARE] == 0b001101101110101010000000000000000);
        ck_assert(test_two.bits[MEDIUM] == 0b01101101011111101110100100110010);
        ck_assert(test_two.bits[WELL] == 0);
        ck_assert(test_two.bits[DATA] == 0b00000000000100000000000000000000);
    }
    {
        // 265 - 20
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00000000000000000000000100001001;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b00000000000101000000000000000000;
        // 789
        s21_decimal test_two;
        test_two.bits[RARE] = 0b00000000000000000000001100010101;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0;
        EqualizeDecimal(&test_one, &test_two);
        ck_assert(test_one.bits[RARE] == 0b00000000000000000000000100001001);
        ck_assert(test_one.bits[MEDIUM] == 0);
        ck_assert(test_one.bits[WELL] == 0);
        ck_assert(test_one.bits[DATA] == 0b00000000000101000000000000000000);
        ck_assert(test_two.bits[RARE] == 0b01010000010100000000000000000000);
        ck_assert(test_two.bits[MEDIUM] == 0b00101101011101010100000111100010);
        ck_assert(test_two.bits[WELL] == 0b00000000000000000001000010110101);
        ck_assert(test_two.bits[DATA] == 0b00000000000101000000000000000000);
    }
    {
        // 265 - 8
        s21_decimal test_one;
        test_one.bits[RARE] = 0b00000000000000000000000100001001;
        test_one.bits[MEDIUM] = 0;
        test_one.bits[WELL] = 0;
        test_one.bits[DATA] = 0b00000000000010000000000000000000;
        // 789 - 4
        s21_decimal test_two;
        test_two.bits[RARE] = 0b00000000000000000000001100010101;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b00000000000001000000000000000000;
        EqualizeDecimal(&test_one, &test_two);
        ck_assert(test_one.bits[RARE] == 0b00000000000000000000000100001001);
        ck_assert(test_one.bits[MEDIUM] == 0);
        ck_assert(test_one.bits[WELL] == 0);
        ck_assert(test_one.bits[DATA] == 0b00000000000010000000000000000000);
        ck_assert(test_two.bits[RARE] == 0b00000000011110000110010001010000);
        ck_assert(test_two.bits[MEDIUM] == 0);
        ck_assert(test_two.bits[WELL] == 0);
        ck_assert(test_two.bits[DATA] == 0b00000000000010000000000000000000);
    }
    {
        // 5673828563284239023423532 - 14
        s21_decimal test_one;
        test_one.bits[RARE] = 0b10111101101000010100000000101100;
        test_one.bits[MEDIUM] = 0b11011100110110111111001011101011;
        test_one.bits[WELL] = 0b00000000000001001011000101111010;
        test_one.bits[DATA] = 0b00000000000011100000000000000000;
        // 32534 - 5
        s21_decimal test_two;
        test_two.bits[RARE] = 0b00000000000000000111111100010110;
        test_two.bits[MEDIUM] = 0;
        test_two.bits[WELL] = 0;
        test_two.bits[DATA] = 0b00000000000001010000000000000000;
        EqualizeDecimal(&test_one, &test_two);
        ck_assert(test_one.bits[RARE] == (int)0b10111101101000010100000000101100);
        ck_assert(test_one.bits[MEDIUM] == (int)0b11011100110110111111001011101011);
        ck_assert(test_one.bits[WELL] == 0b00000000000001001011000101111010);
        ck_assert(test_one.bits[DATA] == 0b00000000000011100000000000000000);
        ck_assert(test_two.bits[RARE] == (int)0b11101001100000110101110000000000);
        ck_assert(test_two.bits[MEDIUM] == 0b00000000000000000001110110010110);
        ck_assert(test_two.bits[WELL] == 0);
        ck_assert(test_two.bits[DATA] == 0b00000000000011100000000000000000);
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
        EqualizeDecimal(&test_one, &test_two);
        ck_assert_int_eq(test_two.bits[RARE], (int)0b11010001111100011111011000000000);
        ck_assert_int_eq(test_two.bits[MEDIUM], 0b00000000000000010010011111100101);
        ck_assert_int_eq(test_two.bits[WELL], 0);
        ck_assert_int_eq(test_two.bits[DATA], 0b00000000000011100000000000000000);
    }
    {
        s21_decimal dec1;
        dec1.bits[0] = 0b01100011000011111111111111111111;
        dec1.bits[1] = 0b01101011110001110101111000101101;
        dec1.bits[2] = 0b00000000000000000000000000000101;
        dec1.bits[3] = 0b10000000000010100000000000000000;
        s21_decimal result;
        result.bits[0] = 0b01010100000010111110010000000000;
        result.bits[1] = 0b00000000000000000000000000000010;
        result.bits[2] = 0b00000000000000000000000000000000;
        result.bits[3] = 0b10000000000000000000000000000000;
        s21_decimal res1;
        s21_round(dec1, &res1);
        ck_assert_float_eq(res1.bits[0], result.bits[0]);
        ck_assert_float_eq(res1.bits[1], result.bits[1]);
        ck_assert_float_eq(res1.bits[2], result.bits[2]);
        ck_assert_float_eq(res1.bits[3], result.bits[3]);
    }
    {
        s21_decimal dec1;
        dec1.bits[0] = 0b01010101001110101110101110110001;
        dec1.bits[1] = 0b00001101101101001101101001011111;
        dec1.bits[2] = 0b00000000000000000000000000000000;
        dec1.bits[3] = 0b10000000000100100000000000000000;
        s21_decimal result;
        result.bits[0] = 0b00000000000000000000000000000001;
        result.bits[1] = 0b00000000000000000000000000000000;
        result.bits[2] = 0b00000000000000000000000000000000;
        result.bits[3] = 0b10000000000000000000000000000000;
        s21_decimal res1;
        s21_round(dec1, &res1);
        ck_assert_float_eq(res1.bits[0], result.bits[0]);
        ck_assert_float_eq(res1.bits[1], result.bits[1]);
        ck_assert_float_eq(res1.bits[2], result.bits[2]);
        ck_assert_float_eq(res1.bits[3], result.bits[3]);
    }
    {
        s21_decimal dec1;
        dec1.bits[0] = 0b10010011111100000001110001010010;
        dec1.bits[1] = 0b00000000000000000000000100100000;
        dec1.bits[2] = 0b00000000000000000000000000000000;
        dec1.bits[3] = 0b00000000000010100000000000000000;
        s21_decimal result;
        result.bits[0] = 0b00000000000000000000000001111100;
        result.bits[1] = 0b00000000000000000000000000000000;
        result.bits[2] = 0b00000000000000000000000000000000;
        result.bits[3] = 0b00000000000000000000000000000000;
        s21_decimal res1;
        s21_round(dec1, &res1);
        ck_assert_float_eq(res1.bits[0], result.bits[0]);
        ck_assert_float_eq(res1.bits[1], result.bits[1]);
        ck_assert_float_eq(res1.bits[2], result.bits[2]);
        ck_assert_float_eq(res1.bits[3], result.bits[3]);
    }
    {
        s21_decimal dec1;
        dec1.bits[0] = 0b11001101110001110111110001000000;
        dec1.bits[1] = 0b00111110001001010000001001100000;
        dec1.bits[2] = 0b00100000010011111100111001011110;
        dec1.bits[3] = 0b10000000000001000000000000000000;
        s21_decimal result;
        result.bits[0] = 0b10100000111111100100111000000100;
        result.bits[1] = 0b00011011110011101100110011101101;
        result.bits[2] = 0b00000000000000001101001111000010;
        result.bits[3] = 0b10000000000000000000000000000000;
        s21_decimal res1;
        s21_round(dec1, &res1);
        ck_assert_float_eq(res1.bits[0], result.bits[0]);
        ck_assert_float_eq(res1.bits[1], result.bits[1]);
        ck_assert_float_eq(res1.bits[2], result.bits[2]);
        ck_assert_float_eq(res1.bits[3], result.bits[3]);
    }
    {
        s21_decimal dec1;
        dec1.bits[0] = 0b10100000111111100100111000000100;
        dec1.bits[1] = 0b00011011110011101100110011101101;
        dec1.bits[2] = 0b00000000000000001101001111000010;
        dec1.bits[3] = 0b00000000000000000000000000000000;
        s21_decimal res1;
        s21_round(dec1, &res1);
        s21_decimal result;
        result.bits[0] = 0b10100000111111100100111000000100;
        result.bits[1] = 0b00011011110011101100110011101101;
        result.bits[2] = 0b00000000000000001101001111000010;
        result.bits[3] = 0b00000000000000000000000000000000;
        ck_assert_float_eq(res1.bits[0], result.bits[0]);
        ck_assert_float_eq(res1.bits[1], result.bits[1]);
        ck_assert_float_eq(res1.bits[2], result.bits[2]);
        ck_assert_float_eq(res1.bits[3], result.bits[3]);
    }
    {
        s21_decimal dec1;
        dec1.bits[0] = 0b10010111011100111001111111111111;
        dec1.bits[1] = 0b00111100000010000011000110001101;
        dec1.bits[2] = 0b00000000000000000000000000000001;
        dec1.bits[3] = 0b00000000000001110000000000000000;
        s21_decimal res1;
        s21_round(dec1, &res1);
        s21_decimal result;
        result.bits[3] = 0;
        result.bits[2] = 0;
        result.bits[1] = 0b00000000000000000000001000010010;
        result.bits[0] = 0b00110110101101101000110001000000;
        ck_assert_float_eq(res1.bits[0], result.bits[0]);
        ck_assert_float_eq(res1.bits[1], result.bits[1]);
        ck_assert_float_eq(res1.bits[2], result.bits[2]);
        ck_assert_float_eq(res1.bits[3], result.bits[3]);
    }
    {
        s21_decimal dec1;
        dec1.bits[0] = 0b10010111011100111001111111111111;
        dec1.bits[1] = 0b00111100000010000011000110001101;
        dec1.bits[2] = 0b00000000000000000000000000000001;
        dec1.bits[3] = 0b10000000000001110000000000000000;
        s21_decimal res1;
        s21_round(dec1, &res1);
        s21_decimal result;
        result.bits[3] = 0b10000000000000000000000000000000;
        result.bits[2] = 0;
        result.bits[1] = 0b00000000000000000000001000010010;
        result.bits[0] = 0b00110110101101101000110001000000;
        ck_assert_float_eq(res1.bits[0], result.bits[0]);
        ck_assert_float_eq(res1.bits[1], result.bits[1]);
        ck_assert_float_eq(res1.bits[2], result.bits[2]);
        ck_assert_float_eq(res1.bits[3], result.bits[3]);
    }
    {
        s21_decimal dec1;
        dec1.bits[0] = 0b10010111011100111001111111111111;
        dec1.bits[1] = 0b00111100000010000011000110001101;
        dec1.bits[2] = 0b00000000000000000000000000000001;
        dec1.bits[3] = 0b10000000000001110000000000000000;
        s21_decimal res1;
        s21_round(dec1, &res1);
        s21_decimal result;
        result.bits[3] = 0b10000000000000000000000000000000;
        result.bits[2] = 0;
        result.bits[1] = 0b00000000000000000000001000010010;
        result.bits[0] = 0b00110110101101101000110001000000;
        ck_assert_float_eq(res1.bits[0], result.bits[0]);
        ck_assert_float_eq(res1.bits[1], result.bits[1]);
        ck_assert_float_eq(res1.bits[2], result.bits[2]);
        ck_assert_float_eq(res1.bits[3], result.bits[3]);
    }
    {
        s21_decimal dec1;
        s21_decimal dec2;
        int tmp1 = -100;
        int tmp2 = 2;
        float res_s21 = 0;
        float res = tmp1 % tmp2;
        s21_from_int_to_decimal(tmp1, &dec1);
        s21_from_int_to_decimal(tmp2, &dec2);
        s21_decimal res1;
        s21_mod(dec1, dec2, &res1);
        s21_from_decimal_to_float(res1, &res_s21);
        ck_assert_float_eq(res_s21, res);
    }
    {
        s21_decimal dec1;
        s21_decimal dec2 = {{0, 0, 0, 0}};
        float tmp1 = 1.2;
        float tmp2 = 0.0;
        s21_from_float_to_decimal(tmp1, &dec1);
        s21_from_float_to_decimal(tmp2, &dec2);
        s21_decimal res_d;
        int res = s21_mod(dec1, dec2, &res_d);
        ck_assert_int_eq(res, 3);
    }
}
END_TEST

START_TEST(s21_decimal_other_func) {
    {
        int a = -11;
        int res_a = 0;
        s21_decimal test;
        s21_decimal res;
        s21_from_int_to_decimal(a, &test);
        int error = s21_negate(test, &res);
        s21_from_decimal_to_int(res, &res_a);
        ck_assert_int_eq(11, res_a);
        ck_assert_int_eq(error, 0);
    }

    {
        int a = 11;
        int res_a = 0;
        s21_decimal test;
        s21_decimal res;
        s21_from_int_to_decimal(a, &test);
        int error = s21_negate(test, &res);
        s21_from_decimal_to_int(res, &res_a);
        ck_assert_int_eq(-11, res_a);
        ck_assert_int_eq(error, 0);
    }

    {
        int a = 0;
        int res_a = 0;
        s21_decimal test;
        s21_decimal res;
        s21_from_int_to_decimal(a, &test);
        int error = s21_negate(test, &res);
        s21_from_decimal_to_int(res, &res_a);
        ck_assert_int_eq(0, res_a);
        ck_assert_int_eq(error, 0);
    }

    {
        s21_decimal test;
        s21_decimal res;
        test.bits[RARE] = 0b00000000000000000000000000000001;
        test.bits[MEDIUM] = 0b00000000000000000000000000000000;
        test.bits[WELL] = 0b00000000000000000000000000000000;
        test.bits[DATA] = 0b00000000000010100000000000000000;
        int error = s21_negate(test, &res);
        ck_assert(res.bits[RARE] == 0b00000000000000000000000000000001);
        ck_assert(res.bits[MEDIUM] == 0b00000000000000000000000000000000);
        ck_assert(res.bits[WELL] == 0b00000000000000000000000000000000);
        ck_assert(res.bits[DATA] == (int)0b10000000000010100000000000000000);
        ck_assert_int_eq(error, 0);
    }

    {
        s21_decimal test;
        s21_decimal res;
        test.bits[RARE] = 0b00000000000000000000000000000001;
        test.bits[MEDIUM] = 0b00000000000000000000000000000000;
        test.bits[WELL] = 0b00000000000000000000000000000000;
        test.bits[DATA] = 0b10000000000000010000000000000000;
        int error = s21_negate(test, &res);
        ck_assert(res.bits[RARE] == 0b00000000000000000000000000000001);
        ck_assert(res.bits[MEDIUM] == 0b00000000000000000000000000000000);
        ck_assert(res.bits[WELL] == 0b00000000000000000000000000000000);
        ck_assert(res.bits[DATA] == 0b00000000000000010000000000000000);
        ck_assert_int_eq(error, 0);
    }
    {
        s21_decimal test;
        s21_from_int_to_decimal(0, &test);
        s21_negate(test, NULL);
        ck_assert_int_eq(test.bits[RARE], 0);
    }
}
END_TEST

int TestOther_func() {
    Suite *suite = suite_create("Other_func");
    TCase *getCase = tcase_create("Core");
    SRunner *runner = srunner_create(suite);
    int check = 0;

    //   puts("\e[32m");
    suite_add_tcase(suite, getCase);
    tcase_add_test(getCase, s21_decimal_vsp_func);
    tcase_add_test(getCase, taken_tests);
    tcase_add_test(getCase, s21_decimal_other_func);

    srunner_run_all(runner, CK_ENV);
    check = srunner_ntests_failed(runner);
    srunner_free(runner);
    return check;
}
