/*************************************************************************
	> File Name: 1_string_algorithm.c
	> Author: moying
	> Mail: 996941856@qq.com
	> Created Time: 2018年08月02日 星期四 20时35分43秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int BF(const char *text, const char *pattern, int *p_cnt) {
    #define cnt (*p_cnt)
    int len1 = strlen(text);
    int len2 = strlen(pattern);
    for(int i = 0; i < len1 - len2 + 1; ++i, ++cnt) {
        int flag = 1;
        for(int j = 0; pattern[j] && flag; ++j, ++cnt) {
            if(text[i + j] == pattern[j])continue;
            flag = 0;
        }
        if(flag) return 1;
    }
    return 0;
    #undef cnt
}

int KMP(const char *text, const char *pattern, int *p_cnt) {
    #define cnt (*p_cnt)
    #define RETURN(a) {\
        free(next);\
        return a;\
    }
    
    int len1 = strlen(text);
    int len2 = strlen(pattern);
    int *next = (int *)malloc(sizeof(int) * len2);
    next[0] = -1;
    int j = -1;
    for(int i = 1; i < len2; ++i, ++cnt) {
        while(j >= 0 && pattern[j + 1] != pattern[i]) j = next[j], ++cnt;
        if(pattern[j + 1] == pattern[i]) j++;
        next[i] = j;
    }
    j = -1;
    for(int i = 0; text[i]; ++i, ++cnt) {
        while(j >= 0 && pattern[j + 1] != text[i]) j = next[j], ++cnt;
        if(pattern[j + 1] == text[i]) j++;
        if(j == len2 - 1) RETURN(i - j);
    }
    RETURN(-1);
    #undef cnt
    #undef RETURN
}





int main() {
    char str1[] = "hello world";
    int cnt = 0;
    
    printf("BF(%s,%s) == %d\n", str1, "wor", BF(str1, "wor", &cnt));
    printf("cnt = %d\n", cnt);
    cnt = 0;
    printf("KMP(%s,%s) == %d\n", str1, "wor", KMP(str1, "wor", &cnt));
    printf("cnt = (%d)\n", cnt);
    
    
    return 0;
}
