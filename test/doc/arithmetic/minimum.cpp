//#include <eve/function/minimum.hpp>
#include <eve/module/arithmetic.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_it = eve::wide<std::int16_t, eve::fixed<4>>;

int main()
{
  wide_ft pf = {-1.0f, 2.0f, -3.0f, -32768.0f};
  wide_it pi = {-1, 2, -32768, 3};

  std::cout << "---- simd" << '\n'
            << "<- pf           = " << pf << '\n'
            << "-> minimum(pf)  = " << eve::minimum(pf) << '\n'
            << "<- pi           = " << pi << '\n'
            << "-> minimum(pi)  = " << eve::minimum(pi) << '\n';

  return 0;
}
