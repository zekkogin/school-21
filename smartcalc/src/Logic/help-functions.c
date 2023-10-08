#include "../s21_calc.h"

Token getSymbolType(char *string, int index) {
  Token test = NONE;
  if (isDigit(string[index]) != NONE) {
    test = DIGIT;
  } else if (isOperation(string[index]) != NONE) {
    test = isOperation(string[index]);
  } else if (isMOD(string, index) != NONE) {
    test = MOD;
  } else if (isVariable(string[index]) != NONE) {
    test = VARIABLE;
  } else if (isSpace(string[index]) != NONE) {
    test = SPACE;
  } else if (isFunctionTrigonometric(string, index) != NONE) {
    test = isFunctionTrigonometric(string, index);
  } else if (isFunction(string, index) != NONE) {
    test = isFunction(string, index);
  }
  return test;
}

Token isDigit(char c) {
  Token ans = NONE;
  if ((c >= ASCII_DIGIT_START && c <= ASCII_DIGIT_END) || c == '.' || c == ',')
    ans = DIGIT;
  return ans;
}

Token isOperation(char c) {
  Token ans = NONE;
  if (c == '+') {
    ans = PLUS;
  } else if (c == '-') {
    ans = MINUS;
  } else if (c == '/') {
    ans = DIVIDE;
  } else if (c == '*') {
    ans = MULTIPLY;
  } else if (c == '(') {
    ans = OPEN_BRACKET;
  } else if (c == ')') {
    ans = CLOSE_BRACKET;
  } else if (c == '^') {
    ans = POWER;
  }
  return ans;
}

Token isVariable(char c) {
  Token ans = NONE;
  if (c == 'x')
    ans = VARIABLE;
  return ans;
}

Token isSpace(char c) {
  Token ans = NONE;
  if (c == ' ')
    ans = SPACE;
  return ans;
}

Token isMOD(char *infix, int index) {
  Token ans = NONE;
  if ((index > 0 && infix[index - 1] == 'm' && infix[index] == 'o' &&
       infix[index + 1] != '\0' && infix[index + 1] == 'd') ||
      (index > 1 && infix[index - 2] == 'm' && infix[index - 1] == 'o' &&
       infix[index] == 'd')) {
    ans = MOD;
  }
  return ans;
}

Token isFunctionTrigonometric(char *infix, int index) {
  Token ans = NONE;
  if ((index > 0 && infix[index - 1] == 's' && infix[index] == 'i' &&
       infix[index + 1] != '\0' && infix[index + 1] == 'n') ||
      (index > 1 && infix[index - 2] == 's' && infix[index - 1] == 'i' &&
       infix[index] == 'n'))
    ans = SIN;
  if ((index > 0 && infix[index - 1] == 'c' && infix[index] == 'o' &&
       infix[index + 1] != '\0' && infix[index + 1] == 's') ||
      (index > 1 && infix[index - 2] == 'c' && infix[index - 1] == 'o' &&
       infix[index] == 's'))
    ans = COS;
  if ((index > 0 && infix[index - 1] == 't' && infix[index] == 'a' &&
       infix[index + 1] != '\0' && infix[index + 1] == 'n') ||
      (index > 1 && infix[index - 2] == 't' && infix[index - 1] == 'a' &&
       infix[index] == 'n'))
    ans = TAN;
  if ((index > 0 && infix[index - 1] == 'a' && infix[index] == 's' &&
       infix[index + 1] != '\0' && infix[index + 1] == 'i' &&
       infix[index + 2] != '\0' && infix[index + 2] == 'n') ||
      (index > 1 && infix[index - 2] == 'a' && infix[index - 1] == 's' &&
       infix[index] == 'i' && infix[index + 1] != '\0' &&
       infix[index + 1] == 'n') ||
      (index > 2 && infix[index - 3] == 'a' && infix[index - 2] == 's' &&
       infix[index - 1] == 'i' && infix[index] == 'n'))
    ans = ASIN;
  if ((index > 0 && infix[index - 1] == 'a' && infix[index] == 'c' &&
       infix[index + 1] != '\0' && infix[index + 1] == 'o' &&
       infix[index + 2] != '\0' && infix[index + 2] == 's') ||
      (index > 1 && infix[index - 2] == 'a' && infix[index - 1] == 'c' &&
       infix[index] == 'o' && infix[index + 1] != '\0' &&
       infix[index + 1] == 's') ||
      (index > 2 && infix[index - 3] == 'a' && infix[index - 2] == 'c' &&
       infix[index - 1] == 'o' && infix[index] == 's'))
    ans = ACOS;
  if ((index > 0 && infix[index - 1] == 'a' && infix[index] == 't' &&
       infix[index + 1] != '\0' && infix[index + 1] == 'a' &&
       infix[index + 2] != '\0' && infix[index + 2] == 'n') ||
      (index > 1 && infix[index - 2] == 'a' && infix[index - 1] == 't' &&
       infix[index] == 'a' && infix[index + 1] != '\0' &&
       infix[index + 1] == 'n') ||
      (index > 2 && infix[index - 3] == 'a' && infix[index - 2] == 't' &&
       infix[index - 1] == 'a' && infix[index] == 'n'))
    ans = ATAN;
  return ans;
}

Token isFunction(char *infix, int index) {
  Token ans = NONE;
  if (index > 0 && infix[index - 1] == 'l' && infix[index] == 'n')
    ans = LN;
  if ((index > 0 && infix[index - 1] == 'l' && infix[index] == 'o' &&
       infix[index + 1] != '\0' && infix[index + 1] == 'g') ||
      (index > 1 && infix[index - 2] == 'l' && infix[index - 1] == 'o' &&
       infix[index] == 'g'))
    ans = LOG;
  if ((index > 0 && infix[index - 1] == 's' && infix[index] == 'q' &&
       infix[index + 1] != '\0' && infix[index + 1] == 'r' &&
       infix[index + 2] != '\0' && infix[index + 2] == 't') ||
      (index > 1 && infix[index - 2] == 's' && infix[index - 1] == 'q' &&
       infix[index] == 'r' && infix[index + 1] != '\0' &&
       infix[index + 1] == 't') ||
      (index > 2 && infix[index - 3] == 's' && infix[index - 2] == 'q' &&
       infix[index - 1] == 'r' && infix[index] == 't'))
    ans = SQRT;
  return ans;
}
