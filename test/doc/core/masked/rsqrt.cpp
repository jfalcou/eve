#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {1.0f, 0.5f, -3.0f, eve::inf(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf               = " << pf << '\n'
            << "-> rsqrt[pf > 0](pf)        = " << eve::rsqrt[pf > 0](pf) << '\n';
  return 0;
}
