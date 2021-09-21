#include <eve/function/countr_zero.hpp>
#include <eve/constant/inf.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_it = eve::wide<std::uint32_t, eve::fixed<4>>;

int main()
{
  wide_it pi = {14, 1, 3, 0};

  std::cout << "---- simd" << '\n'
            << "<- pi              = " << pi << '\n'
            << "-> countr_zero(pi) = " << eve::countr_zero(pi) << '\n';

  std::uint32_t xf = 48;

  std::cout << "---- scalar" << '\n'
            << "<- xf              = " << xf << '\n'
            << "-> countr_zero(xf) = " << eve::countr_zero(xf) << '\n';
  return 0;
}
