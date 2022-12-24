#include "decimal_test.h"

int main(void) {
    int check = 0;
    check += TestS21_ADD();
    check += TestConvertFunc();
    check += TestMulFunc();
    check += TestOther_func();
    check += TestComparisonFunc();
    return check;
}
