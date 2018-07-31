/*************************************************************************
	> File Name: three_search.c
	> Author: moying
	> Mail: 996941856@qq.com
	> Created Time: 2018年07月28日 星期六 14时59分17秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
double f(double x, double a, double b, double c) {
    return a * x * x + b * x + c;
}

double three_point_search(double a, double b, double c) {  
    #define EPS 1e-6
    double head = -10000, tail = 10000, m1, m2;
    if(a > 0) {
        a = -a, b = -b, c = -c;
    }
    while(fabs(tail - head) > EPS) {
        m1 = (tail - head) / 3 + head;
        m2 = (tail - head) / 3 * 2 + head;
        if(f(m1, a, b, c) < f(m2, a, b, c)) {
            head = m1;
        } else {
            tail = m2;
        }
    }
    return head;
}


int main() {
    double a, b, c;
    while(~scanf("%lf%lf%lf", &a, &b, &c))  {
        printf("%lf\n", three_point_search(a, b, c));
    }
    
    
    return 0;
}
