### **题目    28. 实现strStr()**

#### 题目描述
实现 strStr() 函数。

给定一个 haystack 字符串和一个 needle 字符串，在 haystack 字符串中找出 needle 字符串出现的第一个位置 (从0开始)。如果不存在，则返回  -1。
#### 示例 1:
```
输入: haystack = "hello", needle = "ll"
输出: 2
```
#### 示例 2:
```
输入: haystack = "aaaaa", needle = "bba"
输出: -1
```
**说明:**
当 needle 是空字符串时，我们应当返回什么值呢？这是一个在面试中很好的问题。
对于本题而言，当 needle 是空字符串时我们应当返回 0 。这与C语言的 strstr() 以及 Java的 indexOf() 定义相符。

#### 解析
这题用的sunday 字符串匹配算法, 先预处理needle字符串, 之后正常匹配,匹配返回下标.
注意字符串为空的情况
#### 代码
```
int strStr(char* haystack, char* needle) {
    int len = strlen(needle);
    int len1 = strlen(haystack);
    if(!len) return 0;
    int p[128] = {0};
    for(int i = 0; i < 128; ++i) p[i] = len;
    for(int i = 0; needle[i]; ++i) p[needle[i]] = len - i;
    
    for(int i = 0; i < strlen(haystack) - len + 1;) {
        int j = 0;
        for(; j < len; ++j) {
            if(needle[j] != haystack[i + j]) break;  
        }
        if(j == len) return i;
        if(i + len > len1 - 1) return -1;
        i += p[haystack[i + len]];
    }
    return -1;
}
```
























