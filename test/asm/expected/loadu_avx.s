loadu(signed char const*, eve::fixed<8l>):          
    vmovsd    xmm0, qword ptr [rdi]           
    ret

loadu(unsigned char const*, eve::fixed<16l>):         
    vmovups    xmm0, xmmword ptr [rdi]
    ret

loadu(signed char const*, eve::fixed<32l>):         
    vmovups    ymm0, ymmword ptr [rdi]
    ret

loadu(unsigned char const*, eve::fixed<64l>):         
    mov    rax, rdi
    vmovups    ymm0, ymmword ptr [rsi]
    vmovups    ymm1, ymmword ptr [rsi + 32]
    vmovaps    ymmword ptr [rdi], ymm0
    vmovaps    ymmword ptr [rdi + 32], ymm1
    vzeroupper
    ret

loadu(short const*, eve::fixed<4l>):          
    vmovsd    xmm0, qword ptr [rdi]           
    ret

loadu(unsigned short const*, eve::fixed<8l>):          
    vmovups    xmm0, xmmword ptr [rdi]
    ret

loadu(short const*, eve::fixed<16l>):         
    vmovups    ymm0, ymmword ptr [rdi]
    ret

loadu(unsigned short const*, eve::fixed<32l>):         
    mov    rax, rdi
    vmovups    ymm0, ymmword ptr [rsi]
    vmovups    ymm1, ymmword ptr [rsi + 32]
    vmovaps    ymmword ptr [rdi], ymm0
    vmovaps    ymmword ptr [rdi + 32], ymm1
    vzeroupper
    ret

loadu(int const*, eve::fixed<2l>):          
    vmovsd    xmm0, qword ptr [rdi]           
    ret

loadu(unsigned int const*, eve::fixed<4l>):          
    vmovups    xmm0, xmmword ptr [rdi]
    ret

loadu(int const*, eve::fixed<8l>):          
    vmovups    ymm0, ymmword ptr [rdi]
    ret

loadu(unsigned int const*, eve::fixed<16l>):         
    mov    rax, rdi
    vmovups    ymm0, ymmword ptr [rsi]
    vmovups    ymm1, ymmword ptr [rsi + 32]
    vmovaps    ymmword ptr [rdi], ymm0
    vmovaps    ymmword ptr [rdi + 32], ymm1
    vzeroupper
    ret

loadu(long const*, eve::fixed<1l>):          
    vmovsd    xmm0, qword ptr [rdi]           
    ret

loadu(unsigned long const*, eve::fixed<2l>):          
    vmovups    xmm0, xmmword ptr [rdi]
    ret

loadu(int const*, eve::fixed<4l>):          
    vmovups    xmm0, xmmword ptr [rdi]
    ret

loadu(unsigned int const*, eve::fixed<8l>):          
    vmovups    ymm0, ymmword ptr [rdi]
    ret

loadu(float const*, eve::fixed<2l>):          
    vmovsd    xmm0, qword ptr [rdi]           
    ret

loadu(float const*, eve::fixed<4l>):          
    vmovups    xmm0, xmmword ptr [rdi]
    ret

loadu(float const*, eve::fixed<8l>):          
    vmovups    ymm0, ymmword ptr [rdi]
    ret

loadu(float const*, eve::fixed<16l>):         
    mov    rax, rdi
    vmovups    ymm0, ymmword ptr [rsi]
    vmovups    ymm1, ymmword ptr [rsi + 32]
    vmovaps    ymmword ptr [rdi], ymm0
    vmovaps    ymmword ptr [rdi + 32], ymm1
    vzeroupper
    ret

loadu(double const*, eve::fixed<1l>):          
    vmovsd    xmm0, qword ptr [rdi]           
    ret

loadu(double const*, eve::fixed<2l>):          
    vmovups    xmm0, xmmword ptr [rdi]
    ret

loadu(double const*, eve::fixed<4l>):          
    vmovups    ymm0, ymmword ptr [rdi]
    ret

loadu(double const*, eve::fixed<8l>):          
    mov    rax, rdi
    vmovups    ymm0, ymmword ptr [rsi]
    vmovups    ymm1, ymmword ptr [rsi + 32]
    vmovaps    ymmword ptr [rdi], ymm0
    vmovaps    ymmword ptr [rdi + 32], ymm1
    vzeroupper
    ret
