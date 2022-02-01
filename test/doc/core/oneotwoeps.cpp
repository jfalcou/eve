#include <eve/module/math/constant/oneotwoeps.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;
using wide_it = eve::wide<std::int16_t>;

int main()
{
  wide_ft wxf;
  wide_it wxi;

  std::cout << "---- simd"  << std::endl
            << "-> oneotwoeps(as<wide_ft>())  = " << eve::oneotwoeps(eve::as<wide_ft>()) << std::endl
            << "-> oneotwoeps(as<wide_it>())  = " << eve::oneotwoeps(eve::as<wide_it>()) << std::endl
            << "-> oneotwoeps(as(wxf))        = " << eve::oneotwoeps(eve::as(wxf))       << std::endl
            << "-> oneotwoeps(as(wxi))        = " << eve::oneotwoeps(eve::as(wxi))       << std::endl;

  double       xf;
  std::int16_t xi;

  std::cout << "---- scalar" << std::endl
            << "-> oneotwoeps(as<float>())         = " << eve::oneotwoeps(eve::as(float())) << std::endl
            << "-> oneotwoeps(as<std::int16_t>())  = " << eve::oneotwoeps(eve::as(std::int16_t())) << std::endl
            << "-> oneotwoeps(as<xf))              = " << eve::oneotwoeps(eve::as(xf)) << std::endl
            << "-> oneotwoeps(as<xi))              = " << eve::oneotwoeps(eve::as(xi)) << std::endl;

  return 0;
}
