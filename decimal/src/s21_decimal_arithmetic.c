#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int error = 0;
    if (!result) {
        error = 1;
    } else {
        BufferForEqualizeDecimal(&value_1, &value_2);
        int sign = CheckSignForSummation(value_1, value_2);
        if (sign == 1 || sign == 0) {
            int check_overflow = 0;
            char buffer_decimal[264] = "";
            s21_long_decimal long_value_1 = {{0, 0, 0, 0, 0, 0, 0}};
            s21_long_decimal long_value_2 = {{0, 0, 0, 0, 0, 0, 0}};
            s21_long_decimal long_result = {{0, 0, 0, 0, 0, 0, 0}};
            from_s21_decimal_to_s21_long_decimal(value_1, &long_value_1);
            from_s21_decimal_to_s21_long_decimal(value_2, &long_value_2);
            from_s21_decimal_to_s21_long_decimal(*result, &long_result);
            check_overflow = SummationLongDecimal(long_value_1, long_value_2, buffer_decimal);
            if (!check_overflow && sign != -1) {
                int counter_reduse_scale = 0;
                s21_reverse_string(buffer_decimal, strlen(buffer_decimal));
                ConvertStringToLongDecimal(buffer_decimal, &long_result);
                s21_decimal buffer_result = {{0, 0, 0, 0}};
                check_overflow = from_s21_long_decimal_to_s21_decimal(long_result, &buffer_result);
                int check = 0;
                check = GetFractionStDecimal(value_2.bits[DATA]);
                if (check_overflow && check) {
                    for (; long_result.bits[3];) {
                        DivInTenLongDecimal(&long_result);
                        ++counter_reduse_scale;
                        if (check >= counter_reduse_scale) {
                            break;
                        }
                        break;
                    }
                }
                check_overflow = from_s21_long_decimal_to_s21_decimal(long_result, &buffer_result);
                if (!check_overflow) {
                    CleanDecimal(result);
                    *result = buffer_result;
                    result->bits[DATA] = value_1.bits[DATA];
                    if (counter_reduse_scale) {
                        int scale = GetFractionStDecimal(result->bits[DATA]) - counter_reduse_scale;
                        result->bits[DATA] = scale;
                        result->bits[DATA] <<= 16;
                    }
                    if (sign) {
                        result->bits[DATA] |= 0b10000000000000000000000000000000;
                    }
                }
            }
            error = check_overflow;
        } else if (sign == -1) {
            int sign_one = CheckLeftBit(value_1.bits[DATA]);
            int sign_two = CheckLeftBit(value_2.bits[DATA]);
            value_1.bits[DATA] &= 0b01111111111111111111111111111111;
            value_2.bits[DATA] &= 0b01111111111111111111111111111111;
            int size = s21_is_greater(value_1, value_2);
            error = s21_sub(value_1, value_2, result);
            if (sign_one && size) {
                result->bits[DATA] |= 0b10000000000000000000000000000000;
            } else if (sign_two && !size && !sign_one) {
                result->bits[DATA] |= 0b10000000000000000000000000000000;
            } else if (sign_one && !size && !sign_two) {
                result->bits[DATA] &= 0b01111111111111111111111111111111;
            }
        }
    }
    return error;
}

