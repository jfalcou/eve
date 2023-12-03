#include <eve/module/core.hpp>
#include <tts/tts.hpp>

using w_t = eve::wide<std::uint32_t, eve::fixed<4>>;


int main()
{
  w_t x {0, 1, 2, 3};

  TTS_EXPECT( eve::all( w_t{1, 1, 1, 1} == eve::broadcast_lane(x, eve::index<1>)) );
  TTS_EXPECT( eve::all( w_t{2, 3, 2, 3} == eve::broadcast_lane(x, eve::lane<2>, eve::index<1>)) );
  TTS_EXPECT( eve::all( w_t{0, 1, 2, 3} == eve::broadcast_lane(x, eve::lane<4>, eve::index<0>)) );
}
