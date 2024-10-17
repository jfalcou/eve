#include "unit/api/compress/compress_test.hpp"

#ifdef SPY_SIMD_IS_RISCV_FIXED_RVV
using types = tts::filter<rvv_compress_filter, eve::test::simd::all_types>::type;
#else
using types = eve::test::simd::all_types;
#endif

TTS_CASE_WITH("Check compress behavior", types, tts::generate(tts::ramp(1)))
<typename T> (T data)
{
  compress_test<eve::logical<T>>(data);
};
