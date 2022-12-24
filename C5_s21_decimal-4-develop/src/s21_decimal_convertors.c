#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
    int error_check = 0;
    if (dst) {
        CleanDecimal(dst);
        AddSign(&dst->bits[DATA], src);
        unsigned int buffer = ConvertSignInt(src);
        dst->bits[RARE] = buffer;
    } else {
        error_check = 1;
    }
    return error_check;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
    int error_check = 0;
    if (dst) {
        if (!CheckFraction(src.bits[DATA]) && !src.bits[MEDIUM] && !src.bits[WELL]) {
            *dst = src.bits[RARE];
            if (src.bits[DATA] & 0b10000000000000000000000000000000) {
                *dst = *dst * -1;
            }
        } else {
            float check;
            s21_from_decimal_to_float(src, &check);
            *dst = check;
        }
    } else {
        error_check = 1;
    }
    return error_check;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    int error = 0;
    int binaryScale = 0;
    bool minus = false;
    if (src < 0) {
        minus = true;
        src = -src;
    }
    unsigned int fbits = *((unsigned int *)&src);
    double number_double = (double)src;
    CleanDecimal(dst);
    binaryScale = getBinaryExp(fbits);
    if (isinf(src) || isnan(src)) {
        error = 1;
    } else {
        if (number_double != 0.0) {
            int scale = 0;
            for (; !(int)(number_double / 1E7); number_double *= 10) scale += 1;
            number_double = (float)number_double;
            while (fmod(number_double, 10.0) == 0 && scale > 0) {
                number_double = number_double / 10;
                scale -= 1;
            }
            if (scale <= 28 && (binaryScale + 1 > -95 && binaryScale + 1 <= 95)) {
                src = number_double;
                unsigned int fbits = *((unsigned int *)&src);
                binaryScale = getBinaryExp(fbits);
                setMantissa(dst, binaryScale);
                if (src != 1) {
                    setFloat(dst, binaryScale, fbits);
                }
                for (int i = 1; i <= scale; i++) {
                    ChangeDegree(1, &dst->bits[DATA]);
                }
                if (minus == true) {
                    dst->bits[DATA] |= 0b10000000000000000000000000000000;
                }
            } else {
                error = 1;
            }
        }
    }
    return error;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
    int error = 0;
    if (!dst) {
        error = 1;
    } else {
        double dst_temp = 0;
        int i = 95;
        *dst = 0;
        int counter = 31;
        int scale = 0;
        bool minus = false;
        if (src.bits[DATA] & 0b10000000000000000000000000000000) {
            minus = true;
        }
        while (1) {
            int mask = 0b00000000000000000000000000000001;
            mask <<= counter;
            counter--;
            if (i >= 0 && i <= 31) {
                if (src.bits[RARE] & mask) dst_temp += 1 * pow(2, i);
            }
            if (i >= 32 && i <= 63) {
                if (src.bits[MEDIUM] & mask) dst_temp += 1 * pow(2, i);
            }
            if (i >= 64 && i <= 95) {
                if (src.bits[WELL] & mask) dst_temp += 1 * pow(2, i);
            }
            i = i - 1;
            if (i == -1) break;
            if (counter == -1) {
                counter = 31;
            }
        }
        scale = GetFractionStDecimal(src.bits[DATA]);
        dst_temp = dst_temp / pow(10, scale);
        if (minus == true) {
            dst_temp = -dst_temp;
        }
        *dst = (float)dst_temp;
    }
    return error;
}

void from_s21_decimal_to_s21_long_decimal(s21_decimal src, s21_long_decimal *dst) {
    if (dst) {
        dst->bits[0] = src.bits[RARE];
        dst->bits[1] = src.bits[MEDIUM];
        dst->bits[2] = src.bits[WELL];
        dst->bits[3] = 0;
        dst->bits[4] = 0;
        dst->bits[5] = 0;
        dst->bits[6] = src.bits[DATA];
    }
}

int from_s21_long_decimal_to_s21_decimal(s21_long_decimal src, s21_decimal *dst) {
    int error = 0;
    if (!dst) {
        error = 1;
    } else {
        if (!src.bits[3] && !src.bits[4] && !src.bits[5]) {
            dst->bits[RARE] = src.bits[0];
            dst->bits[MEDIUM] = src.bits[1];
            dst->bits[WELL] = src.bits[2];
            dst->bits[DATA] = src.bits[6];
        } else {
            error = 1;
        }
    }
    return error;
}
