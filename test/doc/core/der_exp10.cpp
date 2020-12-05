#include <eve/function/derivative/exp10.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{

  wide_ft pf = {0.0f, -0.0f, -1.0f, 1.0f, 2.0f,
               eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf      = " << pf << '\n'
            << "-> eve::derivative(eve::exp10)(pf)     = " << eve::derivative(eve::exp10)(pf) << '\n'
            << "-> eve::derivative(eve::exp10)(pf, 2u) = " << eve::derivative(eve::exp10)(pf, 2u) << '\n' ;

  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf      = " << xf << '\n'
            << "-> eve::derivative(eve::exp10)(xf) = " << eve::derivative(eve::exp10)(xf) << '\n';
  return 0;
}
