#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using int_16 = eve::as<std::int16_t>;

int main()
{
  wide_ft pf = {-1.0f, 2.3f, 45000.7f, -64768.6f};

  std::cout << "---- simd" << '\n'
            << "<- pf                                 = " << pf << '\n'
            << "-> convert(pf, int_16()_)             = " << eve::convert(pf, int_16()) << '\n'
            << "-> saturated(convert)(pf, int_16())   = " << eve::saturated(eve::convert)(pf, int_16()) << '\n';
  return 0;
}
