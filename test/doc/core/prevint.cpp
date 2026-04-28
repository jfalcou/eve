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
  std::cout << "-> prevint[saturated](w) = " << eve::prevint[eve::saturated](w) << "\n";
  std::cout << "-> prevint[raw](w)       = " << eve::prevint[eve::raw](w) << "\n";

  eve::wide<std::int16_t, eve::fixed<4>> iw{0, 1, 32767, -32768};
  std::cout << "<- iw                     = " << iw << "\n";
  std::cout << "-> prevint(iw)            = " << eve::prevint(iw) << "\n";
  std::cout << "-> prevint[saturated](iw) = " << eve::prevint[eve::saturated](iw) << "\n";
  std::cout << "-> prevint[raw](iw)       = " << eve::prevint[eve::raw](iw) << "\n";
}
