#include "../s21_calc.h"

int process(char *input, double *result) {
  double result_calc = 0;
  int flag = 0;
  if (input == NULL)
    return 1;
  char *expression = calloc(strlen(input) + 1, sizeof(char));
  expression = scanner_for_test(input);
  if (expression) {
    errorType checkString = validString(expression);
    if (checkString != errNONE) {
      fprintf(stderr,
              "\nCheck your write errorType is -> %u\nMore info of this error "
              "in file s21_calc.h\n",
              checkString);
      free(expression);
      return 2;
    }
    struct Lexeme *Lexems = stringToLexems(expression, 0);
    errorType checkLexems = validLexems(Lexems);
    if (checkLexems != errNONE) {
      fprintf(stderr,
              "\nSomething wrong when string going to Nodes(lexems), errorType "
              "is -> %u\nCheck file s21_calc.h for more info.\n",
              checkLexems);
      free(expression);
      return 3;
    }
    char *postFix = InfixToPostfix(Lexems);
    struct Lexeme *LexemsPostfix = stringToLexems(postFix, 1);
    flag = Calculation(LexemsPostfix, &result_calc);
    free(expression);
  }
  *result = result_calc;
  return flag;
}

int calc_cpp(char *c_string, double *res) {
  int flag = 0;
  double result_double = 0;
  flag = process(c_string, &result_double);
  if (flag == 0)
    *res = result_double;
  return flag;
}
