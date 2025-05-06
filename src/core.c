#include <stdio.h>
#include <emscripten.h>
#include <stdlib.h> // malloc, free 사용을 위해 필요
#include <string.h> // strcpy, strlen 등 문자열 함수 사용을 위해 필요


struct Plan
{
    int index;
    int x;
    int y;
    char *title; // 문자열을 가리키는 포인터
    char *content; // 문자열을 가리키는 포인터
    char *created_at; // 문자열을 가리키는 포인터
};

EMSCRIPTEN_KEEPALIVE
int main() {
    struct Plan plan1;
    plan1.index=1;
    printf("%d\n",plan1.index);
    printf("WASM 모듈 초기화 중...\n");
    return 0;
};


EMSCRIPTEN_KEEPALIVE
int add_numbers(int a, int b) {
    return a + b;
}