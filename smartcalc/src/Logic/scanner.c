#include "../s21_calc.h"

char *scanner_for_test(char *input) {
  size_t lentgh = strlen(input);
  size_t i = 0;
  size_t j = 0;
  char *noSpaces = (char *)malloc(sizeof(char));
  for (i = 0; i < lentgh; i++) {
    if (input[i] == ' ')
      continue;
    noSpaces = realloc(noSpaces, j + 1);
    noSpaces[j] = input[i];
    j++;
  }
  noSpaces = realloc(noSpaces, j + 1);
  noSpaces[j] = '\0';
  noSpaces = removeExtraPlus(noSpaces);
  return noSpaces;
}

errorType validString(char *expression) {
  size_t lentgh = strlen(expression);
  int equilibriumBrackets = 0;
  errorType error = errNONE;
  char *validSymbols = ".,0123456789()+-*/^modcossintansqrtlnlog";
  char *digits = "0123456789.,";
  bool dot = false;
  for (size_t i = 0; i < lentgh; i++) {
    if ((expression[i] == '.' || expression[i] == ',') && dot)
      error = err_EXTRA_DOT;
    if (strchr(digits, expression[i]) != NULL) {
      if (expression[i] == '.' || expression[i] == ',')
        dot = true;
    } else {
      dot = false;
    }
    if (expression[i] == '(')
      equilibriumBrackets += 1;
    if (expression[i] == ')')
      equilibriumBrackets -= 1;
    if (equilibriumBrackets == -1) {
      error = err_BRACKETS_NOT_EQUAL;
      break;
    }
    if (strchr(validSymbols, expression[i]) == NULL)
      error = err_INVALID_SYMBOL;
  }
  if (equilibriumBrackets != 0)
    error = err_BRACKETS_NOT_EQUAL;
  return error;
}

errorType validLexems(struct Lexeme *Lexemes) {
  errorType error = errNONE;
  if (!Lexemes) {
    error = err_NULL;
    return error;
  }
  Token previous = NONE;
  while (Lexemes != NULL) {
    Token current = Lexemes->type;
    if ((previous != DIGIT && previous != CLOSE_BRACKET) &&
        current == CLOSE_BRACKET) {
      error = err_BRACKETS_CLOSE_BRACKET;
    } else if ((previous >= 15 && previous <= 23) && current != OPEN_BRACKET) {
      error = err_BRACKETS_WITH_FUNC;
    } else if (previous == OPEN_BRACKET && current == CLOSE_BRACKET) {
      error = err_BRACKETS_VOID;
    } else if (previous == OPEN_BRACKET &&
               (current == DIVIDE || current == MOD || current == POWER)) {
      error = err_BRACKETS_VOID_OPERATION;
    } else if ((previous == CLOSE_BRACKET || previous == DIGIT) &&
               current > 10 && current < 5) {
      error = err_AFTER_OPERAND_NO_OPERATION;
    } else if (previous == NONE && (current >= 4 && current <= 10)) {
      error = err_AFTER_NONE_VOID_OPERATION;
    }
    else if ((previous >= 5 && previous <= 10) &&
             ((current >= 4 && current <= 10) || current == CLOSE_BRACKET)) {
      error = err_AFTER_OPERATION_OPERATION;
    } else if (previous == UNARY_MINUS && (current >= 4 && current <= 12)) {
      error = err_AFTER_UNARY_MINUS_NO_OPERAND;
    }
    previous = current;
    if (Lexemes->next == NULL &&
        (current != DIGIT && current != CLOSE_BRACKET)) {
      error = err_LAST_LEXEME_OPERATION;
    }
    if (Lexemes->next != NULL) {
      Lexemes = Lexemes->next;
    } else {
      break;
    }
  }
  return error;
}

char *removeExtraPlus(char *expression) {
  size_t lentgh = strlen(expression);
  size_t j = 0;
  char *newString = (char *)malloc(sizeof(char));
  for (size_t i = 0; i < lentgh; i++) {
    if (i == 0 && expression[i] == '+')
      continue;
    if (i > 0 && (expression[i - 1] == '+' || expression[i - 1] == '-') &&
        expression[i] == '+')
      continue;
    newString = realloc(newString, j + 1);
    newString[j] = expression[i];
    j++;
  }
  newString = realloc(newString, j + 1);
  newString[j] = '\0';
  free(expression);
  return newString;
}
