// #include "s21_calc.h"

// int main() {
// 	char* infix;
// 	infix = scanner();
// 	if(infix == NULL) { return 0;}
// 	print(infix);
// 	errorType checkString = validString(infix);
// 	if(checkString != errNONE) {
// 		printf("\nCheck your write errorType is -> %u\nMore info of this
// error in file scanner.h ", checkString); 		return 0;
// 	}
// 	struct Lexeme* Lexems = stringToLexems(infix, 0);
// 	errorType checkLexems = validLexems(Lexems);
// 	if(checkLexems != errNONE) {
// 		printf("\nSomething wrong when string going to Nodes(lexems),
// errorType is -> %u\nCheck file scanner.c for more info. ", checkLexems);
// 		return 0;
// 	}
// 	// while(Lexems) {
// 	// 	printf("\n%s", Lexems->value);
// 	// 	Lexems = Lexems->next;
// 	// }
// 	char* postFix = InfixToPostfix(Lexems);
//     printf("\n postfix == %s", postFix);
// 	struct Lexeme* LexemsPostfix = stringToLexems(postFix, 1);
// 	printf("\n before calc");
// 	// while(LexemsPostfix) {
// 	// 	printf("\n%s", LexemsPostfix->value);
// 	// 	LexemsPostfix = LexemsPostfix->next;
// 	// }
// 	double result = Calculation(LexemsPostfix);
// 	printf("result == %lf", result);
// 	return 0;
// }

// void print(char* postFix) {
// 	printf("\n%s", postFix);
// }
