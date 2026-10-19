#include <eve/module/core.hpp>
#include <tts/tts.hpp>

using w_t = eve::wide<std::uint32_t, 4>;

int main()
{
  w_t x {0, 1, 2, 3};

  TTS_EXPECT( eve::all( w_t{1, 0, 3, 2} == eve::swap_adjacent(x)) );
  TTS_EXPECT( eve::all( w_t{1, 0, 3, 2} == eve::swap_adjacent(x, eve::lanes<1>)) );
  TTS_EXPECT( eve::all( w_t{2, 3, 0, 1} == eve::swap_adjacent(x, eve::lanes<2>)) );

  // lanes<0> and lanes<4> are not OK.
}
