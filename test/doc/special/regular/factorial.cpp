#include <eve/module/special.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  using w32_t = eve::wide<std::uint32_t, eve::fixed<8>>;
  w32_t pi32 = {93, 25, 32, 180, 1, 2, 3, 4};

  std::cout << "---- simd" << std::setprecision(17) << '\n'
            << " <- pi32              = " << pi32 << '\n'
            << " -> factorial(pi32)   = " << eve::factorial(pi32) << '\n';

  std::uint32_t xi = 18;
  std::cout << "---- scalar" << '\n'
            << " xi                   = " << xi << '\n'
            << " -> factorial(xi)     = " << eve::factorial(xi) << '\n';


  return 0;
}
