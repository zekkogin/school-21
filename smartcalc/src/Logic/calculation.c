#include "../s21_calc.h"

int Calculation(struct Lexeme *Lexems, double *result) {
  int flag = 0;
  struct Stack *stack = initstack();
  struct Lexeme *current = Lexems;
  double operandUP = 0;
  double operandDOWN = 0;
  double operand = 0;
  double result_minor = 0;
  while (current != NULL && flag == 0) {
    switch (current->type) {
    case DIGIT:
    case DIGIT_DOT:
      push(current->value, stack);
      break;
    case PLUS ... MOD:;
      if (stack->topElement != NULL) {
        operandUP = strtod(pop(stack), NULL);
      } else {
        flag = -1;
        break;
      }
      if (stack->topElement != NULL) {
        operandDOWN = strtod(pop(stack), NULL);
      } else {
        flag = -1;
        break;
      }
      result_minor = 0;
      flag = GenericOperation(current->type, operandUP, operandDOWN,
                              &result_minor);
      if (flag != 0)
        break;
      char *str_result = (char *)malloc(20 * sizeof(char));
      snprintf(str_result, 20, "%.9lf", result_minor);
      push(str_result, stack);
      break;
    case COS ... LOG:;
      if (stack->topElement != NULL) {
        operand = strtod(pop(stack), NULL);
      } else {
        flag = -1;
        break;
      }
      result_minor = 0;
      flag = GenericFunc(current->type, operand, &result_minor);
      if (flag != 0)
        break;
      char *str_result_func = (char *)malloc(20 * sizeof(char));
      snprintf(str_result_func, 20, "%.9lf", result_minor);
      push(str_result_func, stack);
      break;
    default:
      break;
    }
    current = current->next;
  }
  if (flag == 0)
    *result = strtod(pop(stack), NULL);
  free(stack);
  return flag;
}

int GenericOperation(Token type, double operand2, double operand1,
                     double *result) {
  int flag = 0;
  switch (type) {
  case PLUS:
    *result = operand1 + operand2;
    break;
  case MINUS:
    *result = operand1 - operand2;
    break;
  case MULTIPLY:
    *result = operand1 * operand2;
    break;
  case DIVIDE:
    if (operand2 > EPS || operand2 < -EPS) {
      *result = operand1 / operand2;
    } else {
      flag = 24;
    }
    break;
  case POWER:
    *result = pow(operand1, operand2);
    break;
  case MOD:
    *result = fmod(operand1, operand2);
    break;
  default:
    break;
  }
  return flag;
}

int GenericFunc(Token type, double operand, double *result) {
  int flag = 0;
  switch (type) {
  case COS:
    *result = cos(operand);
    break;
  case SIN:
    *result = sin(operand);
    break;
  case TAN:
    *result = tan(operand);
    break;
  case ASIN:
    *result = asin(operand);
    break;
  case ACOS:
    *result = acos(operand);
    break;
  case ATAN:
    *result = atan(operand);
    break;
  case SQRT:
    if (operand < 0.0) {
      flag = 17;
    } else {
      *result = sqrt(operand);
    }
    break;
  case LN:
    if (operand < 0.0) {
      flag = 18;
    } else {
      *result = ln(operand);
    }
    break;
  case LOG:
    if (operand < 0.0) {
      flag = 18;
    } else {
      *result = log10(operand);
    }
    break;
  default:
    break;
  }
  return flag;
}
