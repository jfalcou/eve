#include "unit/api/compress/compress_test.hpp"

TTS_CASE_WITH( "Check compress behavior for logicals"
        , eve::test::simd::all_types
        , tts::generate(tts::logicals(1,2))
        )
<typename L> (L logical_data)
{
  using N = eve::fixed<L::size()>;

  smaller_test_for<L>(logical_data);
  smaller_test_for<eve::logical<eve::wide<std::uint8_t,  N>>>(logical_data);
  smaller_test_for<eve::logical<eve::wide<std::uint16_t, N>>>(logical_data);
  smaller_test_for<eve::logical<eve::wide<std::uint32_t, N>>>(logical_data);
  smaller_test_for<eve::logical<eve::wide<std::uint64_t, N>>>(logical_data);
};
