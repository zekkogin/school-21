#include "../s21_calc.h"

char *InfixToPostfix(struct Lexeme *slovo) {
  char postFix[512];
  int postFixLenght = 0;
  struct Lexeme *current = slovo;
  struct Stack *stack = initstack();
  while (current != NULL) {
    switch (current->type) {
    case DIGIT:
      strcpy(postFix + postFixLenght, current->value);
      postFixLenght = postFixLenght + strlen(current->value);
      postFix[postFixLenght] = ' ';
      postFixLenght++;
      break;
    case OPEN_BRACKET ... LOG:
      if (current->type == OPEN_BRACKET) {
        push(current->value, stack);
      } else if (current->type == CLOSE_BRACKET) {
        char *oper = pop(stack);
        while (strcmp(oper, "(") != 0) {
          strcpy(postFix + postFixLenght, oper);
          postFixLenght = postFixLenght + strlen(oper);
          postFix[postFixLenght] = ' ';
          postFixLenght++;
          oper = pop(stack);
        }
      }
      // Exception for degree
      else if (stack->topElement != NULL && current->type == POWER &&
               priority(stack->topElement->oper) == 3) {
        push(current->value, stack);
      } else {
        // Check prior != 3 and == 3 for *right associative degree operator*
        // (like ^^^+ in stack to catch all ^^^)
        while (stack->topElement != NULL &&
               (priority(stack->topElement->oper) >= priority(current->value) ||
                (priority(current->value) != 3 &&
                 priority(stack->topElement->oper) == 3))) {
          char *oper = pop(stack);
          strcpy(postFix + postFixLenght, oper);
          postFixLenght = postFixLenght + strlen(oper);
          postFix[postFixLenght] = ' ';
          postFixLenght++;
        }
        push(current->value, stack);
      }
      break;
    default:
      break;
    }
    current = current->next;
  }

  while (stack->topElement != NULL) {
    char *oper = pop(stack);
    strcpy(postFix + postFixLenght, oper);
    postFixLenght = postFixLenght + strlen(oper);
    postFix[postFixLenght] = ' ';
    postFixLenght++;
  }
  postFix[postFixLenght - 1] = '\0';
  char *result = malloc(sizeof(char) * postFixLenght);
  strcpy(result, postFix);
  freestack(stack);
  return result;
}

int priority(char *c) {
  int res = 0;
  if (strcmp(c, "-") == 0 || strcmp(c, "+") == 0)
    res = 1;
  if (strcmp(c, "*") == 0 || strcmp(c, "/") == 0 || strcmp(c, "mod") == 0)
    res = 2;
  if (strcmp(c, "cos") == 0 || strcmp(c, "sin") == 0 || strcmp(c, "tan") == 0 ||
      strcmp(c, "acos") == 0 || strcmp(c, "asin") == 0 ||
      strcmp(c, "atan") == 0 || strcmp(c, "sqrt") == 0 ||
      strcmp(c, "ln") == 0 || strcmp(c, "log") == 0)
    res = 3;
  if (strcmp(c, "^") == 0)
    res = 3;
  return res;
}
