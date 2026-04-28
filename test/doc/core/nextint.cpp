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
    eve::valmax(eve::as<eve::float16_t>{}),
  };

  std::cout << "<- w                     = " << w << "\n";
  std::cout << "-> nextint(w)            = " << eve::nextint(w) << "\n";
  std::cout << "-> nextint[saturated](w) = " << eve::nextint[eve::saturated](w) << "\n";
  std::cout << "-> nextint[raw](w)       = " << eve::nextint[eve::raw](w) << "\n";

  eve::wide<std::int16_t, eve::fixed<4>> iw{0, 1, 32767, -32768};
  std::cout << "<- iw                     = " << iw << "\n";
  std::cout << "-> nextint(iw)            = " << eve::nextint(iw) << "\n";
  std::cout << "-> nextint[saturated](iw) = " << eve::nextint[eve::saturated](iw) << "\n";
  std::cout << "-> nextint[raw](iw)       = " << eve::nextint[eve::raw](iw) << "\n";
}
