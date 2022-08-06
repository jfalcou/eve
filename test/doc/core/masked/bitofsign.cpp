#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {-1.0f, 0.0f, 3.0f, -0.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf            = " << pf << '\n'
            << "-> bitofsign[pf!= 3.0f](pf) = " << eve::bitofsign[pf!= 3.0f](pf) << '\n';
  return 0;
}
