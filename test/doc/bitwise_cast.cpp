#include <eve/function/bitwise.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using iT      = std::int32_t;
using wide_it = eve::wide<iT, eve::fixed<4>>;

int main()
{
  wide_ft pf = {1.0f, 2.0f, -1.0f, 0.5f};

  std::cout << "---- simd" << '\n'
            << "<- pf =                            " << pf << '\n'
            << "-> eve::bitwise_cast<wide_it>(pf) = " << eve::bitwise_cast<wide_it>(pf) << '\n';

  float xf = 2.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf =                            " << xf << '\n'
            << "-> eve::bitwise_cast<iT>(xf) =      " << eve::bitwise_cast<iT>(xf) << '\n';
  return 0;
}
