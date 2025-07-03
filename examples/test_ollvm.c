#include <stdio.h>
#include <stdlib.h>
void testpass(int age) {
    if (age < 18) {
        printf("You are a minor.\n");
    } else {
        printf("You are an adult.\n");
    }
}

int test_func(int a) {
    if (a < 10) return a * a;
    if (a > 10) return a + a;
    return -1;
}

int test_func_fla(int a) {
    if (a < 10) return a * a;
    if (a > 10) return a + a;
    return -1;
}

int test_func_fla_bcf(int a) {
    if (a < 10) return a * a;
    if (a > 10) return a + a;
    return -1;
}

void test_ollvm() {
    printf("Testing OLLVM...\n");
    int age = 20;  // Example age
    testpass(age);
    test_func(5);
    test_func_fla(10);
    test_func_fla_bcf(20);
    printf("Test completed.\n");
}
