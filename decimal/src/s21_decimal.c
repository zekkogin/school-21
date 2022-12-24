#include "s21_decimal.h"

// другие функции
int s21_negate(s21_decimal value, s21_decimal *result) {
    int error_check = 0;
    if (result == NULL) {
        error_check = 1;
    } else {
        if (CheckLeftBit(value.bits[DATA])) {
            value.bits[DATA] &= 0b01111111111111111111111111111111;

        } else {
            value.bits[DATA] |= 0b10000000000000000000000000000000;
        }
        *result = value;
    }
    return error_check;
}

int s21_round(s21_decimal value, s21_decimal *result) {
    int error = 0;
    if (!result) {
        error = 1;
    } else {
        int scale = GetFractionStDecimal(value.bits[DATA]) - 1;
        if (scale > -1) {
            for (; scale; --scale) {
                error = ReduceDegree(&value);
            }
            if (!error) {
                int sign = CheckLeftBit(value.bits[DATA]);
                s21_decimal last_num;
                CleanDecimal(&last_num);
                s21_decimal ten = {{10, 0, 0, 0}};
                value.bits[DATA] = 0;
                s21_mod(value, ten, &last_num);
                int last_num_in_int = last_num.bits[RARE];
                if (last_num_in_int >= 5) {
                    ReduceDegree(&value);
                    s21_decimal one = {{1, 0, 0, 0}};
                    s21_add(value, one, result);
                } else {
                    ReduceDegree(&value);
                    *result = value;
                }
                if (sign) {
                    result->bits[DATA] = 0b10000000000000000000000000000000;
                }
            }
        } else {
            *result = value;
        }
    }
    return error;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
    int error = 0;
    CleanDecimal(result);
    int scale = GetFractionStDecimal(value.bits[DATA]);
    int sign = 0;
    if (CheckLeftBit(value.bits[DATA])) {
        sign = 1;
    }
    if ((unsigned int)value.bits[WELL] == 0b11111111111111111111111111111111) {
        value.bits[RARE] = 0b00000000000000000000000000000111;
        value.bits[MEDIUM] = 0;
        value.bits[WELL] = 0;
    } else {
        for (; scale; --scale) {
            error = ReduceDegree(&value);
        }
    }
    *result = value;
    result->bits[DATA] = 0;
    if (sign) {
        result->bits[DATA] |= 0b10000000000000000000000000000000;
    }
    return error;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
    int error = 0;
    if (!result) {
        error = 1;
    } else {
        if (GetFractionStDecimal(value.bits[DATA])) {
            error = s21_truncate(value, result);
            if (CheckLeftBit(value.bits[DATA])) {
                s21_decimal one = {{1, 0, 0, 0}};
                int sign = CheckLeftBit(result->bits[DATA]);
                if (sign) {
                    s21_sub(*result, one, result);
                } else {
                    s21_add(*result, one, result);
                }
            }
        } else {
            *result = value;
        }
    }
    return error;
}

// операции над битами
void AddBitInDecimal(int new_bit, char *buffer_decimal, int counter_buffer_decimal, int *save_bit) {
    if (new_bit == 0) {
        if (*save_bit == 0) {
            buffer_decimal[counter_buffer_decimal] = '0';
        } else {
            buffer_decimal[counter_buffer_decimal] = '1';
            *save_bit -= 1;
        }
    } else if (new_bit == 1) {
        if (*save_bit != 0) {
            buffer_decimal[counter_buffer_decimal] = '0';
        } else {
            buffer_decimal[counter_buffer_decimal] = '1';
        }
    } else {
        if (*save_bit == 0) {
            buffer_decimal[counter_buffer_decimal] = '0';
            *save_bit += 1;
        } else {
            buffer_decimal[counter_buffer_decimal] = '1';
        }
    }
    buffer_decimal[counter_buffer_decimal + 1] = '\0';
}

// маски
void CleanSign(int *num) {
    *num <<= 1;
    *num >>= 1;
}

int CheckRigtBit(int num) {
    int res = 0;
    if (num & 0b00000000000000000000000000000001) {
        res = 1;
    }
    return res;
}

