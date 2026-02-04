#ifndef ISR_H
#define ISR_H
struct registers {
    uint64_t r15, r14, r13, r12, r11, r10, r9, r8;
    uint64_t rsi, rdi, rbp, rdx, rcx, rbx, rax, rsp;
    uint64_t error_code;
    uint64_t vector;
    uint64_t rip;
    uint64_t cs;
    uint64_t rflags;
};
__attribute__((noreturn))
void print_error(struct registers *reg);
void init_isr();
#endif