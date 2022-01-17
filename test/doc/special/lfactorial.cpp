//#include <eve/function/lfactorial.hpp>
#include <eve/module/combinatorial.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  using w32_t = eve::wide<std::uint32_t, eve::fixed<8>>;
  w32_t pi32 = {93, 25, 32, 180, 1, 2, 3, 4};

  std::cout << "---- simd" << std::setprecision(17) << '\n'
            << " <- pi32               = " << pi32 << '\n'
            << " -> lfactorial(pi32)   = " << eve::lfactorial(pi32) << '\n';

  std::uint32_t xi = 18;
  std::cout << "---- scalar" << '\n'
            << " xi                    = " << xi << '\n'
            << " -> lfactorial(xi)     = " << eve::lfactorial(xi) << '\n';


  return 0;
}
