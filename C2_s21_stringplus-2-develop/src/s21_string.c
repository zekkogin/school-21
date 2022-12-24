#include "s21_string.h"
#include <stdio.h>

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
    const unsigned char *p_str1 = str1;
    const unsigned char *p_str2 = str2;
    int dif = 0;
    while (n--) {
        if (*p_str1 != *p_str2)
            dif = *p_str1 - *p_str2;
        else
            p_str1++, p_str2++;
    }
    p_str1 = s21_NULL;
    p_str2 = s21_NULL;
    return dif;
}

void *s21_memchr(const void *str, int c, s21_size_t n) {
    unsigned char *str1 = (unsigned char *)str;
    unsigned char pc = (unsigned char)c;
    void *p_str1 = s21_NULL;
    while (n--)
        if (*str1 != pc)
            str1++;
        else
            p_str1 = str1;
    return p_str1;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
    char *dest1 = dest;
    const char *src1 = src;
    while (n--) {
        *dest1 = *src1;
        dest1++;
        src1++;
    }
    return dest;
}

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
    char *pdest = (char *)dest;
    char *psrc = (char *)src;
    char tmp[50];
    for (int i = 0; i < n; i++) {
        tmp[i] = psrc[i];
        pdest[i] = tmp[i];
    }
    return pdest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
    unsigned char *pstr = (unsigned char *)str;
    while (n--) {
        *pstr = (unsigned char)c;
        pstr++;
    }
    pstr = s21_NULL;
    return str;
}

char *s21_strcat(char *dest, const char *src) {
    char *end_of_dest = dest + s21_strlen(dest);
    while (*src != '\0') {
        *end_of_dest = *src;
        end_of_dest++;
        src++;
    }
    return dest;
}

char *s21_strchr(const char *str, int c) {
    for (; *str != (char)c && *str; str++) {
    }
    return (*str == c ? (char *)str : 0);
}

int s21_strcmp(const char *str1, const char *str2) {
    for (; *str1 && (*str1 == *str2); str1++, str2++) {
    }
    int dif = *(unsigned char *)str1 - *(unsigned char *)str2;
    return dif;
}

char *s21_strcpy(char *dest, const char *src) {
    char *ptr_to_dest = dest;
    while (*src != '\0') {
        *ptr_to_dest = *src;
        ptr_to_dest++;
        src++;
    }
    *ptr_to_dest = '\0';
    return dest;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
    s21_size_t count = 0;
    s21_size_t test = 0;
    while (*str1 != '\0' && test == 0) {
        if (s21_strchr(str2, *str1)) {
            test = 1;
            count--;
        }
        count++;
        str1++;
    }
    return count;
}

s21_size_t s21_strlen(const char *str) {
    s21_size_t len = 0;
    if (str != s21_NULL)
        while (*str++) ++len;
    return len;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
    s21_size_t end_of_dest = s21_strlen(dest);
    s21_size_t i = 0;
    for (; i < n && src[i]; i++) {
        dest[end_of_dest + i] = src[i];
    }
    dest[end_of_dest + i] = '\0';
    return dest;
}


int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
    int result = 0;
    if (str1 && str2 && n > 0) {
        for (s21_size_t i = 0; i < n; i++) {
            if (str1[i]  == '\0' || str1[i] != str2[i]) {
                result = str1[i] - str2[i];
                break;
            }
        }
    }

    return result;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
    size_t i = n;
    while (i > 0) {
        *dest = *src;
        dest++;
        src++;
        i--;
    }
    return (dest - n);
}

char *s21_strpbrk(const char *str1, const char *str2) {
    const char *pstr1 = str1;
    const char *pstr2 = str2;
    int counter = 1;
    char *res = s21_NULL;
    while (*pstr1 != '\0' && counter == 1) {
        char sym = *pstr1;
        if (s21_strchr(pstr2, sym) != s21_NULL) {
        res = (char *)pstr1;
        counter = 0;
        }
        pstr1++;
    }
    return res;
}

    char *s21_strrchr(const char *str, int c) {
    int i = s21_strlen(str);
    char *dest = s21_NULL;
    while (i >= 0) {
        if (str[i] == (char)c) {
            dest = (char *)str + i;
            break;
        } else {
            i--;
        }
    }
    return dest;
}

    s21_size_t s21_strspn(const char *str1, const char *str2) {
    s21_size_t count = 0;
    while (*str1 != '\0' && s21_strchr(str2, *str1) != 0) {
        count++;
        str1++;
    }
    return count;
}


char *s21_strstr(const char *haystack, const char *needle) {
    char *phay = s21_NULL;
    if (s21_strlen(haystack) >= s21_strlen(needle)) {
        for (s21_size_t i = 0; i <= s21_strlen(haystack) - s21_strlen(needle); i++) {
            int found = 0;
            for (s21_size_t j = 0; needle[j]; j++) {
                if (haystack[i + j] != needle[j]) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                phay = (char *)haystack + i;
                break;
            }
        }
    }
    return phay;
}

char *s21_strtok(char *str, const char *delim) {
    static char *p_str = s21_NULL;
    if (str)
        p_str = str;
    if (p_str) {
        str = p_str + s21_strspn(p_str, delim);
        p_str = str + s21_strcspn(str, delim);
        if (*p_str != '\0') {
            *p_str = '\0';
            ++p_str;
        }
    }
    return *str != '\0' ? str : s21_NULL;
}

char *s21_strerror(int errnum) {
    static char buffer2[1024] = {'\0'};
    if (errnum == -1) {
        s21_strcpy(buffer2, "Unknown error: -1");
    } else if (errnum >= 0 && errnum < (int)EMAX) {
        const char *error[] = S21_ERRORS;
        s21_strcpy(buffer2, error[errnum]);
    } else {
        s21_sprintf(buffer2, "Unknown error: %d", errnum);
    }
    return buffer2;
}

void *s21_to_upper(const char *str) {
    char *buffer = s21_NULL;
    if (str) {
        buffer = (char *)calloc(s21_strlen(str) + 1, sizeof(char));
        char *up = UP;
        char *low = LOW;
        for (int i = 0; str[i] != '\0'; i++) {
            buffer[i] = str[i];
            for (int j = 0; low[j] != '\0'; j++) {
                if (str[i] == low[j]) {
                    buffer[i] = up[j];
                } else {
                    continue;
                }
            }
        }
    }
    return (void *)buffer;
}

void *s21_to_lower(const char *str) {
    char *buffer = s21_NULL;
    if (str) {
        buffer = (char *)calloc(s21_strlen(str) + 1, sizeof(char));
        char *up = UP;
        char *low = LOW;
        for (int i = 0; str[i] != '\0'; i++) {
            buffer[i] = str[i];
            for (int j = 0; up[j] != '\0'; j++) {
                if (str[i] == up[j]) {
                    buffer[i] = low[j];
                } else {
                    continue;
                }
            }
        }
    }
    return buffer;
}


void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
    char *buffer = s21_NULL;
    s21_size_t len_src = s21_strlen(src);
    s21_size_t len_str = s21_strlen(str);
    if (str && src) {
        if (s21_strlen(src) >= start_index) {
            if (len_src >= len_str + start_index) {
                s21_size_t length = len_str + len_src;
                buffer = (char *)calloc(length + 1, sizeof(char));
                s21_size_t j = 0;
                for (s21_size_t i = 0; src[i]; i++) {
                    if (i == start_index) {
                        while (str[j] != '\0') {
                            buffer[i + j] = str[j];
                            j++;
                        }
                    }
                    buffer[i + j] = src[i];
                }
            }
        }
    }
    return (void *)buffer;
}
