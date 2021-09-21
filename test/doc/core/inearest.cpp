#include <eve/function/inearest.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {-1.0f, -1.3f, -1.5f, -1.7f, 2.0f, 2.3f, 2.5f, 2.7f};

  std::cout << "---- simd" << '\n'
            << "<- pf           = " << pf << '\n'
            << "-> inearest(pf) = " << eve::inearest(pf) << '\n';

  float xf = -32.768f;

  std::cout << "---- scalar" << '\n'
            << "<- xf           = " << xf << '\n'
            << "-> inearest(xf) = " << eve::inearest(xf) << '\n';
  return 0;
}
