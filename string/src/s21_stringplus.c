#include "s21_stringplus.h"

START_TEST(test_s21_strlen) {
    ck_assert_uint_eq(strlen(test1), s21_strlen(test1));
    ck_assert_uint_eq(strlen(test2), s21_strlen(test2));
    ck_assert_uint_eq(strlen(test3), s21_strlen(test3));
    ck_assert_uint_eq(strlen(test4), s21_strlen(test4));
    ck_assert_uint_eq(strlen(test5), s21_strlen(test5));
    ck_assert_uint_eq(strlen(test6), s21_strlen(test6));
    ck_assert_uint_eq(strlen(test7), s21_strlen(test7));
}
END_TEST

START_TEST(test_s21_strchr) {
    ck_assert_ptr_eq(strchr(test1, '\n'), s21_strchr(test1, '\n'));
    ck_assert_ptr_eq(strchr(test2, 'o'), s21_strchr(test2, 'o'));
    ck_assert_ptr_eq(strchr(test3, 'a'), s21_strchr(test3, 'a'));
    ck_assert_ptr_eq(strchr(test4, '\n'), s21_strchr(test4, '\n'));
    ck_assert_ptr_eq(strchr(test5, ' '), s21_strchr(test5, ' '));
    ck_assert_ptr_eq(strchr(test6, '\0'), s21_strchr(test6, '\0'));
    ck_assert_ptr_eq(strchr(test7, 'w'), s21_strchr(test7, 'w'));
}
END_TEST

START_TEST(test_s21_memcmp) {
    char std1[20] = "Hello world\n\0";
    ck_assert_int_eq(memcmp(test1, std1, 10), s21_memcmp(test1, std1, 10));

    char std2[20] = "Hi world\0";
    ck_assert_int_eq(memcmp(test2, std2, 1), s21_memcmp(test2, std2, 1));

    char std3[20] = "a\n\0";
    ck_assert_int_eq(memcmp(test3, std3, 4), s21_memcmp(test3, std3, 4));

    char std4[20] = " \n\0";
    ck_assert_int_eq(memcmp(test4, std4, 3), s21_memcmp(test4, std4, 3));
    char std5[20] = "Yesno\n\0";
    ck_assert_int_eq(memcmp(test5, std5, 1), s21_memcmp(test5, std5, 1));

    char std6[20] = "\n\0";
    ck_assert_int_eq(memcmp(test6, std6, 2), s21_memcmp(test6, std6, 2));

    char std7[20] = "\0";
    ck_assert_int_eq(memcmp(test7, std7, 1), s21_memcmp(test7, std7, 1));
}
END_TEST

START_TEST(test_s21_memchr) {
    ck_assert_ptr_eq(memchr(test1, 'w', 8), s21_memchr(test1, 'w', 8));
    ck_assert_ptr_eq(memchr(test2, 'l', 8), s21_memchr(test2, 'l', 8));
    ck_assert_ptr_eq(memchr(test3, 'a', 8), s21_memchr(test3, 'a', 8));
    ck_assert_ptr_eq(memchr(test4, ' ', 8), s21_memchr(test4, ' ', 8));
    ck_assert_ptr_eq(memchr(test5, 'd', 8), s21_memchr(test5, 'd', 8));
    ck_assert_ptr_eq(memchr(test6, '\n', 8), s21_memchr(test6, '\n', 8));
    ck_assert_ptr_eq(memchr(test7, '\0', 8), s21_memchr(test7, '\0', 8));
}
END_TEST

