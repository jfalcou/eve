#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_it = eve::wide<std::int32_t, eve::fixed<4>>;

int main()
{
  wide_ft pf = {-1.0f, 2.0f, -3.0f, -32768.0f};
  wide_it pi = {-1, 2, 3, 0};

  std::cout << "---- simd" << '\n'
            << "<- pf =                            " << pf << '\n'
            << "-> eve::lookup(pf, pi) =           " << eve::lookup(pf, pi) << '\n';

  float        xf = -327.0f;
  std::int32_t xi = 0;

  std::cout << "---- scalar" << '\n'
            << "<- xf =                            " << xf << '\n'
            << "-> eve::lookup(xf, xi) =           " << eve::lookup(xf, xi) << '\n';
  return 0;
}
