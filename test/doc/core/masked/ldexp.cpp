#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using iT      = std::int32_t;
using wide_it = eve::wide<iT, eve::fixed<4>>;
using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_it qi = {12, 2, -2, 3 };
  wide_ft pf = {1.0f, -1.0f, 0.0f, -2.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf            = " << pf << '\n'
            << "<- qi            = " << qi << '\n'
            << "-> ldexp[pf < 0.0](pf, qi) = " << eve::ldexp[pf < 0.0](pf, qi) << '\n';
  return 0;
}
