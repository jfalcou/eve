#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {1.0f, 2.0f, -3.0f, eve::inf(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf              = " << pf << '\n'
            << "-> sqrt[pf > 0](pf)= " << eve::sqrt(pf) << '\n';
  return 0;
}
