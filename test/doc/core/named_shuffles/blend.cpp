#include <eve/module/core.hpp>

#include <tts/tts.hpp>

using w_t = eve::wide<std::uint32_t, eve::fixed<4>>;

int
main()
{
  w_t x {0, 1, 2, 3};
  w_t y {4, 5, 6, 7};

  // basic example
  TTS_EXPECT(eve::all(w_t{4, 1, 2, 7} == eve::blend(x, y, eve::pattern<1, 0, 0, 1>)));

  // basic example, formula
  TTS_EXPECT(
      eve::all(w_t{0, 5, 2, 7} == eve::blend(x, y, [](int i, int /*size*/) { return i % 2; })));

  // mixing groups
  TTS_EXPECT(eve::all(w_t{4, 5, 2, 3} == eve::blend(x, y, eve::lane<2>, eve::pattern<1, 0>)));
}
