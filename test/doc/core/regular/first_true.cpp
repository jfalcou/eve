#include <eve/module/core.hpp>
#include <tts/tts.hpp>

using w_t = eve::wide<int, eve::fixed<4>>;

int main()
{
  w_t x = {1, 2, 3, 4};

  // logicals

  TTS_EQUAL(std::nullopt, eve::first_true(x == 0));
  TTS_EQUAL(0, eve::first_true(x == 1));
  TTS_EQUAL(1, eve::first_true(x == 2));

  TTS_EQUAL(std::nullopt, eve::first_true[eve::ignore_first(1)](x == 1));
  TTS_EQUAL(2, eve::first_true[eve::ignore_first(2)](x < 5));

  // top_bits

  eve::top_bits mmask{x >= 2};
  TTS_EQUAL(1, eve::first_true(mmask));

  // scalar

  TTS_EQUAL(std::nullopt, eve::first_true(false));
  TTS_EQUAL(0, eve::first_true(true));
}