int CheckLeftBit(int num) {
    int res = 0;
    if (num & 0b10000000000000000000000000000000) {
        res = 1;
    }
    return res;
}

int CheckBitInTwoInt(int num_one, int num_two) {
    int result = 0;
    if (CheckRigtBit(num_one) && CheckRigtBit(num_two)) {
        result = -1;
    } else if (CheckRigtBit(num_one) || CheckRigtBit(num_two)) {
        result = 1;
    }
    return result;
}

void AddSign(int *part_decimal, const int src) {
    if (src & 0b10000000000000000000000000000000) {
        *part_decimal |= 0b10000000000000000000000000000000;
    } else {
        *part_decimal = 0;
    }
}

int CheckNotZero(int num) {
    int res = 0;
    if ((unsigned int)num & 0b11111111111111111111111111111111) {
        res = 1;
    }
    return res;
}

int CheckFraction(int num) {
    int res = 0;
    if (num & 0b00000000111111110000000000000000) {
        res = 1;
    }
    return res;
}

// вспомогательные функции
int DivInTen(s21_decimal *value) {
    if (!CheckRigtBit(value->bits[RARE])) {
        value->bits[RARE] |= 0b0000000000000000000000000000111;
    }
    s21_decimal first_buf = *value;
    s21_decimal second_buf = *value;

    ShiftRightCycle(&first_buf, 1);
    ShiftRightCycle(&second_buf, 2);

    s21_add(first_buf, second_buf, value);

    first_buf = *value;
    ShiftRightCycle(&first_buf, 4);
    s21_add(*value, first_buf, value);

    first_buf = *value;
    ShiftRightCycle(&first_buf, 8);
    s21_add(*value, first_buf, value);

    first_buf = *value;
    ShiftRightCycle(&first_buf, 16);
    s21_add(*value, first_buf, value);

    first_buf = *value;
    ShiftRightCycle(&first_buf, 32);
    s21_add(*value, first_buf, value);

    first_buf = *value;
    ShiftRightCycle(&first_buf, 64);
    s21_add(*value, first_buf, value);

    first_buf = *value;
    ShiftRightCycle(&first_buf, 132);
    s21_add(*value, first_buf, value);
    ShiftRightCycle(value, 3);
    return 0;
}

int DivInTenLongDecimal(s21_long_decimal *value) {
    if (!CheckRigtBit(value->bits[0])) {
        value->bits[0] |= 0b0000000000000000000000000000111;
    }

    s21_long_decimal first_buf = *value;
    s21_long_decimal second_buf = *value;

    ShiftRightCycleLongDecinal(&first_buf, 1);
    ShiftRightCycleLongDecinal(&second_buf, 2);

    s21_add_long_decimal(first_buf, second_buf, value);

    first_buf = *value;
    ShiftRightCycleLongDecinal(&first_buf, 4);
    s21_add_long_decimal(*value, first_buf, value);

    first_buf = *value;
    ShiftRightCycleLongDecinal(&first_buf, 8);
    s21_add_long_decimal(*value, first_buf, value);

    first_buf = *value;
    ShiftRightCycleLongDecinal(&first_buf, 16);
    s21_add_long_decimal(*value, first_buf, value);

    first_buf = *value;
    ShiftRightCycleLongDecinal(&first_buf, 32);
    s21_add_long_decimal(*value, first_buf, value);

    first_buf = *value;
    ShiftRightCycleLongDecinal(&first_buf, 64);
    s21_add_long_decimal(*value, first_buf, value);

    first_buf = *value;
    ShiftRightCycleLongDecinal(&first_buf, 132);
    s21_add_long_decimal(*value, first_buf, value);

    first_buf = *value;
    ShiftRightCycleLongDecinal(&first_buf, 264);
    s21_add_long_decimal(*value, first_buf, value);

    ShiftRightCycleLongDecinal(value, 3);

    return 0;
}

int ReduceDegree(s21_decimal *value) {
    int error = 0;
    if (!value->bits[MEDIUM] && !value->bits[WELL]) {
        value->bits[RARE] /= 10;
    } else {
        error = DivInTen(value);
    }
    return error;
}

