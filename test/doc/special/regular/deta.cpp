#include <eve/module/complex.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft xf = { 3.0f, 2.0f, 1.0f, 0.5f};
  std::cout
    << "---- simd" << std::endl
    << "<- z           = " << xf << std::endl
    << "-> deta(1, xf)  = " << eve::deta(1u, xf) << std::endl
    << "-> deta(2, xf)  = " << eve::deta(2u, xf) << std::endl
    << "-> deta(3, xf)  = " << eve::deta(3u, xf) << std::endl;
  return 0;
}
