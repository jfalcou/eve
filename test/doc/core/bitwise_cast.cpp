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
            << "-> eve::bitwise_cast(pf,as_<wide_it>()) = " << eve::bitwise_cast(pf, eve::as_<wide_it>()) << '\n';

  float xf = 2.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf =                            " << xf << '\n'
            << "-> eve::bitwise_cast(xf, as_<iT>()) =      " << eve::bitwise_cast(xf, eve::as_<iT>()) << '\n';
  return 0;
}