int ReduceDegreeLongDecimal(s21_long_decimal *value) {
    int error = 0;
    if (value->bits[1] && value->bits[2] && value->bits[3] && value->bits[4] && value->bits[5]) {
        value->bits[0] /= 10;
    } else {
        error = DivInTenLongDecimal(value);
    }
    return error;
}

void PrintDecimalBinary(s21_decimal decimal) {
    for (int part_decinal = 0; part_decinal < 4; ++part_decinal) {
        char buffer[32];
        for (int counter = 0; counter < 32; ++counter) {
            if (CheckRigtBit(decimal.bits[part_decinal])) {
                buffer[counter] = '1';
            } else {
                buffer[counter] = '0';
            }
            buffer[counter + 1] = '\0';
            decimal.bits[part_decinal] = decimal.bits[part_decinal] >> 1;
        }
        s21_reverse_string(buffer, 32);
        printf("%s ", buffer);
    }
    printf("\n");
}

void PrintLongDecimalBinary(s21_long_decimal decimal) {
    for (int part_decinal = 0; part_decinal < 7; ++part_decinal) {
        char buffer[32];
        for (int counter = 0; counter < 32; ++counter) {
            if (CheckRigtBit(decimal.bits[part_decinal])) {
                buffer[counter] = '1';
            } else {
                buffer[counter] = '0';
            }
            buffer[counter + 1] = '\0';
            decimal.bits[part_decinal] = decimal.bits[part_decinal] >> 1;
        }
        s21_reverse_string(buffer, 32);
        printf("%s ", buffer);
    }
    printf("\n");
}

void s21_reverse_string(char *line_for_num, int size) {
    for (int i = 0, j = size - 1; i < j; i++, j--) {
        char buffer = line_for_num[i];
        line_for_num[i] = line_for_num[j];
        line_for_num[j] = buffer;
    }
}

unsigned int ConvertSignInt(int src) {
    unsigned int result = 0;
    if (src < 0) {
        result = -src;
    } else {
        result = src;
    }
    return result;
}

void CleanDecimal(s21_decimal *dst) {
    dst->bits[RARE] = 0;
    dst->bits[MEDIUM] = 0;
    dst->bits[WELL] = 0;
    dst->bits[DATA] = 0;
}

void ConvertStringToDecimal(const char *buffer_decimal, s21_decimal *result) {
    int counter_buffer_decimal = 0;
    for (int counter_part = 2; counter_part > -1; --counter_part) {
        for (int counter_bit = 0; counter_bit < 32; ++counter_bit) {
            if (buffer_decimal[counter_buffer_decimal] == '0') {
                result->bits[counter_part] = result->bits[counter_part] << 1;
            } else {
                result->bits[counter_part] = result->bits[counter_part] << 1;
                result->bits[counter_part] = result->bits[counter_part] | 1;
            }
            ++counter_buffer_decimal;
        }
    }
}

void ConvertStringToLongDecimal(const char *buffer_decimal, s21_long_decimal *result) {
    int counter_buffer_decimal = 0;
    for (int counter_part = 5; counter_part > -1; --counter_part) {
        for (int counter_bit = 0; counter_bit < 32; ++counter_bit) {
            if (buffer_decimal[counter_buffer_decimal] == '0') {
                result->bits[counter_part] = result->bits[counter_part] << 1;
            } else {
                result->bits[counter_part] = result->bits[counter_part] << 1;
                result->bits[counter_part] = result->bits[counter_part] | 1;
            }
            ++counter_buffer_decimal;
        }
    }
}

int Summation(s21_decimal value_1, s21_decimal value_2, char *buffer_decimal) {
    int check_overflow = 0;
    int save_bit = 0;
    int counter_buffer_decimal = 0;
    for (int counter_part = 0; counter_part < 3; ++counter_part) {
        for (int counter_bit = 0; counter_bit < 32; ++counter_bit, ++counter_buffer_decimal) {
            AddBitInDecimal(CheckBitInTwoInt(value_1.bits[counter_part], value_2.bits[counter_part]),
                            buffer_decimal, counter_buffer_decimal, &save_bit);
            value_1.bits[counter_part] >>= 1;
            value_2.bits[counter_part] >>= 1;
            if (counter_buffer_decimal == 95 && save_bit) {
                check_overflow = 1;
            }
        }
    }
    return check_overflow;
}

