loadu(signed char const*, eve::fixed<8l>):  # sse2, sse3, ssse3, sse4
loadu(short const*, eve::fixed<4l>):        # sse2, sse3, ssse3, sse4
loadu(int const*, eve::fixed<2l>):          # sse2, sse3, ssse3, sse4
loadu(long const*, eve::fixed<1l>):         # sse2, sse3, ssse3, sse4
loadu(float const*, eve::fixed<2l>):        # sse2, sse3, ssse3, sse4
loadu(double const*, eve::fixed<1l>):       # sse2, sse3, ssse3, sse4
    movsd    xmm0, qword ptr [rdi]           
    ret


loadu(unsigned char const*, eve::fixed<16l>):  # sse2, sse3, ssse3, sse4
loadu(unsigned short const*, eve::fixed<8l>):  # sse2, sse3, ssse3, sse4
loadu(unsigned int const*, eve::fixed<4l>):    # sse2, sse3, ssse3, sse4
loadu(unsigned long const*, eve::fixed<2l>):   # sse2, sse3, ssse3, sse4
loadu(int const*, eve::fixed<4l>):             # sse2, sse3, ssse3, sse4
loadu(float const*, eve::fixed<4l>):           # sse2, sse3, ssse3, sse4
loadu(double const*, eve::fixed<2l>):          # sse2, sse3, ssse3, sse4
    movups    xmm0, xmmword ptr [rdi]
    ret


loadu(signed char const*, eve::fixed<32l>):  # sse2, sse3, ssse3, sse4
loadu(short const*, eve::fixed<16l>):        # sse2, sse3, ssse3, sse4
loadu(int const*, eve::fixed<8l>):           # sse2, sse3, ssse3, sse4
loadu(unsigned int const*, eve::fixed<8l>):  # sse2, sse3, ssse3, sse4
loadu(float const*, eve::fixed<8l>):         # sse2, sse3, ssse3, sse4
loadu(double const*, eve::fixed<4l>):        # sse2, sse3, ssse3, sse4
    mov    rax, rdi
    movups    xmm0, xmmword ptr [rsi]
    movups    xmm1, xmmword ptr [rsi + 16]
    movaps    xmmword ptr [rdi], xmm0
    movaps    xmmword ptr [rdi + 16], xmm1
    ret


loadu(unsigned char const*, eve::fixed<64l>):   # sse2, sse3, ssse3, sse4
loadu(unsigned short const*, eve::fixed<32l>):  # sse2, sse3, ssse3, sse4
loadu(unsigned int const*, eve::fixed<16l>):    # sse2, sse3, ssse3, sse4
loadu(float const*, eve::fixed<16l>):           # sse2, sse3, ssse3, sse4
loadu(double const*, eve::fixed<8l>):           # sse2, sse3, ssse3, sse4
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


loadu(signed char const*, eve::fixed<8l>):  # avx, avx2
loadu(short const*, eve::fixed<4l>):        # avx, avx2
loadu(int const*, eve::fixed<2l>):          # avx, avx2
loadu(long const*, eve::fixed<1l>):         # avx, avx2
loadu(float const*, eve::fixed<2l>):        # avx, avx2
loadu(double const*, eve::fixed<1l>):       # avx, avx2
    vmovsd    xmm0, qword ptr [rdi]           
    ret


loadu(unsigned char const*, eve::fixed<16l>):  # avx, avx2
loadu(unsigned short const*, eve::fixed<8l>):  # avx, avx2
loadu(unsigned int const*, eve::fixed<4l>):    # avx, avx2
loadu(unsigned long const*, eve::fixed<2l>):   # avx, avx2
loadu(int const*, eve::fixed<4l>):             # avx, avx2
loadu(float const*, eve::fixed<4l>):           # avx, avx2
loadu(double const*, eve::fixed<2l>):          # avx, avx2
    vmovups    xmm0, xmmword ptr [rdi]
    ret


loadu(signed char const*, eve::fixed<32l>):  # avx, avx2
loadu(short const*, eve::fixed<16l>):        # avx, avx2
loadu(int const*, eve::fixed<8l>):           # avx, avx2
loadu(unsigned int const*, eve::fixed<8l>):  # avx, avx2
loadu(float const*, eve::fixed<8l>):         # avx, avx2
loadu(double const*, eve::fixed<4l>):        # avx, avx2
    vmovups    ymm0, ymmword ptr [rdi]
    ret


loadu(unsigned char const*, eve::fixed<64l>):   # avx, avx2
loadu(unsigned short const*, eve::fixed<32l>):  # avx, avx2
loadu(unsigned int const*, eve::fixed<16l>):    # avx, avx2
loadu(float const*, eve::fixed<16l>):           # avx, avx2
loadu(double const*, eve::fixed<8l>):           # avx, avx2
    mov    rax, rdi
    vmovups    ymm0, ymmword ptr [rsi]
    vmovups    ymm1, ymmword ptr [rsi + 32]
    vmovaps    ymmword ptr [rdi], ymm0
    vmovaps    ymmword ptr [rdi + 32], ymm1
    vzeroupper
    ret


