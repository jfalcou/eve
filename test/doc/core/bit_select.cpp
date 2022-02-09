#include <eve/function/bit_select.hpp>
#include <eve/module/core/constant/eps.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_t = eve::wide<std::uint16_t, eve::fixed<4>>;

int main()
{

  wide_t pi = {2, -3, 0,  1 << 10};
  wide_t qi = {3, -2, 4,  2 };
  wide_t mi = {0, -1, 1, ~0u << 8};

  std::cout << "---- simd" << '\n'
            << " <- mi                                = " << mi << '\n'
            << " <- pi                                = " << pi << '\n'
            << " <- qi                                = " << qi << '\n'
            << " -> bit_select(mi, pi, qi)            = " << eve::bit_select(mi, pi, qi) << '\n';

  std::cout << "---- scalar" << std::setprecision(10) << '\n'
            << " -> bit_select(32767, 1, 32768 )      = " << eve::bit_select(32767, 1, 32768) << '\n';
  return 0;
}
