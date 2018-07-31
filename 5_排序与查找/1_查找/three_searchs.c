/*************************************************************************
	> File Name: three_point_search.c
	> Author: moying
	> Mail: 996941856@qq.com
	> Created Time: 2018年07月28日 星期六 15时29分49秒
 ************************************************************************/

#include<stdio.h>



int binary_search1(int *num, int n, int x) {   //正常二分查找
    int head = 0, tail = n - 1, mid ;
    while(head <= tail) {
        mid = (head + tail) >> 1;
        if(num[mid] == x) return mid;
        if(num[mid] < x) head = mid + 1;
        else tail = mid - 1;
    }
    return -1;
}
//111111100000000000           
int binary_search2(int *num, int n, int x) {
    int head = -1, tail = n - 1, mid;
    while(head < tail) {
        mid = (head + tail + 1) >> 1;
        if(num[mid] == 1) {
            head = mid;
        } else {
            tail = mid - 1;
        }
    }
    return head;
}
//00000001111111111
int binary_search3(int *num, int n, int x) {
    int head = 0, tail = n, mid;
    while(head < tail) {
        mid = (head + tail) >> 1;
        if(num[mid] == 1) {
            tail = mid;
        } else {
            head = mid + 1;
        }
    }
    return head == n ? -1 : head;

}