START_TEST(test_s21_memcpy) {
    char whr1[20] = "I'll be";
    char frm1[10] = " back";
    ck_assert_str_eq(memcpy(whr1, frm1, 6), s21_memcpy(whr1, frm1, 6));

    char whr2[20] = "Where is ";
    char frm2[15] = "your pants?\0";
    ck_assert_str_eq(memcpy(whr2, frm2, 12), s21_memcpy(whr2, frm2, 12));

    char whr3[20] = "1234";
    char frm3[15] = "\n5678\n9";
    ck_assert_str_eq(memcpy(whr3, frm3, 7), s21_memcpy(whr3, frm3, 7));

    char whr4[20] = "-+-+-";
    char frm4[10] = "\n+-+-+";
    ck_assert_str_eq(memcpy(whr4, frm4, 6), s21_memcpy(whr4, frm4, 6));

    char whr5[20] = "  \0";
    char frm5[10] = "  \n";
    ck_assert_str_eq(memcpy(whr5, frm5, 3), s21_memcpy(whr5, frm5, 3));

    char whr6[21] = "";
    char frm6[20] = "Now it is not empty?";
    ck_assert_str_eq(memcpy(whr6, frm6, 20), s21_memcpy(whr6, frm6, 20));

    char whr7[20] = "123";
    char frm7[10] = "\0";
    ck_assert_str_eq(memcpy(whr7, frm7, 1), s21_memcpy(whr7, frm7, 1));
}
END_TEST

START_TEST(test_s21_memmove) {
    char whr1[10] = "LOL?\0";
    char frm1[10] = "LOL?\0";
    ck_assert_ptr_eq(memmove(test1, whr1, 4), s21_memmove(test1, frm1, 4));
    char whr2[25] = "Where is your pants?\0";
    char frm2[25] = "Where is your pants?\0";
    ck_assert_ptr_eq(memmove(test2, whr2, 15), s21_memmove(test2, frm2, 15));
    char whr3[20] = "\n5678\n9";
    char frm3[10] = "\n5678\n9";
    ck_assert_ptr_eq(memmove(test3, whr3, 3), s21_memmove(test3, frm3, 3));
    char whr4[10] = "-+-+-";
    char frm4[10] = "-+-+-";
    ck_assert_ptr_eq(memmove(test4, whr4, 5), s21_memmove(test4, frm4, 5));
    char whr5[10] = "ABCD";
    char frm5[10] = "ABCD";
    ck_assert_ptr_eq(memmove(test5, whr5, 4), s21_memmove(test5, frm5, 4));
    char whr6[20] = "It is empty string";
    char frm6[20] = "It is empty string";
    ck_assert_ptr_eq(memmove(test6, whr6, 2), s21_memmove(test6, frm6, 2));
    char whr7[20] = "Hello world\n\0";
    char frm7[20] = "Hello world\n\0";
    ck_assert_str_eq(memmove(whr7, test7, 2), s21_memmove(frm7, test7, 2));
}
END_TEST

START_TEST(test_s21_memset) {
    char whr10[20] = "I h8 g1t!\0";
    char whr11[20] = "I h8 g1t!\0";
    ck_assert_str_eq(memset(whr10, '*', 5), s21_memset(whr11, '*', 5));

    char whr20[20] = "Hello world\0";
    char whr22[20] = "Hello world\0";
    ck_assert_str_eq(memset(whr20, '*', 5), s21_memset(whr22, '*', 5));

    char whr30[20] = "a\n\0";
    char whr33[20] = "a\n\0";
    ck_assert_str_eq(memset(whr30, '*', 3), s21_memset(whr33, '*', 3));

    char whr40[20] = " \n\0";
    char whr44[20] = " \n\0";
    ck_assert_str_eq(memset(whr40, '*', 2), s21_memset(whr44, '*', 2));

    char whr50[20] = " \0";
    char whr55[20] = " \0";
    ck_assert_str_eq(memset(whr50, '*', 1), s21_memset(whr55, '*', 1));

    char whr60[20] = "\n\0";
    char whr66[20] = "\n\0";
    ck_assert_str_eq(memset(whr60, '*', 2), s21_memset(whr66, '*', 2));

    char whr70[20] = "\0";
    char whr77[20] = "\0";
    ck_assert_str_eq(memset(whr70, '*', 1), s21_memset(whr77, '*', 1));
}
END_TEST

