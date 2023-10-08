#include "../s21_calc.h"

struct Stack *initstack() {
  struct Stack *stack = malloc(sizeof(struct Stack));
  stack->topElement = NULL;
  return stack;
}

void push(char *oper, struct Stack *stack) {
  struct Node *node = malloc(sizeof(struct Node));
  node->oper = oper;
  node->previous = stack->topElement;
  stack->topElement = node;
}

char *pop(struct Stack *stack) {
  struct Node *removeElement = stack->topElement;
  char *oper = stack->topElement->oper;
  stack->topElement = stack->topElement->previous;
  free(removeElement);
  return oper;
}

void freestack(struct Stack *stack) {
  while (stack->topElement != NULL) {
    pop(stack);
  }
  free(stack);
}