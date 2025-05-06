#include <stdio.h>
#include <emscripten.h>

int main() {
    printf("Hello from C in Docker WASM env!\n");
    return 0;
}

EMSCRIPTEN_KEEPALIVE
int add_numbers(int a, int b) {
    return a + b;
}