START_TEST(test_s21_strcat) {
    char whr1[30] = "Monkey business";
    char frm1[30] = "Monkey business";
    ck_assert_str_eq(strcat(whr1, test1), s21_strcat(frm1, test1));

    char whr2[30] = "***\n\0";
    char frm2[30] = "***\n\0";
    ck_assert_str_eq(strcat(whr2, test2), s21_strcat(frm2, test2));

    char whr3[30] = "\n";
    char frm3[30] = "\n";
    ck_assert_str_eq(strcat(whr3, test3), s21_strcat(frm3, test3));

    char whr4[30] = "Hi\0";
    char frm4[30] = "Hi\0";
    ck_assert_str_eq(strcat(whr4, test4), s21_strcat(frm4, test4));

    char whr5[30] = "Hello world\n\0";
    char frm5[30] = "Hello world\n\0";
    ck_assert_str_eq(strcat(whr5, test5), s21_strcat(frm5, test5));

    char whr6[30] = "*\0";
    char frm6[30] = "*\0";
    ck_assert_str_eq(strcat(whr6, test6), s21_strcat(frm6, test6));

    char whr7[30] = "\0";
    char frm7[30] = "\0";
    ck_assert_str_eq(strcat(whr7, test7), s21_strcat(frm7, test7));
}
END_TEST

START_TEST(test_s21_strcmp) {
    char std1[20] = "Hello world\0";
    ck_assert_int_eq(strcmp(test1, std1), s21_strcmp(test1, std1));

    char std2[20] = "Hello world\n\0";
    ck_assert_int_eq(strcmp(test2, std2), s21_strcmp(test2, std2));

    char std3[20] = "Oops";
    ck_assert_int_eq(strcmp(test3, std3), s21_strcmp(test3, std3));

    char std4[20] = "Dont w8 y0rself";
    ck_assert_int_eq(strcmp(test4, std4), s21_strcmp(test4, std4));

    char std5[20] = "Hell0";
    ck_assert_int_eq(strcmp(test5, std5), s21_strcmp(test5, std5));

    char std6[20] = "\n\0";
    ck_assert_int_eq(strcmp(test6, std6), s21_strcmp(test6, std6));

    char std7[20] = "\0";
    ck_assert_int_eq(strcmp(test7, std7), s21_strcmp(test7, std7));
}
END_TEST

START_TEST(test_s21_strcpy) {
    char whr1[30] = "Monkey business";
    char frm1[30] = "Monkey business";
    ck_assert_str_eq(strcpy(test1, whr1), s21_strcpy(test1, frm1));

    char whr2[30] = "***\n\0";
    char frm2[30] = "***\n\0";
    ck_assert_str_eq(strcpy(test2, whr2), s21_strcpy(test2, frm2));

    char whr3[30] = "\n";
    char frm3[30] = "\n";
    ck_assert_str_eq(strcpy(test3, whr3), s21_strcpy(test3, frm3));

    char whr4[30] = "Hi\0";
    char frm4[30] = "Hi\0";
    ck_assert_str_eq(strcpy(test4, whr4), s21_strcpy(test4, frm4));

    char whr5[30] = "Hello world\n\0";
    char frm5[30] = "Hello world\n\0";
    ck_assert_str_eq(strcpy(test5, whr5), s21_strcpy(test5, frm5));

    char whr6[30] = "*\0";
    char frm6[30] = "*\0";
    ck_assert_str_eq(strcpy(test6, whr6), s21_strcpy(test6, frm6));

    char whr7[30] = "\0";
    char frm7[30] = "\0";
    ck_assert_str_eq(strcpy(test7, whr7), s21_strcpy(test7, frm7));
}
END_TEST

START_TEST(test_s21_strcspn) {
    char whr[10] = " \n0";
    ck_assert_uint_eq(strcspn(test1, whr), s21_strcspn(test1, whr));
    ck_assert_uint_eq(strcspn(test2, whr), s21_strcspn(test2, whr));
    ck_assert_uint_eq(strcspn(test3, whr), s21_strcspn(test3, whr));
    ck_assert_uint_eq(strcspn(test4, whr), s21_strcspn(test4, whr));
    ck_assert_uint_eq(strcspn(test5, whr), s21_strcspn(test5, whr));
    ck_assert_uint_eq(strcspn(test6, whr), s21_strcspn(test6, whr));
    ck_assert_uint_eq(strcspn(test7, whr), s21_strcspn(test7, whr));
}
END_TEST

