#include <eve/function/tofloat.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/wide.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <iostream>

using wide_it = eve::wide<std::int32_t, eve::fixed<8>>;

int main()
{
  using eve::pedantic_;

  wide_it pi = {0, 1, -1, -2, -10000, -65535, eve::Valmax<std::int32_t>(), eve::Valmin<std::int32_t>()}; 

  std::cout << "---- simd" << '\n'
            << "<- pi =                      " << pi << '\n'
            << "-> eve::tofloat(pi) =            " << eve::tofloat(pi) << '\n'; 

  std::int32_t xi = 1; 
  std::int32_t yi = eve::Valmax<std::int32_t>();

  std::cout << "---- scalar" << '\n'
            << "<- xi =                      " << xi << '\n'
            << "-> eve::tofloat(xf) =            " << eve::tofloat(xi) << '\n'
            << "<- yi =                      " << yi << '\n'
            << "-> eve::tofloat(yi) =            " << eve::tofloat(yi) << '\n'; 
  return 0;
}