int SummationLongDecimal(s21_long_decimal value_1, s21_long_decimal value_2, char *buffer_decimal) {
    int check_overflow = 0;
    int save_bit = 0;
    int counter_buffer_decimal = 0;
    for (int counter_part = 0; counter_part < 6; ++counter_part) {
        for (int counter_bit = 0; counter_bit < 32; ++counter_bit, ++counter_buffer_decimal) {
            AddBitInDecimal(CheckBitInTwoInt(value_1.bits[counter_part], value_2.bits[counter_part]),
                            buffer_decimal, counter_buffer_decimal, &save_bit);
            value_1.bits[counter_part] >>= 1;
            value_2.bits[counter_part] >>= 1;
            if (counter_buffer_decimal == 263 && save_bit) {
                check_overflow = 1;
            }
        }
    }
    return check_overflow;
}

int CheckSignForSummation(s21_decimal value_1, s21_decimal value_2) {
    int sign = 0;
    if (CheckLeftBit(value_1.bits[DATA]) && CheckLeftBit(value_2.bits[DATA])) {
        sign = 1;
    } else if ((!CheckLeftBit(value_1.bits[DATA]) && CheckLeftBit(value_2.bits[DATA])) ||
               (CheckLeftBit(value_1.bits[DATA]) && !CheckLeftBit(value_2.bits[DATA]))) {
        sign = -1;
    }
    return sign;
}

int GetFractionStDecimal(int num) {
    int buffer = 0;
    buffer = num;
    buffer >>= 16;
    buffer &= 0b00000000000000000000111111111111;
    return buffer;
}

int CheckFractionDecimal(int val_1, int val_2) {
    int res = 0;
    if (CheckFraction(val_1) || CheckFraction(val_2)) {
        val_1 <<= 1;
        val_1 >>= 1;
        val_2 <<= 1;
        val_2 >>= 1;
        val_1 >>= 16;
        val_2 >>= 16;
        if (val_1 != val_2) {
            res = 1;
        }
    }
    return res;
}

void BufferForEqualizeDecimal(s21_decimal *value_1, s21_decimal *value_2) {
    int check_overflow = 1;
    if (!value_1 || !value_2) {
        check_overflow = 0;
    } else {
        s21_decimal buffer_value_1 = {{0, 0, 0, 0}};
        s21_decimal buffer_value_2 = {{0, 0, 0, 0}};
        buffer_value_1 = *value_1;
        buffer_value_2 = *value_2;
        check_overflow = EqualizeDecimal(&buffer_value_1, &buffer_value_2);
        if (check_overflow) {
            *value_1 = buffer_value_1;
            *value_2 = buffer_value_2;
        } else {
            if (GetFractionStDecimal(value_1->bits[DATA]) > GetFractionStDecimal(value_2->bits[DATA])) {
                int sign = CheckLeftBit(value_1->bits[DATA]);
                int search =
                    GetFractionStDecimal(value_1->bits[DATA]) - GetFractionStDecimal(value_2->bits[DATA]);
                for (; search; --search) {
                    DivInTen(value_1);
                }
                value_1->bits[DATA] = value_2->bits[DATA];
                if (sign) {
                    value_1->bits[DATA] |= 0b100000000000000000000000000000;
                }
            } else if (GetFractionStDecimal(value_2->bits[DATA]) >
                       GetFractionStDecimal(value_1->bits[DATA])) {
                int sign = CheckLeftBit(value_2->bits[DATA]);
                int search =
                    GetFractionStDecimal(value_2->bits[DATA]) - GetFractionStDecimal(value_1->bits[DATA]);
                for (; search; --search) {
                    DivInTen(value_2);
                }
                value_2->bits[DATA] = value_1->bits[DATA];
                if (sign) {
                    value_2->bits[DATA] |= 0b100000000000000000000000000000;
                }
            }
        }
    }
}

