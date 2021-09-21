#include <eve/function/bit_cast.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using iT      = std::int32_t;
using wide_it = eve::wide<iT, eve::fixed<4>>;

int main()
{
  wide_ft pf = {1.0f, 2.0f, -1.0f, 0.5f};

  std::cout << "---- simd" << '\n'
            << "<- pf =                              " << pf << '\n'
            << "-> eve::bit_cast(pf,as<wide_it>()) = " << std::hex << eve::bit_cast(pf, eve::as<wide_it>()) << '\n';

  float xf = 2.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf =                               " << xf << '\n'
            << "-> eve::bit_cast(xf, as<iT>()) =      " << std::hex << eve::bit_cast(xf, eve::as<iT>()) << '\n';
  return 0;
}
