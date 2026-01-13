.global _start
_start:
    addi x3, x0, 5
    addi x3, x3, 7   # x3 = 12

    li a7, 93
    li a0, 0
    ecall
