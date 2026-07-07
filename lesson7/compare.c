#include <stdio.h>

// Macro constant (true compile-time constant)
#define SIZE_MACRO 5

// const variable (read-only variable, NOT a compile-time constant in C)
const int SIZE_CONST = 5;

int main(void)
{
    // Using #define: OK in all C standards
    int arr_macro[SIZE_MACRO];
    printf("Array defined with #define: size = %zu\n", sizeof(arr_macro)/sizeof(arr_macro[0]));

    // Using const: this creates a VLA (Variable Length Array) in C99/C11
    // In C89, this would be an ERROR because VLA is not supported
    int arr_const[SIZE_CONST];
    printf("Array defined with const:   size = %zu\n", sizeof(arr_const)/sizeof(arr_const[0]));

    // Verify the addresses: const variable has an address (it's a real variable)
    printf("\nAddresses:\n");
    printf("  SIZE_CONST  : %p (value = %d)\n", (void*)&SIZE_CONST, SIZE_CONST);
    printf("  arr_macro   : %p\n", (void*)arr_macro);
    printf("  arr_const   : %p\n", (void*)arr_const);

    return 0;
}