START_TEST(test_s21_strncat) {
    char frm[10] = "\nwhy?\0";
    char test11[25] = "Hello world\0";
    ck_assert_str_eq(strncat(test1, frm, 6), s21_strncat(test11, frm, 6));
    char test12[25] = "Hello world\n\0";
    ck_assert_str_eq(strncat(test2, frm, 6), s21_strncat(test12, frm, 6));
    char test13[25] = "a\n\0";
    ck_assert_str_eq(strncat(test3, frm, 6), s21_strncat(test13, frm, 6));
    char test14[25] = " \n\0";
    ck_assert_str_eq(strncat(test4, frm, 6), s21_strncat(test14, frm, 6));
    char test15[25] = " \0";
    ck_assert_str_eq(strncat(test5, frm, 6), s21_strncat(test15, frm, 6));
    char test16[25] = "\n\0";
    ck_assert_str_eq(strncat(test6, frm, 6), s21_strncat(test16, frm, 6));
    char test17[25] = "\0";
    ck_assert_str_eq(strncat(test7, frm, 6), s21_strncat(test17, frm, 6));
}
END_TEST

START_TEST(test_s21_strncmp) {
    char frm1[10] = "Hel why?\0";
    ck_assert_int_eq(strncmp(test1, frm1, 3), s21_strncmp(test1, frm1, 3));

    char frm2[10] = "Her";
    ck_assert_int_eq(strncmp(test2, frm2, 3), s21_strncmp(test2, frm2, 3));

    char frm3[10] = " \n ";
    ck_assert_int_eq(strncmp(test3, frm3, 3), s21_strncmp(test3, frm3, 3));

    char frm4[10] = "a\0";
    ck_assert_int_eq(strncmp(test4, frm4, 3), s21_strncmp(test4, frm4, 3));

    char frm5[10] = "\0";
    ck_assert_int_eq(strncmp(test5, frm5, 2), s21_strncmp(test5, frm5, 2));

    char frm6[10] = "\n\0";
    ck_assert_int_eq(strncmp(test6, frm6, 2), s21_strncmp(test6, frm6, 2));

    char frm7[10] = "0";
    ck_assert_int_eq(strncmp(test7, frm7, 2), s21_strncmp(test7, frm7, 2));
}
END_TEST

START_TEST(test_s21_strncpy) {
    char frm[10] = "\nI\nh8\ngit\0";
    ck_assert_ptr_eq(strncpy(test1, frm, 10), s21_strncpy(test1, frm, 10));
    ck_assert_ptr_eq(strncpy(test2, frm, 9), s21_strncpy(test2, frm, 9));
    ck_assert_ptr_eq(strncpy(test3, frm, 8), s21_strncpy(test3, frm, 8));
    ck_assert_ptr_eq(strncpy(test4, frm, 7), s21_strncpy(test4, frm, 7));
    ck_assert_ptr_eq(strncpy(test5, frm, 6), s21_strncpy(test5, frm, 6));
    ck_assert_ptr_eq(strncpy(test6, frm, 5), s21_strncpy(test6, frm, 5));

    char frm2[10] = "";
    ck_assert_ptr_eq(strncpy(test7, frm2, 1), s21_strncpy(test7, frm2, 1));
}
END_TEST

START_TEST(test_s21_strpbrk) {
    char frm[6] = "\n la \0";
    ck_assert_ptr_eq(strpbrk(test1, frm), s21_strpbrk(test1, frm));
    ck_assert_ptr_eq(strpbrk(test2, frm), s21_strpbrk(test2, frm));
    ck_assert_ptr_eq(strpbrk(test3, frm), s21_strpbrk(test3, frm));
    ck_assert_ptr_eq(strpbrk(test4, frm), s21_strpbrk(test4, frm));
    ck_assert_ptr_eq(strpbrk(test5, frm), s21_strpbrk(test5, frm));
    ck_assert_ptr_eq(strpbrk(test6, frm), s21_strpbrk(test6, frm));
    ck_assert_ptr_eq(strpbrk(test7, frm), s21_strpbrk(test7, frm));
}
END_TEST

