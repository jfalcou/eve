loadu(signed char const*, eve::fixed<8l>):          
    movsd    xmm0, qword ptr [rdi]           
    ret

loadu(unsigned char const*, eve::fixed<16l>):         
    movups    xmm0, xmmword ptr [rdi]
    ret

loadu(signed char const*, eve::fixed<32l>):         
    mov    rax, rdi
    movups    xmm0, xmmword ptr [rsi]
    movups    xmm1, xmmword ptr [rsi + 16]
    movaps    xmmword ptr [rdi], xmm0
    movaps    xmmword ptr [rdi + 16], xmm1
    ret

loadu(unsigned char const*, eve::fixed<64l>):         
    mov    rax, rdi
    movups    xmm0, xmmword ptr [rsi]
    movups    xmm1, xmmword ptr [rsi + 16]
    movups    xmm2, xmmword ptr [rsi + 32]
    movups    xmm3, xmmword ptr [rsi + 48]
    movaps    xmmword ptr [rdi], xmm0
    movaps    xmmword ptr [rdi + 16], xmm1
    movaps    xmmword ptr [rdi + 32], xmm2
    movaps    xmmword ptr [rdi + 48], xmm3
    ret

loadu(short const*, eve::fixed<4l>):          
    movsd    xmm0, qword ptr [rdi]           
    ret

loadu(unsigned short const*, eve::fixed<8l>):          
    movups    xmm0, xmmword ptr [rdi]
    ret

loadu(short const*, eve::fixed<16l>):         
    mov    rax, rdi
    movups    xmm0, xmmword ptr [rsi]
    movups    xmm1, xmmword ptr [rsi + 16]
    movaps    xmmword ptr [rdi], xmm0
    movaps    xmmword ptr [rdi + 16], xmm1
    ret

loadu(unsigned short const*, eve::fixed<32l>):         
    mov    rax, rdi
    movups    xmm0, xmmword ptr [rsi]
    movups    xmm1, xmmword ptr [rsi + 16]
    movups    xmm2, xmmword ptr [rsi + 32]
    movups    xmm3, xmmword ptr [rsi + 48]
    movaps    xmmword ptr [rdi], xmm0
    movaps    xmmword ptr [rdi + 16], xmm1
    movaps    xmmword ptr [rdi + 32], xmm2
    movaps    xmmword ptr [rdi + 48], xmm3
    ret

loadu(int const*, eve::fixed<2l>):          
    movsd    xmm0, qword ptr [rdi]           
    ret

loadu(unsigned int const*, eve::fixed<4l>):          
    movups    xmm0, xmmword ptr [rdi]
    ret

loadu(int const*, eve::fixed<8l>):          
    mov    rax, rdi
    movups    xmm0, xmmword ptr [rsi]
    movups    xmm1, xmmword ptr [rsi + 16]
    movaps    xmmword ptr [rdi], xmm0
    movaps    xmmword ptr [rdi + 16], xmm1
    ret

loadu(unsigned int const*, eve::fixed<16l>):         
    mov    rax, rdi
    movups    xmm0, xmmword ptr [rsi]
    movups    xmm1, xmmword ptr [rsi + 16]
    movups    xmm2, xmmword ptr [rsi + 32]
    movups    xmm3, xmmword ptr [rsi + 48]
    movaps    xmmword ptr [rdi], xmm0
    movaps    xmmword ptr [rdi + 16], xmm1
    movaps    xmmword ptr [rdi + 32], xmm2
    movaps    xmmword ptr [rdi + 48], xmm3
    ret

loadu(long const*, eve::fixed<1l>):          
    movsd    xmm0, qword ptr [rdi]           
    ret

loadu(unsigned long const*, eve::fixed<2l>):          
    movups    xmm0, xmmword ptr [rdi]
    ret

loadu(int const*, eve::fixed<4l>):          
    movups    xmm0, xmmword ptr [rdi]
    ret

loadu(unsigned int const*, eve::fixed<8l>):          
    mov    rax, rdi
    movups    xmm0, xmmword ptr [rsi]
    movups    xmm1, xmmword ptr [rsi + 16]
    movaps    xmmword ptr [rdi], xmm0
    movaps    xmmword ptr [rdi + 16], xmm1
    ret

loadu(float const*, eve::fixed<2l>):          
    movsd    xmm0, qword ptr [rdi]           
    ret

loadu(float const*, eve::fixed<4l>):          
    movups    xmm0, xmmword ptr [rdi]
    ret

loadu(float const*, eve::fixed<8l>):          
    mov    rax, rdi
    movups    xmm0, xmmword ptr [rsi]
    movups    xmm1, xmmword ptr [rsi + 16]
    movaps    xmmword ptr [rdi], xmm0
    movaps    xmmword ptr [rdi + 16], xmm1
    ret

loadu(float const*, eve::fixed<16l>):         
    mov    rax, rdi
    movups    xmm0, xmmword ptr [rsi]
    movups    xmm1, xmmword ptr [rsi + 16]
    movups    xmm2, xmmword ptr [rsi + 32]
    movups    xmm3, xmmword ptr [rsi + 48]
    movaps    xmmword ptr [rdi], xmm0
    movaps    xmmword ptr [rdi + 16], xmm1
    movaps    xmmword ptr [rdi + 32], xmm2
    movaps    xmmword ptr [rdi + 48], xmm3
    ret

loadu(double const*, eve::fixed<1l>):          
    movsd    xmm0, qword ptr [rdi]           
    ret

loadu(double const*, eve::fixed<2l>):          
    movups    xmm0, xmmword ptr [rdi]
    ret

loadu(double const*, eve::fixed<4l>):          
    mov    rax, rdi
    movups    xmm0, xmmword ptr [rsi]
    movups    xmm1, xmmword ptr [rsi + 16]
    movaps    xmmword ptr [rdi], xmm0
    movaps    xmmword ptr [rdi + 16], xmm1
    ret

loadu(double const*, eve::fixed<8l>):          
    mov    rax, rdi
    movups    xmm0, xmmword ptr [rsi]
    movups    xmm1, xmmword ptr [rsi + 16]
    movups    xmm2, xmmword ptr [rsi + 32]
    movups    xmm3, xmmword ptr [rsi + 48]
    movaps    xmmword ptr [rdi], xmm0
    movaps    xmmword ptr [rdi + 16], xmm1
    movaps    xmmword ptr [rdi + 32], xmm2
    movaps    xmmword ptr [rdi + 48], xmm3
    ret
