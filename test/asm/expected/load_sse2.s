load(eve::aligned_ptr<signed char const, 8ul>, eve::fixed<8l>): 
    movsd    xmm0, qword ptr [rdi]           
    ret

load(eve::aligned_ptr<unsigned char const, 16ul>, eve::fixed<16l>): 
    movaps    xmm0, xmmword ptr [rdi]
    ret

load(eve::aligned_ptr<signed char const, 32ul>, eve::fixed<32l>): 
    mov    rax, rdi
    movaps    xmm0, xmmword ptr [rsi]
    movaps    xmm1, xmmword ptr [rsi + 16]
    movaps    xmmword ptr [rdi], xmm0
    movaps    xmmword ptr [rdi + 16], xmm1
    ret

load(eve::aligned_ptr<unsigned char const, 64ul>, eve::fixed<64l>): 
    mov    rax, rdi
    movaps    xmm0, xmmword ptr [rsi]
    movaps    xmm1, xmmword ptr [rsi + 16]
    movaps    xmm2, xmmword ptr [rsi + 32]
    movaps    xmm3, xmmword ptr [rsi + 48]
    movaps    xmmword ptr [rdi], xmm0
    movaps    xmmword ptr [rdi + 16], xmm1
    movaps    xmmword ptr [rdi + 32], xmm2
    movaps    xmmword ptr [rdi + 48], xmm3
    ret

load(eve::aligned_ptr<short const, 8ul>, eve::fixed<4l>): 
    movsd    xmm0, qword ptr [rdi]           
    ret

load(eve::aligned_ptr<unsigned short const, 16ul>, eve::fixed<8l>): 
    movaps    xmm0, xmmword ptr [rdi]
    ret

load(eve::aligned_ptr<short const, 32ul>, eve::fixed<16l>): 
    mov    rax, rdi
    movaps    xmm0, xmmword ptr [rsi]
    movaps    xmm1, xmmword ptr [rsi + 16]
    movaps    xmmword ptr [rdi], xmm0
    movaps    xmmword ptr [rdi + 16], xmm1
    ret

load(eve::aligned_ptr<unsigned short const, 64ul>, eve::fixed<32l>): 
    mov    rax, rdi
    movaps    xmm0, xmmword ptr [rsi]
    movaps    xmm1, xmmword ptr [rsi + 16]
    movaps    xmm2, xmmword ptr [rsi + 32]
    movaps    xmm3, xmmword ptr [rsi + 48]
    movaps    xmmword ptr [rdi], xmm0
    movaps    xmmword ptr [rdi + 16], xmm1
    movaps    xmmword ptr [rdi + 32], xmm2
    movaps    xmmword ptr [rdi + 48], xmm3
    ret

load(eve::aligned_ptr<int const, 8ul>, eve::fixed<2l>): 
    movsd    xmm0, qword ptr [rdi]           
    ret

load(eve::aligned_ptr<unsigned int const, 16ul>, eve::fixed<4l>): 
    movaps    xmm0, xmmword ptr [rdi]
    ret

load(eve::aligned_ptr<int const, 32ul>, eve::fixed<8l>): 
    mov    rax, rdi
    movaps    xmm0, xmmword ptr [rsi]
    movaps    xmm1, xmmword ptr [rsi + 16]
    movaps    xmmword ptr [rdi], xmm0
    movaps    xmmword ptr [rdi + 16], xmm1
    ret

load(eve::aligned_ptr<unsigned int const, 64ul>, eve::fixed<16l>): 
    mov    rax, rdi
    movaps    xmm0, xmmword ptr [rsi]
    movaps    xmm1, xmmword ptr [rsi + 16]
    movaps    xmm2, xmmword ptr [rsi + 32]
    movaps    xmm3, xmmword ptr [rsi + 48]
    movaps    xmmword ptr [rdi], xmm0
    movaps    xmmword ptr [rdi + 16], xmm1
    movaps    xmmword ptr [rdi + 32], xmm2
    movaps    xmmword ptr [rdi + 48], xmm3
    ret

load(eve::aligned_ptr<long const, 8ul>, eve::fixed<1l>): 
    movsd    xmm0, qword ptr [rdi]           
    ret

load(eve::aligned_ptr<unsigned long const, 16ul>, eve::fixed<2l>): 
    movaps    xmm0, xmmword ptr [rdi]
    ret

load(eve::aligned_ptr<int const, 16ul>, eve::fixed<4l>): 
    movaps    xmm0, xmmword ptr [rdi]
    ret

load(eve::aligned_ptr<unsigned int const, 32ul>, eve::fixed<8l>): 
    mov    rax, rdi
    movaps    xmm0, xmmword ptr [rsi]
    movaps    xmm1, xmmword ptr [rsi + 16]
    movaps    xmmword ptr [rdi], xmm0
    movaps    xmmword ptr [rdi + 16], xmm1
    ret

load(eve::aligned_ptr<float const, 8ul>, eve::fixed<2l>): 
    movsd    xmm0, qword ptr [rdi]           
    ret

load(eve::aligned_ptr<float const, 16ul>, eve::fixed<4l>): 
    movaps    xmm0, xmmword ptr [rdi]
    ret

load(eve::aligned_ptr<float const, 32ul>, eve::fixed<8l>): 
    mov    rax, rdi
    movaps    xmm0, xmmword ptr [rsi]
    movaps    xmm1, xmmword ptr [rsi + 16]
    movaps    xmmword ptr [rdi], xmm0
    movaps    xmmword ptr [rdi + 16], xmm1
    ret

load(eve::aligned_ptr<float const, 64ul>, eve::fixed<16l>): 
    mov    rax, rdi
    movaps    xmm0, xmmword ptr [rsi]
    movaps    xmm1, xmmword ptr [rsi + 16]
    movaps    xmm2, xmmword ptr [rsi + 32]
    movaps    xmm3, xmmword ptr [rsi + 48]
    movaps    xmmword ptr [rdi], xmm0
    movaps    xmmword ptr [rdi + 16], xmm1
    movaps    xmmword ptr [rdi + 32], xmm2
    movaps    xmmword ptr [rdi + 48], xmm3
    ret

load(eve::aligned_ptr<double const, 8ul>, eve::fixed<1l>): 
    movsd    xmm0, qword ptr [rdi]           
    ret

load(eve::aligned_ptr<double const, 16ul>, eve::fixed<2l>): 
    movaps    xmm0, xmmword ptr [rdi]
    ret

load(eve::aligned_ptr<double const, 32ul>, eve::fixed<4l>): 
    mov    rax, rdi
    movaps    xmm0, xmmword ptr [rsi]
    movaps    xmm1, xmmword ptr [rsi + 16]
    movaps    xmmword ptr [rdi], xmm0
    movaps    xmmword ptr [rdi + 16], xmm1
    ret

load(eve::aligned_ptr<double const, 64ul>, eve::fixed<8l>): 
    mov    rax, rdi
    movaps    xmm0, xmmword ptr [rsi]
    movaps    xmm1, xmmword ptr [rsi + 16]
    movaps    xmm2, xmmword ptr [rsi + 32]
    movaps    xmm3, xmmword ptr [rsi + 48]
    movaps    xmmword ptr [rdi], xmm0
    movaps    xmmword ptr [rdi + 16], xmm1
    movaps    xmmword ptr [rdi + 32], xmm2
    movaps    xmmword ptr [rdi + 48], xmm3
    ret