START_TEST(test_s21_strrchr) {
    ck_assert_ptr_eq(strrchr(test1, 'l'), s21_strrchr(test1, 'l'));
    ck_assert_ptr_eq(strrchr(test2, '\n'), s21_strrchr(test2, '\n'));
    ck_assert_ptr_eq(strrchr(test3, '\n'), s21_strrchr(test3, '\n'));
    ck_assert_ptr_eq(strrchr(test4, '\n'), s21_strrchr(test4, '\n'));
    ck_assert_ptr_eq(strrchr(test5, '\n'), s21_strrchr(test5, '\n'));
    ck_assert_ptr_eq(strrchr(test6, '\0'), s21_strrchr(test6, '\0'));
    ck_assert_ptr_eq(strrchr(test7, '0'), s21_strrchr(test7, '0'));
}
END_TEST

START_TEST(test_s21_strspn) {
    ck_assert_uint_eq(strspn(test1, "llo"), s21_strspn(test1, "llo"));
    ck_assert_uint_eq(strspn(test2, "\n\0"), s21_strspn(test2, "\n\0"));
    ck_assert_uint_eq(strspn(test3, "\na"), s21_strspn(test3, "\na"));
    ck_assert_uint_eq(strspn(test4, "\0 "), s21_strspn(test4, "\0 "));
    ck_assert_uint_eq(strspn(test5, "d"), s21_strspn(test5, "d"));
    ck_assert_uint_eq(strspn(test6, "0"), s21_strspn(test6, "0"));
    ck_assert_uint_eq(strspn(test7, "\0"), s21_strspn(test7, "\0"));
}
END_TEST

START_TEST(test_s21_strstr) {
    char frm[5] = "\n\0";
    ck_assert_ptr_eq(strstr(test1, frm), s21_strstr(test1, frm));
    ck_assert_ptr_eq(strstr(test2, frm), s21_strstr(test2, frm));
    ck_assert_ptr_eq(strstr(test3, frm), s21_strstr(test3, frm));
    ck_assert_ptr_eq(strstr(test4, frm), s21_strstr(test4, frm));
    ck_assert_ptr_eq(strstr(test5, frm), s21_strstr(test5, frm));
    ck_assert_ptr_eq(strstr(test6, frm), s21_strstr(test6, frm));
    ck_assert_ptr_eq(strstr(test7, frm), s21_strstr(test7, frm));
}
END_TEST

START_TEST(test_s21_strtok) {
    char whr10[10] = "";
    char whr20[10] = "";
    ck_assert_ptr_eq(strtok(whr10, " "), s21_strtok(whr20, " "));

    char whr11[50] = "Show me the world";
    char whr21[50] = "Show me the world";
    ck_assert_str_eq(strtok(whr11, " "), s21_strtok(whr21, " "));

    char whr12[50] = "You should not pass!";
    char whr22[50] = "You should not pass!";
    ck_assert_str_eq(strtok(whr12, " "), s21_strtok(whr22, " "));

    char whr13[50] = "";
    char whr23[50] = "";
    ck_assert_ptr_eq(strtok(whr13, " "), s21_strtok(whr23, " "));

    char whr14[50] = "It will never happens again";
    char whr24[50] = "It will never happens again";
    ck_assert_str_eq(strtok(whr14, " "), s21_strtok(whr24, " "));

    char whr15[50] = "What is your point?";
    char whr25[50] = "What is your point?";
    ck_assert_str_eq(strtok(whr15, " "), s21_strtok(whr25, " "));

    char whr16[50] = "Hello w0rld";
    char whr26[50] = "Hello w0rld";
    ck_assert_str_eq(strtok(whr16, " "), s21_strtok(whr26, " "));

    char whr17[50] = "1 2 3 4 5 6 7 8 9 0";
    char whr27[50] = "1 2 3 4 5 6 7 8 9 0";
    ck_assert_str_eq(strtok(whr17, " "), s21_strtok(whr27, " "));
}
END_TEST

START_TEST(test_s21_strerror) {
    int i = -10;
    while (i++ < 132) ck_assert_str_eq(s21_strerror(i), strerror(i));
}
END_TEST

START_TEST(test_s21_to_upper) {
    const char test11[25] = "he1lo W0rld\0";
    const char test12[25] = "HE1LO W0RLD\0";
    ck_assert_str_eq((char *)s21_to_upper(test11), test12);
}
END_TEST