int EqualizeDecimal(s21_decimal *value_1, s21_decimal *value_2) {
    int check_overflow = 1;
    if (!value_1 || !value_2) {
        check_overflow = 1;
    } else {
        DATA_FOR_EQUALIZE data;
        data.sign_save = 0;
        data.cursor = *value_1;
        data.res = value_1;
        data.st_search = 0;
        GetDataForEqualizeDecimal(value_1, value_2, &data);
        if (data.res) {
            s21_decimal sl_1 = data.cursor;
            s21_decimal sl_2 = data.cursor;
            sl_1.bits[DATA] = 0;
            sl_2.bits[DATA] = 0;
            if (data.difference) {
                while (data.difference && check_overflow) {
                    for (int counter = 0; counter < 1 && check_overflow; ++counter) {
                        check_overflow = ShiftLeft(&sl_1);
                    }
                    for (int counter = 0; counter < 3 && check_overflow; ++counter) {
                        check_overflow = ShiftLeft(&sl_2);
                    }
                    s21_add(sl_1, sl_2, data.res);
                    --data.difference;
                    sl_1 = *data.res;
                    sl_2 = *data.res;
                }
                if (check_overflow) {
                    while (data.st_search) {
                        ChangeDegree(1, &data.res->bits[DATA]);
                        --data.st_search;
                    }
                }
                if (data.sign_save) {
                    data.res->bits[DATA] = data.res->bits[DATA] | 0b10000000000000000000000000000000;
                }
            }
        }
    }
    return check_overflow;
}

void GetDataForEqualizeDecimal(s21_decimal *value_1, s21_decimal *value_2, DATA_FOR_EQUALIZE *data) {
    if (value_1 && value_2 && data) {
        int st_val_1 = 0;
        int st_val_2 = 0;
        st_val_1 = GetFractionStDecimal(value_1->bits[DATA]);
        st_val_2 = GetFractionStDecimal(value_2->bits[DATA]);
        if (st_val_1 > st_val_2) {
            data->difference = st_val_1 - st_val_2;
            data->cursor = *value_2;
            data->res = value_2;
            data->st_search = GetFractionStDecimal(value_1->bits[DATA]);
            if (CheckLeftBit(value_2->bits[DATA])) {
                data->sign_save = 1;
            }
        } else {
            data->difference = st_val_2 - st_val_1;
            data->cursor = *value_1;
            data->res = value_1;
            data->st_search = GetFractionStDecimal(value_2->bits[DATA]);
            if (CheckLeftBit(value_1->bits[DATA])) {
                data->sign_save = 1;
            }
        }
    }
}

int ShiftLeft(s21_decimal *num) {
    int res = 1;
    if (!num) {
        res = 0;
    } else {
        if (!CheckLeftBit(num->bits[WELL])) {
            int save_rare = 0;
            int save_medium = 0;
            if (!CheckLeftBit(num->bits[RARE])) {
                num->bits[RARE] = num->bits[RARE] << 1;
            } else {
                num->bits[RARE] = num->bits[RARE] << 1;
                save_rare = 1;
            }
            if (!CheckLeftBit(num->bits[MEDIUM])) {
                num->bits[MEDIUM] = num->bits[MEDIUM] << 1;
            } else {
                num->bits[MEDIUM] = num->bits[MEDIUM] << 1;
                save_medium = 1;
            }
            if (save_rare) {
                num->bits[MEDIUM] = num->bits[MEDIUM] | 1;
            }
            num->bits[WELL] = num->bits[WELL] << 1;
            if (save_medium) {
                num->bits[WELL] = num->bits[WELL] | 1;
            }
        } else {
            res = 0;
        }
    }
    return res;
}

int s21_get_long_bit(s21_long_decimal number, int bit_position) {
    int bit_number = bit_position / 32;
    bit_position = bit_position % 32;
    int bit = (int)((number.bits[bit_number] >> bit_position) & 1u);
    return bit;
}

int s21_get_highest_bit(s21_long_decimal number) {
    int bit_position = -1;
    for (int i = 0; i < 192 && bit_position == -1; i++) {
        if (s21_get_long_bit(number, (191 - i)) == 1) {
            bit_position = (191 - i);
        }
    }
    return bit_position;
}

