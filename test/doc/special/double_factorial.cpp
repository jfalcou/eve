//#include <eve/function/double_factorial.hpp>
#include <eve/module/special.hpp>
#include <eve/wide.hpp>
#include <iomanip>
#include <iostream>

int main()
{
  using w32_t = eve::wide<std::uint32_t, eve::fixed<8>>;
  w32_t pi32 = {1, 2, 3, 4, 5, 6, 181, 182};

  std::cout << "---- simd" << std::setprecision(17) << '\n'
            << " <- pi32                   = " << pi32 << '\n'
            << " -> double_factorial(pi32) = " << eve::double_factorial(pi32) << '\n';

  std::uint32_t xi = 18;
  std::cout << "---- scalar" << '\n'
            << " xi                      = " << xi << '\n'
            << " -> double_factorial(xi) = " << eve::double_factorial(xi) << '\n';


  return 0;
}
