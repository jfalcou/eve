#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {-1.0f, 0.0f, 367.0f, -1005600.0f, eve::mindenormal(eve::as<float>()),
               eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf                   = " << pf << '\n'
            << "-> mantissa[pf > 0](pf) = " << eve::mantissa[pf > 0](pf) << '\n';
  return 0;
}
