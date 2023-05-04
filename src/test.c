#include <stdio.h>

void main() {
   int *p; // 주소를 ㅈ
   int a = 123;
   p = &a;

    printf("%p\n",&p);

    printf("%p\n", p);
    printf("%p\n",&a);

    printf("%d\n", a);

    *p = 345;

    printf("%d\n", a);
    int b = 345;
    const int* pa = &a; // pa가 가리키는 변수의 값을 바꾸지마라, 즉 pa 에 할당된 a 의 값을 바꾸지마!
    pa = &b;            // 가능
    int* const pa = &a; //
}