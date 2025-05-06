#include <stdio.h>
#include <emscripten.h>




EMSCRIPTEN_KEEPALIVE
int addNums(int a,int b){
    return a+b;
}


EMSCRIPTEN_KEEPALIVE
int main(){
    printf("rst: %d\n",addNums(3,6));
    
}