int ShiftLeftLongDecimal(s21_long_decimal *num) {
    int res = 1;
    if (!CheckLeftBit(num->bits[6])) {
        int sava_0 = 0;
        int sava_1 = 0;
        int sava_2 = 0;
        int sava_3 = 0;
        int sava_4 = 0;
        int sava_5 = 0;
        if (!CheckLeftBit(num->bits[0])) {
            num->bits[0] <<= 1;
        } else {
            num->bits[0] = num->bits[0] << 1;
            sava_0 = 1;
        }
        if (!CheckLeftBit(num->bits[1])) {
            num->bits[1] <<= 1;
        } else {
            num->bits[1] = num->bits[1] << 1;
            sava_1 = 1;
        }
        if (!CheckLeftBit(num->bits[2])) {
            num->bits[2] <<= 1;
        } else {
            num->bits[2] = num->bits[2] << 1;
            sava_2 = 1;
        }
        if (!CheckLeftBit(num->bits[3])) {
            num->bits[3] <<= 1;
        } else {
            num->bits[3] = num->bits[3] << 1;
            sava_3 = 1;
        }
        if (!CheckLeftBit(num->bits[4])) {
            num->bits[4] <<= 1;
        } else {
            num->bits[4] = num->bits[4] << 1;
            sava_4 = 1;
        }
        if (!CheckLeftBit(num->bits[5])) {
            num->bits[5] <<= 1;
        } else {
            num->bits[5] = num->bits[5] << 1;
            sava_5 = 1;
        }
        if (!CheckLeftBit(num->bits[6])) {
            num->bits[6] <<= 1;
        } else {
            num->bits[6] = num->bits[6] << 1;
        }
        if (sava_0) {
            num->bits[1] = num->bits[1] | 1;
        }
        if (sava_1) {
            num->bits[2] = num->bits[2] | 1;
        }
        if (sava_2) {
            num->bits[3] = num->bits[3] | 1;
        }
        if (sava_3) {
            num->bits[4] = num->bits[4] | 1;
        }
        if (sava_4) {
            num->bits[5] = num->bits[5] | 1;
        }
        if (sava_5) {
            num->bits[6] = num->bits[6] | 1;
        }
    } else {
        res = 0;
    }
    return res;
}

// sign == 1 - +1 к степени
// sign == 0 - -1 к степени
void ChangeDegree(int sign, int *num) {
    if (num) {
        int sign_num = 0;
        if (CheckRigtBit(*num)) {
            sign_num = 1;
        }
        *num = *num >> 16;
        if (sign) {
            *num += 1;
        } else {
            *num -= 1;
        }
        *num = *num << 16;
        if (sign_num) {
            *num = *num | 1;
        }
    }
}

// zeckodin - вспомогательные функции - начало
int getBinaryExp(unsigned int fbits) {
    int scale = 7;
    unsigned int mask = 0b01000000000000000000000000000000;
    int sum = 0;
    for (int i = 0; i <= 7; i++) {
        if (fbits & mask) {
            sum = sum + pow(2, scale);
        }
        mask >>= 1;
        scale = scale - 1;
    }
    return sum - 127 - 1;
}

void setMantissa(s21_decimal *dst, int binaryScale) {
    binaryScale = binaryScale + 1;
    unsigned int mask = 1;
    for (int i = 0; i < binaryScale % 32; i++) {
        mask <<= 1;
    }
    if (binaryScale >= 0 && binaryScale <= 31) {
        dst->bits[RARE] = dst->bits[RARE] | mask;
    }
    if (binaryScale >= 32 && binaryScale <= 63) {
        dst->bits[MEDIUM] = dst->bits[MEDIUM] | mask;
    }
    if (binaryScale >= 64 && binaryScale <= 95) {
        dst->bits[WELL] = dst->bits[WELL] | mask;
    }
}

void setFloat(s21_decimal *dst, int binaryScale, unsigned int fbits) {
    unsigned int maskFloat = 0b00000000010000000000000000000000;
    while (binaryScale > -2) {
        unsigned int mask = 1;
        for (int i = 0; i < binaryScale % 32; i++) {
            mask <<= 1;
        }
        if (binaryScale <= 31) {
            if (fbits & maskFloat) {
                dst->bits[RARE] = dst->bits[RARE] | mask;
            }
        }
        if (binaryScale >= 32 && binaryScale <= 63) {
            if (fbits & maskFloat) {
                dst->bits[MEDIUM] = dst->bits[MEDIUM] | mask;
            }
        }
        if (binaryScale >= 64 && binaryScale <= 95) {
            if (fbits & maskFloat) {
                dst->bits[WELL] = dst->bits[WELL] | mask;
            }
        }
        mask >>= 1;
        maskFloat >>= 1;
        binaryScale = binaryScale - 1;
    }
}

