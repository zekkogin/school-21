#include "s21_decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
    if (value_1.bits[RARE] != 0 || value_1.bits[MEDIUM] != 0 || value_1.bits[WELL] != 0 ||
        value_2.bits[RARE] != 0 || value_2.bits[MEDIUM] != 0 || value_2.bits[WELL] != 0) {
        EqualizeDecimal(&value_1, &value_2);
    }
    int result = 0;
    int error = 0;
    if (!CheckNotZeroDecimal(&value_1) && !CheckNotZeroDecimal(&value_2) &&
        (CheckLeftBit(value_1.bits[DATA]) || CheckLeftBit(value_2.bits[DATA])) &&
        !CheckFraction(value_1.bits[DATA]) && !CheckFraction(value_2.bits[DATA])) {
        error = 1;
    }
    if (!s21_is_equal(value_1, value_2) && !error) {
        if (!(!CheckLeftBit(value_1.bits[DATA]) && CheckLeftBit(value_2.bits[DATA]))) {
            bool reverse_logic = false;
            EqualizeDecimal(&value_1, &value_2);
            if (CheckLeftBit(value_1.bits[DATA]) && CheckLeftBit(value_2.bits[DATA])) {
                reverse_logic = true;
            }
            if (CheckLeftBit(value_1.bits[DATA]) && !CheckLeftBit(value_2.bits[DATA]) &&
                (CheckNotZeroDecimal(&value_2))) {
                result = 1;
            }
            for (int counter = 2; counter >= 0; --counter) {
                if ((((unsigned int)value_1.bits[counter] > (unsigned int)value_2.bits[counter]) &&
                     reverse_logic == false) ||
                    ((value_1.bits[counter] < value_2.bits[counter]) && reverse_logic == true)) {
                    break;
                }
                if ((((unsigned int)value_1.bits[counter] < (unsigned int)value_2.bits[counter]) &&
                     reverse_logic == false) ||
                    (((unsigned int)value_1.bits[counter] > (unsigned int)value_2.bits[counter]) &&
                     reverse_logic == true)) {
                    result = 1;
                    break;
                }
            }
        }
    }
    return result;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
    int result = 0;
    if (s21_is_less(value_1, value_2) || s21_is_equal(value_1, value_2)) {
        result = 1;
    }
    return result;
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
    int result = 0;
    if (s21_is_not_equal(value_1, value_2)) {
        result = !s21_is_less(value_1, value_2);
    }
    return result;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
    int result = 0;
    if (s21_is_greater(value_1, value_2) || s21_is_equal(value_1, value_2)) {
        result = 1;
    }
    return result;
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
    if (value_1.bits[RARE] != 0 || value_1.bits[MEDIUM] != 0 || value_1.bits[WELL] != 0 ||
        value_2.bits[RARE] != 0 || value_2.bits[MEDIUM] != 0 || value_2.bits[WELL] != 0) {
        EqualizeDecimal(&value_1, &value_2);
    }
    int result = 1;
    int error = 0;
    if (value_1.bits[RARE] == 0 && value_1.bits[MEDIUM] == 0 && value_1.bits[WELL] == 0 &&
        value_2.bits[RARE] == 0 && value_2.bits[MEDIUM] == 0 && value_2.bits[WELL] == 0) {
        error = 1;
    }
    if (!CheckNotZeroDecimal(&value_1) && !CheckNotZeroDecimal(&value_2) &&
        (CheckLeftBit(value_1.bits[DATA]) || CheckLeftBit(value_2.bits[DATA])) &&
        !CheckFraction(value_1.bits[DATA]) && !CheckFraction(value_2.bits[DATA])) {
        error = 1;
    }
    if (!error) {
        for (int counter = 0; counter <= 3; counter++) {
            if ((unsigned int)value_1.bits[counter] != (unsigned int)value_2.bits[counter]) {
                result = 0;
                break;
            }
        }
    }

    return result;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
    if (value_1.bits[RARE] != 0 || value_1.bits[MEDIUM] != 0 || value_1.bits[WELL] != 0 ||
        value_2.bits[RARE] != 0 || value_2.bits[MEDIUM] != 0 || value_2.bits[WELL] != 0) {
        EqualizeDecimal(&value_1, &value_2);
    }
    int result = 0;
    int error = 0;
    if (!CheckNotZeroDecimal(&value_1) && !CheckNotZeroDecimal(&value_2) &&
        (CheckLeftBit(value_1.bits[DATA]) || CheckLeftBit(value_2.bits[DATA])) &&
        !CheckFraction(value_1.bits[DATA]) && !CheckFraction(value_2.bits[DATA])) {
        error = 1;
    }
    if (!error) {
        if (CheckLeftBit(value_1.bits[DATA]) != CheckLeftBit(value_2.bits[DATA])) {
            result = 1;
        }
        for (int counter = 0; counter <= 3; counter++) {
            if (value_1.bits[counter] != value_2.bits[counter]) {
                result = 1;
                break;
            }
        }
    }
    return result;
}
