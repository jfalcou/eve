#include "unit/api/compress/compress_test.hpp"

TTS_CASE_WITH("Check compress behavior",
              simd_types_for_compress<eve::test::simd::all_types>,
              tts::generate(tts::ramp(1)))
<typename T> (T data)
{
  compress_test<eve::logical<T>>(data);
};
