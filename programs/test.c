// tiny RV32IM test program

volatile int result = 0;

int main() {
    int a = 6;
    int b = 7;

    int mul = a * b;      // MUL
    int div = mul / 3;    // DIV

    result = div;         // expect 14

    // Exit via ECALL
    asm volatile (
        "li a7, 93\n"   // exit syscall
        "li a0, 0\n"    // exit code 0
        "ecall\n"
    );

    __builtin_unreachable();
}
