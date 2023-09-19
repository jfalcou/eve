#include <eve/module/core.hpp>
#include <tts/tts.hpp>

using w_t = eve::wide<std::uint32_t, eve::fixed<4>>;

int main()
{
  w_t x {0, 1, 2, 3};

  TTS_EXPECT( eve::all( w_t{3, 2, 1, 0} == eve::reverse(x)) );
  TTS_EXPECT( eve::all( w_t{3, 2, 1, 0} == eve::reverse(x, eve::lane<1>)) );
  TTS_EXPECT( eve::all( w_t{2, 3, 0, 1} == eve::reverse(x, eve::lane<2>)) );

  // lane<0> is not OK
  TTS_EXPECT( eve::all( w_t{0, 1, 2, 3} == eve::reverse(x, eve::lane<4>)) );
}
