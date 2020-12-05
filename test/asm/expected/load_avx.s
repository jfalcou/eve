load(eve::aligned_ptr<signed char const, 8ul>, eve::fixed<8l>): 
    vmovsd    xmm0, qword ptr [rdi]           
    ret

load(eve::aligned_ptr<unsigned char const, 16ul>, eve::fixed<16l>): 
    vmovaps    xmm0, xmmword ptr [rdi]
    ret

load(eve::aligned_ptr<signed char const, 32ul>, eve::fixed<32l>): 
    vmovaps    ymm0, ymmword ptr [rdi]
    ret

load(eve::aligned_ptr<unsigned char const, 64ul>, eve::fixed<64l>): 
    mov    rax, rdi
    vmovaps    ymm0, ymmword ptr [rsi]
    vmovaps    ymm1, ymmword ptr [rsi + 32]
    vmovaps    ymmword ptr [rdi], ymm0
    vmovaps    ymmword ptr [rdi + 32], ymm1
    vzeroupper
    ret

load(eve::aligned_ptr<short const, 8ul>, eve::fixed<4l>): 
    vmovsd    xmm0, qword ptr [rdi]           
    ret

load(eve::aligned_ptr<unsigned short const, 16ul>, eve::fixed<8l>): 
    vmovaps    xmm0, xmmword ptr [rdi]
    ret

load(eve::aligned_ptr<short const, 32ul>, eve::fixed<16l>): 
    vmovaps    ymm0, ymmword ptr [rdi]
    ret

load(eve::aligned_ptr<unsigned short const, 64ul>, eve::fixed<32l>): 
    mov    rax, rdi
    vmovaps    ymm0, ymmword ptr [rsi]
    vmovaps    ymm1, ymmword ptr [rsi + 32]
    vmovaps    ymmword ptr [rdi], ymm0
    vmovaps    ymmword ptr [rdi + 32], ymm1
    vzeroupper
    ret

load(eve::aligned_ptr<int const, 8ul>, eve::fixed<2l>): 
    vmovsd    xmm0, qword ptr [rdi]           
    ret

load(eve::aligned_ptr<unsigned int const, 16ul>, eve::fixed<4l>): 
    vmovaps    xmm0, xmmword ptr [rdi]
    ret

load(eve::aligned_ptr<int const, 32ul>, eve::fixed<8l>): 
    vmovaps    ymm0, ymmword ptr [rdi]
    ret

load(eve::aligned_ptr<unsigned int const, 64ul>, eve::fixed<16l>): 
    mov    rax, rdi
    vmovaps    ymm0, ymmword ptr [rsi]
    vmovaps    ymm1, ymmword ptr [rsi + 32]
    vmovaps    ymmword ptr [rdi], ymm0
    vmovaps    ymmword ptr [rdi + 32], ymm1
    vzeroupper
    ret

load(eve::aligned_ptr<long const, 8ul>, eve::fixed<1l>): 
    vmovsd    xmm0, qword ptr [rdi]           
    ret

load(eve::aligned_ptr<unsigned long const, 16ul>, eve::fixed<2l>): 
    vmovaps    xmm0, xmmword ptr [rdi]
    ret

load(eve::aligned_ptr<int const, 16ul>, eve::fixed<4l>): 
    vmovaps    xmm0, xmmword ptr [rdi]
    ret

load(eve::aligned_ptr<unsigned int const, 32ul>, eve::fixed<8l>): 
    vmovaps    ymm0, ymmword ptr [rdi]
    ret

load(eve::aligned_ptr<float const, 8ul>, eve::fixed<2l>): 
    vmovsd    xmm0, qword ptr [rdi]           
    ret

load(eve::aligned_ptr<float const, 16ul>, eve::fixed<4l>): 
    vmovaps    xmm0, xmmword ptr [rdi]
    ret

load(eve::aligned_ptr<float const, 32ul>, eve::fixed<8l>): 
    vmovaps    ymm0, ymmword ptr [rdi]
    ret

load(eve::aligned_ptr<float const, 64ul>, eve::fixed<16l>): 
    mov    rax, rdi
    vmovaps    ymm0, ymmword ptr [rsi]
    vmovaps    ymm1, ymmword ptr [rsi + 32]
    vmovaps    ymmword ptr [rdi], ymm0
    vmovaps    ymmword ptr [rdi + 32], ymm1
    vzeroupper
    ret

load(eve::aligned_ptr<double const, 8ul>, eve::fixed<1l>): 
    vmovsd    xmm0, qword ptr [rdi]           
    ret

load(eve::aligned_ptr<double const, 16ul>, eve::fixed<2l>): 
    vmovaps    xmm0, xmmword ptr [rdi]
    ret

load(eve::aligned_ptr<double const, 32ul>, eve::fixed<4l>): 
    vmovaps    ymm0, ymmword ptr [rdi]
    ret

load(eve::aligned_ptr<double const, 64ul>, eve::fixed<8l>): 
    mov    rax, rdi
    vmovaps    ymm0, ymmword ptr [rsi]
    vmovaps    ymm1, ymmword ptr [rsi + 32]
    vmovaps    ymmword ptr [rdi], ymm0
    vmovaps    ymmword ptr [rdi + 32], ymm1
    vzeroupper
    ret
