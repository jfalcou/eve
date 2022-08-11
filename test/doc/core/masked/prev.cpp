#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {-10.0f, 2.0f, eve::eps(eve::as<float>()), 0.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf                  =" << std::setprecision(12) << pf << '\n'
            << "-> prev[pf > 0](pf)    =" << eve::prev[pf > 0](pf) << '\n';
  return 0;
}