START_TEST(test_s21_to_lower) {
    const char test11[25] = "HE1LO W0RLD\0";
    const char test12[25] = "he1lo w0rld\0";
    ck_assert_str_eq((char *)s21_to_lower(test11), test12);
}
END_TEST

START_TEST(test_s21_insert) {
    char test10[45] = "I want to break free!\0";
    char *test11 = s21_insert(test10, "1111", 6);
    const char test12[45] = "I want1111 to break free!\0";
    ck_assert_str_eq(test11, test12);
    free(test11);

    char test20[45] = " ";
    char *test21 = s21_insert(test20, "ABCD", 2);
    ck_assert_ptr_null(test21);
    free(test21);

    char test30[45] = "I want to break free!\0";
    char *test31  = s21_insert(test30, "", 6);
    const char test32[45] = "I want to break free!\0";
    ck_assert_str_eq(test31, test32);
    free(test31);

    char test40[45] = "I want to break free!\0";
    char *test41 = s21_insert(test40, "ABCD", 21);
    ck_assert_ptr_null(test41);
    free(test41);
}
END_TEST


START_TEST(test_s21_sprintf_d_i_u_signs) {
    char s21sprintf[SMAX] = "\0";
    char original[SMAX] = "\0";
    unsigned int t1 = +65111;
    unsigned int t2 = 47777;
    sprintf(original, \
    "%+-5i %-6i %-4u \\ %10d %% %4u", \
    +-123, -+1234, t1, -890, t2);
    s21_sprintf(s21sprintf, \
    "%+-5i %-6i %-4u \\ %10d %% %4u", \
    +-123, -+1234, t1, -890, t2);
    ck_assert_str_eq(original, s21sprintf);
}
END_TEST

START_TEST(test_s21_sprintf_d_i_u_width) {
    char s21sprintf[SMAX] = "\0";
    char original[SMAX] = "\0";
    unsigned int t1 = +65111;
    unsigned int t2 = 47777;
    sprintf(original, \
    "%+5.6i %-6.2i %-4.2u %10.2d %4u", \
    +-123, -+1234, t1, -890, t2);
    s21_sprintf(s21sprintf, \
    "%+5.6i %-6.2i %-4.2u %10.2d %4u", \
    +-123, -+1234, t1, -890, t2);
    ck_assert_str_eq(original, s21sprintf);
}
END_TEST

START_TEST(test_s21_sprintf_d_i_u_hl) {
    char s21sprintf[SMAX] = "\0";
    char original[SMAX] = "\0";
    short int t1 = 123;
    unsigned long t2 = 1844674407370955161;
    unsigned short t3 = 222;
    short int t4 = 1234;
    sprintf(original, \
    "% 10hi %- 10hi %-10ld %+10ld %-10lu %10hu", \
    t1, t4, 3300000011, 36000000667, t2, t3);
    s21_sprintf(s21sprintf, \
    "% 10hi %- 10hi %-10ld %+10ld %-10lu %10hu", \
    t1, t4, 3300000011, 36000000667, t2, t3);
    ck_assert_str_eq(original, s21sprintf);
}
END_TEST

START_TEST(test_s21_sprintf_s_c) {
    char s21sprintf[SMAX] = "\0";
    char original[SMAX] = "\0";
    sprintf(original, \
    "%6s %-c %-s %-2c %-7s", \
    "12345", '&', "A1b2/34", '\n', "ABCD\nDE");
    s21_sprintf(s21sprintf, \
    "%6s %-c %-s %-2c %-7s", \
    "12345", '&', "A1b2/34", '\n', "ABCD\nDE");
    ck_assert_str_eq(original, s21sprintf);
}

START_TEST(test_s21_sprintf_s_c_precision) {
    char s21sprintf[SMAX] = "\0";
    char original[SMAX] = "\0";
    unsigned long int t1 = 0251;
    unsigned long int t2 = 100;
    sprintf(original, \
    "%.4ls %4lc %2c %-3lc %ls %c %.8s %-1s", \
    L"12345", t1, 104, t2, L"A1b2/34", '\n', "ABCD\nDE", "ttt");
    s21_sprintf(s21sprintf, \
    "%.4ls %4lc %2c %-3lc %ls %c %.8s %-1s", \
    L"12345", t1, 104, t2, L"A1b2/34", '\n', "ABCD\nDE", "ttt");
    ck_assert_str_eq(original, s21sprintf);
}
END_TEST

