#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {-1.0f, -1.3f, -1.5f, -1.7f, 2.0f, 2.3f, 2.5f, 2.7f};

  std::cout << "---- simd" << '\n'
            << "<- pf                   = " << pf << '\n'
            << "-> floor[pf > -1.5](pf) = " << eve::floor[pf > -1.5](pf) << '\n';
  return 0;
}
