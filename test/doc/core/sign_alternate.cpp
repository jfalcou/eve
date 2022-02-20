//#include <eve/function/sign_alternate.hpp>
#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_it = eve::wide <std::int16_t, eve::fixed<8>>;

int main()
{
  wide_it pi = { 0, 1, 2, 3, -1, -32766, 32767, -32768};

  std::cout
    << "---- simd" << '\n'
    << "<- pi                   = " << pi << '\n'
    << "-> sign_alternate(pi)             = " << eve::sign_alternate(pi) << '\n';


  float xf = 2.0f;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                   = " << xf << '\n'
    << "-> sign_alternate(xf)             = " << eve::sign_alternate(xf) << '\n';

  return 0;
}
