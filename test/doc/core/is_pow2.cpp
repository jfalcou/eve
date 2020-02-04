#include <eve/function/is_pow2.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <iostream>

using wide_it = eve::wide<std::int32_t, eve::fixed<8>>;

int main()
{
  wide_it pf = {0, 1, -1, 3, 27, 4, 65536, 65537};

  std::cout << "---- simd" << '\n'
            << "<- pf =                  " << pf << '\n'
            << "-> eve::is_pow2(pf) = " << eve::is_pow2(pf) << '\n';

  std::int32_t xi = 1;
  std::int16_t yi = 3;

  std::cout << "---- scalar" << '\n'
            << "<- xi =                  " << xi << '\n'
            << "-> eve::is_pow2(xi) = " << eve::is_pow2(xi) << '\n'
            << "<- yi =                  " << yi << '\n'
            << "-> eve::is_pow2(yi) = " << eve::is_pow2(yi) << '\n';
  return 0;
}
