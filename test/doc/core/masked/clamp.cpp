#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_t = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_t xi = {2, -3, 0, 4};
  wide_t lo = {3, -2, -10, 0};
  wide_t hi = {4, -1, 0, 5};

  std::cout << "---- ximd" << '\n'
            << " <- xi                          = " << xi << '\n'
            << " <- lo                          = " << lo << '\n'
            << " <- hi                          = " << hi << '\n'
            << " -> clamp[xi > -2](xi, lo, hi)  = " << eve::clamp[xi > -2](xi, lo, hi) << '\n';
   return 0;
}