int CheckNotZeroDecimal(s21_decimal *decimal) {
    int res = 0;
    for (int i = 0; i <= 2; i++) {
        if (CheckNotZero(decimal->bits[i])) res = 1;
    }
    return res;
}

void s21_div_simple_dimple(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    for (int i = 0; i < 3; i++) {
        result->bits[i] = 0;
    }
    int a = signific_bits(value_1);
    int b = signific_bits(value_2);
    int diff = b - a;
    for (int i = 0; i < diff; i++) {
        ShiftLeft(&value_2);
    }
    for (int i = 0; i <= diff && ShiftLeft(result); i++) {
        if (s21_is_greater_or_equal_simple(value_1, value_2)) {
            s21_sub(value_1, value_2, &value_1);
            result->bits[0] += 1;
        }
        ShiftRightCycle(&value_2, 1);
    }
}

int s21_is_greater_or_equal_simple(s21_decimal value_1, s21_decimal value_2) {
    int res = 0;
    if (s21_is_greater_or_equal(value_1, value_2)) {
        res = 1;
    }
    return res;
}

int signific_bits(s21_decimal value) {
    int number_of_depth = 0;
    for (int i = 95; i >= 0; i--) {
        int mask = 1;
        int number_of_bits = i / 32;
        int number_of_cell = i % 32;
        mask <<= number_of_cell;
        if (value.bits[number_of_bits] & mask) {
            break;
        } else {
            number_of_depth++;
        }
    }
    return number_of_depth;
}

void setMaxDecimal(s21_decimal *value) {
    for (int i = 0; i <= 2; i++) {
        value->bits[0] = 0b11111111111111111111111111111111;
    }
}

// zeckodin - вспомогательные функции - конец
// alessand - вспомогательные функции - начало
void s21_set_sign(s21_decimal *number, int sign) {
    if (sign == 0) {
        number->bits[DATA] <<= 1;
        number->bits[DATA] >>= 1;
    }
    if (sign == 1) {
        int mask = 0b10000000000000000000000000000000;
        number->bits[DATA] = number->bits[DATA] | mask;
    }
}

int s21_get_scale(s21_decimal number) {
    int scale = 0;
    number.bits[DATA] >>= 16;
    for (int j = 0; j < 8; j++) {
        scale += (int)(((number.bits[DATA] >> j) & 1u) * (int)pow(2, j));
    }
    return scale;
}

void s21_set_scale(s21_decimal *number, int scale) {
    if (number) {
        int sign = 0;
        sign = s21_get_sign(*number);
        number->bits[DATA] = scale;
        number->bits[DATA] <<= 16;
        if (sign) {
            s21_set_sign(number, 1);
        }
    }
}

int s21_get_bit(s21_decimal number, int bit_position) {
    int bit_number = bit_position / 32;
    bit_position = bit_position % 32;
    int bit = (int)((number.bits[bit_number] >> bit_position) & 1u);
    return bit;
}

int s21_get_sign(s21_decimal number) {
    int sign = 0;
    sign = (int)((number.bits[DATA] >> 31) & 1u);
    return sign;
}

void ShiftRightCycle(s21_decimal *num, int counter) {
    int save_well = 0;
    int save_medium = 0;
    for (int i = 1; i <= counter; i++) {
        if (!CheckRigtBit(num->bits[WELL])) {
            num->bits[WELL] = num->bits[WELL] >> 1;
        } else {
            num->bits[WELL] = num->bits[WELL] >> 1;
            save_well = 1;
        }
        if (!CheckRigtBit(num->bits[MEDIUM])) {
            num->bits[MEDIUM] = num->bits[MEDIUM] >> 1;
        } else {
            num->bits[MEDIUM] = num->bits[MEDIUM] >> 1;
            save_medium = 1;
        }
        if (save_well) {
            num->bits[MEDIUM] = num->bits[MEDIUM] | 0b10000000000000000000000000000000;
            save_well = 0;
        } else {
            num->bits[MEDIUM] = num->bits[MEDIUM] & 0b01111111111111111111111111111111;
        }
        num->bits[RARE] = num->bits[RARE] >> 1;
        if (save_medium) {
            num->bits[RARE] = num->bits[RARE] | 0b10000000000000000000000000000000;
            save_medium = 0;
        } else {
            num->bits[RARE] = num->bits[RARE] & 0b01111111111111111111111111111111;
        }
    }
}

