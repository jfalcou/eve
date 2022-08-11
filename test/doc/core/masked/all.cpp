#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {0.0f, 1.0f, 3.0f, 32768.0f};
  std::cout << "---- simd" << '\n'
            << "<- pf       = " << pf << '\n'
            << "-> all[ignore_first(1)](pf > 0.5f)  = " << eve::all[eve::ignore_first(1)](pf > 0.5) << '\n';

  return 0;
}
