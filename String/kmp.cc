#include <iostream>
#include <string>

using namespace std;

#define TEST(func, s, t) { \
    printf("%s(%s, %s) = %d\n", #func, s, t, func(s, t)); \
} \

int *getNext(const char *t) {
    int tlen = strlen(t);
    int *next = (int *)malloc(sizeof(int) * tlen);
    next[0] = -1;
    int j = -1; // j 代表 next[i - 1] 的值
    for (int i = 1; t[i]; ++i) {
        while (j != -1 && t[i] != t[j + 1]) {
            j = next[j];
        }
        if (t[i] == t[j + 1]) {
            j += 1;
        }
        next[i] = j;
    }
    return next;
}

int KMP(const char *s, const char *t) {
    int *next = getNext(t);
    int j = -1; // j 指向模式串的已匹配部分的末尾
    int tlen = strlen(t);
    for (int i = 0; s[i]; ++i) {
        while (j != -1 && s[i] != t[j + 1]) {
            j = next[j];
        }
        if (s[i] == t[j + 1]) {
            j += 1;
        }
        if (t[j + 1] == '\0') {
            return i - tlen + 1;
        }
    }
    return -1;
}

int main() {
    char s[100], t[100];
    while (~scanf("%s%s", s, t)) { 
        TEST(KMP, s, t);
    }
    return 0;
}