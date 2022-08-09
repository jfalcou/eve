#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {-1.0f, 2.0f, -3.0f, eve::inf(eve::as<float>())};
  wide_ft qf = {-4, 3, -2, , eve::nan(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf                     = " << pf << '\n'
            << "<- qf                     = " << qf << '\n'
            << "-> pedantic(manhattan)(pf, qf) = " <<  eve::pedantic(eve::manhattan)(pf, qf) << '\n';
  return 0;
}
