#include <stdio.h>
#include "head.h"

int main()
{
    int a = 20;
    int b = 12;
// 如果定义了DEBUG，则输出debug信息
#ifdef DEBUG 
    printf("这是一行debug内容\n");
#endif
    printf("a = %d, b = %d\n", a, b);
    printf("a + b = %d\n", add(a, b));
    printf("a - b = %d\n", subtract(a, b));
    printf("a * b = %d\n", multiply(a, b));
    printf("a / b = %f\n", divide(a, b));
    return 0;
}


