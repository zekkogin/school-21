#include "../s21_calc.h"

struct Lexeme *stringToLexems(char *infix, bool postfixLexemes) {
  int start = 0;
  int end = 0;
  Token previusSymbolType = NONE;
  Token currentSymbolType = NONE;
  struct Lexeme *lastLexeme = NULL;
  struct Lexeme *firstLexeme = NULL;
  for (size_t i = 0; i <= strlen(infix); i++) {
    if (i == strlen(infix)) {
      currentSymbolType = NONE;
    } else {
      currentSymbolType = getSymbolType(infix, i);
    }
    if (checkUnaryMinus(previusSymbolType, currentSymbolType))
      currentSymbolType = DIGIT;
    if (postfixLexemes && i < strlen(infix)) {
      if (currentSymbolType == MINUS && infix[i + 1] != '\0') {
        if (infix[i + 1] != ' ')
          currentSymbolType = DIGIT;
      }
    }
    if (((previusSymbolType == DIGIT || previusSymbolType == UNARY_MINUS) &&
         currentSymbolType == DIGIT) ||
        currentSymbolType == MOD ||
        (currentSymbolType >= COS && currentSymbolType <= LOG)) {
      end = i;
      previusSymbolType = currentSymbolType;
      continue;
    } else if (previusSymbolType != NONE && previusSymbolType != SPACE) {
      struct Lexeme *Lexeme = malloc(sizeof(struct Lexeme));
      Lexeme->next = NULL;
      Lexeme->type = NONE;
      Lexeme->value = NULL;
      char *value = malloc(sizeof(char) * (end - start + 2));
      strncpy(value, infix + start, end - start + 1);
      value[end - start + 1] = '\0';
      Lexeme->value = value;
      Lexeme->type = previusSymbolType;
      if (firstLexeme == NULL) {
        firstLexeme = Lexeme;
      } else {
        lastLexeme->next = Lexeme;
      }
      lastLexeme = Lexeme;
    }
    start = i;
    end = i;
    previusSymbolType = currentSymbolType;
  }
  return firstLexeme; // net reakcii na incorrect
}

bool checkUnaryMinus(Token previusSymbolType, Token currentSymbolType) {
  bool ans = false;
  if (((previusSymbolType >= PLUS && previusSymbolType <= MOD) ||
       previusSymbolType == NONE || previusSymbolType == OPEN_BRACKET) &&
      currentSymbolType == MINUS)
    ans = true;
  return ans;
}
