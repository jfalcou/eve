#include <eve/function/count_true.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::logical<eve::wide<float, eve::fixed<4>>>;
using wide_it = eve::logical<eve::wide<std::int16_t, eve::fixed<4>>>;

int main()
{
  wide_ft pf = {true,false,true,false};
  wide_it qf = {false,true,true,true};

  std::cout << "---- simd" << '\n'
            << "<- pf         = " << pf << '\n'
            << "-> count_true(pf) = " << eve::count_true(pf) << '\n'
            << "<- qf         = " << qf << '\n'
            << "-> count_true(qf) = " << eve::count_true(qf) << '\n';

  eve::logical<float>  xf = true;
  eve::logical<int>    yf = false;

  std::cout << "---- scalar" << '\n'
            << "<- xf         = " << xf << '\n'
            << "-> count_true(xf) = " << eve::count_true(xf) << '\n'
            << "<- yf         = " << yf << '\n'
            << "-> count_true(yf) = " << eve::count_true(yf) << '\n';

  return 0;
}
