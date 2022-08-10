#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {0.0f,1.0f, -1.0f, -2.0f,
                eve::mindenormal(eve::as<float>()),  -eve::mindenormal(eve::as<float>()),
                eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf                          = " << pf << '\n'
            << "-> is_not_denormal[pf > 0](pf) = " << eve::is_not_denormal[pf > 0](pf) << '\n';
  return 0;
}