START_TEST(test_s21_sprintf_f) {
    char s21sprintf[SMAX] = "\0";
    char original[SMAX] = "\0";
    sprintf(original, \
    "%.2f %+.5f %.15f %.15lf %f %.f %.0f %.0f", \
    25.6, -0.1234567890, 0.111244333444, -0.111222333444, 0.0, 10.6, 10.4, 10.50001);
    s21_sprintf(s21sprintf, \
    "%.2f %+.5f %.15f %.15lf %f %.0f %.f %.0f", \
    25.6, -0.1234567890, 0.111244333444, -0.111222333444, 0.0, 10.6, 10.4, 10.50001);
    ck_assert_str_eq(original, s21sprintf);
}
END_TEST

START_TEST(test_s21_sprintf_f_precision) {
    char s21sprintf[SMAX] = "\0";
    char original[SMAX] = "\0";
    sprintf(original, \
    "%.6f %+.15f %2.5f %.7f %2.2f", \
    25.6, -0.1234567890, 0.111222333444, -0.111222333444, 0.0);
    s21_sprintf(s21sprintf, \
    "%.6f %+.15f %2.5f %.7f %2.2f", \
    25.6, -0.1234567890, 0.111222333444, -0.111222333444, 0.0);
    ck_assert_str_eq(original, s21sprintf);
}
END_TEST

Suite *test_lab(void) {
    Suite *all;
    all = suite_create("tests");
    TCase *tst_All;
    tst_All = tcase_create("tests");
    suite_add_tcase(all, tst_All);
    tcase_add_test(tst_All, test_s21_strlen);

    tcase_add_test(tst_All, test_s21_strchr);
    tcase_add_test(tst_All, test_s21_memcmp);
    tcase_add_test(tst_All, test_s21_memchr);
    tcase_add_test(tst_All, test_s21_memcpy);
    tcase_add_test(tst_All, test_s21_memmove);
    tcase_add_test(tst_All, test_s21_memset);
    tcase_add_test(tst_All, test_s21_strcat);
    tcase_add_test(tst_All, test_s21_strcmp);
    tcase_add_test(tst_All, test_s21_strcpy);
    tcase_add_test(tst_All, test_s21_strcspn);
    tcase_add_test(tst_All, test_s21_strncat);
    tcase_add_test(tst_All, test_s21_strncmp);
    tcase_add_test(tst_All, test_s21_strncpy);
    tcase_add_test(tst_All, test_s21_strpbrk);
    tcase_add_test(tst_All, test_s21_strrchr);
    tcase_add_test(tst_All, test_s21_strspn);
    tcase_add_test(tst_All, test_s21_strstr);
    tcase_add_test(tst_All, test_s21_strtok);
    tcase_add_test(tst_All, test_s21_strerror);

    tcase_add_test(tst_All, test_s21_to_upper);
    tcase_add_test(tst_All, test_s21_to_lower);
    tcase_add_test(tst_All, test_s21_insert);
    // tcase_add_test(tst_All, test_s21_trim);

    tcase_add_test(tst_All, test_s21_sprintf_d_i_u_signs);
    tcase_add_test(tst_All, test_s21_sprintf_d_i_u_width);
    tcase_add_test(tst_All, test_s21_sprintf_d_i_u_hl);
    tcase_add_test(tst_All, test_s21_sprintf_s_c);
    tcase_add_test(tst_All, test_s21_sprintf_s_c_precision);
    tcase_add_test(tst_All, test_s21_sprintf_f);
    tcase_add_test(tst_All, test_s21_sprintf_f_precision);

    return all;
}

int main(void) {
    Suite *s;
    SRunner *sr;
    int nf;

    s = test_lab();
    sr = srunner_create(s);
    nf = srunner_ntests_failed(sr);
    srunner_run_all(sr, CK_VERBOSE);

    return (nf == 0 ? 0 : 1);
}
