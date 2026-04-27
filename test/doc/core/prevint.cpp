#include <eve/eve.hpp>
#include <iostream>

int main()
{
  eve::wide<eve::float16_t, eve::fixed<8>> w{
    static_cast<eve::float16_t>(-0.0f),
    static_cast<eve::float16_t>(0.0f),
    static_cast<eve::float16_t>(32768.0f),
    static_cast<eve::float16_t>(-32768.0f),
    eve::nan(eve::as<eve::float16_t>{}),
    eve::inf(eve::as<eve::float16_t>{}),
    eve::minf(eve::as<eve::float16_t>{}),
    eve::valmin(eve::as<eve::float16_t>{}),
  };

  std::cout << "<- w                     = " << w << "\n";
  std::cout << "-> prevint(w)            = " << eve::prevint(w) << "\n";
}
