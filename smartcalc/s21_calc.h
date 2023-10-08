/**
 * @file s21_calc.h
 *
 * All logic of calculator in C (from (char*) infix notation to reverse polish notation, then to result in &double)
 *
 */
#ifndef SRC_S21_CALC_H
#define SRC_S21_CALC_H
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE_OF_STRING 256
#define MAX 256
#define ASCII_DIGIT_START 48
#define ASCII_DIGIT_END 57
#define ASCII_LETTER_START 97
#define ASCII_LETTER_END 122
#define ln(x) log(x)
#define EPS DBL_EPSILON

/**
 * @brief All Lexemes in Typedef Token (UNARY PLUS I DELETE IN MY LOGIC)
 */

typedef enum {
  NONE,          // 0
  DIGIT,         // 1
  VARIABLE,      // 2
  OPEN_BRACKET,  // 3
  CLOSE_BRACKET, // 4
  PLUS,          // 5
  MINUS,         // 6
  MULTIPLY,      // 7
  DIVIDE,        // 8
  POWER,         // 9
  MOD,           // 10
  UNARY_PLUS,    // 11
  UNARY_MINUS,   // 12
  SPACE,         // 13
  PI,            // 14
  COS,           // 15
  SIN,           // 16
  TAN,           // 17
  ACOS,          // 18
  ASIN,          // 19
  ATAN,          // 20
  SQRT,          // 21
  LN,            // 22
  LOG,           // 23
  DIGIT_DOT      // 24
} Token;

/**
 * @brief All Errors in Typedef errorType
 */

typedef enum {
  errNONE,                          // 0
  err_BRACKETS_NOT_EQUAL,           // 1
    /**
     * @brief Example log12 . Func don`t have ()
     */
  err_BRACKETS_WITH_FUNC,           // 2
    /**
     * @brief Error like log(12-)
     */
  err_BRACKETS_CLOSE_BRACKET,       // 3
  err_INVALID_SYMBOL,               // 4
    /**
     * @brief Example log()
     */
  err_BRACKETS_VOID,                // 5
    /**
     * @brief If operation in brackets don`t have operands. Like log(*)
     */
  err_BRACKETS_VOID_OPERATION,      // 6
    /**
     * @brief In start of string_input like /123+23
     */
  err_AFTER_NONE_VOID_OPERATION,    // 7
  err_AFTER_OPERAND_NO_OPERATION,   // 8
    /**
     * @brief Errors like ** or //
     */
  err_AFTER_OPERATION_OPERATION,    // 9
    /**
     * @brief Errors like -/
     */
  err_AFTER_UNARY_MINUS_NO_OPERAND, // 10
    /**
     * @brief In end of string 123+23*
     */
  err_LAST_LEXEME_OPERATION,        // 11
  err_NULL,                         // 12
  err_EXTRA_DOT
} errorType;

typedef struct x {
    /**
     * @brief For plotting graphs in CPP file.
     */
  double start, end, step;
} x_x;

struct Lexeme {
  char *value;
  Token type;
  struct Lexeme *next;
};

/**
 * @brief Used inside stack data-structure.
 */
struct Node {
  char *oper;
  struct Node *previous;
};

/**
 * @brief topElement for check Upper operation.
 */
struct Stack {
  struct Node *topElement;
};

// Main proccess -> process.c
/**
 * @brief Main process, catch input* from Calculator QLineEdit and save result in &result (type double)
 * @param input for Calculator LABEL
 * @param pointer to save result
 * @return returns a flag for fprintf errors in STDERR
 */
int process(char *input, double *result);

/**
 * @brief Оболочка над process.c для расчета графиков.
 */
int calc_cpp(char *c_string, double *res);

// Reader of string from calculator -> scanner.c

/**
 * @brief Just remove extra UNARY PLUS and ALL SPACES.
 * @param input for Calculator LABEL
 * @return returns new string without spaces and extra pluses.
 */
char *scanner_for_test(char *input);
/**
 * @brief Check Lexemes for errors
 * @param All lexemes in infix notation
 * @return typedef errorType
 */
errorType validLexems(struct Lexeme *Lexemes);
/**
 * @brief Check string for errors
 * @param Raw string without spaces and extra pluses
 * @return typedef errorType
 */
errorType validString(char *expression);
/**
 * @brief Garbage func
 */
bool validVariable(char *variable);
/**
 * @brief Function for scanner_for_test to delete extra pluses.
 * @return new string
 */
char *removeExtraPlus(char *expression);

// Implementation of stack -> stack.c

/**
 * @brief Inmplementation for stack
 * @return new stack.
 */
struct Stack *initstack();
/**
 * @brief To push string operator in stack data type
 * @param string
 * @param which stack to use
 */
void push(char *oper, struct Stack *stack);
/**
 * @brief To pop from stack
 * @param which stack to use.
 * @return string
 */
char *pop(struct Stack *stack);
/**
 * @brief Just delete a stack
 * @param which stack do delete.
 */
void freestack(struct Stack *stack);

// String to lexems -> getLexems.c

/**
 * @brief Just string -> lexemes
 * @param infix string or postfix string
 * @param infix - 0 , postfix - 1
 * @return Lexemes in infix notation
 */
struct Lexeme *stringToLexems(char *infix, bool postfixLexemes);
/**
 * @brief Check to know unary or not unary minus
 */
bool checkUnaryMinus(Token previusSymbolType, Token currentSymbolType);
#endif

// Process of calculation -> calculation.c
/**
 * @brief Main process of math calculation
 * @param Lexemes in RPN
 * @param pointer to double from cpp side
 * @return flag of error
 */
int Calculation(struct Lexeme *Lexems, double *result);
/**
 * @brief All math operation (+,-,/,^,fmod)
 * @param Token type of operation
 * @param first pop from stack
 * @param second pop from stack
 * @param pointer to result
 * @return flag of error (like divide 1/0)
 */
int GenericOperation(Token type, double operand2, double operand1,
                     double *result);
/**
 * @brief All math func operation (sin,cos,asin,tan,acos, etc..)
 * @param Token type of operation
 * @param first pop from stack
 * @param pointer to result
 * @return flag of error (like divide 1/0)
 */
int GenericFunc(Token type, double operand, double *result);

// Help-functions.c
/**
 * @brief To know digit or not digit
 * @param One char
 * @return DIGIT or NONE
 */
Token isDigit(char c);
Token isOperation(char c);
Token isVariable(char c);
/**
 * @brief Main tokenizer
 * @param One char
 * @param Index of char in string (to safe from buffer-overflow or undeflow)
 * @return Token (all tokens upper in this file)
 */
Token getSymbolType(char *string, int index);
Token isSpace(char c);
Token isMOD(char *infix, int index);
Token isFunctionTrigonometric(char *infix, int index);
Token isFunction(char *infix, int index);

// Lexemes to postfix nodes -> lexemsToPostfix.c

/**
 * @brief Infix lexemes To Postfix STRING
 * @param Infix lexemes
 * @return Postfix String
 */
char *InfixToPostfix(struct Lexeme *slovo);
/**
 * @brief To kno priority of math operation
 * @param One char
 * @return 0 - digit,none; 1 - +,-; 2 - *,mod,/; 3 - functions and degree
 */
int priority(char *c);
