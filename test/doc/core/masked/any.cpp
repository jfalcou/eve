#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {1.0f, 0.0f, 0.0f, 0.0f};
  std::cout << "---- simd" << '\n'
            << "<- pf       = " << pf << '\n'
            << "-> any[ignore_first(1)](pf > 0.5f)  = " << eve::any[eve::ignore_first(1)](pf > 0.5f) << '\n';

  return 0;
}
