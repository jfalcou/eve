#include <eve/module/complex.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{

  std::cout
    << "---- simd" << '\n'
    << "-> i(as<wide_ft()) = " << eve::i(eve::as<wide_ft>())  << '\n';

  std::cout
    << "---- scalar"  << '\n'
    << "-> i(as(1.0)) = " << eve::i(eve::as(1.0)) << '\n';
  return 0;
}
