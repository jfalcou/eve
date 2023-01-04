#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::logical<eve::wide<float, eve::fixed<4>>>;

int main()
{
  wide_ft pf = {true,false,true,false};

  std::cout << "---- simd" << '\n'
            << "<- pf                              = " << pf << '\n'
            << "-> count_true(pf)                  = " << eve::count_true(pf) << '\n'
            << "-> count_true[ignore_first(2)](pf) = " << eve::count_true[eve::ignore_first(2)](pf) << '\n';

  return 0;
}