void ShiftRightCycleLongDecinal(s21_long_decimal *num, int counter) {
    int save_1 = 0;
    int save_2 = 0;
    int save_3 = 0;
    int save_4 = 0;
    int save_5 = 0;

    for (int i = 1; i <= counter; i++) {
        if (!CheckRigtBit(num->bits[5])) {
            num->bits[5] = num->bits[5] >> 1;
        } else {
            num->bits[5] = num->bits[5] >> 1;
            save_5 = 1;
        }
        if (!CheckRigtBit(num->bits[4])) {
            num->bits[4] = num->bits[4] >> 1;
        } else {
            num->bits[4] = num->bits[4] >> 1;
            save_4 = 1;
        }
        if (!CheckRigtBit(num->bits[3])) {
            num->bits[3] = num->bits[3] >> 1;
        } else {
            num->bits[3] = num->bits[3] >> 1;
            save_3 = 1;
        }
        if (!CheckRigtBit(num->bits[2])) {
            num->bits[2] = num->bits[2] >> 1;
        } else {
            num->bits[2] = num->bits[2] >> 1;
            save_2 = 1;
        }
        if (!CheckRigtBit(num->bits[1])) {
            num->bits[1] = num->bits[1] >> 1;
        } else {
            num->bits[1] = num->bits[1] >> 1;
            save_1 = 1;
        }
        if (save_5) {
            num->bits[4] = num->bits[4] | 0b10000000000000000000000000000000;
        } else {
            num->bits[4] = num->bits[4] & 0b01111111111111111111111111111111;
        }
        if (save_4) {
            num->bits[3] = num->bits[3] | 0b10000000000000000000000000000000;
        } else {
            num->bits[3] = num->bits[3] & 0b01111111111111111111111111111111;
        }
        if (save_3) {
            num->bits[2] = num->bits[2] | 0b10000000000000000000000000000000;
        } else {
            num->bits[2] = num->bits[2] & 0b01111111111111111111111111111111;
        }
        if (save_2) {
            num->bits[1] = num->bits[1] | 0b10000000000000000000000000000000;
        } else {
            num->bits[1] = num->bits[1] & 0b01111111111111111111111111111111;
        }
        num->bits[0] = num->bits[0] >> 1;
        if (save_1) {
            num->bits[0] = num->bits[0] | 0b10000000000000000000000000000000;
        } else {
            num->bits[0] = num->bits[0] & 0b01111111111111111111111111111111;
        }
    }
}

// alessand - вспомогательные функции - конец
// qylenett - вспомогательные функции - начало
void subtraction(const s21_decimal *value_1, s21_decimal *value_2, s21_decimal *result) {
    int check_overflow;
    char buffer_decimal[96];
    s21_decimal num;
    s21_from_int_to_decimal(1, &num);
    s21_decimal val_2;
    inversion(value_2);
    val_2 = *value_2;
    s21_add(val_2, num, &val_2);
    check_overflow = Summation(*value_1, val_2, buffer_decimal);
    if (check_overflow) {
        CleanDecimal(result);
        s21_reverse_string(buffer_decimal, 96);
        ConvertStringToDecimal(buffer_decimal, result);
    } else {
        CleanDecimal(result);
        s21_reverse_string(buffer_decimal, 96);
        ConvertStringToDecimal(buffer_decimal, result);
    }
}

int inversion(s21_decimal *value) {
    value->bits[RARE] = ~value->bits[RARE];
    value->bits[MEDIUM] = ~value->bits[MEDIUM];
    value->bits[WELL] = ~value->bits[WELL];
    return 0;
}

// qylenett - вспомогательные функции - конец
