#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf( [](auto i, auto) { return 1.2345678+i; } );

  std::cout << "---- simd" << '\n'
            << " <- pf                            = " << pf << '\n'
            << " -> fracscale(pf, 4)              = " << eve::fracscale(pf, 4) << '\n';
            << " -> upward(fracscale)(pf, 4)      = " << eve::downward(eve::fracscale)(pf, 4) << '\n'
            << " -> downward(fracscale)(pf, 4)    = " << eve::upward(eve::fracscale)(pf, 4) << '\n'
            << " -> to_nearest(fracscale)(pf, 4)  = " << eve::to_nearest(eve::fracscale)(pf, 4) << '\n';
   return 0;
}
