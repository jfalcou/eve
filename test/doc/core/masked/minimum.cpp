#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_it = eve::wide<std::int16_t, eve::fixed<4>>;

int main()
{
  wide_it pi = {-1, 2, -3, -18};

  std::cout << "---- simd" << '\n'
            << "<- pi                    = " << pi << '\n'
            << "-> minimum[pi > -2](pi)  = " << eve::minimum[pi > -2](pi) << '\n';
  return 0;
}
