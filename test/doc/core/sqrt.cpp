//#include <eve/function/sqrt.hpp>
#include <eve/module/core.hpp>
#include <eve/module/core/constant/inf.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {1.0f, 2.0f, -3.0f, eve::inf(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf              = " << pf << '\n'
            << "-> sqrt(pf)        = " << eve::sqrt(pf) << '\n'
            << "-> raw(sqrt)(pf)  = " << eve::raw(eve::sqrt)(pf) << '\n';


  float xf = 32.768f;

  std::cout << "---- scalar" << '\n'
            << "<- xf              = " << xf << '\n'
            << "-> sqrt(xf)        = " << eve::sqrt(xf) << '\n';

  return 0;
}