int s21_add_long_decimal(s21_long_decimal value_1, s21_long_decimal value_2, s21_long_decimal *result) {
    int error = 0;
    if (!result) {
        error = 0;
    } else {
        char buffer_decimal[264];
        int check_overflow = 0;
        check_overflow = SummationLongDecimal(value_1, value_2, buffer_decimal);
        if (!check_overflow) {
            s21_long_decimal long_result = {{0, 0, 0, 0, 0, 0, 0}};
            s21_reverse_string(buffer_decimal, strlen(buffer_decimal));
            ConvertStringToLongDecimal(buffer_decimal, &long_result);
            long_result.bits[6] = value_1.bits[6];
            *result = long_result;
        }
        error = check_overflow;
    }
    return error;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int error = 0;
    if (!result) {
        error = 1;
    } else {
        CleanDecimal(result);
        int scale = 0;
        int sign1 = s21_get_sign(value_1);
        int sign2 = s21_get_sign(value_2);
        s21_set_sign(&value_1, 0);
        s21_set_sign(&value_2, 0);
        EqualizeDecimal(&value_1, &value_2);
        scale = s21_get_scale(value_1);
        s21_set_scale(&value_1, 0);
        s21_set_scale(&value_2, 0);
        if (sign1 == 0 && sign2 == 0) {
            if (s21_is_greater(value_1, value_2)) {
                subtraction(&value_1, &value_2, result);
            } else {
                subtraction(&value_2, &value_1, result);
                s21_set_sign(result, 1);
            }
        } else if (sign1 == 1 && sign2 == 0) {
            value_1.bits[DATA] &= 0b01111111111111111111111111111111;
            value_2.bits[DATA] &= 0b01111111111111111111111111111111;
            error = s21_add(value_1, value_2, result);
            s21_set_sign(result, 1);
        } else if (sign1 == 0 && sign2 == 1) {
            value_1.bits[DATA] &= 0b01111111111111111111111111111111;
            value_2.bits[DATA] &= 0b01111111111111111111111111111111;
            error = s21_add(value_1, value_2, result);
        } else if (sign1 == 1 && sign2 == 1) {
            if (s21_is_greater(value_1, value_2)) {
                subtraction(&value_1, &value_2, result);
                s21_set_sign(result, 1);
            } else if (s21_is_less(value_1, value_2)) {
                subtraction(&value_2, &value_1, result);
            }
        }
        s21_set_scale(result, scale);
    }
    return error;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int exit_status = 0;
    if (!result) {
        exit_status = 1;
    } else {
        int final_sign = 0;
        int value1_scale = s21_get_scale(value_1);
        int value2_scale = s21_get_scale(value_2);
        int value1_sign = CheckLeftBit(value_1.bits[DATA]);
        int value2_sign = CheckLeftBit(value_2.bits[DATA]);
        s21_long_decimal buffer = {{0, 0, 0, 0, 0, 0, 0}};
        int final_scale = value1_scale + value2_scale;
        if (value1_sign != value2_sign) {
            final_sign = 1;
        }
        CleanDecimal(result);
        s21_long_decimal long_value_1 = {{0, 0, 0, 0, 0, 0, 0}};
        s21_long_decimal long_value_2 = {{0, 0, 0, 0, 0, 0, 0}};
        s21_long_decimal long_result = {{0, 0, 0, 0, 0, 0, 0}};
        value_1.bits[DATA] &= 0b00000000000000000000000000000000;
        from_s21_decimal_to_s21_long_decimal(value_1, &long_value_1);
        value_2.bits[DATA] &= 0b00000000000000000000000000000000;
        from_s21_decimal_to_s21_long_decimal(value_2, &long_value_2);
        from_s21_decimal_to_s21_long_decimal(*result, &long_result);
        int value2_highest_bit = s21_get_highest_bit(long_value_2);
        for (int i = 0; i < value2_highest_bit + 1 && exit_status == 0; i++) {
            s21_long_decimal tmp = long_value_1;
            tmp.bits[DATA] = 0;
            if (s21_get_long_bit(long_value_2, i) == 1) {
                for (int j = 0; j < i; j++) {
                    ShiftLeftLongDecimal(&tmp);
                }
                int add_res = 0;
                add_res = s21_add_long_decimal(tmp, buffer, &long_result);
                if (add_res != 0) {
                    exit_status = 1;
                } else {
                    buffer = long_result;
                    exit_status = 0;
                }
            }
        }
        int check_overflow = 0;
        s21_decimal buffer_result = {{0, 0, 0, 0}};
        check_overflow = from_s21_long_decimal_to_s21_decimal(long_result, &buffer_result);
        int counter_reduse_scale = 0;
        if (check_overflow) {
            for (; long_result.bits[3];) {
                DivInTenLongDecimal(&long_result);
                ++counter_reduse_scale;
                if (counter_reduse_scale + final_scale > 28) {
                    break;
                }
            }
        }
        check_overflow = from_s21_long_decimal_to_s21_decimal(long_result, &buffer_result);
        if (!check_overflow) {
            CleanDecimal(result);
            *result = buffer_result;
            if (counter_reduse_scale) {
                final_scale += counter_reduse_scale;
            }
        } else {
            exit_status = 1;
        }
        s21_set_scale(result, final_scale);
        s21_set_sign(result, final_sign);
        if (final_scale > 28) {
            exit_status = 2;
        }
    }
    return exit_status;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int exit_status = 0;
    float float_value_1, float_value_2;
    for (int i = 0; i < 4; i++) result->bits[i] = 0;
    s21_from_decimal_to_float(value_1, &float_value_1);
    s21_from_decimal_to_float(value_2, &float_value_2);
    exit_status = (float_value_2 == 0 ? 3 : 0);
    if (!exit_status) {
        s21_from_float_to_decimal((float_value_1 / float_value_2), result);
    }
    return exit_status;
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int counter_of_minus_dividend = 0;
    int counter_of_minis_divisor = 0;
    int exit_status = 0;
    if (!result) {
        exit_status = 1;
    } else if (!CheckNotZeroDecimal(&value_2)) {
        exit_status = 3;
    } else {
        if (CheckLeftBit(value_1.bits[DATA])) counter_of_minus_dividend++;
        if (CheckLeftBit(value_2.bits[DATA])) counter_of_minis_divisor++;
        CleanSign(&value_1.bits[DATA]);
        CleanSign(&value_2.bits[DATA]);
        if (s21_is_greater(value_2, value_1)) {
            *result = value_1;
        } else if (s21_is_equal(value_1, value_2)) {
            CleanDecimal(result);
        } else {
            EqualizeDecimal(&value_1, &value_2);
            CleanDecimal(result);
            s21_decimal temp = {{0, 0, 0, 0}};
            s21_div_simple_dimple(value_1, value_2, &temp);
            s21_mul(value_2, temp, &temp);
            s21_sub(value_1, temp, result);
            if ((counter_of_minis_divisor && counter_of_minus_dividend) && CheckNotZeroDecimal(result)) {
                result->bits[DATA] |= 0b10000000000000000000000000000000;
            }
        }
    }
    return exit_status;
}
