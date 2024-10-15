#include "unit/api/compress/compress_test.hpp"
#ifdef SPY_SIMD_IS_RISCV_FIXED_RVV
using types = tts::filter<rvv_compress_filter, eve::test::simd::all_types>::type;
#else
using types = eve::test::simd::all_types;
#endif

TTS_CASE_WITH("Check compress behavior for logicals", types, tts::generate(tts::logicals(1, 2)))
<typename L> (L logical_data)
{
  using N = eve::fixed<L::size()>;

  smaller_test_for<L>(logical_data);
  smaller_test_for<eve::logical<eve::wide<std::uint8_t,  N>>>(logical_data);
  smaller_test_for<eve::logical<eve::wide<std::uint16_t, N>>>(logical_data);
  smaller_test_for<eve::logical<eve::wide<std::uint32_t, N>>>(logical_data);
  smaller_test_for<eve::logical<eve::wide<std::uint64_t, N>>>(logical_data);
};
