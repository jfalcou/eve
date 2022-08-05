#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf( [](auto i, auto) { return 1.2345678+i; } );

  std::cout << "---- simd" << '\n'
            << "<- pf                                 = " << pf << '\n'
            << "-> roundscale[ignore_first(2)](pf, 4) = " << eve::roundscale[eve::ignore_first(2)](pf, 4) << '\n';
  return 0;
}
